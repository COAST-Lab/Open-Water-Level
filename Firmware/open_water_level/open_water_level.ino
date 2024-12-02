#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SdFat.h>
#include <Wire.h>
#include <Adafruit_SleepyDog.h>
#include <SPI.h>

//------------------SD SPI Configuration Details--------------------------------
const int SD_CHIP_SELECT = 10; // Pin 10
SdFat sd;

//------------------Display Configuration----------------------------------------
Adafruit_SSD1306 display(128, 32, &Wire); // Declare at global scope

//------------------LED Setup
int led = 13; // Using onboard LED for Arduino
bool led_state = HIGH; // Starting state

//------------------Maxbotix Sensor
float filterArray[200]; // Array to store data samples from sensor
float distance_unconverted; // Store the distance from sensor
float range_cm;

unsigned long real_time;
unsigned long millis_now;

//------------------State variables
enum State {
  DATALOG_STATE,
  PUBLISH_STATE,
  SLEEP_STATE
};
State state = DATALOG_STATE;

// Define whether (1) or not (0) to publish
#define PUBLISHING 0

unsigned long stateTime = 0;
char data[120];

// Timing constants
const unsigned long MAX_TIME_TO_PUBLISH_MS = 20000; // Max time for publishing
const unsigned long SECONDS_BETWEEN_MEASUREMENTS = 10; // Sampling period

// Non-blocking timing for display updates
unsigned long lastDisplayUpdate = 0;
const unsigned long displayInterval = 1000; // Update every second

// Function prototypes
int secondsUntilNextEvent();

void setup() {
  pinMode(led, OUTPUT);

  Serial.begin(9600);
  //while (!Serial); // Wait for serial connection (debugging)
  Serial.println("Maxbotix Test");

  // Initialize SD card
  if (!sd.begin(SD_CHIP_SELECT)) {
    Serial.println("SD card initialization failed!");
  } else {
    Serial.println("SD card initialized.");
  }
  
  // Initialize display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 initialization failed!");
    while (true); // Halt if the display initialization fails
  }
  // Rotate display 180 degrees
  display.setRotation(2); 

  // Show startup screen
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("SEAS the");
  display.println("  day!");
  display.display(); // Show the splash screen
  delay(1000);       // Wait for the user to see it

  display.clearDisplay(); // Clear display for new data
}

void loop() {
  switch (state) {
    //////////////////////////////////////////////////////////////////////////////
    /*** DATALOG_STATE ***/
    case DATALOG_STATE: {
      // Take multiple measurements and store in array
      for (int sample = 0; sample < 200; sample++) {
        filterArray[sample] = analogRead(A1);
        delay(50); // To avoid ultrasonic interference
      }

      // Sort the array
      for (int i = 0; i < 199; i++) {
        for (int j = i + 1; j < 200; j++) {
          if (filterArray[i] > filterArray[j]) {
            float swap = filterArray[i];
            filterArray[i] = filterArray[j];
            filterArray[j] = swap;
          }
        }
      }

      // Exclude the 10 smallest and 10 largest samples
      double sum = 0;
      for (int sample = 10; sample < 190; sample++) {
        sum += filterArray[sample];
      }
      distance_unconverted = sum / 180;

      // Convert distance to cm
      range_cm = (float)distance_unconverted * 0.25;

      // Record current time
      real_time = millis() / 1000; // Using millis() as a time placeholder
      millis_now = millis();

      // Prepare data string
      snprintf(data, sizeof(data), "%lu,%.5f", real_time, range_cm);

      // Save data to SD card
      File dataFile = sd.open("distance.csv", FILE_WRITE);
      if (dataFile) {
        dataFile.println(data);
        dataFile.close();
        Serial.println("Data saved to SD:");
        Serial.println(data);
      } else {
        Serial.println("Error opening distance.csv");
      }

      // Update display 
      if (millis() - lastDisplayUpdate >= displayInterval) {
        lastDisplayUpdate = millis();
        display.clearDisplay();
        display.setTextSize(2);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(0, 0);
        display.println("Dist (cm):");
        display.println(range_cm, 1); // Display range in cm with 1 decimal place
        display.display();
      }

      if (PUBLISHING == 1) {
        state = PUBLISH_STATE;
      } else {
        state = SLEEP_STATE;
      }
    }
    break;

    //////////////////////////////////////////////////////////////////////////////
    /*** PUBLISH_STATE ***/
    case PUBLISH_STATE: {
      // Replace with cellular publishing logic if applicable
      Serial.println("Publishing data...");
      delay(1000); // Simulate publishing
      state = SLEEP_STATE;
    }
    break;

    //////////////////////////////////////////////////////////////////////////////
    /*** SLEEP_STATE ***/
    case SLEEP_STATE: {
      Serial.println("Entering sleep mode...");

      int wakeInSeconds = secondsUntilNextEvent();
      Watchdog.sleep(wakeInSeconds * 1000); // Use SleepyDog for low-power sleep

      state = DATALOG_STATE;
    }
    break;
  }
}

int secondsUntilNextEvent() {
  unsigned long current_seconds = millis() / 1000; // Replace with real-time logic if needed
  int seconds_to_sleep = SECONDS_BETWEEN_MEASUREMENTS - (current_seconds % SECONDS_BETWEEN_MEASUREMENTS);
  Serial.print("Sleeping for ");
  Serial.print(seconds_to_sleep);
  Serial.println(" seconds.");
  return seconds_to_sleep;
}
