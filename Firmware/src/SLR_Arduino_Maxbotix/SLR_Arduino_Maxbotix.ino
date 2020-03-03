// Maxbotix UART Code from https://forum.arduino.cc/index.php?topic=114808.0, original solution by 'Goldthing'
// Modified by PJB, 2-Mar-2020
// Modified by BDD, 2-Mar-20

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);

#include <SoftwareSerial.h>
#define txPin 4                                         //define pins used for software serial for sonar (Not Connected)
#define rxPin 3                                         //Connect to TX of the sensor
SoftwareSerial sonarSerial(rxPin, txPin, true);         //define serial port for recieving data, output from maxSonar is inverted requiring true to be set.

boolean stringComplete = false;

void setup()
{
  Serial.begin(9600);                                      //start serial port for display
  sonarSerial.begin(9600);                                 //start serial port for maxSonar

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
  display.println("Seas the day!");
  display.setCursor(0,0);
  display.display(); // actually display all of the above

  delay(500);                                              //wait for everything to initialize

}

void loop()
{
  int range = EZread();
  if(stringComplete)
  {
    stringComplete = false;                                //reset sringComplete; ready for next reading

    Serial.print("Range ");
    Serial.println(range);

    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0,0);
    display.println("Dist (in):");
    display.println(range); //Counts * (V range/count range) * (Inch range/V range)
    display.display();


    delay(500);                                          //delay for debugging
  }

}


int EZread()
{
  int result;
  char inData[4];                                          //char array to read data into
  int index = 0;

  sonarSerial.flush();                                     // Clear cache ready for next reading

  while (stringComplete == false) {
    //Serial.print("reading ");    //debug line

    if (sonarSerial.available())
    {
      char rByte = sonarSerial.read();                     //read serial input for "R" to mark start of data
      if(rByte == 'R')
      {
        //Serial.println("rByte set");
        while (index < 3)                                  //read next three character for range from sensor
        {
          if (sonarSerial.available())
          {
            inData[index] = sonarSerial.read();
            index++;                                       // Increment where to write next
          }
        }
        inData[index] = 0x00;                              //add a padding byte at end for atoi() function
      }

      rByte = 0;                                           //reset the rByte ready for next reading
      index = 0;                                           // Reset index ready for next reading
      stringComplete = true;                               // Set completion of read to true
      result = atoi(inData);                               // Changes string data into an integer for use
    }
  }

  return result;
}
