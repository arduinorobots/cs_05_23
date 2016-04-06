/*
    Created by Kirill Osipov on 31/01/2016.
    Copyright (c) Kirill Osipov 2016. All rights reserved.
*/

#include <Servo.h>

#include "KOPin.h"
#include "KOMotor.h"
#include "KOBuzzer.h"
#include "KOEcho.h"

#define TIMESTEP    500
#define MAX_DIST    100
#define MIN_DIST    20

Servo servo_on_1, servo_on_2, servo_off;
KOMotor platform = KOMotor();
KOBuzzer buzzer = KOBuzzer();
KOEcho echo = KOEcho();

unsigned long previousMillis = 0;
unsigned long magicMillis = 0;
direction curDir = none;
unsigned int curDis = 1000;
int triggerCounter = 0;

static unsigned int servoState[2] = {20, 160};

bool cargo = 0;
bool target = 0;
bool trigged = 0;
bool magic =0;

void setup() {

    buzzer.attach(PIN_BUZZER);

    servo_off.attach(PIN_SERVO_OFF, servoState[0], servoState[1]);
    servo_on_1.attach(PIN_SERVO_ON_1, servoState[0], servoState[1]);
    servo_on_2.attach(PIN_SERVO_ON_2, servoState[0], servoState[1]);

    platform.attach(PIN_MOT_IN_01, PIN_MOT_EN_01);
    platform.attach(PIN_MOT_IN_02, PIN_MOT_EN_02);

    echo.attach(PIN_ECHO, PIN_TRIG);

    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_YLW, OUTPUT);
    pinMode(PIN_CARGO, INPUT);

    // Serial.begin(9600);
}

void loop() {

    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis > TIMESTEP) {
        previousMillis = currentMillis;

        cargo = cargoState();
        if (!trigged) {
            triggerCounter++;
            cargoTrigger();
        }
    }

    if (cargo && trigged) { // поиск цели

        // buzzer.toneAlert();
        curDis = echo.measureDistance();

        if (currentMillis - magicMillis > 200) {
            magicMillis = currentMillis;

            if (curDis > MAX_DIST) curDir = right;
            if (curDis < MAX_DIST && curDis >= MIN_DIST) curDir = forward;
            if (curDis < MIN_DIST && curDis >= MIN_DIST/2) curDir = none;
            if (curDis < MIN_DIST/2) curDir = back;

            magic = !magic;
        }

        target = curDis > MIN_DIST ? 0 : 1;
    }

    curDir = magic && cargo ? curDir : none;
    platform.turn(curDir);

    if (cargo && trigged && target) { // спуск затвора

        delay(TIMESTEP);
        servo_off.write(servoState[1]);
        delay(TIMESTEP);
        target = !target;
        trigged = !trigged;
        cargo = !cargo;
    }

    digitalWrite(PIN_RED, cargo);
    digitalWrite(PIN_YLW, !cargo);
}

bool cargoState() {

    unsigned int analogData = analogRead(PIN_CARGO);
    unsigned int cargoData = map(analogData, 0, 1023, 0, 200);
    bool state = cargoData > 70 ? 0 : 1;
    return state;
}

void cargoTrigger() {
    switch (triggerCounter) {
        case 1:
            servo_on_1.write(servoState[1]);
            servo_on_2.write(servoState[0]);
            servo_off.write(servoState[1]);
        break;
        case 2:
            servo_off.write(servoState[0]);
        break;
        case 3:
            servo_on_1.write(servoState[0]);
            servo_on_2.write(servoState[1]);
            triggerCounter = 0;
            trigged = !trigged;
        break;
    }
}
