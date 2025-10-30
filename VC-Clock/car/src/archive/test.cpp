#include <Arduino.h>
#include <SoftwareSerial.h>

#define WINDOW_SIZE 35
#define TEST_PIN A12
#define TEST_PIN2 2

void setup() {
    Serial.begin(9600);
    pinMode(TEST_PIN, INPUT);
    pinMode(TEST_PIN2, OUTPUT);
}

void loop() {
    Serial.println(analogRead(TEST_PIN));
    delay(5);
}
