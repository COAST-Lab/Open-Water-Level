# Some getting started tips for compiling and flashing the firmware on your own computer

I had to uninstall and reinstall Arduino, the Arduino libraries, and the Arduino15 folder before this all worked, likely because I hadn't used Arduino in over a year and the Bluefruit Feathers are evolving quickly.

1. Install nRF52832 Bluefruit Feather
https://learn.adafruit.com/bluefruit-nrf52-feather-learning-guide/arduino-bsp-setup

2. Make sure to follow all of the setup steps, like https://learn.adafruit.com/bluefruit-nrf52-feather-learning-guide/arduino-board-setup

3. Install libraries for OLED featherwing
https://learn.adafruit.com/adafruit-oled-featherwing/usage

4. Here are some basics, including code, for the sensor but they’re not perfectly accurate for our sensor: https://www.maxbotix.com/articles/mb1240-ultrasonic-sensor-arduino.htm. Also note that they appear to round some values in their calculations to make the firmware easier to read but that makes the results less accurate. 
