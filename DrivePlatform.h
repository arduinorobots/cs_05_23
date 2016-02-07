/*
    DrivePlatform.h

    Created by Kirill Osipov on 31/01/2016.
    Copyright (c) Kirill Osipov 2016. All rights reserved.
*/

#ifndef DrivePlatform_h
#define DrivePlatform_h

#define MAX_MOTORS 4    // arduino need reserved mem befor start :(
#include <inttypes.h>

struct Motor {
    uint8_t pin_in;     // for LOW HIGH
    uint8_t pin_en;     // for 0 - 255
};

enum direction {
    left, right
};

class DrivePlatform {

    public:
        DrivePlatform();
        void attachMotor(int pin_in, int pin_en);
        void acceleration(uint8_t acceleration);
        void driveWithSpeed(int endSpeed);
        void turnAt(direction direction);

    private:
        uint8_t _accelStepper;
        uint16_t _previousMillis;
        uint16_t _acceleration;
        uint16_t _accelSpeed;
        int16_t _endSpeed;
        uint8_t _motorCount;
        Motor _motorPins[MAX_MOTORS];

};

#endif