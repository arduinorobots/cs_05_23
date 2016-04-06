/*
    Created by Kirill Osipov on 29/02/2016.
    Copyright (c) Kirill Osipov 2016. All rights reserved.
*/

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "KOEcho.h"

uint8_t arr[5] = {1,1,1,1,1};
uint8_t max = 0, counter = 0;

KOEcho::KOEcho() {
    _distance = 255;
}

void KOEcho::attach(int pinEcho, int pinTrig) {

    _pinEcho = pinEcho;
    _pinTrig = pinTrig;
    pinMode(_pinEcho, INPUT);
    pinMode(_pinTrig, OUTPUT);
}

unsigned int KOEcho::measureDistance() {

    digitalWrite(_pinTrig, HIGH);
    digitalWrite(_pinTrig, LOW);
    _distance = pulseIn(_pinEcho, HIGH, 15000) / 54;
    _distance = constrain(_distance, 1, 255);

    arr[counter] = _distance;
    for (int i = 0; i < 5; ++i) {
        if (arr[max] < arr[i]) max = i;
    }
    _distance = arr[max];
    counter == 4 ? counter = 0 : counter++;

    return _distance == 1 ? 255 : _distance;
}
