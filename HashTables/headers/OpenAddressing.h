#pragma once
#include "Bucket.h"
#include "utility.h"
#include <iostream>

struct OpenAddressingNode : public Node {
    bool isDeleted = false;

    OpenAddressingNode(const std::string& k, int v) : Node(k, v) {}
};

class OpenAddressing : public Bucket {
private:
    OpenAddressingNode** table;
    size_t capacity;
    size_t size;

    void destroy();
    size_t hash(const std::string& key) const;
    OpenAddressingNode* insert_node(const std::string& key, int value);
    OpenAddressingNode* find_node(const std::string& key) const;
    void resize();

public:
    OpenAddressing(size_t initial_capacity = 16);
    ~OpenAddressing();

    void insert(const std::string& key, int value) override;
    int remove(const std::string& key) override;
    Node* find(const std::string& key) override;
    void print(void) override;
};