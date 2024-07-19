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

Using epoxy, carefully glue four M2x0.4mm 1.6mm length hex nuts in the four hexagonal holes of the chassis. Let dry / cure fully.
    <img src="Photos/PVC_Chassis_Screws_Nuts.jpg" width="400">

Solder microUSB connector to solar cable with shrink tubing over the bare wire.

Stack short stacking header pins onto Adalogger FeatherWing; solder.
    <img src="Photos/AdaFeather_Pins.jpeg" width="400">

Update Boron 404X system firmware to match current firmware as shown in the Firmware/target directory.
    <img src="Photos/BRN404X.jpeg" width="400">

Insert microSD card into FeatherWing microSD port. (microSD card may need to be manually formatted by inserting it into your computer first.)
    <img src="Photos/Install_SD.jpeg" width="400">

Stack Boron 404X on FeatherWing; solder.
    `INSERT PHOTO?`

Place the Boron/FeatherWing/pins device atop the chassis so that the ...
- ... pins sit in the rectangular slots without touching anything
- ... screw holes in the Boron and FeatherWing line up with the four screw holes in the chassis
    <img src="Photos/PVC_Chassis.jpeg" width="300"> <img src="Photos/PVC_Chassis2.jpeg" width="300">
    <img src="Photos/" width="400">

Attach cellular antenna cable to Boron 404X.
    <img src="Photos/PVC_Chassis_Boron_Antenna.jpg" width="400">

Peel off sticker backing on cellular antenna cable and gently stick to flat underside of chassis.
    <img src="Photos/PVC_Chassis_Antenna.jpg" width="400">

Solder 3-pin cable with female receptacle onto FeatherWing spare pins corresponding to the power, ground, and analog inputs.
    `INSERT PHOTO?`

Solder 3-pin cable with male block onto ultrasonic distance sensor on pins corresponding to the power, ground, and analog outputs.
    `INSERT PHOTO?`

`CONT'D ... NEEDS UPDATING`

## Assembling the PVC enclosure
Parts:
- 1.5” sch-40 330 psi PVC
- Maxbotix Ultrasonic Rangefinder
- 1.5" gripper end cap (red)
- 3D printed end cap
- Solar system
- Epoxy
- Assembled chassis with electronics
- Pipe tape (?)

1. Chop 1.5" sch-40 PVC into 8" sections.
2. Drill a 9/64" hole 5cm from top of an 8" PVC section (this hole will be for solar panel cable).
3. 3D print bottom end cap; sand.
4. Carefully re-tap NPT threads in bottom end cap (take care not to use too much force, as this can crack the brittle 3D printed cap)
5. Cut the solar panel cable terminator.
6. Pass solar cable (red cable) through 9/64" hole drilled in step 2. Take care to give enough slack inside to make the connection/solder to microUSB connector, and enough outside to be able to maneuver the solar panel cable terminator.
7. Attach solar cable to Boron; slide chassis and electronics into PVC pipe.
<img src="Photos/PVC_Chassis_Boron_SolarCable.jpg" width="400">

7. Seal solar cable entry with epoxy; let dry/cure fully.
8. Slide end caps onto PVC fully; seal in place with epoxy; let dry/cure fully.
    `INSERT PHOTO`
9. Thread ultrasonic distance into bottom end cap, wrapping pipe tape around sensor threads (3 wraps in proper direction).
    `CLARIFY PROPER DIRECTION?`
    `INSERT PHOTO`
10. CONT'D ... NEEDS UPDATING


# Instructions: Rough Draft
- [ ] Chop 1.5” sch-40 PVC into 8” sections
- [ ] Drill 9/64” hole 5 cm from top of PVC for solar panel cable (red cable)
- [ ] 3D print top end cap; sand
`Is this the new red screw-in end cap?`
- [ ] 3D print bottom end cap; sand
- [ ] Re-tap NPT threads (take care not to use too much force as it can crack the brittle end caps)
`Do we need to include more detail for this step? or is this something we assume users will know how to do?`
- [ ] Cut solar panel cable terminator
`Do we need to include more detail for this step? or is this something we assume users will know how to do?`
- [ ] Pass solar cable into PVC, taking care to give enough slack inside to make connection/solder to microUSB connector and enough outside to be able to maneuver solar panel onto top end cap
- [ ] Solder microUSB connector to solar cable with shrink tubing over bare wire
- [ ] Solder stacking headers onto adalogger featherwing
- [ ] Update system firmware on Boron to match current firmware as shown in Firmware/target directory
- [ ] Insert microSD card into featherwing (microSD card may need to be manually formatted by inserting it into your computer first)
- [ ] Stack Boron on FeatherWing
- [ ] Attach cellular antenna onto Boron
- [ ] Solder 3-pin cable with female receptacle onto FeatherWing spare pins corresponding to tbe power, ground, and analog inputs
- [ ] Solder 3-pin cable with male block onto ultrasonic distance sensor on pins corresponding to the power, ground, and analog outputs
- [ ] Drill holes in top end cap for solar mounting screws (nb: change end cap design so that drilling isn't necessary)
`I don't think this step is necessary anymore?`
- [ ] If end caps are sanded enough to slide onto PVC all the way, epoxy in place. Allow to fully dry/cure.
`I think this step should be changed to account for cable gland, not epoxy, correct?`
- [ ] Epoxy solar panel cable in place
`I think this step should be changed to account for cable gland, not epoxy, correct?`
- [ ] Thread distance sensor into bottom end cap with pipe tape around sensor threads (3 wraps in proper direction)
`Do we need to include more detail for this step? or is this something we assume users will know how to do?`
- [ ] Connect 3-pin cables for distance sensor through inside of PVC
`This step should be changed to account for chassis (e.g. thread through semi-cylinder chassis)`
- [ ] Insert remaining electronics
`This step should be deleted, correct? Since all parts will be connected to chassis?`
- [ ] Plug battery into Boron
`Is this step still relevant?`
- [ ] Plug solar panel cable with newly terminated microUSB plug into Boron USB port
- [ ] Plug top end cap with PVC pipe plug
`Is this step still relevant with the new end cap?`
- [ ] Screw solar panel onto top end cap (4-40 screws)
`Are these the correct fabrications considering the new solar panel / battery?`