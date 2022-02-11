#include <Arduino_AVRSTL.h>
#include <SoftwareSerial.h>
using namespace std;

void setup() {
    Serial.begin(9600);
    pinMode(7, OUTPUT);
    digitalWrite(7, HIGH);
    Serial.println("TIME,READING");
    last_10.resize(10);
}

int interval = 100;  // milliseconds
int timer = 0;

int falling_count = 0;
int last_avg = INT32_MAX;
int time_start_val = 0;

vector<int> last_10;

void loop() {
    int sensor_val = analogRead(A0);
    last_10.erase(0);
    last_10.push_back(sensor_val);
    int avg = rolling_average();

    if (avg <= last_avg) {
        last_avg = avg;
        ++falling_count;
    } else {
        falling_count = 0;
    }

    if (falling_count > 100 && sensor_val <= 1100) {
        digitalWrite(7, LOW);
        time_start_val = sensor_val;
        Serial.println();
        Serial.println("TIMER STARTED");
        timing();
    }

    Serial.println(timer + "," + sensor_val);

    delay(interval);
    timer += interval / 1000;
}

int rolling_average() {
    int sum = 0;
    for (int x : last_10) {
        sum += x;
    }
    return sum / 10;
}

void timing() {
    timer = 0;
    while (true) {}
}