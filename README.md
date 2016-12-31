# Gadget-Speed-Radar
Measure and output speed of objects using the HB100. Tested two iterations of amps for amplifying and conditioning the HB100 signal.

## Iteration 1
An amp based on the design suggested in the application note p.5 (http://www.limpkin.fr/public/HB100/HB100_Microwave_Sensor_Application_Note.pdf) with the addition of an op-amp comparator to generate a square wave signal that a MCU like an Arduino easily can detect. The schema is available in `hardware/rev1`.

This design showed usable range of detecting moving persons in walking speeds up to 10 meters and could provide reasonable speed measurement of moving persons within 2 meters. The design was bad at detecting moving cars within 5-10 meters at speeds less than 10km/h and could not reliably detect cars at higher speeds in the same range, the design could not provide any reasonable speed measurements of cars at either speeds.

This design is usable only for detecting moving persons up to 10 meters or to measure speed of walking persons within 2 meters. Modifiying capacitor values to provide different filtering to be able to detect higher speeds created to much noise so I moved on to a different design. 

## Iteration 2
This iteration was based on the design of Limpkin (http://www.limpkin.fr/index.php?post/2013/08/09/Making-the-electronics-for-a-%247-USD-doppler-motion-sensor) which sells a breakout board for the HB100 at Tindie (https://www.tindie.com/products/limpkin/hb100-doppler-speed-sensor-arduino-compatible/), thanks Limpkin for your thourough explanation of the circuit and answers to question about the hb100 and more! 

I modified Limpkins design with different capacitor values with the goal of a band pass between 3Hz to 2500Hz but came a bit short of that. I could only modify the first opamp's filter to get close to this range. The schema is available in `hardware/rev2`. I have not simulated the final band pass but practically it shows some improvements.

This design showed a similar usable range of detecting moving persons in walking speeds up to 10 meters but could provide reasonable speed measurement of moving persons within 5 meters. I would guess this is true for the original filters as well if not better. 

The design detects moving cars reliably in the tests I have done up to around 70km/h, unfortunately I have yet to test the detection of highway speeds. I would not trust the design for speed measurements but the measured speeds are at least more reasonable than before.

A slight drawback for this design is that it is more susceptible for noise with the wider band pass. I have seen brief noise in a few ms around 2kHz indoors for example. This could potentially be fixed by adding an increased hysteres to the comparator, which I have yet to experiment with. 

This design is usable for detecting moving persons up to 10 meters or to measure speed of walking persons within 5 meters. It can detect moving cars in the same range at speeds upto and possibly beyond 70km/h, it can not measure car speeds reliably. 

I would also want to point out that the original design by Limpkin most likely can't reasonably measure car speeds above walking speeds, it seems quite unlikely with the results I have seen. However it is for sure good enough for the applications he states.

## Can I use an HB100 to measure normal car speeds reasonably?
I don't think so, the range is just too short to get a stable reading of a fast car and it seems higher speeds get attenuated by the HB100. But if you have, please reach out to mik4el.4ndersson@gmail.com, I'd love to learn more!

## Test setup
I put together an Arduino Nano to measure the output from the amp and display it on a I2C LCD so I could test this in the field. This was powered from a usb battery pack.
