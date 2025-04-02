Once you have successfully fabricated the **PVC Model** based on these [steps](https://github.com/COAST-Lab/Open-Water-Level/tree/ac8e949a22b2f5b2a5e1ccd7503b6fde46d579b2/Fabrication/PVC-Enclosure), follow this guide for deployment. Extra supplies needed for these steps are PVC cement, Silicon Sealant, Low Density PTFE seal tape, and O-Ring Silicon Grease.
1. Ensure that the extra LiPo battery and Solar system battery are fully charged.
2. Verify that the correct code and firmware is flashed onto your Boron.
3. We recommend including electrical tape to secure the antenna and 3 pin wires to the side of the chassis. This will help decrease any noise and movement within the PVC during deployment. 
4.Use PVC cement to securely bond the PVC Reducer Bushing, PVC Coupler, and PVC Pipe. Follow the manufacturer's guidelines on the PVC cement packaging for best results. **Safety Note:** Always use PVC cement in a well-ventilated area, preferably outdoors, and wear protective gloves. After cementing, place the assembled product in a fume hood to minimize exposure to fumes.
5. Apply O-ring grease to the O-rings on the PVC end cap and cable gland. **Note:** Before greasing, ensure the O-rings and grooves are completely free of dust and other particles. We recommend using Kimwipes and gloves to clean the rings and grooves thoroughly. Additionally, place Kimwipes on your work surface to keep the components clean during the process.
6.Wrap PTFE seal tape around the threads of the Maxsonar. **Note:** Apply the tape in the same direction as the threading to ensure it remains securely in place when tightened into the PVC bushing, preventing it from unraveling.
7. Once fully charged, place the lipo battery back on the chassis, attach the 3-pin wires together, and slide the chassis into the PVC pipe. 
8. Attach the solar cable gland to the PVC end cap. **Note:** Once the Lipo battery or solar panel cable is plugged into the Boron it will turn on and begin collecting data every hour on the hour. This may be important for your cellular usage. 
9. Once all components are securely placed and connected inside the pipe, attach the PVC cap. Apply silicone sealant to seal the gap between the PVC end cap and the pipe, as well as the space between the solar cable gland and the PVC top.

**Field Specific Deployment Considerations**

According to the ultrasonic sensor's datasheet, objects within a 30 cm radius of a beam normal to the sensor's surface could interfere with its measurements. We recommend deploying the sensor at least **45 cm (or a 50% margin)** away from the closest object to the sensor's downward beam. Also condifer that this sensor has a minimum report distance of **25 cm** and a maximum report distance of **700 cm**. 
