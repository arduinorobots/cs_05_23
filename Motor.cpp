/*
    Created by Kirill Osipov on 31/01/2016.
    Copyright (c) Kirill Osipov 2016. All rights reserved.
*/

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "Motor.h"

Motor::Motor() {
    _accelStepper = 0;
    _accelSpeed = 0;
    _previousMillis = 0;
    _acceleration = 100;
    _motorCount = 0;
    _endSpeed = 0;
}

void Motor::attach(int pin_in, int pin_en) {

    MotorPin motor = {pin_in, pin_en};
    _motorPins[_motorCount] = motor;
    _motorCount++;

    for (uint8_t i = 0; i < _motorCount; i++) {
        pinMode(_motorPins[i].pin_in, OUTPUT);
        pinMode(_motorPins[i].pin_en, OUTPUT);
    }

}

void Motor::acceleration(uint8_t acceleration) {
    _acceleration = acceleration >= 10 ? acceleration / 10 : 1;
}

void Motor::drive(int endSpeed) {

    _endSpeed = abs(constrain(endSpeed, -255, 255));
    bool direction = endSpeed >= 0 ? HIGH : LOW;

    uint16_t _currentMillis = millis();
    if (_currentMillis - _previousMillis >= _acceleration &&
        _accelSpeed < _endSpeed) {

        _previousMillis = _currentMillis;
        _accelStepper++;
        _accelSpeed += _endSpeed * _accelStepper / 10;

    } else {
        _accelStepper = 0;
        _accelSpeed = 0;
    }

    uint16_t _speed = _accelStepper == 0 ? _endSpeed : _accelSpeed;
    for (uint8_t i = 0; i < _motorCount; i++) {
        digitalWrite(_motorPins[i].pin_in, direction);
        analogWrite(_motorPins[i].pin_en, _speed);
    }

}

void Motor::turnAt(direction direction) {

    if (_motorCount >= 2) {

        switch (direction) {
            case left:
                digitalWrite(_motorPins[0].pin_in, HIGH);
                analogWrite(_motorPins[0].pin_en, 100);

                digitalWrite(_motorPins[1].pin_in, LOW);
                analogWrite(_motorPins[1].pin_en, 100);
            break;
            case right:



            break;
        }

    }

}
