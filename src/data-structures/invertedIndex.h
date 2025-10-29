//Inverted Index Interface implementation; used for Hash Map and Trie

#pragma once

#include <vector>
#include <string>
#include "..\recipe.h"

using namespace std;

class invertedIndex{
public:
    virtual ~invertedIndex(){};
    virtual void buildIndex(vector<Recipe>& recipes) = 0;
    virtual vector<int> findRecipes(const vector<string>& ingredients) = 0;
    virtual string getIndexType() const = 0;
};