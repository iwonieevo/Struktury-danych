#pragma once
#include "PriorityQueue.h"
#include <stdexcept>

class LinkedList : public PriorityQueue {
private:
    struct Node {
        int element;
        unsigned int priority;
        Node* next;

        Node(int e, unsigned int p, Node* n = nullptr) : element(e), priority(p), next(n) {}
    };

    Node* head;
    size_t size;

public:
    LinkedList();
    ~LinkedList();

    void insert(int e, unsigned int p) override;
    int extract_max(void) override;
    const int& find_max(void) const override;
    void modify_key(int e, unsigned int new_priority) override;
    size_t return_size(void) const override;
};