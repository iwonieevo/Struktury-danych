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
    unsigned long long results[3][7] = {{0, 0, 0, 0, 0, 0, 0},    // ArrayList - append, prepend, insert, pop_front, pop_back, remove, search
                                        {0, 0, 0, 0, 0, 0, 0},    // SinglyLinkedList - append, prepend, insert, pop_front, pop_back, remove, search
                                        {0, 0, 0, 0, 0, 0, 0}};   // DoublyLinkedList - append, prepend, insert, pop_front, pop_back, remove, search
    std::ofstream file1("Lists/_append.txt"), 
                  file2("Lists/_prepend.txt"), 
                  file3("Lists/_insert.txt"), 
                  file4("Lists/_pop_front.txt"), 
                  file5("Lists/_pop_back.txt"), 
                  file6("Lists/_remove.txt"), 
                  file7("Lists/_search.txt");
    
    for(size_t i = THE_LEAST; i <= THE_MOST; i += STEP) {
        for(size_t j = 1; j <= NUM_OF_TIMES; j++) { 
            std::string path = "data/random_data-" + std::to_string(i) + "-#" + std::to_string(j) + ".txt";
            generate_random_integers(path, -10000, 10000, i);
            
            // append - ArrayList
            test = new ArrayList(i);
            load_from_file(path, *test);
            results[0][0] += measure_time(test, List::prepend, 10001);
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
    
    //       size        ArrayList                                SinglyLinkedList                         DoublyLinkedList
    file1 << i << " " << (results[0][0] / NUM_OF_TIMES) << " " << (results[1][0] / NUM_OF_TIMES) << " " << (results[2][0] / NUM_OF_TIMES) << std::endl;
    file2 << i << " " << (results[0][1] / NUM_OF_TIMES) << " " << (results[1][1] / NUM_OF_TIMES) << " " << (results[2][1] / NUM_OF_TIMES) << std::endl;
    file3 << i << " " << (results[0][2] / NUM_OF_TIMES) << " " << (results[1][2] / NUM_OF_TIMES) << " " << (results[2][2] / NUM_OF_TIMES) << std::endl;
    file4 << i << " " << (results[0][3] / NUM_OF_TIMES) << " " << (results[1][3] / NUM_OF_TIMES) << " " << (results[2][3] / NUM_OF_TIMES) << std::endl;
    file5 << i << " " << (results[0][4] / NUM_OF_TIMES) << " " << (results[1][4] / NUM_OF_TIMES) << " " << (results[2][4] / NUM_OF_TIMES) << std::endl;
    file6 << i << " " << (results[0][5] / NUM_OF_TIMES) << " " << (results[1][5] / NUM_OF_TIMES) << " " << (results[2][5] / NUM_OF_TIMES) << std::endl;
    file7 << i << " " << (results[0][6] / NUM_OF_TIMES) << " " << (results[1][6] / NUM_OF_TIMES) << " " << (results[2][6] / NUM_OF_TIMES) << std::endl;
    }

    file1.close();
    file2.close();
    file3.close();
    file4.close();
    file5.close();
    file6.close();
    file7.close();
    return 0;
}