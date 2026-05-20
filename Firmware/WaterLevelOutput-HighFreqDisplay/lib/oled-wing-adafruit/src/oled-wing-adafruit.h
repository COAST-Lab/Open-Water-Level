#ifndef __OLED_WING_ADAFRUIT_H
#define __OLED_WING_ADAFRUIT_H

#include "Adafruit_GFX_RK.h"
#include "Adafruit_SSD1306_RK.h"
#include "Debounce.h"


/**
 * @brief Class for using the Adafruit 128x32 OLED FeatherWing
 *
 * https://www.adafruit.com/product/2900
 * https://learn.adafruit.com/adafruit-oled-featherwing/overview
 */
class OledWingAdafruit : public Adafruit_SSD1306 {
public:
	/**
	 * @brief Construct the object. Default is to support buttons A, B, and C.
	 *
	 * Buttons A and B conflict with the Ethernet FeatherWing, so if you are using both
	 * wings pass USE_BUTTON_C so only button C will be used.
	 */
	OledWingAdafruit(int useButtons = USE_BUTTON_ALL);
	virtual ~OledWingAdafruit();

	/**
	 * @brief You must call this to set up the display during setup()
	 */
	void setup();

	/**
	 * @brief You should call this on every call to loop() to keep the button debouncer running.
	 */
	void loop();

	/**
	 * @brief Returns true if button A was enabled and pressed (with debouncing)
	 */
	bool pressedA();

	/**
	 * @brief Returns true if button B was enabled and pressed (with debouncing)
	 */
	bool pressedB();

	/**
	 * @brief Returns true if button C was enabled and pressed (with debouncing)
	 */
	bool pressedC();

	/**
	 * @brief Optional mutex to make it easier to use the display from multiple threads
	 *
	 * Typical use:
	 *
	 * WITH_LOCK(display) {
	 * 		// Code that uses the display
	 * }
	 */
    void lock() { os_mutex_lock(mutex); };

	/**
	 * @brief Optional mutex to make it easier to use the display from multiple threads
	 */
    bool trylock() { return os_mutex_trylock(mutex)==0; };

	/**
	 * @brief Optional mutex to make it easier to use the display from multiple threads
	 */
    void unlock() { os_mutex_unlock(mutex); };


	static const int USE_BUTTON_A 	= 0b001;
	static const int USE_BUTTON_B 	= 0b010;
	static const int USE_BUTTON_C 	= 0b100;
	static const int USE_BUTTON_ALL = 0b111;

	static const int BUTTON_A_PIN = D4;
	static const int BUTTON_B_PIN = D3;
	static const int BUTTON_C_PIN = D2;

private:
	os_mutex_t mutex = 0;
	int useButtons;
	Debounce buttonA;
	Debounce buttonB;
	Debounce buttonC;
};

#endif /* __OLED_WING_ADAFRUIT_H */
