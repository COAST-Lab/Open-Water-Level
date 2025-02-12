/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

/* 
 * Project myProject
 * Author: Your Name
 * Date: 
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */

// Include Particle Device OS APIs
#include "Particle.h"
#include "SdFat.h"

 //------------------SD SPI Configuration Details--------------------------------
const int SD_CHIP_SELECT = D5;
SdFat sd;

//------------------LED Setup
int led = D7; // blink to let us know you're alive
bool led_state = HIGH; // starting state

//------------------Maxbotix sensor
int j;
float dist_in_sum;
float dist_in_avg;
float range_cm;

long real_time;
int millis_now;

float filterArray[200]; // array to store data samples from sensor
float distance_unconverted; // store the distance from sensor


// function prototype` <br />
int secondsUntilNextEvent();

//------------------State variables
// not yet used but placeholders in case of additional states
enum State {
  DATALOG_STATE,
  PUBLISH_STATE,
  SLEEP_STATE
};
State state = DATALOG_STATE;

// Define whether (1) or not (0) to publish
#define PUBLISHING 1

unsigned long stateTime = 0;
char data[120];

//------------------Turn off cellular for prelim testing; turn on for deployment
//SYSTEM_MODE(MANUAL); // uncomment for prelim testing
SYSTEM_MODE(SEMI_AUTOMATIC); // uncomment for deployment
SYSTEM_THREAD(ENABLED);

// Global objects
FuelGauge batteryMonitor;
const char * eventName = "waterLevel";
SerialLogHandler logHandler;

SystemSleepConfiguration config;

// Various timing constants
const unsigned long MAX_TIME_TO_PUBLISH_MS = 20000; // Only stay awake for this time trying to connect to the cloud and publish
const unsigned long TIME_AFTER_PUBLISH_MS = 4000; // After publish, wait 4 seconds for data to go out

// ***** IMPORTANT!!!
 //If SECONDS_BETWEEN_MEASUREMENTS < 600, must use 
 //.network(NETWORK_INTERFACE_CELLULAR, SystemSleepNetworkFlag::INACTIVE_STANDBY);
// in sleep configuration to avoid reconnection penalty
const unsigned long SECONDS_BETWEEN_MEASUREMENTS = 3600; // What should sampling period be?
// ***** IMPORTANT!!! See note above this const.


void setup(void) {
  if (PUBLISHING==0) {
    Particle.connect();
  }
  else{
    Cellular.off(); // turn off cellular for prelim testing (uncomment)
  }

  // delay(5000); // to see response from begin command

  Serial.begin(9600);
  Log.info("Maxbotix Test");

}

void loop(void) {
  // Enter state machine
  switch (state) {

    //////////////////////////////////////////////////////////////////////////////
    /*** DATALOG_STATE ***/
    /*** Get here from boot. 
    If so, poll Maxbotix and save to SD card.
    Then, if PUBLISHING==1, go to PUBLISH_STATE. Else,
    go to SLEEP_STATE.
    ***/
  case DATALOG_STATE: {
    // Take multiple measurements and store in array
    for (int sample = 0; sample < 200; sample++) {
      filterArray[sample] = (analogRead(A1));
      delay(50); // to avoid untrasonic interfering
    }
    // Sort; TODO: this looks inefficient. Investigate options to improve (or reject) sorting
    for (int i = 0; i < 199; i++) {
      for (int j = i + 1; j < 200; j++) {
        if (filterArray[i] > filterArray[j]) { //takes highest value
          float swap = filterArray[i];
          filterArray[i] = filterArray[j];
          filterArray[j] = swap; //puts highest number on top
        }
      }
    }
    

    // Filter noise by excluding 10 smallest and 10 largest samples 
    double sum = 0;
    for (int sample = 10; sample < 190; sample++) {
      sum += filterArray[sample];
    }

    // Get average of the middle samples (from 10 to 190)
    distance_unconverted = sum / 180;

    // Get all metrics which are to be reused:
    range_cm = (float) distance_unconverted * 0.25; // conversion factor for MB7092 XL-MaxSonar-WRMA1; TODO: check new sensor's datasheet
    real_time = Time.now(); // "Real" time and current millis for logging
    millis_now = millis();

    // Get battery charge if Boron provides it
    float cellVoltage = batteryMonitor.getVCell();
    float stateOfCharge = batteryMonitor.getSoC();

    snprintf(data, sizeof(data), "%li,%.5f,%.02f,%.02f", //,%.5f,%.5f,%.5f,%.5f,%.5f,%.02f,%.02f",
      real_time, // if it takes a while to connect, this time could be offset from sensor recording
      range_cm,
      cellVoltage,
      stateOfCharge
    );

    // Print out data buffer
    Log.info(data);

    // Start SD stuff
    File myFile;

    // Initialize the library
    if (!sd.begin(SD_CHIP_SELECT, SPI_FULL_SPEED)) {
      Log.info("failed to open card");
    }

    // open the file for write at end like the "Native SD library"
    if (!myFile.open("distance.csv", O_RDWR | O_CREAT | O_AT_END)) {
      Log.info("opening distance.csv for write failed");
    }
    else{ // if file does open, save to SD; otherwise, proceed to publish
      // Save to SD card
      myFile.print(data);
      myFile.print("\n"); // put next data on new line
      myFile.close();
    }

    if (PUBLISHING==1) {
      state = PUBLISH_STATE;
    }
    else{
      state = SLEEP_STATE;
    }

  }
  break;

    //////////////////////////////////////////////////////////////////////////////
    /*** PUBLISH_STATE ***/
    /*** Get here from DATALOG_STATE if PUBLISHING==1. Ensure that we're connected to Particle Cloud.
    If so, send data to cloud then
    go to SLEEP_STATE
    If not connected, then go to SLEEP_STATE.
    ***/
  case PUBLISH_STATE: {

    // Prep for cellular transmission
    bool isMaxTime = false;
    stateTime = millis();

    while (!isMaxTime) {
      //connect particle to the cloud
      if (Particle.connected() == false) {
        Particle.connect();
        Log.info("Trying to connect");
      }

      // If connected, publish data buffer
      if (Particle.connected()) {

        Log.info("publishing data");

        // bool (or Future) below requires acknowledgment to proceed
        bool success = Particle.publish(eventName, data, 60, PRIVATE, WITH_ACK);
        Log.info("publish result %d", success); 

        isMaxTime = true;
        state = SLEEP_STATE;
      }
      // If not connected after certain amount of time, go to sleep to save battery
      else {
        // Took too long to publish, just go to sleep
        if (millis() - stateTime >= MAX_TIME_TO_PUBLISH_MS) {
          isMaxTime = true;
          state = SLEEP_STATE;
          Log.info("max time for publishing reached without success; go to sleep");
        }
        Log.info("Not max time, try again to connect and publish");
        delay(500);
      }
    }
  }
  break;

  //////////////////////////////////////////////////////////////////////////////
  /*** SLEEP_STATE ***/
  /*** Get here from PUBLISH_STATE after attempted publish or DATALOG_STATE if PUBLISHING==0
  ***/
  case SLEEP_STATE: {
    Log.info("going to sleep");
    delay(500);

    // Sleep time determination and configuration
    int wakeInSeconds = secondsUntilNextEvent(); // Calculate how long to sleep 

    config.mode(SystemSleepMode::ULTRA_LOW_POWER)
      .gpio(D2, FALLING)
      .duration(wakeInSeconds* 1000L); // Set seconds until wake
      // .network(NETWORK_INTERFACE_CELLULAR, SystemSleepNetworkFlag::INACTIVE_STANDBY); // keeps the cellular modem powered, but does not wake the MCU for received data

    // Ready to sleep
    SystemSleepResult result = System.sleep(config); // Device sleeps here

    // It'll only make it here if the sleep call doesn't work for some reason (UPDATE: only true for hibernate. ULP will wake here.)
    Log.info("Feeling restless");
    stateTime = millis();
    state = DATALOG_STATE;
  }
  break;
  }
}

int secondsUntilNextEvent() {

  int current_seconds = Time.now();
  int seconds_to_sleep = SECONDS_BETWEEN_MEASUREMENTS - (current_seconds % SECONDS_BETWEEN_MEASUREMENTS);

  Log.info("Sleeping for %i", seconds_to_sleep);

  return seconds_to_sleep;
}
