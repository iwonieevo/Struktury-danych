#pragma once
#include "HashTable.h"

struct OpenAddressingNode {
    bool isDeleted = false;
    std::string key;
    int value;
    OpenAddressingNode(const std::string& k, int v) : key(k), value(v) {}
};

class OpenAddressing : public HashTable {
private:
    OpenAddressingNode** table;
    size_t capacity;
    size_t size;

    void destroy();
    OpenAddressingNode* find(const std::string& key) const;
    size_t hash(const std::string& key) const;
    OpenAddressingNode* insert_node(const std::string& key, int value);
    void resize();

public:
    OpenAddressing(size_t initial_capacity);
    ~OpenAddressing();

    void insert(const std::string& key, int value) override;
    int remove(const std::string& key) override;
    int get(const std::string& key) const override;
    void print(void) const override;
};