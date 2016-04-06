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

KOBuzzer::KOBuzzer() {
    _frequency = 200;
    _duration = 200;
}

void KOBuzzer::attach(int pin) {
    _pin = pin;
    pinMode(_pin, OUTPUT);
}

void KOBuzzer::toneAlert(unsigned int duration) {

    uint16_t _currentMillis = millis();
    if (_currentMillis - _previousMillis > duration * 2) {
        _previousMillis = _currentMillis;

        tone(_pin, _frequency, duration);

    }

}

void KOBuzzer::toneAlert() {
    this->toneAlert(_duration);
}
