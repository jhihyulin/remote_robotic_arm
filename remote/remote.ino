// 8 Channel Receiver
// output on pins D2, D3, D4, D5 , D6, D9, D14, D15

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

int ch_width_1, ch_width_2, ch_width_3, ch_width_4, ch_width_5, ch_width_6;
Servo ch1, ch2, ch3, ch4, ch5, ch6;
int throttle, pitch, roll, yaw, rotateL, rotateR;
bool switchL, switchR;

const uint64_t pipeIn = 0xE9E8F0F0E1LL;
RF24 radio(7, 8); 

void ResetData() {
    ch_width_1 = 1500;
    ch_width_2 = 2000;
    ch_width_3 = 2000;
    ch_width_4 = 2500;
    ch_width_5 = 1500;
    ch_width_6 = 1000;
    throttle, pitch, roll, yaw, rotateL, rotateR = 127;
    switchL, switchR = false;
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
        // radio.read(&data, sizeof(Signal));
        int data[8];
        radio.read(&data, sizeof(data));
        Serial.print(data[0]);
        throttle = data[0];
        pitch = data[1];
        roll = data[2];
        yaw = data[3];
        rotateL = data[4];
        rotateR = data[5];
        switchL = data[6];
        switchR = data[7];

        lastRecvTime = millis();
        Serial.println('Recieved Data');
    }
}

float limit(int value, int min, int max) {
    if ( value < min ) {
        return min;
    } else if ( value > max ) {
        return max;
    } else {
        return value;
    }
}

float deadzone(int value, int deadzone) {
    if ( value == deadzone ) {
        return 0;
    } else {
        return value;
    }
}

void loop() {
    recvData();
    unsigned long now = millis();
    if ( now - lastRecvTime > 1000 ) {
        Serial.println("Lost connection");
    }

    ch_width_1 = limit(map(deadzone(throttle, 127), 0, 255, -10, 10) + ch_width_1, 500, 2500);
    ch_width_2 = limit(map(deadzone(roll, 127), 0, 255, 10, -10) + ch_width_2, 500, 2500);
    ch_width_3 = limit(map(deadzone(pitch, 127), 0, 255, -10, 10) + ch_width_3, 500, 2000);
    ch_width_4 = limit(map(deadzone(yaw, 127), 0, 255, 10, -10) + ch_width_4, 500, 2500);
    ch_width_5 = map(rotateL, 0, 255, 500, 2500);
    ch_width_6 = map(rotateR, 0, 255, 1000, 2300);

    ch1.writeMicroseconds(ch_width_1);
    ch2.writeMicroseconds(ch_width_2);
    ch3.writeMicroseconds(ch_width_3);
    ch4.writeMicroseconds(ch_width_4);
    ch5.writeMicroseconds(ch_width_5);
    ch6.writeMicroseconds(ch_width_6);

    Serial.print("ch1:");
    Serial.print(ch_width_1);
    Serial.print(" ch2:");
    Serial.print(ch_width_2);
    Serial.print(" ch3:");
    Serial.print(ch_width_3);
    Serial.print(" ch4:");
    Serial.print(ch_width_4);
    Serial.print(" ch5:");
    Serial.print(ch_width_5);
    Serial.print(" ch6:");
    Serial.print(ch_width_6);

    Serial.print(" throttle:");
    Serial.print(throttle);
    Serial.print(" pitch:");
    Serial.print(pitch);
    Serial.print(" roll:");
    Serial.print(roll);
    Serial.print(" yaw:");
    Serial.print(yaw);
    Serial.print(" rotateL:");
    Serial.print(rotateL);
    Serial.print(" rotateR:");
    Serial.print(rotateR);
    Serial.print(" switchL:");
    Serial.print(switchL);
    Serial.print(" switchR:");
    Serial.println(switchR);

    digitalWrite(14, switchL);
    digitalWrite(15, switchR);
}