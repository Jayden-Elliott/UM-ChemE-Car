#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <cmath>
using namespace std;

int last_20[20] = {100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100};
int rolling_index = 0;
int start_time = 0;
int highest = 0;
int lowest = 1023;
bool peaked = false;
bool bottomed = false;
double speed = 0.0005;  // in m/ms
double min_mass = 0.1;
double max_mass = 0.4;
double rxn_time;

int main() {
    ifstream in("/Users/jayden/Documents/Code/ChemE_Car/data/10_31_2022_0.3gNaOH_0.03gKMnO4.csv");
    string line;
    while (getline(in, line)) {

        int millis = stoi(line.substr(0, line.find(',')));
        int val = stoi(line.substr(line.find(',') + 1, line.size()));
        last_20[rolling_index] = val;
        rolling_index = (rolling_index + 1) % 20;
        int avg = 0;
        for (int x : last_20) {
            avg += x / 20;
        }

        if (!peaked) {
            if (avg > highest) {
                highest = avg;
            } else if (highest > 600) {
                peaked = true;
                cout << "Peak time: " << millis << ", Peak avg: " << val << ", Highest avg: " << highest << endl;
            }
        } else if (!bottomed) {
            if (avg < lowest) {
                lowest = avg;
            } else if (lowest < 800 && avg > lowest + 5) {
                bottomed = true;
                highest = 0;
                start_time = millis;
                cout << "Bottom time: " << millis << ", Bottom avg: " << val << endl;
            }
        } else if (millis - start_time >= 400) {
            if (avg > highest) {
                highest = avg;
            } else if (highest > lowest + 50 && avg < highest - 5) {
                rxn_time = (double)(millis - start_time);
                cout << "End time: " << millis << ", End avg: " << val << endl;
                cout << "Time to peak: " << rxn_time << endl;
                double mass = (1 / sqrt(rxn_time) - 0.0048) / 0.0271;
                cout << "Mass: " << mass << endl;
                double distance = 20 * (mass - min_mass) / (max_mass - min_mass);
                cout << "Distance: " << distance << endl;
                double time = distance / speed;
                cout << "Time: " << time << endl;
                double wait_start = millis;
                break;
            }
        }
    }
}