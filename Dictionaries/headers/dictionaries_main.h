#pragma once
#include "Dictionary.h"
#include "utility.h"
#include <string>
#include <cstdint> // uint8_t
#include <initializer_list>

// Function loading data into Dictionary
void load_from_file(const std::string& keys_path, const std::string& values_path, Dictionary& dict);

void dictionaries_main(std::initializer_list<unsigned int> SIZES, uint8_t NUM_OF_TIMES);