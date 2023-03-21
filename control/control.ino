// 6 Channel controller
// input on pins A0, A1, A2, A3, A4, A5, D2, D3

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const uint64_t pipeOut = 0xE9E8F0F0E1LL;
RF24 radio(7, 8);

int throttle, pitch, roll, yaw, rotateL, rotateR;
bool switchL, switchR;

void ResetData() {
    throttle, pitch, roll, yaw, rotateL, rotateR = 127;
    switchL, switchR = false;
}

void setup() {
    radio.begin();
    radio.openWritingPipe(pipeOut);
    radio.stopListening();
    ResetData();

    Serial.begin(115200);
}

int mapJoystickValues(int val, int lower, int middle, int upper, bool reverse) {
    val = constrain(val, lower, upper);
    if ( val < middle )
    val = map(val, lower, middle, 0, 128);
    else
    val = map(val, middle, upper, 128, 255);
    return ( reverse ? 255 - val : val );
}

void loop() {
    throttle = mapJoystickValues( analogRead(A0), 524, 524, 1015, true );
    roll = mapJoystickValues( analogRead(A1), 12, 524, 1020, true );
    pitch = mapJoystickValues( analogRead(A2), 12, 524, 1020, true );
    yaw = mapJoystickValues( analogRead(A3), 12, 524, 1020, true );
    rotateL = mapJoystickValues( analogRead(A4), 12, 524, 1020, true );
    rotateR = mapJoystickValues( analogRead(A5), 12, 524, 1020, true );
    switchL = !digitalRead(2);
    switchR = !digitalRead(3);

    Serial.print("Throttle: ");
    Serial.print(throttle);
    Serial.print(" Pitch: ");
    Serial.print(pitch);
    Serial.print(" Roll: ");
    Serial.print(roll);
    Serial.print(" Yaw: ");
    Serial.print(yaw);
    Serial.print(" RotateL: ");
    Serial.print(rotateL);
    Serial.print(" RotateR: ");
    Serial.print(rotateR);
    Serial.print(" SwitchL: ");
    Serial.print(switchL);
    Serial.print(" SwitchR: ");
    Serial.println(switchR);

    int data[8] = {throttle, pitch, roll, yaw, rotateL, rotateR, switchL, switchR};
    radio.write(&data, sizeof(data));
}