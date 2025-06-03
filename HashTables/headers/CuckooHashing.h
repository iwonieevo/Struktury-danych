#pragma once
#include "Bucket.h"
#include "utility.h"
#include <iostream>
#include <climits>

struct CuckooNode : public Node {
    bool isOccupied = false;

    CuckooNode() : Node("", 0) {}
    CuckooNode(const std::string& k, int v) : Node(k, v), isOccupied(true) {}
};

class CuckooHashing : public Bucket {
private:
    static const size_t MAX_REHASH_ATTEMPTS = 10;
    static const size_t MAX_LOOP_ITERATIONS = 100;
    
    CuckooNode** table1;
    CuckooNode** table2;
    size_t capacity;
    size_t size;

    size_t hash1(const std::string& key) const;
    size_t hash2(const std::string& key) const;
    void rehash();
    void destroy();
    bool insert_with_replacement(const std::string& key, int value, bool useFirstHash, size_t iterations = 0);

public:
    CuckooHashing(size_t initial_capacity = 16);
    ~CuckooHashing();

    void insert(const std::string& key, int value) override;
    int remove(const std::string& key) override;
    Node* find(const std::string& key) override;
    void print(void) override;
};