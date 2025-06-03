#include "../headers/ChainAVL.h"

ChainAVL::ChainAVL(size_t size = 0) {
    table_size = size ? size : 1;
    table = new AVLTree*[size];
    for (size_t i = 0; i < size; i++) {
        table[i] = new AVLTree();
    }
}

ChainAVL::~ChainAVL() {
    for (size_t i = 0; i < table_size; i++) {
        delete table[i];
    }
    delete[] table;
}

size_t ChainAVL::hash(const std::string& key) const {
    size_t hashed = 0;
    for (char c : key) {
        hashed = (hashed * 31 + c) % table_size;
    }
    return hashed;
}

void ChainAVL::insert(const std::string& key, int value) {
    table[hash(key)]->insert(key, value);
}

int ChainAVL::remove(const std::string& key) {
    return table[hash(key)]->remove(key);
}

void ChainAVL::print(void) const {
    for(size_t i = 0; i < table_size; i++) {
        std::cout << "\n@@@ Tree #" << i << std::endl;
        table[i]->print();
    }
}

int ChainAVL::get(const std::string& key) const {
    AVLNode* temp = table[hash(key)]->find(key);
    return (temp) ? temp->value : INT_MIN;
}

