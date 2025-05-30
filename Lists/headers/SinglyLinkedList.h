#pragma once
#include "List.h"

class SinglyLinkedList : public List {
public:
    virtual void show(void) override;
    virtual size_t get_size(void) const override;
    virtual int get_element(size_t index) const override;

    virtual void append(int value) override;
    virtual void prepend(int value) override;
    virtual void insert(int value, size_t index) override;

    virtual int pop_front(void) override;
    virtual int pop_back(void) override;
    virtual int remove(size_t index) override;

    virtual bool search(int value) override;

    SinglyLinkedList();
    ~SinglyLinkedList();

private:
    struct Node {
        int data;
        Node* next;
        Node(int value) : data(value), next(nullptr) {}
    };

    size_t size;
    Node* head;
    Node* tail;
};