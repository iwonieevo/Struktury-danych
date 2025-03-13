#pragma once
#include <cstdint>
#include <string>

// Virtual interface for DT's from Project 1
class List {
    public:
        virtual void load_from_file(std::string source_path) = 0; // load the data from file at specified path
        virtual void display(void) = 0; // iterate through the List and show values inside it
        virtual void append(int32_t value) = 0; // add item at the end
        virtual void prepend(int32_t value) = 0; // add item at the beginning
        virtual void insert(int32_t value, size_t index) = 0; // add item at the specified position
        virtual int32_t pop_first(void) = 0; // remove item from the beggining and return removed item
        virtual int32_t pop_last(void) = 0; // remove item from the end and return removed item
        virtual int32_t remove(size_t index) = 0; // remove item from the specified position
        virtual bool search(int32_t value) = 0; // check if the specified value is in the List
        virtual ~List() {}
    };

class ArrayList : public List {
    public:
    virtual void load_from_file(std::string source_path) override;
    virtual void display(void) override;
    virtual void append(int32_t value) override;
    virtual void prepend(int32_t value) override;
    virtual void insert(int32_t value, size_t index) override;
    virtual int32_t pop_first() override;
    virtual int32_t pop_last() override;
    virtual int32_t remove(size_t index) override;
    virtual bool search(int32_t value) override;
};

class SingleLinkedList : public List {
    public:
    virtual void load_from_file(std::string source_path) override;
    virtual void display(void) override;
    virtual void append(int32_t value) override;
    virtual void prepend(int32_t value) override;
    virtual void insert(int32_t value, size_t index) override;
    virtual int32_t pop_first() override;
    virtual int32_t pop_last() override;
    virtual int32_t remove(size_t index) override;
    virtual bool search(int32_t value) override;
};

class SingleLinkedList : public List {
    public:
    virtual void load_from_file(std::string source_path) override;
    virtual void display(void) override;
    virtual void append(int32_t value) override;
    virtual void prepend(int32_t value) override;
    virtual void insert(int32_t value, size_t index) override;
    virtual int32_t pop_first() override;
    virtual int32_t pop_last() override;
    virtual int32_t remove(size_t index) override;
    virtual bool search(int32_t value) override;
};