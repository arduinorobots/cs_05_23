/*
    Created by Kirill Osipov on 31/01/2016.
    Copyright (c) Kirill Osipov 2016. All rights reserved.
*/

#ifndef KOMotor_h
#define KOMotor_h

#define MAX_MOTORS 2    // arduino need reserved mem befor start :(
#include <inttypes.h>

struct MotorPin {
    uint8_t pin_in;     // for LOW HIGH
    uint8_t pin_en;     // for 0 - 255
};

enum direction {
    left, right, forward, back, none
};

class KOMotor {

    public:
        KOMotor();
        void attach(int pin_in, int pin_en);
        void drive(int endSpeed);
        void turn(direction direction);

    private:
        int16_t _endSpeed;
        uint8_t _motorCount;
        MotorPin _motorPins[MAX_MOTORS];

};

#endif