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
    _previousMillis = 0;
}

static uint16_t _lenMicroSecondsOfPeriod = 24 * 1000;    // 25 milliseconds
static uint16_t _lenMicroSecondsOfPulse = 1 * 1000;      // 1 ms is 0 degrees
static uint16_t _increment = 0.01 * 1000;

static uint16_t _aPosition = 0.7 * 1000;
static uint16_t _bPosition = 1.9 * 1000;


void Servo::attach(int pin) {
    _pin = pin;
    pinMode(_pin, OUTPUT);
}

// Servos work by sending a 20 or 25 ms pulse.
// 0.7 ms at the start of the pulse will turn the servo to the 0 degree position
// 2.2 ms at the start of the pulse will turn the servo to the 90 degree position
// 3.7 ms at the start of the pulse will turn the servo to the 180 degree position
// Turn voltage high to start the period and pulse

void Servo::write(int angle) {

    // TODO: angle
    _angle = constrain(angle, ANGLE_MIN, ANGLE_MAX);

    uint16_t _curAngle = 0;
    for (_curAngle = _aPosition; _curAngle < _bPosition; _curAngle += _increment) {
        digitalWrite(_pin, HIGH);

        // Delay for the length of the pulse
        delayMicroseconds(_curAngle);

        // Turn the voltage low for the remainder of the pulse
        digitalWrite(_pin, LOW);

        // Delay this loop for the remainder of the period so we don't
        // send the next signal too soon or too late
        delayMicroseconds(_lenMicroSecondsOfPeriod - _curAngle);

    }
    for (_curAngle = _bPosition; _curAngle > _aPosition; _curAngle -= _increment) {
         digitalWrite(_pin, HIGH);
         delayMicroseconds(_curAngle);
         digitalWrite(_pin, LOW);
         delayMicroseconds(_lenMicroSecondsOfPeriod - _curAngle);
    }

}
