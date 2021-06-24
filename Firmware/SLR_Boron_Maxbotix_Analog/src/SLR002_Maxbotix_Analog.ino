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
  // Read analog value and convert
  //Counts * (V range/count range) * (Inch range/V range)
  dist_in = analogRead(V_ultraS)*(3.3/2048)*(254/3.3);

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

  delay(5000);
}
