#include "oled-wing-adafruit.h"

SYSTEM_THREAD(ENABLED);

OledWingAdafruit display;

void graphicsTest();
void bitmapTest();

void setup() {
	display.setup();

	display.clearDisplay();
	display.display();
}

void loop() {
	display.loop();

	if (display.pressedA()) {
		display.clearDisplay();

		display.setTextSize(1);
		display.setTextColor(WHITE);
		display.setCursor(0,0);
		display.println("Hello, world!");
		display.display();
	}
	if (display.pressedB()) {
		graphicsTest();
	}

	if (display.pressedC()) {
		bitmapTest();
	}
}

void graphicsTest() {
	display.clearDisplay();

	{
		uint8_t color = 1;
		for (int16_t i=0; i<display.height()/2; i+=3) {
			// alternate colors
			display.fillRect(i, i, display.width()-i*2, display.height()-i*2, color%2);
			display.display();
			delay(1);
			color++;
		}
		delay(500);
		display.clearDisplay();
	}
	{
		for (int16_t i=0; i<min(display.width(),display.height())/2; i+=5) {
			display.drawTriangle(display.width()/2, display.height()/2-i,
					display.width()/2-i, display.height()/2+i,
					display.width()/2+i, display.height()/2+i, WHITE);
			display.display();
			delay(1);
		}
		delay(500);
		display.clearDisplay();
	}
	{
		uint8_t color = WHITE;
		for (int16_t i=min(display.width(),display.height())/2; i>0; i-=5) {
			display.fillTriangle(display.width()/2, display.height()/2-i,
					display.width()/2-i, display.height()/2+i,
					display.width()/2+i, display.height()/2+i, WHITE);
			if (color == WHITE) color = BLACK;
			else color = WHITE;
			display.display();
			delay(1);
		}
		delay(500);
		display.clearDisplay();
	}
	{
		for (int16_t i=0; i<display.height()/2-2; i+=2) {
			display.drawRoundRect(i, i, display.width()-2*i, display.height()-2*i, display.height()/4, WHITE);
			display.display();
			delay(1);
		}
		delay(500);
		display.clearDisplay();
		display.display();
	}
}

#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16
static const unsigned char logo16_glcd_bmp[] =
{   	0b00000000, 0b11000000,
		0b00000001, 0b11000000,
		0b00000001, 0b11000000,
		0b00000011, 0b11100000,
		0b11110011, 0b11100000,
		0b11111110, 0b11111000,
		0b01111110, 0b11111111,
		0b00110011, 0b10011111,
		0b00011111, 0b11111100,
		0b00001101, 0b01110000,
		0b00011011, 0b10100000,
		0b00111111, 0b11100000,
		0b00111111, 0b11110000,
		0b01111100, 0b11110000,
		0b01110000, 0b01110000,
		0b00000000, 0b00110000 };


void bitmapTest() {
	display.clearDisplay();
	display.drawBitmap(30, 16,  logo16_glcd_bmp, 16, 16, 1);
	display.display();
}
