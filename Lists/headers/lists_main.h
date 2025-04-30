#pragma once
#include "List.h"
#include "ArrayList.h"
#include "SinglyLinkedList.h"
#include "DoublyLinkedList.h"
#include "../../utility.h"
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <cstdio>  // remove()
#include <cstddef> // size_t
#include <cstdint> // uint8_t
#include <initializer_list>

// Function loading data into List
void load_from_file(const std::string& source_path, List& list);

void lists_main(std::initializer_list<unsigned int> SIZES, uint8_t NUM_OF_TIMES);