[![DOI](https://zenodo.org/badge/243609204.svg)](https://zenodo.org/badge/latestdoi/243609204)

# Open Water Level Sensor
## ℹ️ About this Repository
This GitHub repository provides updated designs for a low-cost, open-source, cell-equipped water level sensor. The initial design, published in the journal Oceanography in the special section DIY (do-it-yourself) Oceanography, used a lower resolution sensor and had internal datalogging capabilities. In this repo, we describe how to use a higher resolution sensor with a cellular modem for near-real-time water level information. 

The article, *A Low-Cost, DIY Ultrasonic Water Level Sensor for Education, Citizen Science, and Research*, can be found here: [https://doi.org/10.5670/oceanog.2023.101](https://doi.org/10.5670/oceanog.2023.101). The article corresponds to an older version of the code which can be found here: [https://github.com/SUPScientist/Seaport_Tide-SLR](https://github.com/SUPScientist/Seaport_Tide-SLR).

Please read the following for a high-level overview of the project and the contents of this repository.

## Table of Contents 
Scroll down or click the following links for more information: 
- [Introduction to the Sensor](#-introduction-to-the-sensor)
- [How to Build a Sensor](#-how-to-build-a-sensor)
- [Firmware and getting started guide](Firmware)
- [Deployment Considerations](#-Deployment-considerations)
- [Data Analysis](#-example-data-analysis-routine)

![Water level sensor](Photos/SMCKERR_WL_WL01.jpeg)

## 🔌 Introduction to the Sensor
There are several versions of the DIY water level sensor. They include different microcontrollers (e.g., an Arduino-based Feather Adalogger with internal logging capabilities and a Particle Boron with cellular communication capabilities) and sensor interfacing options (analog, serial, and pulse-width modulation). 

If you are looking for a cellular data transmission-enabled device with higher resolution, this repository has what you need. To get started on soldering and building your sensor package, click here [Firmware](Firmware). If you are looking for the original, less expensive Arduino version with internal datalogging capabilities, see [https://github.com/SUPScientist/Seaport_Tide-SLR](https://github.com/SUPScientist/Seaport_Tide-SLR).

The device whose designs are in this repository comprises a low-cost open-sourced sensor package designed to measure distance and transmit and store measurements.  It utilizes a Particle Boron with cellular data transfer, an Adafruit Adalogger Featherwing for local data storage, a Maxbotix ultrasonic rangefinder, a rechargeable lithium-ion battery, and a water-resistant enclosure. 

This repository aims to enable students, communities, businesses, and anyone else to monitor their local water level. To get started, read through this page and subsequent directions. 

## 🔨 How to Build a Sensor
- Getting started with the code: [Firmware](Firmware) 
- Link to parts, suppliers, and costs: [BOM](Fabrication/BOM)
- Enclosure designs (improvements needed!): [Enclosure](Fabrication/Enclosure%20and%20Assembly)
- More information on parts: [Datasheets](Fabrication/Datasheets)

## 🌊 Deployment Considerations
Deployment is the last step but it's probably the most exciting, so we'll start our procedural notes here. The Open Water Level sensor has a ~ 6.5 m (21') range with a 1 cm (0.39") resolution. Deployment locations must be chosen with these values in mind. If you are deploying the monitor at a location reasonably close to an existing NOAA tide station, start by examining the known tidal range at your location: [NOAA tide predictions](https://tidesandcurrents.noaa.gov/tide_predictions.html). You will want to deploy the monitor at a location where it can aim straight down (normal) to the water's surface and at a height that is slightly higher than the highest high tide or floodwater height that the location is expected to experience. You also want it to be low enough that it can capture the lowest low water. The package is water resistant, but not fully waterproof if submerged for extended periods.

## 💻 Example Data Analysis Routine
Please see this [example notebook](Data%20Analysis/open_water_level_analysis.ipynb) for Python code that reads in, parses, and plots water level data, including the critical conversion of `distance from the sensor to the water` to a `referenced water level`.