#include "../headers/hash_tables_main.h"

void unit_test(size_t table_size, uint8_t bucket_type) {
    HashTable test(table_size, bucket_type);

    std::cout << "\n\n%%%%%%%%% table_size=" << table_size << "; bucket_type=" << (int)(bucket_type) << std::endl;
    auto temp = test.remove("???");
    if (!temp) {
        std::cout << "TEST: remove on empty HashTable -> PASSED\n";
    }else {
        std::cerr << "TEST: remove on empty HashTable -> FAILED\n";
        return;
    }

    test.insert("abc", 4);
    test.insert("def", -2);
    test.insert("ghi", 7);
    test.insert("ABC", 7);
    test.insert("DEF", 0);
    test.insert("GHI", 120);
    test.insert("quite long key with spaces", 555);
    test.insert(R"("!@#^()&\\")", -10);

    std::cout << "\n### PRINT #1 ###\n";
    test.print();
    std::cout << std::endl;

    temp = test.remove("ABC");
    if (temp == 7) {
        std::cout << "TEST: remove an existing element from HashTable -> PASSED\n";
    }else {
        std::cerr << "TEST: remove an existing element from HashTable -> FAILED\n";
        return;
    }

    test.insert("abc", 400);
    temp = test.get("abc");
    if (temp == 400) {
        std::cout << "TEST: change value of the element in the HashTable and retrieve it's value with 'get' -> PASSED\n";
    }else {
        std::cerr << "TEST: change value of the element in the HashTable and retrieve it's value with 'get' -> FAILED\n";
        return;
    }

    std::cout << "\n### PRINT #2 ###\n";
    test.print();
    std::cout << std::endl;

    if (!test.get("NonExistentKey")) {
        std::cout << "TEST: using 'get' with key not in the HashTable -> PASSED\n";
    }else {
        std::cerr << "TEST: using 'get' with key not in the HashTable -> FAILED\n";
        return;
    }
}

// Function loading data into the Hash Table
void load_from_file(const std::string& keys_path, const std::string& values_path, HashTable& dict) {
    
}

void hash_tables_main(std::initializer_list<unsigned int> SIZES, uint8_t NUM_OF_TIMES) {
    unit_test(1, 0);
    unit_test(10, 0);
    unit_test(5, 0);
    unit_test(3, 0);
}