#pragma once
#include "HashTable.h"
#include "ChainAVL.h"
#include "OpenAddressing.h"
#include "CuckooHashing.h"
#include "utility.h"
#include <string>
#include <cstdint> // uint8_t
#include <fstream>
#include <random>
#include <initializer_list>

// Function loading data into the Hash Table
void load_from_file(const std::string& k_path, const std::string& v_path, HashTable& dict);

void unit_tests(uint8_t bucket_type);

void hash_tables_main(std::initializer_list<unsigned int> SIZES, uint8_t NUM_OF_TIMES);