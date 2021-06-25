/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/pjb/Dropbox/Particle_Projects/Seaport_SLR_Observation/Seaport_Tide-SLR_Maxbotix_Arduino/Firmware/SLR_Boron_Maxbotix_Analog/src/SLR002_Maxbotix_Analog.ino"
#include "SdFat.h"
//------------------SD SPI Configuration Details--------------------------------
void setup(void);
void loop(void);
#line 3 "/Users/pjb/Dropbox/Particle_Projects/Seaport_SLR_Observation/Seaport_Tide-SLR_Maxbotix_Arduino/Firmware/SLR_Boron_Maxbotix_Analog/src/SLR002_Maxbotix_Analog.ino"
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

//------------------Turn off cellular for prelim testing
SYSTEM_MODE(MANUAL);
// SYSTEM_THREAD(ENABLED);

void setup(void)
{
  Cellular.off();

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
    Serial.print("Time: ");
    Serial.print(Time.now());
    Serial.print(", Distance(in): ");
    
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
  
  dist_in_avg = dist_in_sum/j;

  Serial.print(j);
  Serial.print(",");
  Serial.print(dist_in_sum);
  Serial.print(",");
  Serial.println(dist_in_avg);
}
