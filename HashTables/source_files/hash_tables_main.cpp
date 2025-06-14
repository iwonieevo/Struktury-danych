#include "../headers/hash_tables_main.h"

void generate_keys(std::string& dest_path, std::string& values_path) {
    std::ifstream values(values_path);
    if(!values.is_open()) {
        std::cerr << "Error: couldn't open the file: " << values_path << std::endl;
        return;
    }
    std::ofstream keys(dest_path);
    if(!keys.is_open()) {
        std::cerr << "Error: couldn't open the file: " << dest_path << std::endl;
        return;
    }
    
    std::random_device rd; // random seed
    std::mt19937 gen(rd()); // generator
    std::uniform_int_distribution<int> dist(static_cast<int>('a'), static_cast<int>('z'));

    int value;
    std::string key;
    while(values >> value) {
        key = "";
        for(uint8_t i = 0; i < 10; i++) {
            key.push_back(dist(gen));
        }
        key.append(std::to_string(value));
        keys << key << std::endl;
    }
    values.close();
    keys.close();
}

void load_from_file(const std::string& k_path, const std::string& v_path, HashTable& dict) {
    std::ifstream values(v_path);
    if(!values.is_open()) {
        std::cerr << "Error: couldn't open the file: " << v_path << std::endl;
        return;
    }
    std::ifstream keys(k_path);
    if(!keys.is_open()) {
        std::cerr << "Error: couldn't open the file: " << k_path << std::endl;
        return;
    }

    int value;
    std::string key;
    while(keys >> key && values >> value) {
        dict.insert(key, value);
    }
    values.close();
    keys.close();
}

void unit_tests(uint8_t bucket_type) {
    HashTable* test;
    std::string values_path = "temp_values.txt";
    std::string keys_path = "temp_keys.txt";
    generate_random_integers(values_path, -100, 100, 15);
    generate_keys(keys_path, values_path);
    for (size_t table_size : {2, 7, 12}) {
        switch(bucket_type) {
            case 0:
                std::cout << "\n\n%%%%%%%%% Running unit tests: table_size=" << table_size << "; ChainAVL %%%%%%%%%\n";
                test = new ChainAVL(table_size);
                break;
            case 1:
                std::cout << "\n\n%%%%%%%%% Running unit tests: table_size=" << table_size << "; OpenAddressing %%%%%%%%%\n";
                test = new OpenAddressing(table_size);
                break;
            case 2:
                std::cout << "\n\n%%%%%%%%% Running unit tests: table_size=" << table_size << "; CuckooHashing %%%%%%%%%\n";
                test = new CuckooHashing(table_size);
                break;
            default:
                break;
        }
        
        load_from_file(keys_path, values_path, *test);

        std::cout << "\n### PRINT #1 ###\n";
        test->print();
        std::cout << std::endl;

        // Test: Remove on empty HashTable
        assert(test, &HashTable::remove, INT_MIN, "???");

        // Insert test cases
        test->insert("abc", 4);
        test->insert("ABC", 7);

        // Test: Remove an existing element
        assert(test, &HashTable::remove, 7, "ABC");

        // Test: Change value of an element and retrieve it
        test->insert("abc", 400);
        assert(test, &HashTable::get, 400, "abc");

        // Test: Retrieve non-existent key
        assert(test, &HashTable::get, INT_MIN, "NonExistentKey");

        // Additional test cases
        test->insert("new_key", 42);
        assert(test, &HashTable::get, 42, "new_key");

        test->insert("new_key", 84); // Overwrite value
        assert(test, &HashTable::get, 84, "new_key");

        assert(test, &HashTable::remove, 84, "new_key");
        assert(test, &HashTable::get, INT_MIN, "new_key");

        std::cout << "\n### PRINT #2 ###\n";
        test->print();
        std::cout << "\n%%%%%%%%% Unit tests completed %%%%%%%%%\n";

        delete test;
    }

    if (remove(values_path.c_str()) != 0) {
        perror("Error deleting file");
    }
    if (remove(keys_path.c_str()) != 0) {
        perror("Error deleting file");
    }
}

void hash_tables_main(std::initializer_list<unsigned int> SIZES, uint8_t NUM_OF_TIMES) {
    std::cout << "~~~~~~~~~~~~~~~~~~ Hash Tables main function executing... ~~~~~~~~~~~~~~~~~~\n";

    enum ENUM_HT : uint8_t {AVL, OPEN_ADDRESSING, CUCKOO, HT_COUNT};
    enum ENUM_HT_METHODS : uint8_t {INSERT, REMOVE, HT_METHODS_COUNT};
    std::string values_path = "temp_values.txt";
    std::string keys_path = "temp_keys.txt";
    HashTable* test;
    unsigned long long results[HT_COUNT][HT_METHODS_COUNT] = {{0, 0},
                                                              {0, 0},
                                                              {0, 0}};
    std::ofstream files[HT_METHODS_COUNT];
    std::string filenames[HT_METHODS_COUNT] = { 
                                              "HashTables/results/insert.csv",
                                              "HashTables/results/remove.csv"
                                             };
    for(uint8_t i = 0; i < HT_METHODS_COUNT; i++) {
        files[i].open(filenames[i]);
        if(!files[i]) {
            std::cerr << "Error opening " << filenames[i] << std::endl;
        }
    }
    for(uint8_t i = 0; i < HT_METHODS_COUNT; i++) {
        files[i] << "SIZE;ChainAVL;OpenAddressing;CuckooHashing" << std::endl;
    }

    unit_tests(AVL);
    unit_tests(OPEN_ADDRESSING);
    unit_tests(CUCKOO);

    std::cout << "#-----------------------------------#\nBegin timing methods\n#-----------------------------------#\n\n";
    for(unsigned int SIZE : SIZES) {
        std::cout << "SIZE=" << SIZE << std::endl;
        for(uint8_t i = 1; i <= NUM_OF_TIMES; i++) {
            size_t HS_SIZE = SIZE / 10;
            generate_random_integers(values_path, -10000, 10000, SIZE-1);
            generate_keys(keys_path, values_path);

            // ChainAVL - insert
            test = new ChainAVL(HS_SIZE);
            load_from_file(keys_path, values_path, *test);
            test->insert("key_to_be_deleted", 100);
            results[AVL][INSERT] += measure_time(test, &HashTable::insert, "definetely_unique_key", 10000);
            delete test;

            // ChainAVL - remove
            test = new ChainAVL(HS_SIZE);
            load_from_file(keys_path, values_path, *test);
            test->insert("key_to_be_deleted", 100);
            results[AVL][REMOVE] += measure_time(test, &HashTable::remove, "key_to_be_deleted");
            delete test;

            // OpenAddressing - insert
            test = new OpenAddressing(HS_SIZE);
            load_from_file(keys_path, values_path, *test);
            test->insert("key_to_be_deleted", 100);
            results[OPEN_ADDRESSING][INSERT] += measure_time(test, &HashTable::insert, "definetely_unique_key", 10000);
            delete test;

            // OpenAddressing - remove
            test = new OpenAddressing(HS_SIZE);
            load_from_file(keys_path, values_path, *test);
            test->insert("key_to_be_deleted", 100);
            results[OPEN_ADDRESSING][REMOVE] += measure_time(test, &HashTable::remove, "key_to_be_deleted");
            delete test;

            // CuckooHashing - insert
            test = new CuckooHashing(HS_SIZE);
            load_from_file(keys_path, values_path, *test);
            test->insert("key_to_be_deleted", 100);
            results[CUCKOO][INSERT] += measure_time(test, &HashTable::insert, "definetely_unique_key", 10000);
            delete test;

            // CuckooHashing - remove
            test = new CuckooHashing(HS_SIZE);
            load_from_file(keys_path, values_path, *test);
            test->insert("key_to_be_deleted", 100);
            results[CUCKOO][REMOVE] += measure_time(test, &HashTable::remove, "key_to_be_deleted");
            delete test;
        }

        std::cout << "Saving output..." << std::endl;
        for(uint8_t i = 0; i < HT_METHODS_COUNT; i++) {
            files[i] << SIZE;
            for(uint8_t j = 0; j < HT_COUNT; j++) {
                files[i] << ";" << (results[j][i] / NUM_OF_TIMES);
                results[j][i] = 0;
            }
            files[i] << std::endl;
        }
    }

    // CLEANUP
    for(uint8_t i = 0; i < HT_METHODS_COUNT; i++) {
        files[i].close();
    }
    if (remove(values_path.c_str()) != 0) {
        perror("Error deleting file");
    }
    if (remove(keys_path.c_str()) != 0) {
        perror("Error deleting file");
    }
}