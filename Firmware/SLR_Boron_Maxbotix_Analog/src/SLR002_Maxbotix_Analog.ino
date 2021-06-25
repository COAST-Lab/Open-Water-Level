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
SYSTEM_MODE(AUTOMATIC); // uncomment for deployment

void setup(void)
{
  // Cellular.off(); turn off cellular for prelim testing (uncomment)

  delay(5000); // to see response from begin command

  Serial.begin(9600);
  Serial.println("Maxbotix Test");

}

void loop(void)
{
  // Reinitialize sum variable prior to every loop execution
  dist_in_sum = 0; 

  for(j=0; j<100; j++){
    // Read analog value and convert
    //Counts * (V range/count range) * (Inch range/V range)
    dist_in = analogRead(V_ultraS)*(3.3/2048)*(254/3.3);
    
    // Add new distance to cumulative value
    dist_in_sum += dist_in;

    // Print out distance
    // Serial.print("Time: ");
    // Serial.print(Time.now());
    // Serial.print(", Distance(in): ");
    
    Serial.println(dist_in);

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
    myFile.println(dist_in);
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

  // Get battery charge if Boron provides it
  float cellVoltage = batteryMonitor.getVCell();
  float stateOfCharge = batteryMonitor.getSoC();

  char data[120];
  snprintf(data, sizeof(data), "%d,%.5f,%.02f,%.02f",//,%.5f,%.5f,%.5f,%.5f,%.5f,%.02f,%.02f",
                Time.now(),
                dist_in_avg,
                cellVoltage, stateOfCharge
              );

  // Prep for cellular transmission
  bool isMaxTime = false;
  stateTime = millis();

  while(!isMaxTime)
  {
    //connect particle to the cloud
    if (Particle.connected() == false)
    {
      Particle.connect();
    }

    // If connected, publish data buffer
    if (Particle.connected())
    {
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
        Serial.println("max time for pulishing reach");
      }
      Serial.println("Not max time, try again to publish");
    }
  }
}
