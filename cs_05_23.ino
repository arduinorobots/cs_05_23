/*
    cs_05_23.ino

    Created by Kirill Osipov on 31/01/2016.
    Copyright (c) Kirill Osipov 2016. All rights reserved.
*/

#include <Servo.h>
#include "DrivePlatform.h"


#define PIN_MOT_EN_01   5
#define PIN_MOT_IN_01   4
#define PIN_MOT_EN_02   7
#define PIN_MOT_IN_02   6

#define PIN_SERVO       10

#define PIN_CARGO       11
#define PIN_MAGNET      12

#define PIN_ECHO        8
#define PIN_TRIG        9


Servo           servo;
DrivePlatform   platform;

unsigned int servoPosition[] = {10,90};
unsigned long previousMillis = 0;
bool magnetState = HIGH;


void setup() {

    pinMode(PIN_MAGNET, OUTPUT);

    servo.attach(PIN_SERVO);
    servo.write(servoPosition[HIGH]);

    platform = DrivePlatform();
    platform.attachMotor(PIN_MOT_IN_01, PIN_MOT_EN_01);
    platform.attachMotor(PIN_MOT_IN_02, PIN_MOT_EN_02);

    pinMode(PIN_ECHO, INPUT);
    pinMode(PIN_TRIG, OUTPUT);

    Serial.begin(9600);
}

void loop() {

    digitalWrite(PIN_MAGNET, HIGH);

    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis <= 500) {
        previousMillis = currentMillis;

    }

    platform.driveWithSpeed(200);
    Serial.println(measureDistance());

}

unsigned int measureDistance() {

    digitalWrite(PIN_TRIG, HIGH);
    digitalWrite(PIN_TRIG, LOW);
    int distance = pulseIn(PIN_ECHO, HIGH, 15000)/54;
    return constrain(distance, 1, 300);

}
