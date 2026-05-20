#include "Particle.h"
#include "oled-wing-adafruit.h"

SYSTEM_MODE(MANUAL); 

//------------------Maxbotix sensor
float distance_unconverted; // store the distance from sensor
float range_cm;

long real_time;
int millis_now;

OledWingAdafruit display;

void setup() {

  Cellular.off();

  // Display
  display.setup();

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.setRotation(2); //rotates text on OLED 1=90 degrees, 2=180 degrees
  display.println("Seas the");
  display.println("Day!");
  display.display(); 
  delay(5000); // Wait for the user to see it

  display.clearDisplay(); // Clear display for new data  
}

void loop() {
  //display.loop();
  display.clearDisplay(); // Clear display for new data  
  
  // Take measurement
  distance_unconverted = (analogRead(A1));

  // Get average of the middle samples (from 10 to 190)
  range_cm = (float) distance_unconverted * 0.25; // conversion factor

  // Update display with latest data
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.setRotation(2); //rotates text on OLED 1=90 degrees, 2=180 degrees
  display.println("Distance");
  display.print(range_cm);
  display.println(" (cm)");
  display.display(); 

  // Set analog read and display max frequency (could be slower depending on display speed)
  delay(500); 
}

