#include "../headers/SinglyLinkedList.h"
#include <iostream>

SinglyLinkedList::SinglyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

SinglyLinkedList::~SinglyLinkedList() {
    // freeing memory for each Node in List
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

size_t SinglyLinkedList::get_size(void) const {
    return size;
}

int SinglyLinkedList::get_element(size_t index) const {
    if(index >= size) {
        std::cout << "\nIndex=" << index << " is out of bounds.\n";
        return 0;
    }
    
    if(index == size - 1) {
        return tail->data;
    }

    Node* temp = head;
    for(size_t i = 0; i < index; i++) {
        temp = temp->next;
    }

    return temp->data;
}

void SinglyLinkedList::append(int value) {
    Node* newNode = new Node(value);
    // if the List is empty => head=nullptr => added Node is the head
    if(!head) {
        head = newNode;
    }

    // old tail now points to added Node
    else {
        tail->next = newNode;
    }

    tail = newNode;
    size++;
}

void SinglyLinkedList::prepend(int value) {
    Node* newNode = new Node(value);
    // if the List is empty => tail=nullptr => added Node is the tail
    if(!tail) {
        tail = newNode;
    }

    // new Node should point to old head
    else {
        newNode->next = head;
    }

    head = newNode;
    size++;
}

void SinglyLinkedList::insert(int value, size_t index) {
    // note: for size=0, only index=0 passes this check
    if(index > size && index) {
        std::cout << "\nIndex=" << index << " is out of bounds.\n";
        return;
    }
    
    if(index == 0) {
        this->prepend(value);
        return;
    }

    if(index == size) {
        this->append(value);
        return;
    }

    // find Node prior to the index we want to insert new Node
    Node* newNode = new Node(value);
    Node* prior = head;
    for(size_t i = 1; i < index; i++) {
        prior = prior->next;
    }
    
    // new Node should point to the Node originally to the right of the prior Node
    newNode->next = prior->next;
    // prior Node now points to added Node
    prior->next = newNode;
    size++;
}

int SinglyLinkedList::pop_front(void) {
    if(!head) {
        std::cout << "There are no elements to remove.\n";
        return 0;
    }
    
    Node* temp = head;
    // save removed value to a temporary variable (for returning purposes)
    int temp_v = temp->data;
    if(size == 1) {
        head = nullptr;
        tail = nullptr;
    }

    // unless removed Node is last Node in List, head now points to the second Node
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

    Node* temp = tail;
    // save removed value to a temporary variable (for returning purposes)
    int temp_v = temp->data;
    if(size == 1) {
        head = nullptr;
        tail = nullptr;
    }

    // find Node prior to the last one (to update tail to it and to change where it points). Note: we are allowed only movement from head to tail
    else{
        Node* prior = head;
        for(size_t i = 1; i < size - 1; i++) {
            prior = prior->next;
        }

        prior->next = nullptr;
        tail = prior;
    }

    delete temp;
    size--;
    return temp_v;
}

int SinglyLinkedList::remove(size_t index) {
    if(index >= size) {
        std::cout << "\nIndex=" << index << " is out of bounds.\n";
        return 0;
    }

    if(index == 0) {
        return this->pop_front();
    }

    if(index == size-1) {
        return this->pop_back();
    }

    // find Node prior to the index we want to remove Node from (to change where it points). Note: we are allowed only movement from head to tail
    Node* prior = head;
    for(size_t i = 1; i < index; i++) {
        prior = prior->next;
    }

    // the Node we want to remove
    Node* temp = prior->next;
    // save removed value to a temporary variable (for returning purposes)
    int temp_v = temp->data;
    prior->next = temp->next;
    size--;
    delete temp;
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