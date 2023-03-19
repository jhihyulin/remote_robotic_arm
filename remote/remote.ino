//  6 Channel Receiver | 6 Kanal Alıcı
//  PWM output on pins D2, D3, D4, D5 , D6, D9 (Çıkış pinleri)

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
}

void setup() {
    ch1.attach(2);
    ch2.attach(3);
    ch3.attach(4);
    ch4.attach(5);
    ch5.attach(6);
    ch6.attach(9);

    ResetData();
    radio.begin();
    radio.openReadingPipe(1,pipeIn);
    
    radio.startListening();
}

unsigned long lastRecvTime = 0;

void recvData() {
    while ( radio.available() ) {
        radio.read(&data, sizeof(Signal));
        lastRecvTime = millis();
    }
}

void loop() {
    recvData();
    unsigned long now = millis();
    if ( now - lastRecvTime > 1000 ) {
        ResetData();
    }

    ch_width_1 = map(data.throttle, 0, 255, 1000, 2000);
    ch_width_2 = map(data.pitch,    0, 255, 1000, 2000);
    ch_width_3 = map(data.roll,     0, 255, 1000, 2000);
    ch_width_4 = map(data.yaw,      0, 255, 1000, 2000);
    ch_width_5 = map(data.rotateL,  0, 255, 1000, 2000);
    ch_width_6 = map(data.rotateR,  0, 255, 1000, 2000);    

    ch1.writeMicroseconds(ch_width_1);
    ch2.writeMicroseconds(ch_width_2);
    ch3.writeMicroseconds(ch_width_3);
    ch4.writeMicroseconds(ch_width_4);
    ch5.writeMicroseconds(ch_width_5);
    ch6.writeMicroseconds(ch_width_6);
}