Adafruit_mfGFX Library
====================== 

Multifont GFX library is adapted from Adafruit_GFX library by Paul Kourany

- v1.0.0, May 2014 Initial Release
- v1.0.1, June 2014 Font Compilation update
- v1.0.2, Aug 2015 Added charWidth(char) function to return char width in pixels
- v1.0.3, Jan 2016 update to Libraries V2.0
- V1.0.4 Jan 2020 Move swap() definition from .h to .cpp file

This library supports any compatible Adafruit_GFX display driver. The 
free TheDotFactory Windows program is recommended for creating font data 
compatible with the Adafruit_mfGFX library. 

Please see the HOWTO.pdf file for instructions on creating and adding 
new fonts. The base library comes with 4 fonts and a "test" font so a 
new candidate font data can easily be added and tested before being 
permanently added to the library. 

Base library fonts may be added/removed using compile flags. BE AWARE 
that though font data does not take up Spark RAM, they do however take 
up flash space so having too many fonts may prove problematic. 

The GLCDFONT from original GFX library is included and made the default 
font so code based on the older library will work as expected. 

