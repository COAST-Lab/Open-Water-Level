// Maxbotix UART Code from https://forum.arduino.cc/index.php?topic=114808.0, original solution by 'Goldthing'
// Modified by PJB, 2-Mar-2020
// Modified by BDD, 2-Mar-20
// Modified by EMB, 8-Aug-20


#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);


//here is where initialization code goes
void setup()
{
  Serial.begin(9600);      //start serial port for display

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
  
  display.println("SEAS the");
  display.println("  day!");
  
  display.setCursor(0,0);
  display.display(); // actually display all of the above

  delay(500);   //wait for everything to initialize

}
//here is where your continuously run code goes
void loop()
{
  int range = analogRead(A1);    //read signal on pin A1 and assign to variable: range
  
  {                                   
     //display range data on screen
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0,0);
    display.println("Dist (in):");
    display.println(range); //Counts * (V range/count range) * (Inch range/V range)
    display.display();


    delay(1000);           //delay: can change delay length to change measurement speed
  }

}
