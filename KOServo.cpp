/*
    Created by Kirill Osipov on 11/02/2016.
    Copyright (c) Kirill Osipov 2016. All rights reserved.
*/

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "KOServo.h"

KOServo::KOServo() {
    _previousMillis = 0;
}

void KOServo::attach(int pin) {
    _pin = pin;
}

void KOServo::write(bool state) {

    uint16_t _currentMillis = millis();
    if (_currentMillis - _previousMillis > 300) {
        _previousMillis = _currentMillis;



    }


}
