#pragma once
#include "HashTable.h"
#include <climits>

struct CuckooNode {
    bool isOccupied = false;
    std::string key;
    int value;

    CuckooNode() : key(""), value(0) {}
    CuckooNode(const std::string& k, int v) : key(k), value(v), isOccupied(true) {}
};

class CuckooHashing : public HashTable {
private:
    static const size_t MAX_REHASH_ATTEMPTS = 10;
    static const size_t MAX_LOOP_ITERATIONS = 100;
    
    CuckooNode** table1;
    CuckooNode** table2;
    size_t capacity;
    size_t size;

    CuckooNode* find(const std::string& key) const;
    size_t hash1(const std::string& key) const;
    size_t hash2(const std::string& key) const;
    void rehash();
    void destroy();
    bool insert_with_replacement(const std::string& key, int value, bool useFirstHash, size_t iterations = 0);

public:
    CuckooHashing(size_t initial_capacity);
    ~CuckooHashing();

    void insert(const std::string& key, int value) override;
    int remove(const std::string& key) override;
    int get(const std::string& key) const override;
    void print(void) const override;
};