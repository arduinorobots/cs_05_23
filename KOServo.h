/*
    Created by Kirill Osipov on 11/02/2016.
    Copyright (c) Kirill Osipov 2016. All rights reserved.
*/

#ifndef KOServo_h
#define KOServo_h

#include <inttypes.h>

class KOServo {

    public:
        KOServo();
        void attach(int pin);
        void write(bool state);

    private:
        uint16_t _previousMillis;
        uint8_t _pin;

};

#endif