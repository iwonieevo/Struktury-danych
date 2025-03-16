#pragma once
#include <string>

// Virtual interface for DS's from Project 1
class List {
    public:
        virtual void show(void) = 0; // display the values inside the List

        virtual void append(int value) = 0; // add item at the end
        virtual void prepend(int value) = 0; // add item at the beginning
        virtual void insert(int value, size_t index) = 0; // add item at the specified position

        virtual int pop_front(void) = 0; // remove item from the beggining and return removed item
        virtual int pop_back(void) = 0; // remove item from the end and return removed item
        virtual int remove(size_t index) = 0; // remove item from the specified position

        virtual bool search(int value) = 0; // check if the specified value is in the List

        virtual ~List() {}
    };

class ArrayList : public List {
    public:
        virtual void show(void) override;

        virtual void append(int value) override;
        virtual void prepend(int value) override;
        virtual void insert(int value, size_t index) override;

        virtual int pop_front(void) override;
        virtual int pop_back(void) override;
        virtual int remove(size_t index) override;

        virtual bool search(int value) override;
        
        ArrayList();
        ArrayList(size_t init_capacity);
        ~ArrayList();

    private:
        size_t size;
        size_t capacity;
        int* array;
        void resize(size_t new_capacity);
};

class SinglyLinkedList : public List {
public:
    virtual void show(void) override;

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

class DoublyLinkedList : public List {
    public:
        virtual void show(void) override;

        virtual void append(int value) override;
        virtual void prepend(int value) override;
        virtual void insert(int value, size_t index) override;

        virtual int pop_front(void) override;
        virtual int pop_back(void) override;
        virtual int remove(size_t index) override;

        virtual bool search(int value) override;
        
        DoublyLinkedList();
        ~DoublyLinkedList();

    private:
        struct Node {
            Node* prev;
            int data;
            Node* next;
            Node(int value) : prev(nullptr), data(value), next(nullptr) {}
        };

        size_t size;
        Node* head;
        Node* tail;
};