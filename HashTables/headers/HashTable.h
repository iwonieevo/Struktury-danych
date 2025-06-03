#pragma once
#include <string>
#include <iostream>

class HashTable {
public:
    // Add key-value pair to the dictionary (if element with specified key already exists, then update the value)
    virtual void insert(const std::string& key, int value) = 0;

    // Remove element with specified key and return its value
    virtual int remove(const std::string& key) = 0;

    // Return value of element with specified key
    virtual int get(const std::string& key) const = 0;

    // Display the key-value pairs inside the dictionary
    virtual void print(void) const = 0;

    virtual ~HashTable() {}
};