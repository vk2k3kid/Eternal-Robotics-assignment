#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

struct SensorData {
    double s1_distance;
    double s2_distance;
};

// Function to calculate angle in degrees
double calculateAngle(double distance1, double distance2) {
    return atan(abs(distance1 - distance2) / 30.0) * 180.0 / M_PI;
}

// Function to calculate motor pulses for rotation
int calculateRotationPulses(double angle) {
    int pulsesPerRotation = 2000;
    return static_cast<int>(angle / 360.0 * pulsesPerRotation);
}

// Function to calculate motor pulses for distance
int calculateDistancePulses(double distance) {
    double wheelDiameter = 5.0; // cm
    int pulsesPerRotation = 2000;
    return static_cast<int>(distance / (M_PI * wheelDiameter) * pulsesPerRotation);
}

// Function to determine rotation direction
string determineRotationDirection(double distance1, double distance2) {
    return distance1 > distance2 ? "Clockwise" : "Counterclockwise";
}

int main() {
    ifstream inputFile("input.csv");
    ofstream outputFile("output.csv");

    if (!inputFile) {
        cout << "Error opening input.csv" << endl;
        return 1;
    }

    // Read and skip header
    string header;
    getline(inputFile, header);

    vector<SensorData> sensorDataList;

    string line;
    while (getline(inputFile, line)) {
        SensorData data;
        stringstream ss(line);
        ss >> data.s1_distance >> data.s2_distance;
        sensorDataList.push_back(data);
    }

    outputFile << "Angle,M1 Ticks,M2 Ticks,M3 Ticks,M4 Ticks,Direction,M1 Ticks,M2 Ticks,M3 Ticks,M4 Ticks,Direction" << endl;

    for (const SensorData& data : sensorDataList) {
        double angle = calculateAngle(data.s1_distance, data.s2_distance);
        int rotationPulses = calculateRotationPulses(angle);
        int distancePulses = calculateDistancePulses(data.s1_distance);
        string rotationDirection = determineRotationDirection(data.s1_distance, data.s2_distance);

        outputFile << angle << ","
                   << rotationPulses << "," << rotationPulses << ","
                   << rotationPulses << "," << rotationPulses << ","
                   << rotationDirection << ","
                   << distancePulses << "," << distancePulses << ","
                   << distancePulses << "," << distancePulses << ","
                   << "Forward" << endl;
    }

    inputFile.close();
    outputFile.close();

    return 0;
}
