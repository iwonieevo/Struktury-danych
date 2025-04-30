#pragma once
#include "PriorityQueue.h"

class BinaryHeap : public PriorityQueue {
    private:
    struct Node {
        int element;
        unsigned int priority;
    };

    Node* heap;          // Dynamically allocated array for the heap
    size_t capacity;     // Maximum capacity of the heap
    size_t size;         // Current number of elements in the heap

    void resize();       // Resize the heap when capacity is exceeded
    void heapify(size_t index);

public:
    BinaryHeap(size_t _capacity = 16);
    ~BinaryHeap();

    void insert(int e, unsigned int p) override;
    int extract_max(void) override;
    const int& find_max(void) const override;
    void modify_key(int e, unsigned int new_priority) override;
    size_t return_size(void) const override;

    PriorityQueue* clone(void) const override;
};