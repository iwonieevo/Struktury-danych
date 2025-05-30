#pragma once
#include <string>

struct Node {
    std::string key;
    int value;

    Node(const std::string& k, int v) : key(k), value(v) {}
};

class Bucket {
public:
    virtual void insert(const std::string& key, int value) = 0;
    virtual int remove(const std::string& key) = 0;
    virtual Node* find(const std::string& key) = 0;
    virtual void print(void) = 0;
    virtual ~Bucket() {};
};