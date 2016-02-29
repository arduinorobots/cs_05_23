/*
    Created by Kirill Osipov on 26/02/2016.
    Copyright (c) Kirill Osipov 2016. All rights reserved.
*/

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "KOBuzzer.h"

#define FREQUENCY   200
#define DURATION    200

KOBuzzer::KOBuzzer() { }

void KOBuzzer::attach(int pin) {
    _pin = pin;
    pinMode(_pin, OUTPUT);
}

void KOBuzzer::toneAlert() {

    uint16_t _currentMillis = millis();
    if (_currentMillis - _previousMillis >= DURATION * 2) {
        _previousMillis = _currentMillis;

        tone(_pin, FREQUENCY, DURATION);

    }

}
