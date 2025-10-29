//Hash Map-based Inverted Index data structure, using polymorphism

#pragma once

#include "src/invertedIndex.h"

using namespace std;

// Entry struct for individual key-value pair
struct Entry {
    string key;
    vector<Recipe> recipes;
}