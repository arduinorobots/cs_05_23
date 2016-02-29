/*
    Created by Kirill Osipov on 31/01/2016.
    Copyright (c) Kirill Osipov 2016. All rights reserved.
*/

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "KOMotor.h"

#define SPEED_MIN   100
#define SPEED_MAX   255
#define SPEED_TURN  100

KOMotor::KOMotor() {
    _motorCount = 0;
    _endSpeed = 0;
}

void KOMotor::attach(int pin_in, int pin_en) {

    MotorPin motor = {pin_in, pin_en};
    _motorPins[_motorCount] = motor;
    _motorCount++;

    for (uint8_t i = 0; i < _motorCount; i++) {
        pinMode(_motorPins[i].pin_in, OUTPUT);
        pinMode(_motorPins[i].pin_en, OUTPUT);
    }

}

void KOMotor::drive(int endSpeed) {

    _endSpeed = abs(constrain(endSpeed, -SPEED_MAX, SPEED_MAX));
    bool direction = endSpeed >= 0 ? HIGH : LOW;

    for (uint8_t i = 0; i < _motorCount; i++) {
        digitalWrite(_motorPins[i].pin_in, direction);
        analogWrite(_motorPins[i].pin_en, _endSpeed);
    }

}

void KOMotor::turn(direction direction) {

    uint8_t speed = direction == none ? 0 : SPEED_TURN;
    if (_motorCount >= 2) {

        bool switcher = direction == right ? HIGH : LOW;

        digitalWrite(_motorPins[0].pin_in, switcher);
        analogWrite(_motorPins[0].pin_en, speed);
        digitalWrite(_motorPins[1].pin_in, !switcher);
        analogWrite(_motorPins[1].pin_en, speed);

    }

}
