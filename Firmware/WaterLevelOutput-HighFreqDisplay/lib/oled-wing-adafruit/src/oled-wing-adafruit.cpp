#include "oled-wing-adafruit.h"


OledWingAdafruit::OledWingAdafruit(int useButtons) : Adafruit_SSD1306(128, 32), useButtons(useButtons) {

}
OledWingAdafruit::~OledWingAdafruit() {
	if (mutex) {
		os_mutex_destroy(mutex);
	}
}

void OledWingAdafruit::setup() {
	os_mutex_create(&mutex);

	if (useButtons & USE_BUTTON_A) {
		buttonA.attach(BUTTON_A_PIN, INPUT_PULLUP);
	}
	if (useButtons & USE_BUTTON_B) {
		buttonB.attach(BUTTON_B_PIN, INPUT); // Button B has a hardware 100K pull-up on the board
	}
	if (useButtons & USE_BUTTON_C) {
		buttonC.attach(BUTTON_C_PIN, INPUT_PULLUP);
	}

	// 128x32 = I2C addr 0x3C. Method inherited from Adafruit_SSD1306.
	begin(SSD1306_SWITCHCAPVCC, 0x3C);
}

void OledWingAdafruit::loop() {
	if (useButtons & USE_BUTTON_A) {
		buttonA.update();
	}
	if (useButtons & USE_BUTTON_B) {
		buttonB.update();
	}
	if (useButtons & USE_BUTTON_C) {
		buttonC.update();
	}
}

bool OledWingAdafruit::pressedA() {
	return (useButtons & USE_BUTTON_A) && buttonA.fell();
}

bool OledWingAdafruit::pressedB() {
	return (useButtons & USE_BUTTON_B) && buttonB.fell();
}

bool OledWingAdafruit::pressedC() {
	return (useButtons & USE_BUTTON_C) && buttonC.fell();
}



