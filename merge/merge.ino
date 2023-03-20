// only use for testing
// use without NRF24L01

#include <SPI.h>
#include <Servo.h>

struct Signal {
    byte throttle;
    byte pitch;
    byte roll;
    byte yaw;
    byte rotateL;
    byte rotateR;
};

int ch_width_1 = 0;
int ch_width_2 = 0;
int ch_width_3 = 0;
int ch_width_4 = 0;
int ch_width_5 = 0;
int ch_width_6 = 0;

Servo ch1;
Servo ch2;
Servo ch3;
Servo ch4;
Servo ch5;
Servo ch6;

Signal data;

void ResetData() {
    data.throttle = 127;
    data.pitch = 127;
    data.roll = 127;
    data.yaw = 127;
    data.rotateL = 127;
    data.rotateR = 127;
}

void setup() {
    ch1.attach(2);
    ch2.attach(3);
    ch3.attach(4);
    ch4.attach(5);
    ch5.attach(6);
    ch6.attach(9);
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

int limit(int value, int min, int max, int minValue, int maxValue) {
    if ( value < min ) {
        return minValue;
    } else if ( value > max ) {
        return maxValue;
    } else {
        return value;
    }
}

void loop() {
    data.throttle = mapJoystickValues( analogRead(A0), 12, 524, 1020, true ); 
    data.roll = mapJoystickValues( analogRead(A1), 12, 524, 1020, true );
    data.pitch = mapJoystickValues( analogRead(A2), 12, 524, 1020, true );
    data.yaw = mapJoystickValues( analogRead(A3), 12, 524, 1020, true );
    data.rotateL = mapJoystickValues( analogRead(A4), 12, 524, 1020, true );
    data.rotateR = mapJoystickValues( analogRead(A5), 12, 524, 1020, true );

    ch_width_1 = limit(map(data.throttle, 0, 255, -10, 10) + ch_width_1, -10, 10, 1000, 2000);
    ch_width_2 = limit(map(data.pitch, 0, 255, -10, 10) + ch_width_2, -10, 10, 1000, 2000);
    ch_width_3 = limit(map(data.roll, 0, 255, -10, 10) + ch_width_3, -10, 10, 1000, 2000);
    ch_width_4 = limit(map(data.yaw, 0, 255, -10, 10) + ch_width_4, -10, 10, 1000, 2000);
    ch_width_5 = limit(map(data.rotateL, 0, 255, -10, 10) + ch_width_5, -10, 10, 1000, 2000);
    ch_width_6 = limit(map(data.rotateR, 0, 255, -10, 10) + ch_width_6, -10, 10, 1000, 2000);

    ch1.writeMicroseconds(ch_width_1);
    ch2.writeMicroseconds(ch_width_2);
    ch3.writeMicroseconds(ch_width_3);
    ch4.writeMicroseconds(ch_width_4);
    ch5.writeMicroseconds(ch_width_5);
    ch6.writeMicroseconds(ch_width_6);

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

    Serial.print(' ch_width_1: ');
    Serial.print(ch_width_1);
    Serial.print(' ch_width_2: ');
    Serial.print(ch_width_2);
    Serial.print(' ch_width_3: ');
    Serial.print(ch_width_3);
    Serial.print(' ch_width_4: ');
    Serial.print(ch_width_4);
    Serial.print(' ch_width_5: ');
    Serial.print(ch_width_5);
    Serial.print(' ch_width_6: ');
    Serial.println(ch_width_6);
}
