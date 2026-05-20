/*
  The MIT License (MIT)

  Copyright (c) 2013 thomasfredericks

  Permission is hereby granted, free of charge, to any person obtaining a copy of
  this software and associated documentation files (the "Software"), to deal in
  the Software without restriction, including without limitation the rights to
  use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
  the Software, and to permit persons to whom the Software is furnished to do so,
  subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
  FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
  COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
  IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/* * * * * * * * * * * * * * * * * * * * * * * * * * * *
  Modified for Particle by David Washington (@dwcares)
  Main code by Thomas O Fredericks (tof@t-o-f.info)
  Previous contributions by Eric Lowry, Jim Schimpf and Tom Harkaway
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Debounce.h"

#define DEBOUNCED_STATE 0
#define UNSTABLE_STATE  1
#define STATE_CHANGED   3


Debounce::Debounce()
    : previous_millis(0)
    , interval_millis(10)
    , state(0)
    , pin(0)
{}

void Debounce::attach(int pin) {
    this->pin = pin;
    state = 0;
    if (digitalRead(pin)) {
        state = _BV(DEBOUNCED_STATE) | _BV(UNSTABLE_STATE);
    }
#ifdef BOUNCE_LOCK_OUT
    previous_millis = 0;
#else
    previous_millis = millis();
#endif
}

void Debounce::attach(int pin, PinMode mode){
  pinMode(pin, mode);
  
  this->attach(pin);
}

void Debounce::interval(uint16_t interval_millis)
{
    this->interval_millis = interval_millis;
}

bool Debounce::update()
{
#ifdef BOUNCE_LOCK_OUT
    state &= ~_BV(STATE_CHANGED);
    // Ignore everything if we are locked out
    if (millis() - previous_millis >= interval_millis) {
        bool currentState = digitalRead(pin);
        if ((bool)(state & _BV(DEBOUNCED_STATE)) != currentState) {
            previous_millis = millis();
            state ^= _BV(DEBOUNCED_STATE);
            state |= _BV(STATE_CHANGED);
        }
    }
    return state & _BV(STATE_CHANGED);

#elif defined BOUNCE_WITH_PROMPT_DETECTION
    // Read the state of the switch port into a temporary variable.
    bool readState = digitalRead(pin);

    // Clear Changed State Flag - will be reset if we confirm a button state change.
    state &= ~_BV(STATE_CHANGED);

    if ( readState != (bool)(state & _BV(DEBOUNCED_STATE))) {
      // We have seen a change from the current button state.

      if ( millis() - previous_millis >= interval_millis ) {
	// We have passed the time threshold, so a new change of state is allowed.
	// set the STATE_CHANGED flag and the new DEBOUNCED_STATE.
	// This will be prompt as long as there has been greater than interval_misllis ms since last change of input.
	// Otherwise debounced state will not change again until bouncing is stable for the timeout period.
	state ^= _BV(DEBOUNCED_STATE);
	state |= _BV(STATE_CHANGED);
      }
    }

    // If the readState is different from previous readState, reset the debounce timer - as input is still unstable
    // and we want to prevent new button state changes until the previous one has remained stable for the timeout.
    if ( readState != (bool)(state & _BV(UNSTABLE_STATE)) ) {
	// Update Unstable Bit to macth readState
        state ^= _BV(UNSTABLE_STATE);
        previous_millis = millis();
    }
    // return just the sate changed bit
    return state & _BV(STATE_CHANGED);
#else
    // Read the state of the switch in a temporary variable.
    bool currentState = digitalRead(pin);
    state &= ~_BV(STATE_CHANGED);

    // If the reading is different from last reading, reset the debounce counter
    if ( currentState != (bool)(state & _BV(UNSTABLE_STATE)) ) {
        previous_millis = millis();
        state ^= _BV(UNSTABLE_STATE);
    } else
        if ( millis() - previous_millis >= interval_millis ) {
            // We have passed the threshold time, so the input is now stable
            // If it is different from last state, set the STATE_CHANGED flag
            if ((bool)(state & _BV(DEBOUNCED_STATE)) != currentState) {
                previous_millis = millis();
                state ^= _BV(DEBOUNCED_STATE);
                state |= _BV(STATE_CHANGED);
            }
        }

    return state & _BV(STATE_CHANGED);
#endif
}

bool Debounce::read()
{
    return state & _BV(DEBOUNCED_STATE);
}

bool Debounce::rose()
{
    return ( state & _BV(DEBOUNCED_STATE) ) && ( state & _BV(STATE_CHANGED));
}

bool Debounce::fell()
{
    return !( state & _BV(DEBOUNCED_STATE) ) && ( state & _BV(STATE_CHANGED));
}