// #include <Arduino.h>
// #include <SoftwareSerial.h>


// #define PHOTORESISTOR_PIN_IN A0
// #define VALVE_SWITCH_PIN_IN A1 //7
// #define VALVE_PIN_LIMIT 1015
// #define RELAY_PIN_OUT 2

// enum PROGRAM {
//     //Run the Whole program
//     RUN = 0,
//     //Test the Chemical Reaction (No Motor)
//     TEST = 1,
//     //Test the Relay with 1-2 Delay
//     PULSE = 2,
//     //TEST DATA Calibration curve
//     CURVE = 4,
//     //JUST RELAY
//     RELAY = 5
// };

// /*--------------------------------   SELECT TEST PROGRAM   --------------------------------*/

// #define program CURVE


// /*----------------------------   VARIABLES YOU WANT TO CHANGE   ------------------------------*/
// //Average Window size - Smaller: Faster Detection; Bigger: Resistant to Anomalies; Default: 35;
// #define AVERAGE_WINDOW_SIZE 35
// //Slope that will trigger the car movement
// #define SLOPE_LIMIT 25
// //IF TESTING, SECONDS TO TEST
// #define TEST_TIME 30
// //minimum time before car starts to run
// #define SLOPE_GRACE_PERIOD 5

// /*----------------------------   CHEMICAL CALIBRATION CONSTANTS   ------------------------------*/
// #define CAR_A 1.9 //1.67345 //2.13022  // m/s
// #define CAR_B -0.0347561//-3.2255

// // EQUATION : distance = ae^{btime}+c

// #define CURVE_A -0.25
// #define CURVE_B 35
// //#define CURVE_C 4.88783

// //bool car_timed = false;
// #define CAR_START_DELAY 0


// /*--------------------------------   DONT TOUCH THESE   --------------------------------*/

// //Array of Last Few Values
// float average_buffer[AVERAGE_WINDOW_SIZE];

// //Array of Last Few Times
// float time_buffer[AVERAGE_WINDOW_SIZE];


// //float value_avg_running;
// float value_avg_running;
// float time_of_biggest_slope;
// float biggest_slope;
// float valve_open_time;
// float car_start_time;
// int index;

// bool valve_opened;
// bool reaction_done;




// bool measureData();
// void data_setup();
// void data_loop();
// void moveCar();
// void wait();
// void printDataSummary();
// void printCarMove();
// float calcDistance(float time_of_biggest_slope);
// float calcCarTime(float distance);


// void setup() {
//     //INIT
//     value_avg_running = 0;
//     time_of_biggest_slope = 0;
//     biggest_slope = 0;
//     valve_open_time = 0;
//     car_start_time = 0;
//     valve_opened = false;
//     reaction_done = false;
//     index = 0;


//     Serial.begin(9600);
//     pinMode(VALVE_SWITCH_PIN_IN, INPUT);
//     pinMode(RELAY_PIN_OUT, OUTPUT);
//     digitalWrite(RELAY_PIN_OUT, LOW);
//     delay(10);


//     // fill array with values
//     for (int x = 0; x < AVERAGE_WINDOW_SIZE; x++){
//         //Take In Value From Photoresistor; Add to vab
//         average_buffer[x] = analogRead(PHOTORESISTOR_PIN_IN);
//         time_buffer[x] = float(millis()) / 1000;
//         delay(10);
//         Serial.println(String(value_avg_running) + " : " + String(average_buffer[x]));
//     }

//     value_avg_running = average_buffer[AVERAGE_WINDOW_SIZE - 1];

//     Serial.println("Starting recording data");
// }

// void loop() {
//     if (program == RELAY){
//         Serial.println("USING RELAY");
//         digitalWrite(RELAY_PIN_OUT, HIGH);
//         return;
//     }

//     delay(10);
//     if (!valve_opened){
//         wait();
//         return;
//     }

    

//     if (!reaction_done){
//         measureData();
//         return;
//     }

//     if (program == RUN || program == CURVE)
//         moveCar();
    
    
// }

// void wait(){


//     if (analogRead(VALVE_SWITCH_PIN_IN) < VALVE_PIN_LIMIT) {
//         return;
//     } 
//     delay(5);
//     if (analogRead(VALVE_SWITCH_PIN_IN) < VALVE_PIN_LIMIT) {
//         return;
//     }
//     valve_opened = true;
//     valve_open_time = float(millis()) / 1000;
//     Serial.println("Valve Opened");
    
// }


// bool measureData() {
    

//     float time = float(millis()) / 1000;
//     float value = float(analogRead(PHOTORESISTOR_PIN_IN));
//     value_avg_running += (value - average_buffer[index]) / AVERAGE_WINDOW_SIZE;
//     // Serial.println("Time: " + String(time) + ", Rem Time: " + String(time_buffer[index]) + ", Value Avg: " + String(value_avg_running) + ", Rem Value Avg " + String(value_avg_buffer[index]));
//     float slope = (value_avg_running - average_buffer[index]) / (time - time_buffer[index]);
//     average_buffer[index] = value_avg_running;
//     time_buffer[index] = time;
//     index = (index + 1) % AVERAGE_WINDOW_SIZE;
    
//     Serial.println(String(time - valve_open_time) + ", " + String(value) + ", " + String(slope));
    

//     if (abs(slope) > biggest_slope && time - valve_open_time > SLOPE_GRACE_PERIOD) {
//         biggest_slope = abs(slope);
//         time_of_biggest_slope = time;
//     }


//     if (program == TEST && time - valve_open_time >= TEST_TIME){

//         reaction_done = true;
//         printDataSummary();

        
//     }

//     if (program == CURVE){
//         reaction_done = true;
//         time_of_biggest_slope = TEST_TIME;
//         printDataSummary();
//         Serial.println("REACTION DONE, MOVING CAR");
//         printCarMove();
//     }

//     if (program == RUN && abs(biggest_slope) > SLOPE_LIMIT && (time - valve_open_time) > SLOPE_GRACE_PERIOD){
//         reaction_done = true;
//         printDataSummary();
//         Serial.println("REACTION DONE, MOVING CAR");
//         printCarMove();

//     }

//     // if (car_start_time == 0) {
//     //     if (float(millis()) / 1000 - valve_open_time < CAR_START_DELAY) {
//     //         return;
//     //     }
//     //     car_start_time = float(millis()) / 1000;
//     //     digitalWrite(RELAY_PIN_OUT, HIGH);
//     // }



//     return false;
//     // if (abs(slope) > slope_limit && slope < biggest_slope) {
//     //     Serial.println("Stopped recording data");
//     //     moveCar(time_of_biggest_slope);
//     // }
// }

// void printDataSummary(){
//     Serial.println("Stopped recording data");
//     float time_from_valve = time_of_biggest_slope - valve_open_time;
//     float distance = calcDistance(time_of_biggest_slope);
//     float time = calcCarTime(distance);  // ms
//     Serial.println("Biggest Slope: " + String(biggest_slope));
//     Serial.println("Time of Biggest Slope: " + String(time_from_valve));
//     Serial.println("Estimated Distance: " + String(distance));
//     Serial.println("Wait Time: " + String(time));
// }

// void printCarMove(){
//     float time_from_valve = time_of_biggest_slope - valve_open_time;


//     float distance = calcDistance(time_of_biggest_slope);
//     float calcTime = calcCarTime(distance);
//     Serial.println("Time From Valve: " + String(time_from_valve) + ", ESTIMATED DISTANCE " + String(distance) + ", Time for Car Run " + String(calcTime));
// }

// void moveCar() {

//     float distance = calcDistance(time_of_biggest_slope);


//     if (distance > 30){
//         Serial.println("MAX DISTANCE REACHED");
//         distance = 30;
//     }
//     if (distance < 15){
//         Serial.println("MIN DISTANCE REACHED");
//         distance = 15;
//     }
//     float calcTime = calcCarTime(distance);


//     //float curr_time = float(millis()) / 1000;
//     float time_left = calcTime;// - (curr_time - valve_open_time) + CAR_START_DELAY;
//     Serial.println("Time Left: " + String(time_left));
//     digitalWrite(RELAY_PIN_OUT, HIGH);
//     delay(time_left * 1000);
//     digitalWrite(RELAY_PIN_OUT, LOW);
//     Serial.println("PROGRAM END");
//     delay(100);
//     exit(0);


// }

// float calcDistance(float time_of_biggest_slope){
//     //float calcDistance = CURVE_A * pow(EULER, CURVE_B * time_of_biggest_slope) + CURVE_C;
//     float calcdistance = CURVE_A * (time_of_biggest_slope - valve_open_time) + CURVE_B;
//     return calcdistance;
// }

// float calcCarTime(float distance){
//     return distance * CAR_A + CAR_B;
// }

// // void data_setup() {
// //     Serial.begin(9600);
// //     pinMode(VALVE_SWITCH_PIN_IN, INPUT);
// //     Serial.println("Starting recording data");
// // }

// // void data_loop() {
// //     if (digitalRead(VALVE_SWITCH_PIN_IN) != HIGH && valve_open_time == 0) {
// //         return;
// //     }

// //     if (valve_open_time == 0) {
// //         valve_open_time = millis();
// //         Serial.println("Valve Opened");
// //     }

// //     long time = float(millis() - valve_open_time);
// //     int value = analogRead(PHOTORESISTOR_PIN_IN);
// //     Serial.println(String(time) + ", " + String(value));
// //     delay(10);
// // }