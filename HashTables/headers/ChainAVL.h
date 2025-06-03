#pragma once
#include "HashTable.h"
#include "AVLTree.h"

class ChainAVL : public HashTable {
private:
    size_t table_size;
    AVLTree **table;

    size_t hash(const std::string& key) const;

public:
    ChainAVL(size_t size);
    ~ChainAVL();

    void insert(const std::string& key, int value) override;
    int remove(const std::string& key) override;
    int get(const std::string& key) const override;
    void print(void) const override;
};