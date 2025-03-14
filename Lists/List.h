#pragma once
#include <cstdint>
#include <string>

// Virtual interface for DS's from Project 1
class List {
    public:
        virtual void load_from_file(std::string source_path) = 0; // load the data from file at specified path
        virtual void show(void) = 0; // display the values inside the List

        virtual void append(int32_t value) = 0; // add item at the end
        virtual void prepend(int32_t value) = 0; // add item at the beginning
        virtual void insert(int32_t value, size_t index) = 0; // add item at the specified position

        virtual int32_t pop_front(void) = 0; // remove item from the beggining and return removed item
        virtual int32_t pop_back(void) = 0; // remove item from the end and return removed item
        virtual int32_t remove(size_t index) = 0; // remove item from the specified position

        virtual bool search(int32_t value) = 0; // check if the specified value is in the List

        virtual size_t get_size(void) const = 0;

        virtual ~List() {}
    
    protected:
        size_t size;
    };