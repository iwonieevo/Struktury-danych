#include "data_generation/random_data.h"
#include "Lists/List.h"
#include <fstream>
#include <iostream>
#include <string>

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

/* Function generating files with random integers. from - the smallest quantity of values, to - the largest quantity of values, step - step of quantity, times - number of copy for each step
 e.g. for from = 5000, to = 100000, step = 5000, times = 25, there will be 25 files for each of the quantities so 25 files of files containing 5k integers, 25 files containing 10k integers,..., 25 files containing 100k integers */
void generate_data_files(size_t from, size_t to, size_t step, size_t times) {
    for(size_t i = from; i <= to; i += step){
        for(size_t j = 1; j <= times; j++){
            std::string path = "data/random_data-" + std::to_string(i) + "-#" + std::to_string(j) + ".txt";
            generate_random_integers(path, -10000, 10000, i);
        }
    }
}

int main(){
    // generate_data_files(5000, 100000, 5000, 25);
    List* test;
    std::cout << "Array List:\n";
    test = new ArrayList;
    test->append(4);
    test->prepend(5);
    test->insert(3, 1);
    test->show();
    test->prepend(test->pop_back());
    std::cout << test->search(4) << std::endl;
    test->show();
    test->remove(1);
    test->pop_front();
    test->show();
    std::cout << test->search(4) << std::endl;
    delete test;

    std::cout << "\nSingly Linked List:\n";
    test = new SinglyLinkedList;
    test->append(4);
    test->prepend(5);
    test->insert(3, 1);
    test->show();
    test->prepend(test->pop_back());
    std::cout << test->search(4) << std::endl;
    test->show();
    test->remove(1);
    test->pop_front();
    test->show();
    std::cout << test->search(4) << std::endl;
    delete test;

    std::cout << "\nPress Enter to continue...";
    std::cin.get();  // Waits for the user to press Enter
    std::cout << "\n\nLoading data from files - ArrayList:\n";
    test = new ArrayList(5000);
    load_from_file("data/random_data-5000-#1.txt", *test);
    test->show();
    delete test;

    std::cout << "\nPress Enter to continue...";
    std::cin.get();  // Waits for the user to press Enter
    std::cout << "\n\nLoading data from files - SinglyLinkedList:\n";
    test = new SinglyLinkedList();
    load_from_file("data/random_data-5000-#1.txt", *test);
    test->show();
    delete test;
    return 0;
}