#include "../headers/priority_queues_main.h"

void load_from_file(const std::string& keys_path, std::string& values_path, PriorityQueue& queue) {
    // opening files
    std::ifstream keys(keys_path);
    std::ifstream values(values_path);
    if(!keys.is_open() || !values.is_open()) {
        std::cerr << "Error: couldn't open the files: " << keys_path << " or " << values_path;
        return;
    }

    int value;
    unsigned int key;
    while(keys >> key && values >> value) {
        queue.insert(value, key);
    }
    keys.close();
}

void priority_queues_main(std::initializer_list<unsigned int> SIZES, uint8_t NUM_OF_TIMES) {
    std::cout << "Priority Queues main function executing...\n\n";
    PriorityQueue* test;
    std::string keys_path = "temp_keys.txt";
    std::string values_path = "temp_values.txt";

    enum ENUM_PQ : uint8_t {BINARY_HEAP, PLACEHOLDER, PQ_COUNT}; // ### TODO: @jubilanttae - replace PLACEHOLDER with less ambigous name ###
    enum ENUM_PQ_METHOD : uint8_t {INSERT, EXTRACT_MAX, FIND_MAX, INCREASE_KEY, DECREASE_KEY, RETURN_SIZE, PQ_METHOD_COUNT};

    unsigned long long result = 0;
    unsigned long long results[PQ_COUNT][PQ_METHOD_COUNT] = {{0, 0, 0, 0, 0, 0},   // BinaryHeap - insert, extract_max, find_max, increase_key, decrease_key, return_size
                                                             {0, 0, 0, 0, 0, 0}};  // Placeholder - insert, extract_max, find_max, increase_key, decrease_key, return_size
    std::ofstream files[PQ_METHOD_COUNT];
    std::string filenames[PQ_METHOD_COUNT] = {"PriorityQueues/results/insert.csv", 
                                               "PriorityQueues/results/extract_max.csv", 
                                               "PriorityQueues/results/find_max.csv", 
                                               "PriorityQueues/results/increase_key.csv", 
                                               "PriorityQueues/results/decrease_key.csv",
                                               "PriorityQueues/results/return_size.csv"
                                             };
    for(uint8_t i = 0; i < PQ_METHOD_COUNT; i++) {
        files[i].open(filenames[i]);
        if(!files[i]) {std::cerr << "Error opening " << filenames[i] << std::endl;}
    }

    for(uint8_t i = 0; i < PQ_METHOD_COUNT; i++) {files[i] << "SIZE;BinaryHeap;PLACEHOLDER" << std::endl;} // ### TODO: @jubilanttae - replace PLACEHOLDER with less ambigous name ###

    for(unsigned int SIZE : SIZES) {
        std::cout << "SIZE=" << SIZE << std::endl;
        for(uint8_t i = 1; i <= NUM_OF_TIMES; i++) {
            generate_random_integers(keys_path, (unsigned int)0, SIZE*10, SIZE);
            generate_random_integers(values_path, -100000, 100000, SIZE);

            // PairingHeap - insert
            test = new BinaryHeap();
            load_from_file(keys_path, values_path, *test);
            results[BINARY_HEAP][INSERT] += measure_time(test, &PriorityQueue::insert, 100001, SIZE*5);
            delete test;

            // PairingHeap - extract_max
            test = new BinaryHeap();
            load_from_file(keys_path, values_path, *test);
            results[BINARY_HEAP][EXTRACT_MAX] += measure_time(test, &PriorityQueue::extract_max);
            delete test;

            // PairingHeap - find_max
            test = new BinaryHeap();
            load_from_file(keys_path, values_path, *test);
            results[BINARY_HEAP][FIND_MAX] += measure_time(test, &PriorityQueue::find_max);
            delete test;

            // PairingHeap - modify_key (modifying max element - increase key)
            test = new BinaryHeap();
            load_from_file(keys_path, values_path, *test);
            results[BINARY_HEAP][INCREASE_KEY] += measure_time(test, &PriorityQueue::modify_key, test->find_max(), SIZE*10+1);
            delete test;

            // PairingHeap - modify_key (modifying max element - decrease key)
            test = new BinaryHeap();
            load_from_file(keys_path, values_path, *test);
            results[BINARY_HEAP][DECREASE_KEY] += measure_time(test, &PriorityQueue::modify_key, test->find_max(), (unsigned int)0);
            delete test;

            // PairingHeap - return_size
            test = new BinaryHeap();
            load_from_file(keys_path, values_path, *test);
            results[BINARY_HEAP][RETURN_SIZE] += measure_time(test, &PriorityQueue::return_size);
            delete test;

            // ###########################################################################
            // ### TODO: @jubilanttae - implement other priority queue and its methods ###
            // ###########################################################################
        }

        // Saving mean and max times to output files
        std::cout << "Saving output..." << std::endl;
        for(uint8_t i = 0; i < PQ_METHOD_COUNT; i++) {
            files[i] << SIZE;
            for(uint8_t j = 0; j < PQ_COUNT; j++) {
                files[i] << ";" << (results[j][i] / NUM_OF_TIMES);
                results[j][i] = 0;
            }
            files[i] << std::endl;
        }
    }

    // Closing output files
    for(uint8_t i = 0; i < PQ_METHOD_COUNT; i++) {files[i].close();}

    // Removing temp file
    if (remove(keys_path.c_str()) != 0) {perror("Error deleting file");}
    if (remove(values_path.c_str()) != 0) {perror("Error deleting file");}
}