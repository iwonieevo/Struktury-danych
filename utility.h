#pragma once
#include <string>
#include <random>
#include <fstream>
#include <iostream>
#include <chrono>

// Generates a .txt file containing randomly generated integers
template <typename IntegralType>
void generate_random_integers(std::string& dest_path, IntegralType min, IntegralType max, size_t n_rows){
    if constexpr (!std::is_integral_v<IntegralType>) {
        std::cerr << "Error: generate_random_integers only supports integral types.\n";
        return;
    }

    std::random_device rd; // random seed
    std::mt19937 gen(rd()); // generator
    std::uniform_int_distribution<IntegralType> dist(min, max); // range
    std::ofstream file(dest_path); // opening file
    if(!file.is_open()){
        std::cerr << "Error: couldn't open the file: " << dest_path << std::endl;
        return;
    }
    
    for(size_t i = 0; i < n_rows; i++){
        file << dist(gen) << "\n";
    }
    file.close();
};

// Function that times method execution
template <typename ObjectType, typename ReturnType, typename... Parameters>
unsigned long long measure_time(ObjectType* object, ReturnType (ObjectType::*method)(Parameters...), Parameters... params) {
    auto start = std::chrono::high_resolution_clock::now(); // start tracking time
    (object->*method)(params...);
    auto end = std::chrono::high_resolution_clock::now(); // stop tracking time
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    return duration.count();
}