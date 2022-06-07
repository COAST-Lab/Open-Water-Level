// Maxbotix UART Code from https://forum.arduino.cc/index.php?topic=114808.0, original solution by 'Goldthing'
// Modified by PJB, 2-Mar-2020
// Modified by BDD, 2-Mar-20
// Modified by EMB, 8-Aug-20
// Modified by LCE and PJB, 31-May-22
// Modified by LCE, 01-Jun-22

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
unsigned long t;
String data;

RTC_PCF8523 rtc;
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, & Wire);
const int chipSelect = 4;

// Set time for sleep state in milliseconds
int desired_sleep_time_ms = 30000;
// Set number of samples to be averaged for measurement
int sample_average = 10;

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

  // rtc initial setup
  if (!rtc.begin()) {
    display.println("Can't find RTC");
    display.flush();
    while (1) delay(10);
  }

  if (!rtc.initialized() || rtc.lostPower()) {
    display.println("Time reset");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  rtc.start(); // starts the clock if power was lost

  display.setCursor(0, 0);
  display.clearDisplay();
  display.display();

  display.println("SEAS the"); //write message to screen
  display.println("  day!");

  display.setCursor(0, 0);
  display.display(); // actually display all of the above

  delay(1000); //wait for everything to initialize

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
  // Create csv file with headers
  File dataFile = SD.open("DATA.csv", FILE_WRITE);
  dataFile.println("Distance,Time,Date");
  dataFile.close();
}

void loop() {
  int start_time_ms = millis();
  DateTime now = rtc.now();
  unsigned long cts_cumulative = 0;
  for (int i = 0; i < sample_average; i++) {
    cts_cumulative += analogRead(A1); //check board to ensure correct pin is selected.
  }
  //range_cts = analogRead(A1);    //read signal on pin A1 and assign to variable: range_cts
  //range_V = (float)range_cts*(3.3/1024); // counts*(V/counts) = V (NB: SAMD21's ADC is configured to 10-bit resolution)
  float range_cts_avg = cts_cumulative / sample_average;
  range_V = range_cts_avg * (3.3 / 1024);
  range_in = range_V * (512 / 3.3); // V*(in/V) = in (NB: in/V conversion factor comes from datasheet)
  {
    //display range data on screen
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("Dist (in):");
    display.println(range_in); //Counts * (V range/count range) * (Inch range/V range)
    display.display();
    delay(1000);
    display.clearDisplay();
    display.display();

    File dataFile = SD.open("DATA.csv", FILE_WRITE);
    // if the file is available, write to it:
    if (dataFile) {
      data = ""; // start with empty string, then add to it in subsequent lines
      data += range_in;
      data += ",";
      data += now.hour();
      data += ":";
      data += now.minute();
      data += ":";
      data += now.second();
      data += ",";
      data += now.month();
      data += "/";
      data += now.day();
      data += "/";
      data += now.year();
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
    }
    // Determine time elapsed for more accurate sleep time
    int end_time_ms = millis();
    int elapsed_time = end_time_ms - start_time_ms;
    int sleep_time = desired_sleep_time_ms - elapsed_time;
    int sleep_loops = floor(sleep_time / 16000);
    float sleep_remainder = sleep_time % 16000;

    // This loop puts board into sleep state for number of milliseconds input into desired_sleep_time_ms. 
    for (int i = 0; i < sleep_loops; i++) {
      int sleepMS = Watchdog.sleep(16000); // puts device in low power state for ms, caps at 16 seconds, repeat code to get longer sleep time.
    }
    int sleepMS = Watchdog.sleep(sleep_remainder); // adds on remainder seconds from dividing sleep_time by 16. 
  }
}