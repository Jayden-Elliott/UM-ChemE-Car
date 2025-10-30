#define CAR_A 3.448 //1.67345 //2.13022  // m/s .31
#define CAR_B -0.0347561//-3.2255

// EQUATION : distance = ae^{btime}+c
#define CURVE_A -.33333
#define CURVE_B 31.66667

#include <string>

class CarInfo{
    private:

    float car_start_time;
    float carRunTime;
    
    bool valve_opened;
    bool reaction_done;
    
    int index;

    PROGRAM prog;

    public:

    CarInfo() 
        :CarInfo(RUN){   
        }
    
    CarInfo(PROGRAM p)
        : valve_open_time(0), car_start_time(0), carRunTime(0), 
        valve_opened(false), reaction_done(false), index(0),
        prog(p) { }

    std::string toString() {
        return "Valve open time: " + std::to_string(valve_open_time) + ", Car start time: " + std::to_string(car_start_time) + ", Car run time: " 
        + std::to_string(carRunTime) + ", Is valve opened: " +  valve_opened + ", Is reaction done: " + reaction_done + ", index: " + index;
    }

    void runCar(float timeOfActivation){
        float calcDistance = CURVE_A * (timeOfActivation - valve_open_time - carRunTime/1000) + CURVE_B;
        float carTime = calcDistance * CAR_A + CAR_B;

    }

};

enum PROGRAM {
    //Run the Whole program
    RUN = 0,
    //Test the Chemical Reaction (No Motor)
    TEST = 1,
    //Test the Relay with 1-2 Delay
    PULSE = 2,
    //TEST DATA Calibration curve
    CURVE = 4,
    //JUST RELAY
    RELAY = 5
};

struct Datum{

};

Datum makeDatum(float time, float value){
    
}