/*
    Created by Kirill Osipov on 31/01/2016.
    Copyright (c) Kirill Osipov 2016. All rights reserved.
*/

#include "Motor.h"
#include "Servo.h"


#define PIN_MOT_EN_01   10
#define PIN_MOT_IN_01   12

#define PIN_MOT_EN_02   11
#define PIN_MOT_IN_02   13

#define PIN_BUZZER      4
#define PIN_SERVO       9

// #define PIN_CARGO       100
// #define PIN_MAGNET      100

// #define PIN_ECHO        8
// #define PIN_TRIG        9

Servo servo = Servo();
Motor platform = Motor();

unsigned int servoPosition[] = {10,180};
unsigned long previousMillis = 0;
bool magnetState = HIGH;

void setup() {

    // pinMode(PIN_MAGNET, OUTPUT);

    servo.attach(PIN_SERVO);
    servo.write(200);

    platform.attach(PIN_MOT_IN_01, PIN_MOT_EN_01);
    platform.attach(PIN_MOT_IN_02, PIN_MOT_EN_02);

    // pinMode(PIN_ECHO, INPUT);
    // pinMode(PIN_TRIG, OUTPUT);

    // Serial.begin(9600);
}

void loop() {

    // digitalWrite(PIN_MAGNET, HIGH);

    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= 10000) {
        previousMillis = currentMillis;

        int ss = magnetState ? servoPosition[LOW] : servoPosition[HIGH];
        magnetState = !magnetState;
        servo.write(ss);

    }

    // platform.drive(-100);

    // Serial.println(measureDistance());

}

// unsigned int measureDistance() {

//     digitalWrite(PIN_TRIG, HIGH);
//     digitalWrite(PIN_TRIG, LOW);
//     int distance = pulseIn(PIN_ECHO, HIGH, 15000)/54;
//     return constrain(distance, 1, 300);

// }
