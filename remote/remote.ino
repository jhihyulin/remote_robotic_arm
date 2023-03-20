// 6 Channel Receiver
// output on pins D2, D3, D4, D5 , D6, D9, D14, D15

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

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

const uint64_t pipeIn = 0xE9E8F0F0E1LL;
RF24 radio(7, 8); 

void ResetData() {
    data.throttle = 127;
    data.pitch = 127;
    data.roll = 127;
    data.yaw = 127;
    data.rotateL = 127;
    data.rotateR = 127;
    data.switchL = false;
    data.switchR = false;
}

void setup() {
    ch1.attach(2);
    ch2.attach(3);
    ch3.attach(4);
    ch4.attach(5);
    ch5.attach(6);
    ch6.attach(9);

    pinMode(14, OUTPUT);
    pinMode(15, OUTPUT);

    ResetData();
    radio.begin();
    radio.openReadingPipe(1,pipeIn);

    Serial.begin(115200);

    radio.startListening();
}

unsigned long lastRecvTime = 0;

void recvData() {
    while ( radio.available() ) {
        radio.read(&data, sizeof(Signal));
        lastRecvTime = millis();
    }
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
    recvData();
    unsigned long now = millis();
    if ( now - lastRecvTime > 1000 ) {
        ResetData();
    }

    // Serial.print('RecieveTime: ');
    // Serial.print(now - lastRecvTime);

    Serial.print(' Throttle: ');
    Serial.print(data.throttle);
    Serial.print(' Pitch: ');
    Serial.print(data.pitch);
    Serial.print(' Roll: ');
    Serial.print(data.roll);
    Serial.print(' Yaw: ');
    Serial.print(data.yaw);
    Serial.print(' RotateL: ');
    Serial.print(data.rotateL);
    Serial.print(' RotateR: ');
    Serial.print(data.rotateR);
    Serial.print(' SwitchL: ');
    Serial.print(data.switchL);
    Serial.print(' SwitchR: ');
    Serial.println(data.switchR);

    ch_width_1 = limit(map(data.throttle, 0, 255, -10, 10) + ch_width_1, -10, 10, 1000, 2000);
    ch_width_2 = limit(map(data.pitch, 0, 255, -10, 10) + ch_width_2, -10, 10, 1000, 2000);
    ch_width_3 = limit(map(data.roll, 0, 255, -10, 10) + ch_width_3, -10, 10, 1000, 2000);
    ch_width_4 = limit(map(data.yaw, 0, 255, -10, 10) + ch_width_4, -10, 10, 1000, 2000);
    ch_width_5 = limit(map(data.rotateL, 0, 255, -10, 10) + ch_width_5, -10, 10, 1000, 2000);
    ch_width_6 = limit(map(data.rotateR, 0, 255, -10, 10) + ch_width_6, -10, 10, 1000, 2000);

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

    ch1.writeMicroseconds(ch_width_1);
    ch2.writeMicroseconds(ch_width_2);
    ch3.writeMicroseconds(ch_width_3);
    ch4.writeMicroseconds(ch_width_4);
    ch5.writeMicroseconds(ch_width_5);
    ch6.writeMicroseconds(ch_width_6);

    digitalWrite(14, data.switchL);
    digitalWrite(15, data.switchR);
}