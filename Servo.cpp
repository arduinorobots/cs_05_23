/*
    Created by Kirill Osipov on 11/02/2016.
    Copyright (c) Kirill Osipov 2016. All rights reserved.
*/

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "Servo.h"

Servo::Servo() {

}

static uint16_t _msOfPeriod = 24 * 1000;
static uint16_t _msOfPulse = 1 * 1000;
static uint16_t _msOfStep = 0.01 * 1000;

static uint16_t _msMinPosition = 0.7 * 1000;
static uint16_t _msMaxPosition = 3.7 * 1000;

uint16_t _msCurrentAngle = _msMinPosition;

void Servo::attach(int pin) {
    _pin = pin;
    pinMode(_pin, OUTPUT);
}

void Servo::write(int angle) {

    _angle = constrain(angle, 0, 180);
    uint16_t _msAngle = map(_angle, 0, 180, _msMinPosition, _msMaxPosition);
    uint16_t _sign = _msAngle < _msCurrentAngle ? -1 : 1;

    // TODO: write angle

}

void Servo::switcher() {

    uint16_t _msTemp = _msMinPosition;
    for (_msTemp; _msTemp < _msMaxPosition; _msTemp += _msOfStep) {

        digitalWrite(_pin, HIGH);
        delayMicroseconds(_msTemp);
        digitalWrite(_pin, LOW);
        delayMicroseconds(_msOfPeriod - _msTemp);
    }
    _msTemp = _msMaxPosition;
    for (_msTemp; _msTemp > _msMinPosition; _msTemp -= _msOfStep) {

        digitalWrite(_pin, HIGH);
        delayMicroseconds(_msTemp);
        digitalWrite(_pin, LOW);
        delayMicroseconds(_msOfPeriod - _msTemp);

    }

}
