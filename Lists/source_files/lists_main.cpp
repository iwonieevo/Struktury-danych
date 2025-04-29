#include "../headers/lists_main.h"

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

int lists_main(std::initializer_list<unsigned int> SIZES, uint8_t NUM_OF_TIMES) {
    List* test;
    std::string path = "temp_file.txt";
    
    enum ENUM_LIST : uint8_t {AL, SLL, DLL, LIST_COUNT};
    enum ENUM_LIST_METHOD : uint8_t {APPEND, PREPEND, INSERT, POP_FRONT, POP_BACK, REMOVE, SEARCH, LIST_METHOD_COUNT};

    unsigned long long result = 0;
    unsigned long long results[LIST_COUNT][LIST_METHOD_COUNT] = {{0, 0, 0, 0, 0, 0, 0},    // ArrayList - append, prepend, insert, pop_front, pop_back, remove, search
                                                                 {0, 0, 0, 0, 0, 0, 0},    // SinglyLinkedList - append, prepend, insert, pop_front, pop_back, remove, search
                                                                 {0, 0, 0, 0, 0, 0, 0}};   // DoublyLinkedList - append, prepend, insert, pop_front, pop_back, remove, search

    unsigned long long results_max[LIST_COUNT][LIST_METHOD_COUNT] = {{0, 0, 0, 0, 0, 0, 0},    // ArrayList - append, prepend, insert, pop_front, pop_back, remove, search
                                                                     {0, 0, 0, 0, 0, 0, 0},    // SinglyLinkedList - append, prepend, insert, pop_front, pop_back, remove, search
                                                                     {0, 0, 0, 0, 0, 0, 0}};   // DoublyLinkedList - append, prepend, insert, pop_front, pop_back, remove, search
    // Opening output files
    std::ofstream files[LIST_METHOD_COUNT];
    std::string filenames[LIST_METHOD_COUNT] = {"Lists/results/append.txt", 
                                                "Lists/results/prepend.txt", 
                                                "Lists/results/insert.txt", 
                                                "Lists/results/pop_front.txt", 
                                                "Lists/results/pop_back.txt", 
                                                "Lists/results/remove.txt", 
                                                "Lists/results/search.txt"
                                            };
    for(uint8_t i = 0; i < LIST_METHOD_COUNT; i++) {
        files[i].open(filenames[i]);
        if(!files[i]) {std::cerr << "Error opening " << filenames[i] << std::endl;}
    }

    for(uint8_t i = 0; i < LIST_METHOD_COUNT; i++) {files[i] << "SIZE;ArrayList;ArrayList - max;SinglyLinkedList;SinglyLinkedList - max;DoublyLinkedList;DoublyLinkedList - max";}
    
    for(unsigned int SIZE : SIZES) {
        std::cout << "SIZE=" << SIZE << std::endl;
        for(uint8_t i = 1; i <= NUM_OF_TIMES; i++) {
            generate_random_integers(path, -10000, 10000, SIZE);
            
            // ArrayList - append
            test = new ArrayList(SIZE);
            load_from_file(path, *test);
            result = measure_time(test, &List::append, 10001);
            results[AL][APPEND] += result;
            results_max[AL][APPEND] = result > results_max[AL][APPEND] ? result : results_max[AL][APPEND];
            delete test;
            
            // ArrayList - prepend
            test = new ArrayList(SIZE);
            load_from_file(path, *test);
            result = measure_time(test, &List::prepend, 10001);
            results[AL][PREPEND] += result;
            results_max[AL][PREPEND] = result > results_max[AL][PREPEND] ? result : results_max[AL][PREPEND];
            delete test;

            // ArrayList - insert
            test = new ArrayList(SIZE);
            load_from_file(path, *test);
            result = measure_time(test, &List::insert, 10001, (size_t)SIZE/2);
            results[AL][INSERT] += result;
            results_max[AL][INSERT] = result > results_max[AL][INSERT] ? result : results_max[AL][INSERT];
            delete test;

            // ArrayList - pop_front
            test = new ArrayList(SIZE);
            load_from_file(path, *test);
            result = measure_time(test, &List::pop_front);
            results[AL][POP_FRONT] += result;
            results_max[AL][POP_FRONT] = result > results_max[AL][POP_FRONT] ? result : results_max[AL][POP_FRONT];
            delete test;

            // ArrayList - pop_back
            test = new ArrayList(SIZE);
            load_from_file(path, *test);
            result = measure_time(test, &List::pop_back);
            results[AL][POP_BACK] += result;
            results_max[AL][POP_BACK] = result > results_max[AL][POP_BACK] ? result : results_max[AL][POP_BACK];
            delete test;

            // ArrayList - remove
            test = new ArrayList(SIZE);
            load_from_file(path, *test);
            result = measure_time(test, &List::remove, (size_t)SIZE/2);
            results[AL][REMOVE] += result;
            results_max[AL][REMOVE] = result > results_max[AL][REMOVE] ? result : results_max[AL][REMOVE];
            delete test;

            // ArrayList - search
            test = new ArrayList(SIZE);
            load_from_file(path, *test);
            result = measure_time(test, &List::search, 10001);
            results[AL][SEARCH] += result;
            results_max[AL][SEARCH] = result > results_max[AL][SEARCH] ? result : results_max[AL][SEARCH];
            delete test;

            // SinglyLinkedList - append
            test = new SinglyLinkedList();
            load_from_file(path, *test);
            result = measure_time(test, &List::append, 10001);
            results[SLL][APPEND] += result;
            results_max[SLL][APPEND] = result > results_max[SLL][APPEND] ? result : results_max[SLL][APPEND];
            delete test;

            // SinglyLinkedList - prepend
            test = new SinglyLinkedList();
            load_from_file(path, *test);
            result = measure_time(test, &List::prepend, 10001);
            results[SLL][PREPEND] += result;
            results_max[SLL][PREPEND] = result > results_max[SLL][PREPEND] ? result : results_max[SLL][PREPEND];
            delete test;

            // SinglyLinkedList - insert
            test = new SinglyLinkedList();
            load_from_file(path, *test);
            result = measure_time(test, &List::insert, 10001, (size_t)SIZE/2);
            results[SLL][INSERT] += result;
            results_max[SLL][INSERT] = result > results_max[SLL][INSERT] ? result : results_max[SLL][INSERT];
            delete test;
            
            // SinglyLinkedList - pop_front
            test = new SinglyLinkedList();
            load_from_file(path, *test);
            result = measure_time(test, &List::pop_front);
            results[SLL][POP_FRONT] += result;
            results_max[SLL][POP_FRONT] = result > results_max[SLL][POP_FRONT] ? result : results_max[SLL][POP_FRONT];
            delete test;

            // SinglyLinkedList - pop_back
            test = new SinglyLinkedList();
            load_from_file(path, *test);
            result = measure_time(test, &List::pop_back);
            results[SLL][POP_BACK] += result;
            results_max[SLL][POP_BACK] = result > results_max[SLL][POP_BACK] ? result : results_max[SLL][POP_BACK];
            delete test;

            // SinglyLinkedList - remove
            test = new SinglyLinkedList();
            load_from_file(path, *test);
            result = measure_time(test, &List::remove, (size_t)SIZE/2);
            results[SLL][REMOVE] += result;
            results_max[SLL][REMOVE] = result > results_max[SLL][REMOVE] ? result : results_max[SLL][REMOVE];
            delete test;

            // SinglyLinkedList - search
            test = new SinglyLinkedList();
            load_from_file(path, *test);
            result = measure_time(test, &List::search, 10001);
            results[SLL][SEARCH] += result;
            results_max[SLL][SEARCH] = result > results_max[SLL][SEARCH] ? result : results_max[SLL][SEARCH];
            delete test;

            // DoublyLinkedList - append
            test = new DoublyLinkedList();
            load_from_file(path, *test);
            result = measure_time(test, &List::append, 10001);
            results[DLL][APPEND] += result;
            results_max[DLL][APPEND] = result > results_max[DLL][APPEND] ? result : results_max[DLL][APPEND];
            delete test;

            // DoublyLinkedList - prepend
            test = new DoublyLinkedList();
            load_from_file(path, *test);
            result = measure_time(test, &List::prepend, 10001);
            results[DLL][PREPEND] += result;
            results_max[DLL][PREPEND] = result > results_max[DLL][PREPEND] ? result : results_max[DLL][PREPEND];
            delete test;

            // DoublyLinkedList - insert
            test = new DoublyLinkedList();
            load_from_file(path, *test);
            result = measure_time(test, &List::insert, 10001, (size_t)SIZE/2);
            results[DLL][INSERT] += result;
            results_max[DLL][INSERT] = result > results_max[DLL][INSERT] ? result : results_max[DLL][INSERT];
            delete test;

            // DoublyLinkedList - pop_front
            test = new DoublyLinkedList();
            load_from_file(path, *test);
            result = measure_time(test, &List::pop_front);
            results[DLL][POP_FRONT] += result;
            results_max[DLL][POP_FRONT] = result > results_max[DLL][POP_FRONT] ? result : results_max[DLL][POP_FRONT];
            delete test;

            // DoublyLinkedList - pop_back
            test = new DoublyLinkedList();
            load_from_file(path, *test);
            result = measure_time(test, &List::pop_back);
            results[DLL][POP_BACK] += result;
            results_max[DLL][POP_BACK] = result > results_max[DLL][POP_BACK] ? result : results_max[DLL][POP_BACK];
            delete test;

            // DoublyLinkedList - remove
            test = new DoublyLinkedList();
            load_from_file(path, *test);
            result = measure_time(test, &List::remove, (size_t)SIZE/2);
            results[DLL][REMOVE] += result;
            results_max[DLL][REMOVE] = result > results_max[DLL][REMOVE] ? result : results_max[DLL][REMOVE];
            delete test;

            // DoublyLinkedList - search
            test = new DoublyLinkedList();
            load_from_file(path, *test);
            result = measure_time(test, &List::search, 10001);
            results[DLL][SEARCH] += result;
            results_max[DLL][SEARCH] = result > results_max[DLL][SEARCH] ? result : results_max[DLL][SEARCH];
            delete test;
        }
        
        // Saving mean and max times to output files
        std::cout << "Saving output..." << std::endl;
        for(uint8_t i = 0; i < LIST_METHOD_COUNT; i++) {
            files[i] << SIZE;
            for(uint8_t j = 0; j < LIST_COUNT; j++) {
                files[i] << ";" << (results[j][i] / NUM_OF_TIMES) << ";" << results_max[j][i];
                results[j][i] = 0;
            }
            files[i] << std::endl;
        }
    }

    // Closing output files
    for(uint8_t i = 0; i < LIST_METHOD_COUNT; i++) {files[i].close();}

    // Removing temp file
    if (remove(path.c_str()) != 0) {perror("Error deleting file");}
    return 0;
}