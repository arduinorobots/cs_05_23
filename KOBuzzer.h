/*
    Created by Kirill Osipov on 26/02/2016.
    Copyright (c) Kirill Osipov 2016. All rights reserved.
*/

#ifndef KOBuzzer_h
#define KOBuzzer_h

#include <inttypes.h>

class KOBuzzer {

    public:
        KOBuzzer();
        void attach(int pin);
        void toneAlert();

    private:
        uint8_t _pin;
        uint16_t _previousMillis;

};

#endif