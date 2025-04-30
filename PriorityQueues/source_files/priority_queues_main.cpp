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
    PriorityQueue* original, * test;
    std::string keys_path = "temp_keys.txt";
    std::string values_path = "temp_values.txt";

    enum ENUM_PQ : uint8_t {BINARY_HEAP, LINKED_LIST, PQ_COUNT};
    enum ENUM_PQ_METHOD : uint8_t {INSERT_H, INSERT_L, EXTRACT_MAX, FIND_MAX, INCREASE_KEY, DECREASE_KEY, RETURN_SIZE, PQ_METHOD_COUNT};

    unsigned long long result = 0;
    unsigned long long results[PQ_COUNT][PQ_METHOD_COUNT] = {{0, 0, 0, 0, 0, 0, 0},
                                                             {0, 0, 0, 0, 0, 0, 0}};
    std::ofstream files[PQ_METHOD_COUNT];
    std::string filenames[PQ_METHOD_COUNT] = {"PriorityQueues/results/insert_highest.csv",
                                              "PriorityQueues/results/insert_lowest.csv",  
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

    for(uint8_t i = 0; i < PQ_METHOD_COUNT; i++) {files[i] << "SIZE;BinaryHeap;LinkedList" << std::endl;}

    for(unsigned int SIZE : SIZES) {
        std::cout << "SIZE=" << SIZE << std::endl;
        for(uint8_t i = 1; i <= NUM_OF_TIMES; i++) {
            // generating files with keys and values, while assuring that there will be two unique Nodes: (e=-100001, p=0) and (e=100001, p=SIZE*10+1) -> This way we know the biggest and the smallest priority elements beforehand.
            std::ofstream expand_file;
            generate_random_integers(keys_path, (unsigned int)0, SIZE*10, SIZE-2);
            expand_file.open(keys_path, std::ios::app);
            expand_file << 0 << std::endl << SIZE*10+1 << std::endl;
            expand_file.close();
            generate_random_integers(values_path, -100000, 100000, SIZE-2);
            expand_file.open(values_path, std::ios::app);
            expand_file << -100001 << std::endl << 100001 << std::endl;
            expand_file.close();

            original = new BinaryHeap();
            load_from_file(keys_path, values_path, *original);
            
            // BinaryHeap - insert (highest)
            test = original->clone();
            results[BINARY_HEAP][INSERT_H] += measure_time(test, &PriorityQueue::insert, 100002, SIZE*10+2); // inserting element with the new highest priority
            delete test;

            // BinaryHeap - insert (lowest)
            test = original->clone();
            results[BINARY_HEAP][INSERT_L] += measure_time(test, &PriorityQueue::insert, -100002, 0); // inserting element with the lowest priority
            delete test;

            // BinaryHeap - extract_max
            test = original->clone();
            results[BINARY_HEAP][EXTRACT_MAX] += measure_time(test, &PriorityQueue::extract_max);
            delete test;

            // BinaryHeap - find_max
            test = original->clone();
            results[BINARY_HEAP][FIND_MAX] += measure_time(test, &PriorityQueue::find_max);
            delete test;

            // BinaryHeap - modify_key (increase key)
            test = original->clone();
            results[BINARY_HEAP][INCREASE_KEY] += measure_time(test, &PriorityQueue::modify_key, -100001, SIZE*10+2); // modifying key of element with the lowest priority to the new highest priority
            delete test;

            // BinaryHeap - modify_key (decrease key)
            test = original->clone();
            results[BINARY_HEAP][DECREASE_KEY] += measure_time(test, &PriorityQueue::modify_key, 100001, (unsigned int)0); // modifying key of element with the highest priority to the lowest priority
            delete test;

            // BinaryHeap - return_size
            test = original->clone();
            results[BINARY_HEAP][RETURN_SIZE] += measure_time(test, &PriorityQueue::return_size);
            delete test;

            delete original;
            original = new LinkedList();
            load_from_file(keys_path, values_path, *original);

            // LinkedList - insert (highest)
            test = original->clone();
            results[LINKED_LIST][INSERT_H] += measure_time(test, &PriorityQueue::insert, 100002, SIZE*10+2); // inserting element with the new highest priority
            delete test;

            // LinkedList - insert (lowest)
            test = original->clone();
            results[LINKED_LIST][INSERT_L] += measure_time(test, &PriorityQueue::insert, -100002, 0); // inserting element with the lowest priority
            delete test;

            // LinkedList - extract_max
            test = original->clone();
            results[LINKED_LIST][EXTRACT_MAX] += measure_time(test, &PriorityQueue::extract_max);
            delete test;

            // LinkedList - find_max
            test = original->clone();
            results[LINKED_LIST][FIND_MAX] += measure_time(test, &PriorityQueue::find_max);
            delete test;

            // LinkedList - modify_key (increase key)
            test = original->clone();
            results[LINKED_LIST][INCREASE_KEY] += measure_time(test, &PriorityQueue::modify_key, -100001, SIZE*10+2); // modifying key of element with the lowest priority to the new highest priority
            delete test;

            // LinkedList - modify_key (decrease key)
            test = original->clone();
            results[LINKED_LIST][DECREASE_KEY] += measure_time(test, &PriorityQueue::modify_key, 100001, (unsigned int)0); // modifying key of element with the highest priority to the lowest priority
            delete test;

            // LinkedList - return_size
            test = original->clone();
            results[LINKED_LIST][RETURN_SIZE] += measure_time(test, &PriorityQueue::return_size);
            delete test;

            delete original;
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

    // Removing temp files
    if (remove(keys_path.c_str()) != 0) {perror("Error deleting file");}
    if (remove(values_path.c_str()) != 0) {perror("Error deleting file");}
}