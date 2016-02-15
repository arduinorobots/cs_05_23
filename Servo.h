/*
    Created by Kirill Osipov on 11/02/2016.
    Copyright (c) Kirill Osipov 2016. All rights reserved.
*/

#ifndef Servo_h
#define Servo_h

#include <inttypes.h>

class Servo {

    public:
        Servo();
        void attach(int pin);
        void write(int angle);
        void switcher();

    private:
        uint8_t _angle;
        uint8_t _pin;

};

#endif