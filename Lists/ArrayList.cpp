#include "List.h"
#include <iostream>

ArrayList::ArrayList() : size(0), capacity(2) {
    array = new int[capacity];
}

ArrayList::ArrayList(size_t init_capacity) : size(0), capacity(init_capacity) {
    if(init_capacity < 1) {
        capacity = 1;
    }
    array = new int[capacity];
}

ArrayList::~ArrayList() {
    delete[] array;
}

void ArrayList::resize(size_t new_capacity) {
    int* new_array = new int[new_capacity];

    for(size_t i = 0; i < size; i++) {
        new_array[i] = array[i];
    }

    delete[] array; // free-up the memory of the old array (before resizing)
    array = new_array;
    capacity = new_capacity;
}

void ArrayList::show(void) {
    for(size_t i = 0; i < size; i++) {
        std::cout << "i = " << i << "; value = " << array[i] << std::endl;
    }
    std::cout << std::endl;
}

void ArrayList::append(int value) {
    if(size == capacity) {
        resize(capacity*2);
    }

    array[size] = value;
    size++;
}

void ArrayList::prepend(int value) {
    if(size == capacity) {
        resize(capacity*2);
    }

    for(size_t i = size; i > 0; i--) {
        array[i] = array[i-1];
    }

    array[0] = value;
    size++;
}

// Note: it is impossible to insert element at index that doesn't exist
void ArrayList::insert(int value, size_t index) {
    if(index >= size) {
        std::cout << "\nIndex=" << index << " is out of bounds.\n";
        return;
    }

    if(size == capacity) {
        resize(capacity*2);
    }

    for(size_t i = size; i > index; i--) {
        array[i] = array[i-1];
    }

    array[index] = value;
    size++;
}

int ArrayList::pop_front(void) {
    if(!size) {
        std::cout << "There are no elements to remove.\n";
        return 0;
    }

    int temp = array[0];
    for(size_t i = 0; i < size; i++) {
        array[i] = array[i+1];
    }

    size--;
    return temp;
}

int ArrayList::pop_back(void) {
    if(!size) {
        std::cout << "There are no elements to remove.\n";
        return 0;
    }

    size--;
    return array[size];
}

int ArrayList::remove(size_t index) {
    if(!size) {
        std::cout << "There are no elements to remove.\n";
        return 0;
    }

    if(index >= size) {
        std::cout << "\nIndex=" << index << " is out of bounds.\n";
        return 0;
    }

    int temp = array[index];
    for(size_t i = index; i < size; i++) {
        array[i] = array[i+1];
    }

    size--;
    return temp;
}

// check both ends at once and go towards the middle
bool ArrayList::search(int value) {
    for(size_t i = 0; i <= size / 2; i++) {
        if(size == 0) {
            return false;
        }
        if(array[i] == value) {
            return true;
        }
        else if(array[size-1-i] == value != 0){
            return true;
        }
    }
    return false;
}