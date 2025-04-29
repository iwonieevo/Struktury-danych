#pragma once
#include "PriorityQueue.h"
#include "Heap.h"
#include <string>
#include <cstdint> // uint8_t
#include <initializer_list>

// Function loading data into List
void load_from_file(const std::string& keys_path, std::string& values_path, PriorityQueue& queue);

int priority_queues_main(std::initializer_list<unsigned int> SIZES, uint8_t NUM_OF_TIMES);