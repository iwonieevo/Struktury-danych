#pragma once
#include <cstddef> // size_t

class PriorityQueue {
public:
    // Add element `e` with priority `p`
    virtual void insert(int e, unsigned int p) = 0;

    // Remove and return element with highest priority
    virtual int extract_max(void) = 0;

    // Return element with highest priority (without removing it)
    virtual const int& find_max(void) const = 0;

    // Change priority of element 'e' to 'p'
    virtual void modify_key(int e, unsigned int new_priority) = 0;

    // Return number of elements in queue
    virtual size_t return_size(void) const = 0;

    virtual ~PriorityQueue() {}
};