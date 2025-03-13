#include "random_data.h"

void generate_random_integers(std::string& dest_path, int min, int max, size_t n_rows, size_t n_columns){
    std::random_device rd; // random seed
    std::mt19937 gen(rd()); // generator
    std::uniform_int_distribution<int32_t> dist(min, max); // range
    std::ofstream file(dest_path); // opening file
    if(file.is_open()){
        for(size_t i = 0; i < n_rows; i++){
            for(size_t j = 0; j < n_columns; j++){
                file << dist(gen) << ";";
            }
            file << "\n";
        }
        file.close();
        std::cout << "Successfuly opened the file: " << dest_path;
    } else{
        std::cout << "Error: couldn't open the file: " << dest_path;
    }
};
