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

    // Helper methods that use utility.h functionality
    template<typename... Parameters>
    unsigned long long measure_operation_time(void (OpenAddressing::*method)(const std::string&, int), Parameters... params) {
        return measure_time(this, method, std::forward<Parameters>(params)...);
    }

    template<typename ExpectedType, typename... Parameters>
    bool assert_operation(int (OpenAddressing::*method)(const std::string&), ExpectedType expected, Parameters... params) {
        return assert(this, method, expected, std::forward<Parameters>(params)...);
    }

    // Getter for testing
    size_t get_size() const { return size; }
    size_t get_capacity() const { return capacity; }
};