#include "../headers/BinaryHeap.h"
#include <algorithm> // For std::swap

BinaryHeap::BinaryHeap(size_t initial_capacity) : capacity(initial_capacity), size(0) {
    heap = new Node[capacity];
}

BinaryHeap::~BinaryHeap() {
    delete[] heap;
}

PriorityQueue* BinaryHeap::clone() const {
    BinaryHeap* copy = new BinaryHeap(capacity);
    copy->size = size;
    for (size_t i = 0; i < size; i++) {
        copy->heap[i] = heap[i];
    }
    return copy;
}

void BinaryHeap::resize() {
    capacity *= 2;
    if(capacity == 0) {capacity = 1;}
    Node* new_heap = new Node[capacity];

    for(size_t i = 0; i < size; i++) {new_heap[i] = heap[i];}

    delete[] heap;
    heap = new_heap;
}

void BinaryHeap::heapify(size_t index) {
    size_t left, right, largest;

    while(true) {
        largest = index;
        left = 2 * index + 1;
        right = 2 * index + 2;

        if(left < size && heap[left].priority > heap[largest].priority) {largest = left;}

        if(right < size && heap[right].priority > heap[largest].priority) {largest = right;}

        if(largest == index) {break;}

        std::swap(heap[index], heap[largest]);
        index = largest;
    }
}

void BinaryHeap::insert(int e, unsigned int p) {
    if(size == capacity) {resize();}

    size++;
    size_t i = size - 1;
    heap[i] = {e, p};
    while(i != 0 && heap[(i - 1)/2].priority < heap[i].priority) {
        std::swap(heap[i], heap[(i - 1)/2]);
        i = (i - 1)/2;
    }
    
}

int BinaryHeap::extract_max(void) {
    if(size == 0) {throw std::runtime_error("Heap is empty");}

    int max_element = heap[0].element;
    heap[0] = heap[size - 1];
    size--;
    heapify(0);
    return max_element;
}

const int& BinaryHeap::find_max(void) const {
    if(size == 0) {throw std::runtime_error("Heap is empty");}

    return heap[0].element;
}

void BinaryHeap::modify_key(int e, unsigned int new_priority) {
    for(size_t i = 0; i < size; i++) {
        if (heap[i].element == e) {
            unsigned int old_priority = heap[i].priority;
            heap[i].priority = new_priority;
            if (new_priority > old_priority) {
                while (i != 0 && heap[(i - 1) / 2].priority < heap[i].priority) {
                    std::swap(heap[i], heap[(i - 1) / 2]);
                    i = (i - 1) / 2;
                }
            } else {
                heapify(i);
            }
            return;
        }
    }

    throw std::runtime_error("Element not found in heap");
}

size_t BinaryHeap::return_size(void) const {
    return size;
}
