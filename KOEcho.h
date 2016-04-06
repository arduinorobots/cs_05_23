/*
    Created by Kirill Osipov on 29/02/2016.
    Copyright (c) Kirill Osipov 2016. All rights reserved.
*/

#ifndef KOEcho_h
#define KOEcho_h

#include <inttypes.h>

class KOEcho {

    public:
        KOEcho();
        void attach(int pinEcho, int pinTrig);
        unsigned int measureDistance();

    private:
        uint8_t _pinEcho, _pinTrig;
        uint8_t _distance;

};

#endif