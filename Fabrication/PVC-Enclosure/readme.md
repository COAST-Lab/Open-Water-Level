We're working on this page! Come back soon for complete step-by-step assembly instructions.

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
- 3D printed custom chassis
- M2x0.4mm threaded 16mm screws
- M2x0.4mm 1.6mm hex nuts
- Cellular antenna
- 3-pin cable
- Solar system
- MicroUSB connector
- O-rings
- Lithium Ion Battery Pack - 3.7V 4400mAh

1. Update Boron 404X system firmware to match current firmware as shown in the Firmware/target directory.

<img src="Photos/BRN404X.jpeg" width="200">

2. Using epoxy, carefully glue four M2x0.4mm 1.6mm length hex nuts in the four hexagonal holes of the chassis. Let dry / cure fully.

3. Solder microUSB connector to solar cable with shrink tubing over the bare wire.

4. Stack short stacking header pins onto Adalogger FeatherWing; solder.

<img src="Photos/AdaFeather_Pins.jpeg" width="300">

5. Insert microSD card into FeatherWing microSD port. (microSD card may need to be manually formatted by inserting it into your computer first.)

<img src="Photos/Install_SD.jpeg" width="300">

6. Solder 3-pin cable with female receptacle onto FeatherWing spare pins corresponding to the power, ground, and analog inputs.

7. Solder 3-pin cable with male block onto ultrasonic distance sensor on pins corresponding to the power, ground, and analog outputs.

8. Stack Boron 404X on FeatherWing; solder.

9. Place the soldered Boron/FeatherWing/pins atop the chassis so that the ...
- ... pins sit in the rectangular slots without touching anything
- ... screw holes in the Boron and FeatherWing line up with the four screw holes in the chassis

<img src="Photos/StackOnChasis.jpeg" width="300">

10. Attach cellular antenna cable to Boron 404X.

<img src="Photos/PVC_Chassis_Boron_Antenna.jpg" width="100">

11. Peel off sticker backing on cellular antenna cable and gently stick to flat underside of chassis.

<img src="Photos/PVC_Chassis_Antenna.jpg" width="300">
12. Attach the lithium battery to the slot under the Boron/FeatherWing stack.

13. Attach a zip tie to designated hook on the chasis. This will help with electronic removal from within the PVC pipe.

<img src="Photos/WholeElectronic.jpeg" width="300">



## Assembling the PVC enclosure
Parts:
- 1.5” sch-40 330 psi PVC
- PVC coupler
- PVC reducer
- Maxbotix Ultrasonic Rangefinder
- Solar system
- Silicon grease
- Silicon sealant
- PVC cement
- PVC pipe tape
- Assembled chassis with electronics
- 3D printed PVC Cap

1. Chop 1.5" sch-40 PVC into 8" sections.
2. Designate one side for the solar cable connection and one for the coupler and MaxSonar
3. The side you have designated for the solar cable connection slightly shave down the internal edge. 
4. On the PVC printed end cap attach the cable gland. Run the spliced solar cable through this cable gland.
5. Using silicon grease carefully place O-rings onto designated grooves on end cap. Be sure to wipe the o-rings and grooves with a Kim wipe to remove any particles or lint before adding grease.
6. Place cap, with o-rings and cable gland, onto desginated end.

  <img src="Photos/3dPVCcap.jpeg.jpeg" width="200">
8. Put coupler and PVC Reducer Bushing together
   
<img src="Photos/CouplerReducer.jpeg" width="200">
   
8. Wrap Maxsonar threads with PVC pipe tape (only usable for one entry and removal). Attach coupler/reducer part with MaxSonar.

<img src="Photos/MaxSonarEndCapSide.jpeg" width="200">
    
9. Attach solar cable to Boron; Attach 3 pin on stack to Maxsonar 3-pin. Connect 3-pin wire between Boron stack and Maxsonar; slide chassis and electronics into PVC pipe. 

<img src="Photos/SolarCable.jpeg" width="200">

10. Once everything is inside of the PVC pipe and you are ready for deployment, grab the silicon sealant and PVC cement.
    
11. Using silicon sealant, seal where the PVC 3D cap directly meets PVC pipe, seal around the cable gland o-ring too.

13. Lastly, using PVC cement, seal the space between the coupler and PVC pipe. 




