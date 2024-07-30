We're working on this page!
Come back soon for accurate step-by-step assembly instructions.

# How to assemble a DIY Open Water Level Sensor with a PVC enclosure
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
- 1.5” sch-40 330 psi PVC
- 3D printed custom chassis
- M2x0.4mm threaded 16mm screws
- M2x0.4mm 1.6mm hex nuts
- Cellular antenna
- Maxbotix Ultrasonic Rangefinder
- 3-pin cable
- Solar system
- USB A to Micro-B cable
- 1.5" gripper
- Pipe bushing
- Pipe coupling
- Pipe tape
- Epoxy

# Fabricating electronics to prepare for firmware update
1. Place the stacking header pins through the pin holes of the Adalogger FeatherWing; solder.

<img src="Photos/AdaFeather_Pins.jpeg" width="300">

2. Place the Boron 404X atop the Adalogger FeatherWing so the Boron pins fit into the stacking header holes. (The assembled Boron 404X, Adalogger FeatherWing, and stacking header pins will hereby referred to as the BAda.)

<img src="Photos/BAda_Separate.jpeg" width="200"> <img src="Photos/BRN404X.jpeg" width="200"> <img src="Photos/BAda_Stack.jpeg" width="150">

3. Gently press the microSD card into the Adalogger FeatherWing until it clicks into place.

<img src="Photos/Install_SD.jpeg" width="300">

4. Using the USB A to Micro-B cable and your computer, udate the Boron's system firmware using the steps listed in the `Firmware` directory.

# Fabrication of electronics with enclosure

*Note: Start by taking the Boron off the Adalogger FeatherWing for ease.*

1. Using epoxy, carefully glue four M2x0.4mm 1.6mm length hex nuts in the four hexagonal holes of the chassis. Let dry / cure fully.

<img src="Photos/PVC_Chassis_Screws_Nuts.jpg" width="300">

Optional: Twist the 3-pin cables (insert into a drill bit and spin slowly). Use shrink tubing to cover the cables.

2. Solder the 3-pin cable female receptacle onto the FeatherWing spare pins corresponding to the power, ground, and analog inputs.

<img src="Photos/Solder_3pin_FeatherWing.jpg" width="300">

3. Solder the 3-pin cable male block onto the ultrasonic distance sensor on pins corresponding to the power, ground, and analog outputs.

<img src="Photos/Soldering_3pin_Sensor.jpeg" width="400">

4. Using M2x0.4mm screws, attach the BAda atop the chassis so that ...
- ... the soldered header pins rest in the rectangular slots without touching anything
- ... the screw holes in the Boron and FeatherWing line up with the four hex nuts in the chassis

<img src="Photos/PVC_Chassis.jpeg" width="300"> <img src="Photos/PVC_Chassis_Attached.jpg" width="200">

5. Attach cellular antenna cable to Boron 404X.

<img src="Photos/PVC_Chassis_Boron_Antenna.jpg" width="200">

6. Peel sticker backing off of cellular antenna and gently stick to flat underside of chassis.

<img src="Photos/PVC_Chassis_Antenna.jpg" width="300">

7. Chop 1.5" sch-40 PVC into an 8" section.

8. Drill a 9/64" hole 5cm from top of an 8" PVC section (this hole will be for solar panel cable).

9. Cut the female 5V 2A connector off of the solar cable and feed it through the 9/64" hole so the stripped end is inside the PVC pipe.
 
10. Cut the USB A connector of the USB A to Micro-B cable and strip the end.

11. Solder the +5V wires and GND wires of the USB and solar cables together. (Can use shrink tubing to keep red and black internal wires separate). Cover this connection with shrink tubing / electrical tape / your preference.

12. Plug the Micro-B connector into the Boron's Micro-B port.

<img src="Photos/PVC_Chassis_Boron_SolarCable.jpg" width="250">

13. Wrap the ultrasonic distance sensor's threads with pipe tape; gently screw the distance sensor into pipe bushing.

14. Using the pipe coupling, connect the pipe bushing (with distance sensor) and the PVC pipe. Make sure you connect the white cap ends of the 3-pin cables inside the enclosure.

15. Seal the opposite PVC end with the 1.5" gripper.

16. Seal the solar cable entry hole with marine epoxy to prevent water damage.