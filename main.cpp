#include "random_data.h"

int main(){
    std::string path = "random_data.csv";
    generate_random_integers(path, -10000, 10000, 100000, 25);
    return 0;
}