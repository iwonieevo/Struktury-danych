#include "../headers/CuckooHashing.h"

CuckooHashing::CuckooHashing(size_t initial_capacity) 
    : capacity(initial_capacity), size(0) {
    table1 = new CuckooNode*[capacity];
    table2 = new CuckooNode*[capacity];
    
    for (size_t i = 0; i < capacity; i++) {
        table1[i] = new CuckooNode();
        table2[i] = new CuckooNode();
    }
}

void CuckooHashing::destroy() {
    for (size_t i = 0; i < capacity; i++) {
        delete table1[i];
        delete table2[i];
    }
    delete[] table1;
    delete[] table2;
}

CuckooHashing::~CuckooHashing() {
    destroy();
}

size_t CuckooHashing::hash1(const std::string& key) const {
    size_t hash_value = 0;
    for (char c : key) {
        hash_value = (hash_value * 31 + c) % capacity;
    }
    return hash_value;
}

size_t CuckooHashing::hash2(const std::string& key) const {
    size_t hash_value = 0;
    for (char c : key) {
        hash_value = (hash_value * 37 + c) % capacity;
    }
    return hash_value;
}

bool CuckooHashing::insert_with_replacement(const std::string& key, int value, bool useFirstHash, size_t iterations) {
    if (iterations >= MAX_LOOP_ITERATIONS) {
        return false;
    }

    size_t pos = useFirstHash ? hash1(key) : hash2(key);
    CuckooNode** current_table = useFirstHash ? table1 : table2;

    std::string old_key = current_table[pos]->key;
    int old_value = current_table[pos]->value;
    bool was_occupied = current_table[pos]->isOccupied;

    current_table[pos]->key = key;
    current_table[pos]->value = value;
    current_table[pos]->isOccupied = true;

    if (!was_occupied) {
        size++;
        return true;
    }

    return insert_with_replacement(old_key, old_value, !useFirstHash, iterations + 1);
}

void CuckooHashing::rehash() {
    size_t old_capacity = capacity;
    CuckooNode** old_table1 = table1;
    CuckooNode** old_table2 = table2;

    capacity *= 2;
    size = 0;
    table1 = new CuckooNode*[capacity];
    table2 = new CuckooNode*[capacity];

    for (size_t i = 0; i < capacity; i++) {
        table1[i] = new CuckooNode();
        table2[i] = new CuckooNode();
    }

    for (size_t i = 0; i < old_capacity; i++) {
        if (old_table1[i]->isOccupied) {
            insert(old_table1[i]->key, old_table1[i]->value);
        }
        if (old_table2[i]->isOccupied) {
            insert(old_table2[i]->key, old_table2[i]->value);
        }
        delete old_table1[i];
        delete old_table2[i];
    }
    delete[] old_table1;
    delete[] old_table2;
}

void CuckooHashing::insert(const std::string& key, int value) {
    Node* existing = find(key);
    if (existing) {
        existing->value = value;
        return;
    }

    for (size_t attempt = 0; attempt < MAX_REHASH_ATTEMPTS; attempt++) {
        if (insert_with_replacement(key, value, true)) {
            return;
        }
        rehash();
    }
    std::cerr << "Failed to insert after " << MAX_REHASH_ATTEMPTS << " rehash attempts\n";
}

int CuckooHashing::remove(const std::string& key) {
    size_t pos1 = hash1(key);
    if (table1[pos1]->isOccupied && table1[pos1]->key == key) {
        int value = table1[pos1]->value;
        table1[pos1]->isOccupied = false;
        size--;
        return value;
    }

    size_t pos2 = hash2(key);
    if (table2[pos2]->isOccupied && table2[pos2]->key == key) {
        int value = table2[pos2]->value;
        table2[pos2]->isOccupied = false;
        size--;
        return value;
    }

    return INT_MIN;
}

Node* CuckooHashing::find(const std::string& key) {
    size_t pos1 = hash1(key);
    if (table1[pos1]->isOccupied && table1[pos1]->key == key) {
        return table1[pos1];
    }

    size_t pos2 = hash2(key);
    if (table2[pos2]->isOccupied && table2[pos2]->key == key) {
        return table2[pos2];
    }

    return nullptr;
}

void CuckooHashing::print(void) {
    std::cout << "Table 1:" << std::endl;
    for (size_t i = 0; i < capacity; i++) {
        if (table1[i]->isOccupied) {
            std::cout << table1[i]->key << ": " << table1[i]->value << std::endl;
        }
    }
    std::cout << "Table 2:" << std::endl;
    for (size_t i = 0; i < capacity; i++) {
        if (table2[i]->isOccupied) {
            std::cout << table2[i]->key << ": " << table2[i]->value << std::endl;
        }
    }
}