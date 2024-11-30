[![DOI](https://zenodo.org/badge/243609204.svg)](https://zenodo.org/badge/latestdoi/243609204)

# Open Water Level Sensor
## ℹ️ About this Repository
This GitHub repository provides updated designs for a low-cost, open-source, water level sensor. This branch specifically focuses on utilizing the sensor for educational purposes, in a classroom setting with minimal deployment.

Please read the following for a high-level overview of the project and the contents of this repository.

## 🔮 Table of Contents 
Scroll down or click the following links for more information: 
- [Introduction to the Sensor](#-introduction-to-the-sensor)
- [How to Build a Sensor](#-how-to-build-a-sensor)
- [Firmware and getting started guide](Firmware)
- [Deployment Considerations](#-Deployment-considerations)
- [Data Analysis](#-example-data-analysis-routine)

![Water level sensor](Photos/SMCKERR_WL_WL01.jpeg)

## 🔌 Introduction to the Sensor
There are several versions of the DIY water level sensor. They include different microcontrollers (e.g., an Arduino-based Feather Adalogger with internal logging capabilities and a Particle Boron with cellular communication capabilities) and sensor interfacing options (analog, serial, and pulse-width modulation). 

If you are looking for a low-cost sensor for educational purposes, this is the repository for you. Alternatively, if you are looking for a cellular data transmission-enabled device with higher resolution, see [https://github.com/COAST-Lab/Open-Water-Level](https://github.com/COAST-Lab/Open-Water-Level). If you are looking for the original, less expensive Arduino version with internal datalogging capabilities, see [https://github.com/SUPScientist/Seaport_Tide-SLR](https://github.com/SUPScientist/Seaport_Tide-SLR).

The device designs in this repository comprise a low-cost open-sourced sensor package designed to measure distance and transmit and store measurements, with an added OLED display for displaying real-time measurements. It utilizes a Adafruit ESP32-S3, an Adafruit Adalogger Featherwing for local data storage, an Adafruit Featherwing OLED, a Maxbotix ultrasonic rangefinder, a solar panel with battery, and an enclosure. It also uses several purpose-made parts, such as an Featherwing tripler PCB, an adapter PCB, a custom PolyCase, and the necessary cables and connectors.

This repository focuses specifically on utilizing this sensor for educational purposes, and is simplified compared to the other designs. As such, soldering and knowledge of wiring is reduced to a minimum in favor of purpose-built parts.

## 🔨 How to Build a Sensor
The parts needed for this sensor and instructions can be found below:
- Getting started with the code: [Firmware](Firmware) 
- *Update with links to parts once available*

## 🌊 Deployment Considerations
Deployment is the last step but it's probably the most exciting, so we'll start our procedural notes here. The Open Water Level sensor has a ~ 6.5 m (21') range with a 1 cm (0.39") resolution. Deployment locations must be chosen with these values in mind. If you are deploying the monitor at a location reasonably close to an existing NOAA tide station, start by examining the known tidal range at your location: [NOAA tide predictions](https://tidesandcurrents.noaa.gov/tide_predictions.html). You will want to deploy the monitor at a location where it can aim straight down (normal) to the water's surface and at a height slightly higher than the highest high tide or floodwater height that the location is expected to experience. You also want it to be low enough to capture the lowest low water. The package is water resistant, but not fully waterproof if submerged for extended periods.

## 💻 Example Data Analysis Routine
Please see this [example notebook](Data%20Analysis/open_water_level_analysis.ipynb) for Python code that reads in, parses, and plots water level data, including the critical conversion of `distance from the sensor to the water` to a `referenced water level`.
