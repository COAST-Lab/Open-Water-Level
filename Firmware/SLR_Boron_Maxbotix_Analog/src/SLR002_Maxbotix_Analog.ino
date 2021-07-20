#include "SdFat.h"
//------------------SD SPI Configuration Details--------------------------------
const int SD_CHIP_SELECT = SS;
SdFat sd;

//------------------LED Setup
int led = D7; // blink to let us know you're alive
bool led_state = HIGH; // starting state

//------------------Maxbotix sensor
int V_ultraS = A0;
float dist_in = 0;

int j;
float dist_in_sum;
float dist_in_avg;

//------------------State variables
// not yet used but placeholders in case of additional states
enum State { PUBLISH_STATE, SLEEP_STATE };
State state = PUBLISH_STATE;
unsigned long stateTime = 0;

//------------------Turn off cellular for prelim testing; turn on for deployment
// SYSTEM_MODE(MANUAL); // uncomment for prelim testing
SYSTEM_MODE(SEMI_AUTOMATIC); // uncomment for deployment
SYSTEM_THREAD(ENABLED);

// Global objects
FuelGauge batteryMonitor;
PMIC pmic;
const char *eventName = "SeaLevel_BTown";

SystemSleepConfiguration config;

// Various timing constants
const unsigned long MAX_TIME_TO_PUBLISH_MS = 60000; // Only stay awake for 60 seconds trying to connect to the cloud and publish
const unsigned long TIME_AFTER_PUBLISH_MS = 4000; // After publish, wait 4 seconds for data to go out

void setup(void)
{
  Particle.connect();
  // Cellular.off(); turn off cellular for prelim testing (uncomment)

  delay(5000); // to see response from begin command

  Serial.begin(9600);
  Serial.println("Maxbotix Test");

}

void loop(void)
{
  // Enter state machine
  switch(state) {

  //////////////////////////////////////////////////////////////////////////////
  /*** PUBLISH_STATE ***/
  /*** Get here from boot. Ensure that we're connected to Particle Cloud.
  If so, poll Maxbotix and send to cloud then
  go to SLEEP_STATE
  If not connected, still get/print value then go to SLEEP_STATE.
  ***/
  case PUBLISH_STATE: {
    // Reinitialize sum variable prior to every loop execution
    dist_in_sum = 0; 

    for(j=0; j<100; j++){
      // Read analog value and convert
      int range_cts = analogRead(A1);    //read signal on pin A1 and assign to variable: range_cts
      float range_V = (float)range_cts*(3.3/1024); // counts*(V/counts) = V (NB: SAMD21's ADC is configured to 10-bit resolution)
      float range_in = range_V*(512/3.3); // V*(in/V) = in (NB: in/V conversion factor comes from datasheet)
      
      // Add new distance to cumulative value
      dist_in_sum += range_in;

      // Print out distance
      // Serial.print("Time: ");
      // Serial.print(Time.now());
      // Serial.print(", Distance(in): ");
      
      Serial.println(range_in);

      // Start SD stuff
      File myFile;

      // Initialize the library
      if (!sd.begin(SD_CHIP_SELECT, SPI_FULL_SPEED)) {
        Serial.println("failed to open card");
        return;
      }

      // open the file for write at end like the "Native SD library"
      if (!myFile.open("distance.txt", O_RDWR | O_CREAT | O_AT_END)) {
        Serial.println("opening test.txt for write failed");
        return;
      }

      // Save to SD card
      myFile.print(Time.now());
      myFile.print(",");
      myFile.print(millis());
      myFile.print(",");
      myFile.println(range_in);
      myFile.close();

      delay(100);
    }
    
    // Calculate then print average
    dist_in_avg = dist_in_sum/j;

    Serial.print(j);
    Serial.print(",");
    Serial.print(dist_in_sum);
    Serial.print(",");
    Serial.println(dist_in_avg);

    // Prep for cellular transmission
    bool isMaxTime = false;
    stateTime = millis();

    while(!isMaxTime)
    {
      //connect particle to the cloud
      if (Particle.connected() == false)
      {
        Particle.connect();
        Serial.print("Trying to connect");
      }

      // If connected, publish data buffer
      if (Particle.connected())
      {
        // Get power and time once connected. TODO: ensure contemporaneous time and sensor sampling

        // Get battery charge if Boron provides it
        float cellVoltage = batteryMonitor.getVCell();
        float stateOfCharge = batteryMonitor.getSoC();

        char data[120];
        snprintf(data, sizeof(data), "%li,%.5f,%.02f,%.02f",//,%.5f,%.5f,%.5f,%.5f,%.5f,%.02f,%.02f",
                      Time.now(), // if it takes a while to connect, this time could be offset from sensor recording
                      dist_in_avg,
                      cellVoltage, stateOfCharge
                    );
        Serial.println("publishing data");
        Particle.publish(eventName, data, 60, PRIVATE);

        // Wait for the publish data
        delay(TIME_AFTER_PUBLISH_MS);
        isMaxTime = true;
        state = SLEEP_STATE;
      }
      // If not connected after certain amount of time, go to sleep to save battery
      else
      {
        // Took too long to publish, just go to sleep
        if (millis() - stateTime >= MAX_TIME_TO_PUBLISH_MS)
        {
          isMaxTime = true;
          state = SLEEP_STATE;
          Serial.println("max time for publishing reached without success; go to sleep");
        }
        Serial.println("Not max time, try again to publish");
        delay(100);
      }
    }
  }
  break;

  //////////////////////////////////////////////////////////////////////////////
  /*** SLEEP_STATE ***/
  /*** Get here from PUBLISH_STATE and go to GPS_WAIT_STATE (if code makes it that far)
  or SLEEP_MODE_DEEP after calculating a wakeup time based off of the current time from the cloud.
  ***/
  case SLEEP_STATE: {
    Serial.println("going to sleep");
    delay(500);
   	
    // Set up Gen 3 sleep
    config.mode(SystemSleepMode::ULTRA_LOW_POWER)
          .gpio(D2, FALLING)
          .duration(59min);
    System.sleep(config);

    // It'll only make it here if the sleep call doesn't work for some reason
    Serial.print("Feeling restless");
    stateTime = millis();
    state = PUBLISH_STATE;
  }
  break;

  }

}
