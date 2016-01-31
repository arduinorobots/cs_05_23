/*
    cs_05_23.ino

    Created by Kirill Osipov on 31/01/2016.
    Copyright (c) Kirill Osipov 2016. All rights reserved.

*/

#define PIN_MOT_EN_01 5
#define PIN_MOT_IN_01 4
#define PIN_MOT_EN_02 7
#define PIN_MOT_IN_02 6


unsigned int acceleration = 10;

void setup() {

    for(int pin=4; pin==6; pin++){
        pinMode(pin, OUTPUT);
    }

}

void loop() {

    driveWithSpeed(150);

}

void driveWithSpeed(int endSpeed) {

    endSpeed = constrain(endSpeed, -255, 255);
    bool dir = endSpeed >= 0 ? HIGH : LOW;
    // int fxDir = endSpeed >= 0 ? 1 : -1;

    digitalWrite(PIN_MOT_IN_01, dir);
    digitalWrite(PIN_MOT_IN_02, dir);
    // for(int sVal=endSpeed/2; sVal<=endSpeed; sVal+=acceleration*fxDir) {
    //     analogWrite(PIN_MOT_EN_01, sVal);
    //     analogWrite(PIN_MOT_EN_02, sVal);
    // }
    analogWrite(PIN_MOT_EN_01, abs(endSpeed));
    analogWrite(PIN_MOT_EN_02, abs(endSpeed));

}

// void turnAtAngle(int endAngle) {

//     endAngle = constrain(endAngle, 0, 360);


// }