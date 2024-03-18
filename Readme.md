[![DOI](https://zenodo.org/badge/243609204.svg)](https://zenodo.org/badge/latestdoi/243609204)

# Open Water Level Sensor
This GitHub repository is intended to serve as supplementary information to a manuscript in the journal Oceanography, in the special section DIY (do-it-yourself) Oceanography. 

The article, *A Low-Cost, DIY Ultrasonic Water Level Sensor for Education, Citizen Science, and Research*, can be found here: [https://doi.org/10.5670/oceanog.2023.101](https://doi.org/10.5670/oceanog.2023.101). This article corresponds to an older version of the code which can be found here: [https://github.com/SUPScientist/Seaport_Tide-SLR](https://github.com/SUPScientist/Seaport_Tide-SLR). 

That manuscript contains additional important information beyond what is in this repository. Please read the following for a high-level overview of the project and the contents of this repository.

(insert picture)

## About
This project comprises a low-cost open-sourced sensor package designed to measure distance and either transmit or store measurements.  It utilizes an Arduino-based Adafruit Adalogger with a Particle Boron with cellular data transfer a Maxbotix ultrasonic rangefinder, a rechargeable lithium-ion battery, and either upcycled plastic parts or an off-the-shelf water-resistant enclosure. 

The goals of this repository are to enable citizen scientists, businesses, and anyone with the motivation to monitor their local sea level. To get started read through this page and subsequent directions. 

## Table of Contents 

- [Introduction](#Inroduction)

- [How to get your sensor](How-to-get-your-sensor)
  
- [Datasheets](#Datasheets) 

- [How to get started](#How-to-get-started)

- [Deployment](#Deployment)


## Introduction
There are several versions of the DIY water level sensor, including different microcontrollers and different sensor interfacing options (analog, serial, and pulse-width modulation). 

If you are looking for a cellular data transmission-enabled device with higher resolution, see [Firmware/SLR_Boron_Maxbotix_MB7092_cm](Firmware/SLR_Boron_Maxbotix_MB7092_cm) and the Getting Started guide in that repository's README.

## How to get your sensor
[BOM](BOM)

## Datasheets
Link to  the data sheets of each part in the sensor package

[Datasheets](Datasheets)

## How to get started 

Click this link below to find instructions on getting started with programing and soldering your sensor.

[Firmware](Firmware)


## The Fun Stuff
### Deployment
Deployment is actually the last step but it's probably the most exciting, so we'll start our procedural notes here. The Seaport Tide and Sea Level Rise Monitor has a ~ 6.5 m (21') range with 2.5 cm (1") resolution. Deployment location must be chosen with these values in mind. If you are deploying the monitor at a location reasonably close to an existing NOAA tide station, start by examining the known tidal range at your location: [NOAA tide predictions](https://tidesandcurrents.noaa.gov/tide_predictions.html). You will want to deploy the monitor at location where it can aim straight down to the water's surface and at a height that is slightly higher than the highest high tide that the location is expected to experience. As described above, the package is currently not designed in to be waterproof so it should not be deployed in extreme weather events unless it is modified.

### Assembly
If your monitor arrived unassembled or you were feeling adventurous enough to disassemble it, you may want to follow these directions to put it (back) together.

- **Step 1:** Stack the OLED FeatherWing on top of the RTC FeatherWing on top of the Feather microcontroller.

  - If any of those units arrived without their stacking headers, you will first need to solder the headers in place. [Here](https://www.makerspaces.com/how-to-solder/) is a nice soldering description and tutorial. The OLED screen is an Adafruit FeatherWing, a design specifically meant to be stacked on top of an Adafruit Feather microcontroller, such as the Bluefruit nRF52832 which we are using here (note that there are many microcontrollers that use the Feather form factor and they are almost interchangeable; only a few minor changes need to be made in the setup of the Arduino software and possibly firmware). Adafruit also makes FeatherWing "doublers" and "triplers" which are designed to do the same thing (electronically speaking) as stacking Feathers/FeatherWings on top of each other but with a side-by-side layout.

- **Step 2:** Choose the sensor communication protocol that you will use to get the rangefinder's data from the rangefinder to the microcontroller and wire the sensor to the microcontroller accordingly.

  - Options include UART, PWM, and analog, according to the datasheet. If you want to read more about UART, PWM, analog inputs, and other common microcontroller communication techniques, Arduino has a great primer on analog and digital pin functionality [here](https://www.arduino.cc/en/Tutorial/Foundations). We chose analog for its simplicity though it may sacrifice some accuracy and precision depending on other factors that we won't get into here.

  - By using analog for data transmission, we were able to connect just three things: power (3.3 V output, sometimes written 3V3), ground (GND), and analog data. Maxbotix has a tutorial specifically for Arduino [here](https://www.maxbotix.com/Arduino-Ultrasonic-Sensors-085/) so we will refer you to that page for additional detail. Please see the firmware in this repository to determine which analog pin we used to connect to the sensor's analog output. Also note that we made direct wire connections between the microcontroller and sensor (i.e., we did not use a breadboard as is shown in the hyperlinked tutorial) by taking advantage of the FeatherWing's available prototyping thru holes. This decision has no impact on functionality but makes the final assembly much more compact and, hopefully, more robust (breadboard connections tend to work reasonably well on a bench/desk top but are not well suited for environmental deployments!).

- **Step 3:** Assemble the housing. **MORE DETAIL NEEDED HERE ONCE HOUSING IS FINALIZED!**

- **Step 4:** Calibrate the sensor package.

  - Generally speaking, it is better to calibrate a sensor once it is fully assembled than prior to assembling it because many sensors can be interfered with by other parts of an assembly. For instance, what if this rangefinder was somehow picking up a part of the assembled housing and giving a reading that reflected its detection of the housing instead of its detection of the water surface? Or what if you calibrated a temperature sensor before assembling it with the rest of the parts and then found out that some other part of the package was actually producing heat and thereby altering the temperature reading? Hopefully you will be able to assemble your instruments in ways that circumvent any such problems but it is wise to keep these potential issues in mind and calibrate or recalibrate your instrument once it is in its final form factor. Please see the following section for details on calibration if you are going to (re)calibrate your monitor.

- **Step 5:** Apply the new calibration coefficients in the firmware and recompile and flash the code.

  - See the `Firmware` folder and `firmware_getting_started.md` files therein for more information if you intend to alter or learn more about the sensor's firmware.

- **Step 6:** Deploy the sensor!

  - Please see the Deployment section above for more information.

### Calibration
It is never wise to trust that any sensor will work perfectly out of the box* and a good scientist or engineer (professional or otherwise) would be well served by checking the sensor's accuracy (and improving it, if possible). It is sometimes the case that a sensor manufacturer has very sophisticated calibration equipment and, especially if they provide the calibration data for your instrument, their technique may be hard to replicate for yourself. But, alternatively, sometimes manufacturers do not calibrate every individual instrument and/or their techniques and equipment aren't sufficient for your needs, so you must do it yourself.

The simplest form of (re)calibration or data correction is a simple "offset" adjustment. A good example of this would be if you used this rangefinder to make a measurement where the sensor reported 0" but you knew that the true distance was actually 4". In this case, the offset you should apply would be 4". In other words, you would add 4" to every reading that the sensor provided. (This is only an example; this sensor is not meant for measuring distances ≤ 6" so all measurements from 0 – 6" are considered to be inaccurate, regardless of calibration!!!)

In some cases, there can also be a "gain" correction. A gain correction is the same thing as applying a slope to a line and an offset correction is the same as adding an intercept to a line. Following the same example as above where we already know that the offset is 4", now imagine that when the sensor reads 100", the correct actual distance is 124 inches. The offset of 4 inches doesn't get us close to the difference between 100" and 124". For this simple example (see below for directions for a more comprehensive approach), we can calculate a gain of 1.2. First, subtract the offset from the correct answer: 

$(124^"  –  4^" = 120^")$ 

and then divide by the reported value: 

$(120^" ÷ 100^" = 1.2)$. 

In reverse, we would say that *actual = measured × gain + offset*. Example: 

$(124^" = 100^" × 1.2 + 4^")$.

In order to calculate the gain and offset correction factors for a linear correction such as the one we described here, we would want to collect as many sensor measurements as possible over the sensor's full range (in this case, 6 – 254 inches) as well as make measurements of the "true" value at each of the sensor measurement points. We would then make a plot where sensor value would go on the x-axis and the "true" value would go on the y-axis. We would then use linear regression to calculate the slope (gain) and intercept (offset) of the line and we would apply those values to all future sensor measurements. Note that we put "true" inside quotes because it is extraordinarily difficult to know exactly what the true value is. How will you go about making estimates of the true values against which to compare your sensor measurements? A tape measure? A ruler? A string with distance markings on it? Another electronic distance sensor? How do you know that those measurements are accurate? Who calibrated those instruments and how did they do it???

 - It is also important to recognize that this simple linear calibration technique does not work for all sensors. Sometimes a more appropriate correction equation could use a quadratic equation or an exponential one or perhaps something with an even more bizarre form. But we'll assume that we can use a linear recalibration or correction for this project because it seems to make meaningful improvements in sensor performance without adding too much complexity to the procedure.
