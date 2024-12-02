# Getting Started with Cell-Enabled Water Level Sensing
## Particle and Visual Studio
This section will help you set up Visual Studio Code and Particle Workbench, two important platforms you'll need for the following exercises.

1. Download Arduino IDE
2. Download the following libraries from the library manager (the third icon down on the sidebar):
	- Adafruit_GFX
	- Adafruit_SSD1306
	- SdFat
	- Wire
	- Adafruit_Sleepydog
	- SPI

## Useful features
This section lists some commands and programming features that will be helpful in the following exercises.

1. In the top left corner, there are some important symbols in green circles:
	- Verify
	- Upload
	- Debug
2. These symbols will be used later to compile and flash code (i.e. importing code to the Boron device).
3. Save your projects frequently using Ctrl+S on Windows or Command+S on Mac. Make sure your directories are exactly how you want them to avoid pathway issues in your coding projects!

## Uploading the code to your device

1. Open the code from the .ino file in the \open-water-level folder within \Firmware
2. Connect your ESP32 to your computer via a data capable USB-C cable.
3. Select Adafruit ESP32-S3 from the drop down box to the right of the Verify/Upload/Debug icons.
4. Click on the upload button and wait for the code to be flashed to the device.

## Testing out the sensor

1. Power on the device and let it collect data.
2. Ideally, take measurements at a known distance to verify that the device is reading correctly.
3. The readings should be saved to to the SD card. Remove the SD card from the Adalogger and verify that the excel file has the measurements saved.
4. The sensor should be ready for deployment!