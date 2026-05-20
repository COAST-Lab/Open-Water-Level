DEBOUNCE
=====================

Debounce is a [debouncing](http://en.wikipedia.org/wiki/Debounce#Contact_bounce) library for [Particle](http://particle.io). Debounce is based on [Bounce2](https://github.com/thomasfredericks/Bounce2) orginally written by Thomas Ouellet Fredericks with contributions from: Eric Lowry, Jim Schimpf and Tom Harkaway. Debounce was modified for Particle by David Washington.

EXAMPLE
====================
````
#include "Debounce/Debounce.h"

Debounce debouncer = Debounce(); 

void setup() {
    pinMode(D7, OUTPUT);
    debouncer.attach(D0, INPUT_PULLUP);
    debouncer.interval(20); // interval in ms
}

void loop() {
    debouncer.update();

     if (debouncer.read() == LOW) {
         digitalWrite(D7, HIGH);
     } else {
         digitalWrite(D7, LOW);
     }
}
````

METHODS
====================

## Debounce()

Instantiates a Debounce object.

## void interval(unsigned long interval) 

Sets the debounce time in milliseconds.

## void attach(int pin) 

Sets the pin and matches the internal state to that of the pin. Only attach the pin once you have done setting the pin up (for example setting an internal pull-up).

## bool update()

Because Debounce does not use interrupts, you have to "update" the object before reading its value and it has to be done as often as possible (that means to include it in your loop()). The update() method updates the object and returns true (1) if the pin state changed. False (0) if not. Only call update() once per loop().

## bool read()

Reads the updated pin state.

## bool fell()

Returns true if pin signal transitions from high to low. 

## bool rose()

Returns true if signal transitions from low to high.


DEBOUNCE ALGORITHMS 
====================

## Stable interval

By default, the Bounce library uses a stable interval to process the debouncing. This is simpler to understand and can cancel unwanted noise.

![](https://raw.github.com/thomasfredericks/Bounce-Arduino-Wiring/master/BouncySwitch_stable.png)

## Lock-out interval

By defining "#define BOUNCE_LOCK_OUT" in "Bounce.h" you can activate the alternative debouncing method. This method is a lot more responsive, but does not cancel noise.

![](https://raw.github.com/thomasfredericks/Bounce-Arduino-Wiring/master/BouncySwitch_lockout.png)


