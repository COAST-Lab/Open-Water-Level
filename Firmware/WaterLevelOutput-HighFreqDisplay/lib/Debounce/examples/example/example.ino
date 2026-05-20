#include "Debounce.h"

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