#include "../headers/ArrayList.h"
#include <iostream>
#include <cstring>

ArrayList::ArrayList() : size(0), capacity(2) {
    array = new int[capacity];
}

ArrayList::ArrayList(size_t init_capacity) : size(0), capacity(init_capacity) {
    // capacity should never be 0, especially when chosen resizing startegy is capacity *= 2
    if(init_capacity < 1) {
        capacity = 1;
    }

    array = new int[capacity];
}

ArrayList::~ArrayList() {
    delete[] array;
}

void ArrayList::resize(size_t new_capacity) {
    // create new instance of int[] (with changed capacity)
    int* new_array = new int[new_capacity];

    // copy data from the old array to the new one
    std::memcpy(new_array, array, size * sizeof(int));

    // free up memory taken by old array
    delete[] array;
    array = new_array;
    capacity = new_capacity;
}

void ArrayList::show(void) {
    std::cout << "[" << array[0];
    for(size_t i = 1; i < size; i++) {
        std::cout << ", " << array[i];
    }

    std::cout << "]" << std::endl;
}

size_t ArrayList::get_size(void) const {
    return size;
}

int ArrayList::get_element(size_t index) const {
    if(index >= size) {
        std::cout << "\nIndex=" << index << " is out of bounds.\n";
        return 0;
    }
    return array[index];
}

void ArrayList::append(int value) {
    // double the capacity if at limit
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

    // move all of data one place to the right
    for(size_t i = size; i > 0; i--) {
        array[i] = array[i-1];
    }

    array[0] = value;
    size++;
}

void ArrayList::insert(int value, size_t index) {
    // note: for size=0, only index=0 passes this check
    if(index > size && index) {
        std::cout << "\nIndex=" << index << " is out of bounds.\n";
        return;
    }

    // double the capacity if at limit
    if(size == capacity) {
        resize(capacity*2);
    }

    // move all of data to the right of chosen index one place to the right
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

    // save removed value to a temporary variable (for returning purposes)
    int temp = array[0];
    // move all of data one place to the left (overwriting array[0])
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
    // save removed value to a temporary variable (for returning purposes)
    int temp = array[size];
    return temp;
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

    // save removed value to a temporary variable (for returning purposes)
    int temp = array[index];
    // move all data to the right of chosen index one place to the left (overwriting array[i])
    for(size_t i = index; i < size; i++) {
        array[i] = array[i+1];
    }

    size--;
    return temp;
}

bool ArrayList::search(int value) {
    // 2 "pointers" at both ends of the array moving towards the middle
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