#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
 
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);
 
// OLED FeatherWing buttons map to different pins depending on board:
#if defined(ESP8266)
  #define BUTTON_A  0
  #define BUTTON_B 16
  #define BUTTON_C  2
#elif defined(ESP32)
  #define BUTTON_A 15
  #define BUTTON_B 32
  #define BUTTON_C 14
#elif defined(ARDUINO_STM32_FEATHER)
  #define BUTTON_A PA15
  #define BUTTON_B PC7
  #define BUTTON_C PC5
#elif defined(TEENSYDUINO)
  #define BUTTON_A  4
  #define BUTTON_B  3
  #define BUTTON_C  8
#elif defined(ARDUINO_FEATHER52832)
  #define BUTTON_A 31
  #define BUTTON_B 30
  #define BUTTON_C 27
#else // 32u4, M0, M4, nrf52840 and 328p
  #define BUTTON_A  9
  #define BUTTON_B  6
  #define BUTTON_C  5
#endif

// Use these analog voltage variable, representing ultrasonic sensor output and conversions, later
//const int anPin = A0;
//long V_ultraS, mm, inches;

//int V_ultraS = A0;

int adcin    = A0;
int adcvalue = 0;
float mv_per_lsb = 3600.0F/8192.0F; // 14-bit ADC split in half with 3.6 V input range
float in_per_mv = 254.0F/3600.0F; // 254 in range sensor over 3.6 V input range
float mv, in;

void setup() {

  analogReadResolution(14); // Can be 8, 10, 12 or 14
  
  Serial.begin(9600);
 
  Serial.println("OLED FeatherWing test");
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3C for 128x32
 
  Serial.println("OLED begun");
 
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(1000);
 
  // Clear the buffer.
  display.clearDisplay();
  display.display();
 
  Serial.println("IO test");
 
  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);
  pinMode(BUTTON_C, INPUT_PULLUP);
 
  // text display tests
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("It's alive!");
  display.setCursor(0,0);
  display.display(); // actually display all of the above
  
  delay(2500);
}
 
void loop() {
//  V_ultraS = analogRead(anPin);  // Read analog pin
//
//  mm = V_ultraS*5; // Takes bit count and converts it to mm
//  inches = mm/25.4; // Takes mm and converts it to inches

  // Get a fresh ADC value
  adcvalue = analogRead(adcin);
  mv = (float)adcvalue * mv_per_lsb;
  in = mv*in_per_mv;
  
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("Dist (in):");
  display.println(in); //Counts * (V range/count range) * (Inch range/V range)
  display.display();

  delay(1000);
}
