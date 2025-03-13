#include "data_generation/random_data.h"
#include <string>

int main(){
    std::string path = "data_generation/random_data.csv";
    generate_random_integers(path, -10000, 10000, 100000, 25);
    return 0;
}