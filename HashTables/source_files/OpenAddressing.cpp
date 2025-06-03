#include "../headers/OpenAddressing.h"
#include <climits>

OpenAddressing::OpenAddressing(size_t initial_capacity = 16)
    : capacity(initial_capacity), size(0) {
    table = new OpenAddressingNode*[capacity];
    for (size_t i = 0; i < capacity; i++) {
        table[i] = nullptr;
    }
}

void OpenAddressing::destroy() {
    for (size_t i = 0; i < capacity; i++) {
        if (table[i] != nullptr) {
            delete table[i];
        }
    }
    delete[] table;
}

OpenAddressing::~OpenAddressing() {
    destroy();
}

size_t OpenAddressing::hash(const std::string& key) const {
    size_t hash_value = 0;
    for (char c : key) {
        hash_value = (hash_value * 31 + c) % capacity;
    }
    return hash_value;
}

void OpenAddressing::resize() {
    size_t old_capacity = capacity;
    OpenAddressingNode** old_table = table;

    capacity *= 2;
    table = new OpenAddressingNode*[capacity];
    for (size_t i = 0; i < capacity; i++) {
        table[i] = nullptr;
    }

    size = 0;
    for (size_t i = 0; i < old_capacity; i++) {
        if (old_table[i] != nullptr && !old_table[i]->isDeleted) {
            insert(old_table[i]->key, old_table[i]->value);
            delete old_table[i];
        }
    }

    delete[] old_table;
}

OpenAddressingNode* OpenAddressing::insert_node(const std::string& key, int value) {
    size_t index = hash(key);
    size_t original = index;

    do {
        if (table[index] == nullptr || table[index]->isDeleted) {
            if (table[index] != nullptr) {
                delete table[index];
            }
            table[index] = new OpenAddressingNode(key, value);
            size++;
            return table[index];
        }
        if (table[index]->key == key) {
            table[index]->value = value;
            return table[index];
        }
        index = (index + 1) % capacity;
    } while (index != original);

    return nullptr;
}

void OpenAddressing::insert(const std::string& key, int value) {
    if (static_cast<double>(size) / capacity >= 0.7) {
        resize();
    }

    OpenAddressingNode* node = insert_node(key, value);
    if (!node) {
        resize();
        insert_node(key, value);
    }
}

int OpenAddressing::remove(const std::string& key) {
    size_t index = hash(key);
    size_t original = index;

    do {
        if (table[index] == nullptr) {
            return INT_MIN;
        }
        if (!table[index]->isDeleted && table[index]->key == key) {
            int value = table[index]->value;
            table[index]->isDeleted = true;
            size--;
            return value;
        }
        index = (index + 1) % capacity;
    } while (index != original);

    return INT_MIN;
}

OpenAddressingNode* OpenAddressing::find(const std::string& key) const {
    size_t index = hash(key);
    size_t original = index;

    do {
        if (table[index] == nullptr) {
            return nullptr;
        }
        if (!table[index]->isDeleted && table[index]->key == key) {
            return table[index];
        }
        index = (index + 1) % capacity;
    } while (index != original);

    return nullptr;
}

int OpenAddressing::get(const std::string& key) const {
    OpenAddressingNode* temp = find(key);
    return (temp) ? temp->value : INT_MIN;
}

void OpenAddressing::print(void) const {
    std::cout << std::endl;
    for (size_t i = 0; i < capacity; i++) {
        if (table[i] != nullptr && !table[i]->isDeleted) {
            std::cout << table[i]->key << ": " << table[i]->value << std::endl;
        }
    }
}