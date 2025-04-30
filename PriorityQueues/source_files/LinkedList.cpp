#include "..\headers\LinkedList.h"

LinkedList::LinkedList() : head(nullptr), size(0) {}

LinkedList::~LinkedList() {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

PriorityQueue* LinkedList::clone() const {
    LinkedList* copy = new LinkedList();
    if (!head) return copy;

    // Copy the head node
    copy->head = new Node(head->element, head->priority);
    Node* current_original = head->next;
    Node* current_copy = copy->head;

    // Copy the rest of the nodes
    while (current_original) {
        current_copy->next = new Node(current_original->element, current_original->priority);
        current_copy = current_copy->next;
        current_original = current_original->next;
    }

    copy->size = size; // Copy the size
    return copy;
}

void LinkedList::insert(int e, unsigned int p) {
    Node* new_node = new Node(e, p);
    size++;

    if (!head || p > head->priority) {
        new_node->next = head;
        head = new_node;
        return;
    }

    Node* current = head;
    while (current->next && current->next->priority >= p) {
        current = current->next;
    }

    new_node->next = current->next;
    current->next = new_node;
}

int LinkedList::extract_max() {
    if (!head) throw std::runtime_error("Queue is empty");

    int max_element = head->element;
    Node* temp = head;
    head = head->next;
    delete temp;
    size--;

    return max_element;
}

const int& LinkedList::find_max() const {
    if (!head) throw std::runtime_error("Queue is empty");
    return head->element;
}

void  LinkedList::modify_key(int e, unsigned int new_priority) {
    if (!head) throw std::runtime_error("Queue is empty");

    Node* prev = nullptr;
    Node* current = head;

    while (current && current->element != e) {
        prev = current;
        current = current->next;
    }

    if (!current) throw std::runtime_error("Element not found");

    // Remove current node from the list
    if (prev) {
        prev->next = current->next;
    } else {
        head = current->next;
    }
    size--;

    // Re-insert with new priority
    insert(e, new_priority);
    delete current;
}

size_t LinkedList::return_size() const {
    return size;
}
