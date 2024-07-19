We're working on this page! Come back soon for complete step-by-step assembly instructions.

# How to assemble a DIY Open Water Level Sensor with a Polycase enclosure

See:
- BOM, for bills of materials / lists of parts
- Datasheets, for manufacturer datasheets
- Enclosure and Assembly, for 3D print files

## Assembling the chassis
Parts:
- Boron 404X
- Adalogger FeatherWing
- MicroSD card
- Short stacking header pins
- 3D printed custom chassis + M2.5x0.45 screws/hex nuts
- Cellular antenna
- 3-pin cable
- Solar system
- MicroUSB connector

1. Solder the 3-pin cable female receptacle onto the FeatherWing spare pins corresponding to the power, ground, and analog inputs.
`INSERT PHOTOS`

2. Place the stacking header pins through the pin holes of the Adalogger FeatherWing (make sure the short and long pins and pin holes are aligned); solder.

<img src="Photos/AdaFeather_Pins.jpeg" width="200">

3. Place the Boron 404X atop the Adalogger FeatherWing so the Boron pins fit into the stacking header holes; solder.
4. Gently press the microSD card into the Adalogger FeatherWing until it clicks into place.

<img src="Photos/Install_SD.jpeg" width="200">

5. Lay the soldered Boron 404X, Adalogger FeatherWing, and header pin device (hereby referred to as the BAda) atop the chassis so that the ...
- pins fit in the rectangular slots
- four holes in the BAda corners align with the four small holes in the chassis
Make sure the microUSB port and 3-pin cable of the BAda are facing the end of the chassis with more lengthwise space; this is to ensure that cables aren't bent too much within the enclosure.

<img src="Photos/PolycaseChassis_Simplified.jpeg" width="200">

- Make sure the microUSB port and 3-pin cable of the BAda are facing the end of the chassis with more lengthwise space; this is to ensure that cables aren't bent too much within the enclosure.

6. Screw the BAda to the chassis using the M2x0.45 18mm screws. Screw M2.5x0.45mm threaded 2mm length hex nuts to the screws on the underside of the chassis.
- Be cautious not to move too quickly or harshly, as you can strip the screw / hex nut, or crack the chassis!

<img src="Photos/PolycaseChassis_Screws_Nuts.jpg" width="200">
<img src="Photos/PolycaseChassis_Boron_Attached.jpeg" width="200">
<img src="Photos/PolycaseChassis_Nuts_Under.jpg" width="200">


7. Carefully peel the sticker backing off of the cellular antenna and gently stick the antenna to the outside of the antenna frame on the chassis.
8. Attach the antenna to the BAda.

<img src="Photos/PolycaseChassis_Boron_Antenna.jpg" width="200">

9. Solder the to microUSB connector to the red solar cable.
10. Plug the solar cable into the microUSB port on the Boron 404X.

<img src="Photos/PolycaseChassis_Boron_SolarCable.jpg" width="200">


## Assembling the Polycase enclosure
Parts:
- Polycase ML-24K + screws (included)
- Hi-Lo #4-24 screws
- Maxbotix Ultrasonic Rangefinder
- Solar system
- Epoxy
- Assembled chassis with electronics

1. Cut a hole into of the Polycase lid.
2. Thread the 3-pin cable through the hole in the Polycase lid.
3. Solder the 3-pin cable male block onto the ultrasonic distance sensor on pins corresponding to the power, ground, and analog outputs.
4. Drill a 9/64” hole `INSERT LOCATION` in Polycase for the solar panel cable (red cable); thread the solar cable through this hole.
5. Screw the chassis with attached electronics into the Polycase using the Hi-Lo screws.
6. Screw the ultrasonic distance sensor into the Polycase lid hole.
7. Carefully fit all cords into the Polycase enclosure.
8. Use marine epoxy to seal the solar cable in place.
    - Note: Practice caution when using marine epoxy and let it rest for at least 2 hours to cure.
9. Place the Polycase lid on the enclosure and use the included screws to assemble the enclosure.

<img src="Photos/Polycase_EnclosureScrews.jpg" width="200">
<img src="Photos/Polycase_EnclosureScrews2.jpeg" width="200">