// 6 Channel controller
// input on pins A0, A1, A2, A3, A4, A5, D2, D3

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const uint64_t pipeOut = 0xE9E8F0F0E1LL;
RF24 radio(7, 8);

struct Signal {
    byte throttle;
    byte pitch;
    byte roll;
    byte yaw;
    byte rotateL;
    byte rotateR;
    byte switchL;
    byte switchR;
};

Signal data;

void ResetData() {
    data.throttle = 127;
    data.pitch = 127;
    data.roll = 127;
    data.yaw = 127;
    data.rotateL = 127;
    data.rotateR = 127;
    data.switchL = 0;
    data.switchR = 0;
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
    data.throttle = mapJoystickValues( analogRead(A0), 524, 524, 1015, true );
    data.roll = mapJoystickValues( analogRead(A1), 12, 524, 1020, true );
    data.pitch = mapJoystickValues( analogRead(A2), 12, 524, 1020, true );
    data.yaw = mapJoystickValues( analogRead(A3), 12, 524, 1020, true );
    data.rotateL = mapJoystickValues( analogRead(A4), 12, 524, 1020, true );
    data.rotateR = mapJoystickValues( analogRead(A5), 12, 524, 1020, true );
    data.switchL = !digitalRead(2);
    data.switchR = !digitalRead(3);

    Serial.print("Throttle: ");
    Serial.print(data.throttle);
    Serial.print(" Pitch: ");
    Serial.print(data.pitch);
    Serial.print(" Roll: ");
    Serial.print(data.roll);
    Serial.print(" Yaw: ");
    Serial.print(data.yaw);
    Serial.print(" RotateL: ");
    Serial.print(data.rotateL);
    Serial.print(" RotateR: ");
    Serial.print(data.rotateR);
    Serial.print(" SwitchL: ");
    Serial.print(data.switchL);
    Serial.print(" SwitchR: ");
    Serial.println(data.switchR);

    radio.write(&data, sizeof(Signal));
}