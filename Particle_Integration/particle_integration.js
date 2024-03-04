function test() {
  var e = {};
  e.parameter = {};
  e.parameter.event = 'sheetTest1';
  e.parameter.data = '[1,1234]';
  e.parameter.coreid = '1f0030001647ffffffffffff';
  e.parameter.published_at = new Date().toISOString();
  doPost(e);
}

function doPost(e) {
  // e.parameter.event
  // e.parameter.data
  // e.parameter.coreid
  // e.parameter.published_at "2016-04-16T13:37:08.728Z"

  var particleApiToken = '{YOUR_PARTICLE_TOKEN_HERE}';

  var publishedAt = new Date(e.parameter.published_at);
  var cacheKey = 'deviceName';

  var dataArray = [];
  try {
    dataArray = JSON.parse(e.parameter.data);
  }
  catch(e) {
  }
  
  var cache = CacheService.getScriptCache();
  var deviceNameCache = cache.get(cacheKey);
  
  if (!deviceNameCache) {
    // The device name was not cached, so use the Particle Cloud API
    var result = UrlFetchApp.fetch('https://api.particle.io/v1/devices?access_token=' + particleApiToken);   
    var resultJson = JSON.parse(result.getContentText());
    
    deviceNameCache = {};

    for(var ii = 0; ii < resultJson.length; ii++) {
      deviceNameCache[resultJson[ii].id] = resultJson[ii].name;
    }
    cache.put(cacheKey, JSON.stringify(deviceNameCache));
  }
  else {
    deviceNameCache = JSON.parse(deviceNameCache);
  }
  
  // Use the device name if known, otherwise use Device ID
  var deviceName = deviceNameCache[e.parameter.coreid];
  if (!deviceName) {
    Logger.log('Unknown device ID');
    return;
  }

  var sheet = SpreadsheetApp.getActiveSheet();

  var row = [e.parameter.coreid, publishedAt, deviceName, e.parameter.event, e.parameter.data];

  row = row.concat(dataArray);

  sheet.appendRow(row);

  var result = {};
  result.ok = true;

  return ContentService.createTextOutput(JSON.stringify(result))
    .setMimeType(ContentService.MimeType.JSON);
}