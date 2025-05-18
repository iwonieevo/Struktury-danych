#pragma once
#include <string>

class Dictionary {
public:
    // Add key-value pair to the dictionary
    virtual void insert(std::string key, int value) = 0;

    // Remove element with specified key and return its value
    virtual int remove(std::string key) = 0;

    // Return value of element with specified key
    virtual void get(std::string key) = 0;

    // Change value of element with specified key
    virtual void set(std::string key, int new_value) = 0;

    // Display the key-value pairs inside the dictionary
    virtual void print(void) = 0;

    virtual ~Dictionary() {}
};