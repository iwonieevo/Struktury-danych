#include "../headers/DoublyLinkedList.h"
#include <iostream>

DoublyLinkedList::DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

DoublyLinkedList::~DoublyLinkedList() {
    // freeing memory for each Node in List
    Node* current = head;
    while(current) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
}

void DoublyLinkedList::show(void) {
    Node* current = head;
    while(current) {
        std::cout << "<-" << current->data << "->";
        current = current->next;
    }

    std::cout << std::endl;
}

size_t DoublyLinkedList::get_size(void) const {
    return size;
}

int DoublyLinkedList::get_element(size_t index) const {
    if(index >= size) {
        std::cout << "\nIndex=" << index << " is out of bounds.\n";
        return 0;
    }
    
    Node* temp;
    if(index >= size/2) {
        temp = tail;
        for(size_t i = size - 1; i > index; i--) {
            temp = temp->prev;
        }
    }

    else {
        temp = head;
        for(size_t i = 0; i < index; i++) {
            temp = temp->next;
        }
    }

    return temp->data;
}

void DoublyLinkedList::append(int value) {
    Node* newNode = new Node(value);
    // if the List is empty => head=nullptr => added Node is the head
    if(!head) {
        head = newNode;
    }

    // old tail now points to added Node // added Node should point at old tail
    else {
        tail->next = newNode;
        newNode->prev = tail;
    }

    tail = newNode;
    size++;
}

void DoublyLinkedList::prepend(int value) {
    Node* newNode = new Node(value);
    // if the List is empty => tail=nullptr => added Node is the tail
    if(!head) {
        tail = newNode;
    }

    // new Node should point to old head // old head now points at added Node
    else {
        newNode->next = head;
        head->prev = newNode;
    }

    head = newNode;
    size++;
}

void DoublyLinkedList::insert(int value, size_t index) {
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

    Node* newNode = new Node(value);
    // find Node prior to the index we want to insert new Node (instead of choosing one way by default, check for which one is shorter)
    Node* prior;
    if(index - 1 < size - index) {
        prior = head;
        for(size_t i = 1; i < index; i++) {
            prior = prior->next;
        }
    }

    else {
        prior = tail;
        for(size_t i = size; i > index; i--) {
            prior = prior->prev;
        }
    }

    // from A<->B to A<->C<->B
    newNode->next = prior->next; // C.next = ->B
    newNode->prev = prior;       // C.prev = ->A
    prior->next->prev = newNode; // B.prev = ->C
    prior->next = newNode;       // A.next = ->C
    size++;

}

int DoublyLinkedList::pop_front(void) {
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

    else {
        head->next->prev = nullptr; // Node after old head now points at nothing instead of the old head
        head = head->next; // head is passed to the next Node
    }

    delete temp;
    size--;
    return temp_v;
}

int DoublyLinkedList::pop_back(void) {
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

    else {
        tail->prev->next = nullptr; // Node before old tail now points at nothing instead of the old tail
        tail = tail->prev; // tail is passed to the prior Node
    }
    
    delete temp;
    size--;
    return temp_v;
}

int DoublyLinkedList::remove(size_t index) {
    if(index >= size) {
        std::cout << "\nIndex=" << index << " is out of bounds.\n";
        return 0;
    }

    if(index == 0) {
        return this->pop_front();
    }

    else if(index == size-1) {
        return this->pop_back();
    }

    // find the Node that we want to remove (instead of choosing one way by default, check for which one is shorter)
    Node* temp;
    if(index < size - index - 1) {
        temp = head;
        for(size_t i = 0; i < index; i++) {
            temp = temp->next;
        }
    }

    else {
        temp = tail;
        for(size_t i = size - 1; i > index; i--) {
            temp = temp->prev;
        }
    }

    // save removed value to a temporary variable (for returning purposes)
    int temp_v = temp->data;
    // from A<->C<->B to A<->B
    temp->prev->next = temp->next; // A.next = ->B
    temp->next->prev = temp->prev; // B.prev = ->A
    size--;
    delete temp;
    return temp_v;
}

bool DoublyLinkedList::search(int value) {
    // 2 "pointers" at both ends of the array moving towards the middle until they "collide" (to ensure they will the size must be odd)
    Node* current = head;
    Node* current_end = tail;
    // if the size is even, we skip 1 step (of course we check if we didn't pass our value) and act as we have size-- therefore odd
    if(size % 2 == 0 && size) {
        if(current->data == value) {
            return true;
        }

        current = current->next;
    }

    if(size == 1) {
        if(current->data == value) {
            return true;
        }

        return false;
    }

    while(current != tail) {
        if(current->data == value) {
            return true;
        }

        else if(current_end->data == value) {
            return true;
        }

        current = current->next;
        current_end = current_end->prev;
    }

    return false;
}