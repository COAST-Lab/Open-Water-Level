[![DOI](https://zenodo.org/badge/243609204.svg)](https://zenodo.org/badge/latestdoi/243609204)

# Open Water Level Sensor

## Table of Contents 

- [Introduction](#Introduction)
- [Datasheets](#Datasheets) 
- [Deployment](#Deployment)
- [Sensor components/bill of materials](Fabrication/BOM)  
- [Sensor housing](Fabrication/Enclosure%20and%20Assembly)

- [Calibration](#Calibration)

## About
This GitHub repository is intended to serve as supplementary information to a manuscript in the journal Oceanography, in the special section DIY (do-it-yourself) Oceanography. 

The article, *A Low-Cost, DIY Ultrasonic Water Level Sensor for Education, Citizen Science, and Research*, can be found here: [https://doi.org/10.5670/oceanog.2023.101](https://doi.org/10.5670/oceanog.2023.101). This article corresponds to an older version of the code which can be found here: [https://github.com/SUPScientist/Seaport_Tide-SLR](https://github.com/SUPScientist/Seaport_Tide-SLR). 

That manuscript contains additional important information beyond what is in this repository. Please read the following for a high-level overview of the project and the contents of this repository.

(insert picture)

## Introduction
Several versions of the DIY water level sensor include different microcontrollers and sensor interfacing options (analog, serial, and pulse-width modulation). 

If you are looking for a cellular data transmission-enabled device with higher resolution, see [Firmware/SLR_Boron_Maxbotix_MB7092_cm](Firmware/SLR_Boron_Maxbotix_MB7092_cm) and to get started on soldering and building your sensor package, click here [Firmware](Firmware).

This project comprises a low-cost open-sourced sensor package designed to measure distance and either transmit or store measurements.  It utilizes an Arduino-based Adafruit Adalogger with a Particle Boron with cellular data transfer a Maxbotix ultrasonic rangefinder, a rechargeable lithium-ion battery, and either upcycled plastic parts or an off-the-shelf water-resistant enclosure. 

This repository aims to enable citizen scientists, businesses, and anyone motivated to monitor their local sea level. To get started read through this page and subsequent directions. 

## How to get your sensor
Link to costs and instructions
[BOM](BOM)

## Datasheets
Link to  the data sheets of each part in the sensor package
[Datasheets](Datasheets)

## The Fun Stuff
### Deployment
Deployment is the last step but it's probably the most exciting, so we'll start our procedural notes here. The Seaport Tide and Sea Level Rise Monitor has a ~ 6.5 m (21') range with a 1 cm (0.39") resolution. Deployment locations must be chosen with these values in mind. If you are deploying the monitor at a location reasonably close to an existing NOAA tide station, start by examining the known tidal range at your location: [NOAA tide predictions](https://tidesandcurrents.noaa.gov/tide_predictions.html). You will want to deploy the monitor at a location where it can aim straight down to the water's surface and at a height that is slightly higher than the highest high tide that the location is expected to experience. As described above, the package is currently not designed to be waterproof so it should not be deployed in extreme weather events unless it is modified.

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
