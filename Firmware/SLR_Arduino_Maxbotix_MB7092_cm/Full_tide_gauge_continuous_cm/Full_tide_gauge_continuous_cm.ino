// Maxbotix UART Code from https://forum.arduino.cc/index.php?topic=114808.0, original solution by 'Goldthing'
// Modified by PJB, 2-Mar-2020
// Modified by BDD, 2-Mar-20
// Modified by EMB, 8-Aug-20
// Modified by LCE and PJB, 31-May-22
// Modified by LCE, 01-Jun-22
// Modified by LCE, 08-Jun-22
// Modified by LCE, 13-Jun-22

// ***** This script is intended for use with a different Maxbotix sensor from the other scripts in this repository
// ***** in particular, the MB7092 XL-MaxSonar-WRMA1, with 1 cm resolution

#include <SPI.h>
#include <Wire.h>
#include <SD.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_SleepyDog.h>
#include <RTClib.h>

// Declare main variables
int range_cts;
float range_V;
float range_in;
String data;
float filterArray[200]; // array to store data samples from sensor
float distance_cm; // store the distance from sensor

// Set time for sleep state in milliseconds
//int desired_sleep_time_ms = 60000;

RTC_PCF8523 rtc;
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, & Wire);
const int chipSelect = 4;

/////////////////////////////////////////////////////////////////////////////

void setup() {
  Serial.begin(9600); //start serial port for display

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3C for 128x32

  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(2000);

  // Clear the buffer.
  display.clearDisplay();
  display.display();

  // text display tests
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);

  // rtc setup
  if (!rtc.begin()) {
    display.println("No RTC");
    display.display();
    while (1) delay(10);
 }
  // If the rtc has lost power or has a dead battery, it will reset
  if (!rtc.initialized() || rtc.lostPower()) {
    display.println("Time reset");
    rtc.adjust(DateTime(2000, 1, 1, 0, 0, 0)); // Time is reset to midnight on Jan. 1, 2000
    display.display();
    delay(1000);
  }
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    display.println("No SD card");
    display.display();
    while (1) delay(10);
  }
  display.setCursor(0, 0);
  display.clearDisplay();
  display.display();

  display.println("SEAS the"); //write message to screen
  display.println("  day!");

  display.setCursor(0, 0);
  display.display(); // actually display all of the above

  delay(1000); //wait for everything to initialize

  // Create csv file with headers
  File dataFile = SD.open("DATA.csv", FILE_WRITE);
  dataFile.println("Date-Time,Distance (cm)");
  dataFile.close();
}
/////////////////////////////////////////////////////////////////////////////
void loop() {
  int start_time_ms = millis(); 
  DateTime now = rtc.now();

  {
    //display range data on screen
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("Dist (cm):");
    display.println(analogRead(A1)); //Counts * (V range/count range) * (Inch range/V range)
    display.display();
    delay(1000);
    display.clearDisplay();
    display.display();

    File dataFile = SD.open("DATA.csv", FILE_WRITE);

    // Restarts the SD card if it was removed
    if (!dataFile) {
    SD.begin(chipSelect);
    File dataFile = SD.open("DATA.csv", FILE_WRITE);
    dataFile.close();
      }
    
    // if the file is available, write to it:
    if (dataFile) {
      data = ""; // start with empty string, then add to it in subsequent lines
      data += now.month();
      data += "/";
      data += now.day();
      data += "/";
      data += now.year();
      data += " ";
      data += now.hour();
      data += ":";
      data += now.minute();
      data += ":";
      data += now.second();
      data += ",";
      data += distance_cm; //range_in;
      data += ",";
      
      
      dataFile.println(data);
      dataFile.close();
    }
    // if the file isn't open, pop up an error:
    else {
      display.clearDisplay();
      display.setTextSize(2);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(0, 0);
      display.println("card error");
      display.display();
      delay(1000);
      display.clearDisplay();
      display.display();
    }

    delay(500);
    
//    // Determine time elapsed for more accurate sleep time
//    int end_time_ms = millis();
//    int elapsed_time = end_time_ms - start_time_ms;
//    int sleep_time = desired_sleep_time_ms - elapsed_time;
//    int sleep_loops = sleep_time / 8000;
//    float sleep_remainder = sleep_time % 8000;
//       
//    // This loop puts board into sleep state for number of milliseconds input into desired_sleep_time_ms
//    for (int i = 0; i < sleep_loops; i++) {
//      int sleepMS = Watchdog.sleep(8000); // puts device in low power state for ms, caps at 8 seconds, repeat code to get longer sleep time
//    } 
//      int sleepMS = Watchdog.sleep(sleep_remainder); // adds on remainder seconds from dividing sleep_time 
  }
}
