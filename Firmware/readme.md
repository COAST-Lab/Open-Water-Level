# Getting Started with Cell-Enabled Water Level Sensing
## Particle and Visual Studio

1. Download Visual Studio (the one with the blue icon, not purple) [here](https://code.visualstudio.com/).
2. Download Particle Workbench [here](https://www.particle.io/workbench/) and create an account as a student using your email. Make sure you have Visual Studio installed prior to running the installer
	- The installer says that it will install VS along with Particle, but this does not work properly and will fail if VS is not installed first.
3. Log into Particle on Visual Studio, if it doesn’t automatically (this is important because it won’t let you install necessary libraries without being logged in)
## Useful commands

1. Open Particle command palette: Ctrl+Shift+P on Windows (or select View tab -> command palette, or click “Launch command palette” button on the Welcome tab)
2. In the top right corner, there are some important symbols in white circles
	- Compile: checkmark
	- Flash: lightning bolt
## Practice code with Boron

1. Plug in the Boron to your computer using a micro USB cable.
	- If you get the message `Could not identify device: No serial port identified` but the Boron powers up, ensure that your cable has data transfer capabilities (many are only capable of charging).
2. Create a folder on your computer to store Particle related items (no spaces in title)
3. Create a new project by opening the Particle command palette and selecting “Particle: Create New Project.” You can also click the blue text that says, “Create new project” on the welcome page under Development workflow -> Code
4. Choose the folder you just made on your computer for this class when it asks for the parent folder
5. Once you have the directory in which you want to store your Particle projects, create a project name (no spaces). Something like Blink_LED.
6. Copy the code from the file named `Blink_LED.ino` (not the one you just made but from the example [here](https://github.com/SUPScientist/Smart-Coasts/blob/main/Class-01-Intro/Blink_LED.ino))
7. Navigate to the .ino file that is generated for your new project under the src tab on the left-hand side of screen (under explorer). Delete all the text there and past the code you just copied
8. Open the command palette. Type "particle" and select "Particle Launch CLI"
9. Put the Boron into DFU (device firmware update) mode by pressing and holding the Mode button on the Boron while pressing and releasing the Reset button. Continue holding Mode until the RGB (Red Green Blue) LED starts flashing yellow.
10. Type `particle update` and press enter in the CLI (command line interface) that pops up. This should update your Device OS (mine updated to 4.1.0)
11. Check your Device OS by putting the Boron in listening mode (press and hold Mode until the LED blinks blue) and typing the following command into the CLI: `particle identify` (4.1.0 for me)
12. Configure Workbench to work with the Device OS that you confirmed you're using in the previous step. Your settings should be in the blue line across the bottom of the page. Make sure the first setting says "boron" and the second says "deviceOS@[4.1.0 or your specific number]" by clicking and changing them if need be
13. Open the command palette and run Particle: flash application (local) to compile and flash your script (your .ino file) to your device. If successful, this will result in the blinking of a blue LED close to the micro-USB socket on the Boron

	![](https://github.com/COAST-Lab/Open-Water-Level/blob/main/Firmware/Getting%20Started%20With%20Particle%20for%20Water%20Level%20Sensor%20Images/0.jpg)

## Practice code with Boron and Adalogger

1. Stack the Boron on top of the Adalogger using female headers. 
2. Plug in the Boron and put it in listening mode again. Type `particle identify` into the CLI again and make sure "Boron" is selected in the bottom bar
3. Create a new project (I named mine RTCtest) 
4. Open command palette and type "Particle: Install Library" 
5. Type in 'SdFat' and press enter to install SdFat library 
6. A new tab titled 'lib' should now be under the explorer tab for this project on the left, open it 
7. Click on examples -> ReadWrite -> `ReadWrite.ino` 
8. Copy all the code on this page 
9. Now click the tab that says "src" on the left, then `[your project title].ino` (not the .cpp) 
	- The .ino file will always be the file you will want to use to flash code
10. Highlight and delete everything in the .ino file, replace it with the new code you just copied from the ReadWrite.ino file 
11. In line 25, change `#define SD_CS_PIN SS` to `#define SD_CS_PIN D5` (SS -> D5) 
12. After `File myFile;` create a new line and type `SYSTEM_MODE(MANUAL);`
13. After `void setup(){,` create a new line and type `Cellular.off();”` and in the next line type `delay(2500);` 
14. Where it says `if (!SD.begin(SD_CS_PIN,)) {` type `if (!SD.begin(SD_CS_PIN,SPI_FULL_SPEED)) {`

	![](https://github.com/COAST-Lab/Open-Water-Level/blob/main/Firmware/Getting%20Started%20With%20Particle%20for%20Water%20Level%20Sensor%20Images/1.jpg)

15. Click the checkmark to compile the project (will take a minute) 
16. Once it compiles, click the lightning bolt button to flash the code to the Boron 
	- Boron should flash yellow/green when being put into DFU mode, then should breathe a white/blue light once it’s flashed 
	- Should also say it flashed successfully, unplugging and re-plugging cord into Boron can sometimes help if it doesn’t flash 
17. Open the serial monitor: command palette -> “Particle: Serial Monitor”  
18. If the adalogger does not work, serial monitor may read something like the first chunk of text below, if it does work, it should read like the second chunk of text

	![](https://github.com/COAST-Lab/Open-Water-Level/blob/main/Firmware/Getting%20Started%20With%20Particle%20for%20Water%20Level%20Sensor%20Images/2.jpg)

## Practice water level sensor full code (Boron and Adalogger) 

1. Wiring Connection between Boron/Adalogger stack and water level sensor: The water level sensor's AN pin will connect to the A1 pin of the Boron. Ground the water level sensor by connecting GND to GND on the Boron and connect to power by connecting +5 to 3v3 on the Boron. 
2. On the GitHub repository, go to Firmware -> SLR_Boron_Maxbotix_MB7092_cm -> src -> `SLR_Boron_Maxbotix_MB7092_cm.ino` (or follow [this link](https://github.com/COAST-Lab/Open-Water-Level/blob/main/Firmware/SLR_Boron_Maxbotix_MB7092_cm/src/SLR_Boron_Maxbotix_MB7092_cm.ino))  
3. Copy all the code on this page 
4. In particle workbench, create a new project 
5. Go to the .ino file and delete the code and paste the new code you copied from GitHub there 
6. In lines 32 and 33, change the comments so that 32 is uncommented (delete the double slashes in front) and 33 is commented out (add double slashes in front)

	![](https://github.com/COAST-Lab/Open-Water-Level/blob/main/Firmware/Getting%20Started%20With%20Particle%20for%20Water%20Level%20Sensor%20Images/3.jpg)

7. In line 44, where it says `const unsigned long MAX_TIME_TO_PUBLISH_MS = 60000` change the `60000` to `20000`
8. In lines 49 and 50, swap the comments so that 49 is commented out and 50 is uncommented

	![](https://github.com/COAST-Lab/Open-Water-Level/blob/main/Firmware/Getting%20Started%20With%20Particle%20for%20Water%20Level%20Sensor%20Images/4.jpg)

9. Comment out lines 150–154. You can select all the text in those lines and use the shortcut Ctrl+/

	![](https://github.com/COAST-Lab/Open-Water-Level/blob/main/Firmware/Getting%20Started%20With%20Particle%20for%20Water%20Level%20Sensor%20Images/5.jpg)
10. After line 136 that says `myFile.print(range_cm);` create a new line and make sure it’s in line with the previous line and type `myFile.print(";");` This will make the data easier to read
11. In line 208, where it says `.duration(54min)` change the `54` to `1` 
12. Compile and flash code to boron 
13. Open the serial monitor 
14. Give it a second, but the terminal should look something like the picture below 
	-If it still doesn’t work, try pressing the reset button on the Boron, or unplug and re-plug cord in 
15. It should publish the time and distance once before repeating the phrase “not max time, try again to publish”

	![](https://github.com/COAST-Lab/Open-Water-Level/blob/main/Firmware/Getting%20Started%20With%20Particle%20for%20Water%20Level%20Sensor%20Images/6.jpg)

16. After 20 seconds (because of the value you changed from 60000 to 20000), the serial monitor should say `serial connection closed. Attempting to reconnect…`
17. After 1 minute (because of the value you changed from 54min to 1min), the serial monitor should say `serial monitor opened successfully` 
18. Unplug the boron to stop the code from running 
19. To check all the collected values, take out the SD card from the adalogger and put it into a SD card reader to then plug into your computer 
20. Navigate to file explorer -> this PC -> USB drive -> `distance.txt`. You should see values like below!

	![](https://github.com/COAST-Lab/Open-Water-Level/blob/main/Firmware/Getting%20Started%20With%20Particle%20for%20Water%20Level%20Sensor%20Images/7.jpg)

21. Unix time values are listed first, then another value, and then the distance(cm) values followed by a semi-colon
