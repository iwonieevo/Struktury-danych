#include "random_data.h"
#include <random>
#include <fstream>
#include <iostream>

void generate_random_integers(std::string& dest_path, int min, int max, size_t n_rows){
    std::random_device rd; // random seed
    std::mt19937 gen(rd()); // generator
    std::uniform_int_distribution<int> dist(min, max); // range
    std::ofstream file(dest_path); // opening file
    if(!file.is_open()){
        std::cout << "Error: couldn't open the file: " << dest_path << std::endl;
        return;
    }
    
    for(size_t i = 0; i < n_rows; i++){
        file << dist(gen) << "\n";
    }
    file.close();
};
