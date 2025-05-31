#include "../headers/HashTable.h"

HashTable::HashTable(size_t size=1, uint8_t bucket_type=0) {
    table_size = size ? size : 1;
    switch (bucket_type)
    {
    case 0:
        table = new Bucket*[size];
        for (size_t i = 0; i < size; i++)
            table[i] = new AVLTree();
        break;
    case 1:
        table = new Bucket*[size];
        for (size_t i = 0; i < size; i++)
            table[i] = new AVLTree(); // TODO: @jubilanttae JULKA1
        break;
    case 2:
        table = new Bucket*[size];
        for (size_t i = 0; i < size; i++)
            table[i] = new AVLTree(); // TODO: @jubilanttae JULKA1
        break;  
    default:
        std::cerr << "\nIncorrect BucketType used! Possible options:\n -'0' (AVL Tree)\n -'1' (JULKA1)\n -'2' (JULKA2)\n"; // TODO: @jubilanttae JULKA1 i JULKA2
        break;
    }
}

HashTable::~HashTable() {
    for (size_t i = 0; i < table_size; i++) {
        delete table[i];
    }
    delete[] table;
}

size_t HashTable::hash(const std::string& key) {
    size_t hashed = 0;
    for (char c : key) {
        hashed = (hashed * 31 + c) % table_size;
    }
    return hashed;
}

void HashTable::insert(const std::string& key, int value) {
    table[hash(key)]->insert(key, value);
}

int HashTable::remove(const std::string& key) {
    return table[hash(key)]->remove(key);
}

void HashTable::print(void) {
    for(size_t i = 0; i < table_size; i++) {
        table[i]->print();
    }
}

int HashTable::get(const std::string& key) {
    return (table[hash(key)]->find(key)) ? table[hash(key)]->find(key)->value : INT_MIN;
}

