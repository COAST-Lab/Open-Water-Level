#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);


void setup()
{
  Serial.begin(9600);                                      //start serial port for display

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3C for 128x32

  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(1000);

  // Clear the buffer.
  display.clearDisplay();
  display.display();

  // text display tests
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);

  //write your text here
  display.println("ORE 203L!");
  display.println("Surf Sci");
 
  display.setCursor(0,0);
  display.display(); // actually display all of the above

  delay(500);                                              //wait for everything to initialize

}
void loop() {
  // put your main code here, to run repeatedly:

}
