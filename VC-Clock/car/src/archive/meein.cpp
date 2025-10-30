#include <Arduino.h>
#include <SoftwareSerial.h>

#define PHOTORESISTOR_PIN_IN A0
#define VALVE_SWITCH_PIN_IN A1 //7
#define MULTIMETER_PIN_OUT 4
#define VALVE_PIN_LIMIT 1015
#define RELAY_PIN_OUT 2

enum PROGRAM {
    // Run the Whole program
    RUN = 0,
    // Test the Chemical Reaction (No Motor)
    STOPPING_TEST = 1,
    // Test the Relay with 1-2 Delay
    PULSE = 2,
    // TEST DATA Calibration curve
    CURVE = 4,
    // JUST RELAY
    RELAY = 5
};

/*--------------------------------   SELECT TEST PROGRAM   --------------------------------*/

#define program RUN


/*----------------------------   VARIABLES YOU WANT TO CHANGE   ------------------------------*/

// Average Window size - Smaller: Faster Detection; Bigger: Resistant to Anomalies; Default: 35;
#define AVERAGE_WINDOW_SIZE 35
// Average Value that will trigger the car movement
#define TRIGGER_THRESHOLD 50
// ONLY IF USING STOPPING_TEST, TIME THE TEST RUNS FOR
#define STOPPING_TEST_TIME 40
// START MOVING ONCE POSSIBLE, CALCULATE STOPPING DISTANCE ONCE REACTION HAS OCCURED.
#define START_NOW false


/*----------------------------   CHEMICAL CALIBRATION CONSTANTS   ------------------------------*/
// SLOPE OF CAR RUN TIME VS ESTIMATED DISTANCE (1 / SPEED OF CAR)
#define CAR_A 3.448 
// Y INTERCEPT OF THE AFOREMENTIONED GRAPH
#define CAR_B -0.0347561

// SLOPE OF ESTIMATED DISTANCE VS REACTION TIME
#define CURVE_A -.33333
// Y INTERCEPT OF THE AFOREMENTIONED GRAPH
#define CURVE_B 31.66667


/*--------------------------------   DONT TOUCH THESE   --------------------------------*/

// ARRAY CONTAINING SENSOR VALUES WITH SIZE OF AVERAGE WINDOW SIZE
float valueBuffer[AVERAGE_WINDOW_SIZE];  

// ARRAY CONTAINING TIME CAR HAS BEEN RUNNING WITH SIZE OF AVERAGE WINDOW SIZE
float timeBuffer[AVERAGE_WINDOW_SIZE];

float valueAvgRunning;
float valveOpenTime;


void setup() {
    //INIT
    value_avg_running = 0;
    time_of_biggest_slope = 0;
    biggest_slope = 0;
    valve_open_time = 0;
    car_start_time = 0;
    valve_opened = false;
    reaction_done = false;
    index = 0;


    Serial.begin(9600);
    pinMode(VALVE_SWITCH_PIN_IN, INPUT);
    pinMode(RELAY_PIN_OUT, OUTPUT);
    pinMode(MULTIMETER_PIN_OUT, OUTPUT);
    digitalWrite(RELAY_PIN_OUT, LOW);
    digitalWrite(MULTIMETER_PIN_OUT, HIGH);
    delay(10);


    // fill array with values
    for (int x = 0; x < AVERAGE_WINDOW_SIZE; x++){
        //Take In Value From Photoresistor; Add to vab
        average_buffer[x] = analogRead(PHOTORESISTOR_PIN_IN);
        time_buffer[x] = float(millis()) / 1000;
        delay(10);
        Serial.println(String(value_avg_running) + " : " + String(average_buffer[x]));
    }

    value_avg_running = average_buffer[AVERAGE_WINDOW_SIZE - 1];
    baseline = value_avg_running;
    Serial.println("Starting recording data");
}

