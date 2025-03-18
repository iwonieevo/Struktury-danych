#include "data_generation/random_data.h"
#include "Lists/List.h"
#include <fstream>
#include <iostream>
#include <string>
#include <chrono>

// Function loading data into List
void load_from_file(const std::string& source_path, List& list) {
    std::ifstream file(source_path); // opening file
    if(!file.is_open()) {
        std::cout << "Error: couldn't open the file: " << source_path;
        return;
    }
    
    int value;
    while(file >> value) {
        list.append(value);
    }
    file.close();
}

// Function that times method execution
template <typename ReturnType, typename... Parameters>
unsigned long long measure_time(List* list, ReturnType (List::*method)(Parameters...), Parameters... params) {
    auto start = std::chrono::high_resolution_clock::now(); // start tracking time
    (list->*method)(params...);
    auto end = std::chrono::high_resolution_clock::now(); // stop tracking time
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    return duration.count();
}

int main(){
    List* test;
    size_t THE_LEAST = 5000;
    size_t THE_MOST = 100000;
    size_t STEP = 5000;
    size_t NUM_OF_TIMES = 25;
    for(size_t i = THE_LEAST; i <= THE_MOST; i += STEP) {
        for(size_t j = 1; j <= NUM_OF_TIMES; j++) {
            std::string path = "data/random_data-" + std::to_string(i) + "-#" + std::to_string(j) + ".txt";
            // generate_random_integers(path, -10000, 10000, i);
            test = new ArrayList(i);
            load_from_file(path, *test);
            auto time = measure_time(test, List::prepend, 10001);
            std::cout << "ArrayList;" << i << ";#" << j << ";" << time << std::endl;
            delete test;
        }
    }
    // TODO: dokończyć dla pozostałych operacji i SD, przemyśleć jak zapisywać wyniki, przemyśleć formę badań
    return 0;
}