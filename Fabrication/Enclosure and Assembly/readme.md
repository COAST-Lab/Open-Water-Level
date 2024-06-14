# How to assemble an Open Water Level sensor
## Rough draft
- [ ] Chop 1.5” sch-40 PVC into 8” sections
- [ ] Drill 9/64” hole 5 cm from top of PVC for solar panel cable (red cable)
- [ ] 3D print top end cap; sand
** Is this the new red screw-in end cap?
- [ ] 3D print bottom end cap; sand
- [ ] Re-tap NPT threads (take care not to use too much force as it can crack the brittle end caps)
** Do we need to include more detail for this step? or is this something we assume users will know how to do?
- [ ] Cut solar panel cable terminator
** Do we need to include more detail for this step? or is this something we assume users will know how to do?
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
** I don't think this step is necessary anymore?
- [ ] If end caps are sanded enough to slide onto PVC all the way, epoxy in place. Allow to fully dry/cure.
** I think this step should be changed to account for cable gland, not epoxy, correct?
- [ ] Epoxy solar panel cable in place
** I think this step should be changed to account for cable gland, not epoxy, correct?
- [ ] Thread distance sensor into bottom end cap with pipe tape around sensor threads (3 wraps in proper direction)
** Do we need to include more detail for this step? or is this something we assume users will know how to do?
- [ ] Connect 3-pin cables for distance sensor through inside of PVC
** This step should be changed to account for chassis (e.g. thread through semi-cylinder chassis)
- [ ] Insert remaining electronics
** This step should be deleted, correct? Since all parts will be connected to chassis?
- [ ] Plug battery into Boron
** Is this step still relevant?
- [ ] Plug solar panel cable with newly terminated microUSB plug into Boron USB port
- [ ] Plug top end cap with PVC pipe plug
** Is this step still relevant with the new end cap?
- [ ] Screw solar panel onto top end cap (4-40 screws)
** Are these the correct fabrications considering the new solar panel / battery?