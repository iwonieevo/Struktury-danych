#include "List.h"
#include <iostream>

SinglyLinkedList::SinglyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

SinglyLinkedList::~SinglyLinkedList() {
    Node* current = head;
    while(current) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
}

void SinglyLinkedList::show(void) {
    Node* current = head;
    while(current) {
        std::cout << "->" << current->data;
        current = current->next;
    }
    std::cout << "->\n";
}

void SinglyLinkedList::append(int value) {
    Node* newNode = new Node(value);
    if(!head) {
        head = newNode;
        tail = newNode;
    }

    else {
        tail->next = newNode;
        tail = newNode;
    }

    size++;
}

void SinglyLinkedList::prepend(int value) {
    Node* newNode = new Node(value);
    if(!head) {
        head = newNode;
        tail = newNode;
    }

    else {
        newNode->next = head;
        head = newNode;
    }

    size++;
}

// Note: it is impossible to insert element at index that doesn't exist; Index exists only in theory, it just points after how many Nodes we want to insert new one
void SinglyLinkedList::insert(int value, size_t index) {
    if(index >= size) {
        std::cout << "\nIndex=" << index << " is out of bounds.\n";
        return;
    }

    Node* newNode = new Node(value);
    if(!index) {
        newNode->next = head;
        head = newNode;
    }

    else {
        Node* prev = head;
        for(size_t i = 1; i < index; i++) {
            prev = prev->next;
        }

        newNode->next = prev->next;
        prev->next = newNode;
    }

    size++;
    
}

int SinglyLinkedList::pop_front(void) {
    if(!head) {
        std::cout << "There are no elements to remove.\n";
        return 0;
    }
    
    Node* temp = head;
    int temp_v = temp->data;
    if(size == 1) {
        head = nullptr;
        tail = nullptr;
    }

    else {
        head = head->next;
    }

    delete temp;
    size--;
    return temp_v;
}

int SinglyLinkedList::pop_back(void) {
    if(!head) {
        std::cout << "There are no elements to remove.\n";
        return 0;
    }

    Node* temp = head;
    int temp_v = temp->data;
    if(size == 1) {
        head = nullptr;
        tail = nullptr;
    }

    else{
        for(size_t i = 1; i < size - 1; i++) {
            temp = temp->next;
        }
        Node* prev = temp;
        temp = temp->next;
        prev->next = nullptr;
    }

    temp_v = temp->data;
    delete temp;
    size--;
    return temp_v;
}

int SinglyLinkedList::remove(size_t index) {
    if(index >= size) {
        std::cout << "\nIndex=" << index << " is out of bounds.\n";
        return 0;
    }

    Node* temp = head;
    int temp_v = temp->data;
    if(size == 1) {
        head = nullptr;
        tail = nullptr;
    }

    else if(!index) {
        head = head->next;
    }

    else{
        for(size_t i = 1; i < index; i++) {
            temp = temp->next;
        }
        Node* prev = temp;
        temp = temp->next;
        prev->next = temp->next;
    }

    temp_v = temp->data;
    delete temp;
    size--;
    return temp_v;
}

bool SinglyLinkedList::search(int value) {
    Node* current = head;
    while(current) {
        if(current->data == value) {
            return true;
        }
        current = current->next;
    }
    return false;
}