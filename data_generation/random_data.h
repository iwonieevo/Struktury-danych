#pragma once
#include <string>
#include <random>
#include <fstream>
#include <iostream>
#include <cstdint>

// Generates a .csv file containing randomly generated integers
void generate_random_integers(std::string& dest_path, int min, int max, size_t n_rows, size_t n_columns);