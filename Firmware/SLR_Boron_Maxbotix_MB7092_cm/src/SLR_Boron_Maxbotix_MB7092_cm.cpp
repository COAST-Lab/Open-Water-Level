/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/pjb/Dropbox/Open-Water-Level/Firmware/SLR_Boron_Maxbotix_MB7092_cm/src/SLR_Boron_Maxbotix_MB7092_cm.ino"
#include "SdFat.h"
//------------------SD SPI Configuration Details--------------------------------
void setup(void);
void loop(void);
#line 3 "/Users/pjb/Dropbox/Open-Water-Level/Firmware/SLR_Boron_Maxbotix_MB7092_cm/src/SLR_Boron_Maxbotix_MB7092_cm.ino"
const int SD_CHIP_SELECT = SS;
SdFat sd;

//------------------LED Setup
int led = D7; // blink to let us know you're alive
bool led_state = HIGH; // starting state

//------------------Maxbotix sensor
//int V_ultraS = A1;
//float dist_in = 0;

int j;
float dist_in_sum;
float dist_in_avg;
float range_cm;

long real_time;
int millis_now; 

float filterArray[200]; // array to store data samples from sensor
float distance_unconverted; // store the distance from sensor

//------------------State variables
// not yet used but placeholders in case of additional states
enum State { PUBLISH_STATE, SLEEP_STATE };
State state = PUBLISH_STATE;
unsigned long stateTime = 0;

//------------------Turn off cellular for prelim testing; turn on for deployment
//SYSTEM_MODE(MANUAL); // uncomment for prelim testing
SYSTEM_MODE(SEMI_AUTOMATIC); // uncomment for deployment
SYSTEM_THREAD(ENABLED);

// Global objects
FuelGauge batteryMonitor;
//PMIC pmic;
const char *eventName = "waterlevel";

SystemSleepConfiguration config;

// Various timing constants
const unsigned long MAX_TIME_TO_PUBLISH_MS = 60000; // Only stay awake for 60 seconds trying to connect to the cloud and publish
const unsigned long TIME_AFTER_PUBLISH_MS = 4000; // After publish, wait 4 seconds for data to go out

void setup(void)
{
  Particle.connect();
  //Cellular.off(); // turn off cellular for prelim testing (uncomment)

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
    //dist_in_sum = 0; 
    
    // Take multiple measurements and store in array
    for (int sample = 0; sample < 200; sample++) {
      filterArray[sample] = (analogRead(A1));
      delay(50); // to avoid untrasonic interfering
    }
    // Sort
    for (int i = 0; i < 199; i++) {
      for (int j = i + 1; j < 200; j++) {
        if (filterArray[i] > filterArray[j]) {
          float swap = filterArray[i];
          filterArray[i] = filterArray[j];
          filterArray[j] = swap;
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

  // Convert analog signal to centimeters
  range_cm = (float)distance_unconverted * 0.25; // conversion factor for MB7092 XL-MaxSonar-WRMA1; TODO: check new sensor's datasheet

  // "Real" time and current millis for logging
  real_time = Time.now();
  millis_now = millis();


      // Print out distance
       Serial.print("Time: ");
       Serial.print(real_time);
       Serial.print(", Distance(cm): ");
       Serial.print(range_cm);
      
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
       myFile.print(real_time);
       myFile.print(",");
       myFile.print(millis_now);
       myFile.print(",");
       myFile.print(range_cm);
       myFile.close();

      delay(100);
    //}
    
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
                      real_time, // if it takes a while to connect, this time could be offset from sensor recording
                      range_cm,
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
          .duration(54min);
    System.sleep(config);

    // It'll only make it here if the sleep call doesn't work for some reason
    Serial.print("Feeling restless");
    stateTime = millis();
    state = PUBLISH_STATE;
  }
  break;

  }

}