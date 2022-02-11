#include <SoftwareSerial.h>
using namespace std;

double interval;  // milliseconds
double timer;

int falling_count = 0;
int last_avg = INT32_MAX;
int time_start_val = 0;

int last_10[10];
double avg_index;

void setup() {
    Serial.begin(9600);
    pinMode(7, OUTPUT);
    digitalWrite(7, HIGH);
    Serial.println("START, LOG WITH CONTROL-A SHIFT-H");
    delay(5000);
    Serial.println("TIME,READING");
    timer = 0;
    interval = 20;
}

void loop() {
    int sensor_val = analogRead(A0);
    /* last_10[avg_index++] = sensor_val;
    int avg = rolling_average();

    if (avg <= last_avg) {
        last_avg = avg;
        ++falling_count;
    } else {
        falling_count = 0;
    } */

    /* if (falling_count > 100 && sensor_val <= 1100) {
        digitalWrite(7, LOW);
        time_start_val = sensor_val;
        Serial.println();
        Serial.println("TIMER STARTED");
    } */

    Serial.println(String(timer) + "," + String(sensor_val));

    delay(interval);
    timer += double(interval) / 1000;
}

int rolling_average() {
    int sum = 0;
    for (int x : last_10) {
        sum += x;
    }
    return sum / 10;
}