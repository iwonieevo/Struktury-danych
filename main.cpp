#include "data_generation/random_data.h"
#include "Lists/List.h"
#include <fstream>
#include <iostream>
#include <string>
#include <chrono>
#include <filesystem>

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
    std::string path;
    
    unsigned int MAX_NUM_OF_VALUES = 100000;
    unsigned int NUM_OF_STEPS = 20;
    unsigned int NUM_OF_TIMES = 50;

    unsigned long long results[3][7] = {{0, 0, 0, 0, 0, 0, 0},    // ArrayList - append, prepend, insert, pop_front, pop_back, remove, search
                                        {0, 0, 0, 0, 0, 0, 0},    // SinglyLinkedList - append, prepend, insert, pop_front, pop_back, remove, search
                                        {0, 0, 0, 0, 0, 0, 0}};   // DoublyLinkedList - append, prepend, insert, pop_front, pop_back, remove, search
    // Opening output files
    std::ofstream files[7];
    std::string filenames[7] = {"Lists/results/append.txt", 
                                "Lists/results/prepend.txt", 
                                "Lists/results/insert.txt", 
                                "Lists/results/pop_front.txt", 
                                "Lists/results/pop_back.txt", 
                                "Lists/results/remove.txt", 
                                "Lists/results/search.txt"
                                };
    for(int i = 0; i < 7; i++) {
        files[i].open(filenames[i]);
        if(!files[i]) {
            std::cerr << "Error opening " << filenames[i] << std::endl;
        }
    }
    
    for(unsigned int i = MAX_NUM_OF_VALUES / NUM_OF_STEPS; i <= MAX_NUM_OF_VALUES; i += MAX_NUM_OF_VALUES / NUM_OF_STEPS) {
        for(unsigned int j = 1; j <= NUM_OF_TIMES; j++) { 
            path = "data/random_data-" + std::to_string(i) + "-#" + std::to_string(j) + ".txt";
            if (!std::filesystem::exists(path)) {
                generate_random_integers(path, -10000, 10000, i);
            }
            
            // append - ArrayList
            test = new ArrayList(i);
            load_from_file(path, *test);
            results[0][0] += measure_time(test, List::append, 10001);
            delete test;
            
            // TODO: dokończyć dla pozostałych operacji i SD, pesymistyczne/średnie przypadki (więc ArrayList zawsze na limicie, insert i remove w środku raczej gdzieś, search taki że nie ma na pewno takiego elementu)

            // prepend - ArrayList
            // insert - ArrayList
            // pop_front - ArrayList
            // pop_back - ArrayList
            // remove - ArrayList
            // search - ArrayList

            // append - SinglyLinkedList
            // prepend - SinglyLinkedList
            // insert - SinglyLinkedList
            // pop_front - SinglyLinkedList
            // pop_back - SinglyLinkedList
            // remove - SinglyLinkedList
            // search - SinglyLinkedList

            // append - DoublyLinkedList
            // prepend - DoublyLinkedList
            // insert - DoublyLinkedList
            // pop_front - DoublyLinkedList
            // pop_back - DoublyLinkedList
            // remove - DoublyLinkedList
            // search - DoublyLinkedList
        }
        
        // Saving mean times to output files
        std::cout << "Saving output for size=" << i << "..." << std::endl;
        for(int k = 0; k < 7; k++) {
            files[k] << i;
            for(int m = 0; m < 3; m++) {
                files[k] << ";" << (results[m][k] / NUM_OF_TIMES);
                results[m][k] = 0;
            }
            files[k] << std::endl;
        }
    }

    // Closing output files
    for(int i = 0; i < 7; i++) {
        files[i].close();
    }

    return 0;
}