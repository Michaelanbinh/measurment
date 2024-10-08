#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <cmath>

using namespace std;

// Hàm ghi lỗi vào log file
void logError(const string& error_message) {
    time_t current_time = time(nullptr);
    tm* timeinfo = localtime(&current_time);
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);

    cerr << timestamp << " " << error_message << endl;
}

// Kiểm tra file có ghi được không
bool is_file_writable(const string& filename) {
    ofstream test_stream(filename, ios::out | ios::app);
    if (test_stream) {
        test_stream.close();
        return true;
    }
    return false;
}


void generateData(int num_sensors, int sampling_time, int simulation_interval) {
    string filename = "sensor_data.csv";

    
    if (is_file_writable(filename)) {
        ofstream file(filename, ios::out | ios::app);

        if (file.is_open()) {
           
            file << "id,time,frequency,amplitude\n";

           
            time_t current_time = time(nullptr);

            
            for (int j = 0; j < simulation_interval; j += sampling_time) {
                tm* timeinfo = localtime(&current_time);
                char timestamp[20];
                strftime(timestamp, sizeof(timestamp), "%Y:%m:%d %H:%M:%S", timeinfo);

              
                for (int i = 1; i <= num_sensors; ++i) {
                    
                    float amplitude = static_cast<float>(rand()) / RAND_MAX * 100; 
                    float frequency = static_cast<float>(rand()) / RAND_MAX * 1000;
                    
                   
                    file << i << "," << timestamp << "," << frequency << "," << amplitude << "\n";
                }

                
                current_time += sampling_time;
            }
            file.close();
            cout << "Data generated and saved to sensor_data.csv" << endl;
        } else {
            logError("Error 03: file access denied\n");
        }   
    } else {
        logError("Error 03: file access denied\n");
    }
}

int main(int argc, char* argv[]) {
    int num_sensors = 1;
    int sampling = 10; 
    int interval = 3600;  

    freopen("task1.log", "w", stderr);

    // Parsing command line arguments
    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        if ((arg == "-n" || arg == "-st" || arg == "-si") && i + 1 < argc) {
            try {
                int value = stoi(argv[++i]);
                if (value <= 0) {
                    logError("Error 02: invalid argument");
                    return 1;
                }
                if (arg == "-n") num_sensors = value;
                else if (arg == "-st") sampling = value;
                else if (arg == "-si") interval = value;
            } catch (const invalid_argument&) {
                logError("Error 02: invalid argument");
                return 1;
            }
        } else {
            logError("Error 01: invalid command");
            return 1;
        }
    }

    generateData(num_sensors, sampling, interval);
    return 0;
}

