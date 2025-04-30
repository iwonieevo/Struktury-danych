#pragma once
#include "PriorityQueue.h"
#include "BinaryHeap.h"
#include "LinkedList.h"
#include "utility.h"
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <cstdio>  // remove()
#include <cstddef> // size_t
#include <cstdint> // uint8_t
#include <initializer_list>

// Function loading data into List
void load_from_file(const std::string& keys_path, std::string& values_path, PriorityQueue& queue);

void priority_queues_main(std::initializer_list<unsigned int> SIZES, uint8_t NUM_OF_TIMES);