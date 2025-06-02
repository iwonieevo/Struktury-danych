#pragma once
#include "Bucket.h"
#include "AVLTree.h"
#include "OpenAddressing.h"
#include "CuckooHashing.h"
#include <string>
#include <cstdint> // uint8_t
#include <iostream>

// Implementation of the Hash Table Dictionary. Possible bucket_types: '0' (for AVL Tree), '1' (for Open Addressing), '2' (for Cuckoo Hashing) @jubilanttae
class HashTable {
private:
    size_t table_size;
    Bucket **table;

    size_t hash(const std::string& key);

public:
    // Add key-value pair to the dictionary (if element with specified key already exists, then update the value)
    void insert(const std::string& key, int value);

    // Remove element with specified key and return its value
    int remove(const std::string& key);

    // Return value of element with specified key
    int get(const std::string& key);

    // Display the key-value pairs inside the dictionary
    void print(void);

    HashTable(size_t size = 1, uint8_t bucket_type = 0);
    ~HashTable();
};