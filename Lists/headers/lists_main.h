#pragma once
#include "List.h"
#include <string>
#include <cstdint> // uint8_t
#include <initializer_list>

// Function loading data into List
void load_from_file(const std::string& source_path, List& list);

// Function that times method execution
template <typename ReturnType, typename... Parameters>
unsigned long long measure_time(List* list, ReturnType (List::*method)(Parameters...), Parameters... params);

int lists_main(std::initializer_list<unsigned int> SIZES, uint8_t NUM_OF_TIMES);