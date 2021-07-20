// Maxbotix UART Code from https://forum.arduino.cc/index.php?topic=114808.0, original solution by 'Goldthing'
// Modified by PJB, 2-Mar-2020
// Modified by BDD, 2-Mar-20
// Modified by EMB, 8-Aug-20


#include <SPI.h>
#include <Wire.h>
#include <SD.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);
const int chipSelect = 4;
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
  
  display.println("SEAS the");   //write message to screen
  display.println("  day!");
  
  display.setCursor(0,0);
  display.display(); // actually display all of the above

  delay(500);   //wait for everything to initialize

   // Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
  Serial.println("card initialized.");


}

void loop()
{
  int range_cts = analogRead(A1);    //read signal on pin A1 and assign to variable: range_cts
  float range_V = (float)range_cts*(3.3/1024); // counts*(V/counts) = V (NB: SAMD21's ADC is configured to 10-bit resolution)
  float range_in = range_V*(512/3.3); // V*(in/V) = in (NB: in/V conversion factor comes from datasheet)
  unsigned long t = millis()/1000;
  {                                   
     //display range data on screen
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0,0);
    display.println("Dist (in):");
    display.println(range_in); //Counts * (V range/count range) * (Inch range/V range)
   // display.println(t );
    display.display();
    delay(3000);
      display.clearDisplay();
  display.display();

File dataFile = SD.open("ME.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    String data = "";
    data +=range_in;
    data+= ",";
    data+= t;
    //dataFile.println(range_in);
    dataFile.println(data);
    
    dataFile.close();
   
  }
  // if the file isn't open, pop up an error:
  else {
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0,0);
    display.println("card error");
    display.display();
  
  }
    
    delay(60000);           //delay in milli-seconds (60,000=60 s): can change delay length to change measurement speed
  }

}
