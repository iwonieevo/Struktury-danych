#pragma once
#include <iostream>
#include <cstddef> // size_t

// Virtual interface for DS's from Project 1
class List {
    public:
        virtual void show(void) = 0; // display the values inside the List
        virtual size_t get_size(void) const = 0; // returns size value
        virtual int get_element(size_t index) const = 0; // returns element on the given index

        virtual void append(int value) = 0; // add item at the end
        virtual void prepend(int value) = 0; // add item at the beginning
        virtual void insert(int value, size_t index) = 0; // add item at the specified position

        virtual int pop_front(void) = 0; // remove item from the beggining and return removed item
        virtual int pop_back(void) = 0; // remove item from the end and return removed item
        virtual int remove(size_t index) = 0; // remove item from the specified position

        virtual bool search(int value) = 0; // check if the specified value is in the List

        virtual ~List() {}
};