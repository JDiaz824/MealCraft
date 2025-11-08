//Loads all recipes from dataset
#pragma once

#include <vector>
#include <string>
#include "recipe.h"

using namespace std;

class RecipeLoader{
    public:
        // loads all recipes from csv file
        vector<Recipe> loadRecipes(const string& csvPath);
    private:
        // helper function to parse raw vector of strings 
        vector<string> parseStringList(const string& stringList);

        vector<string> parseQuotedList(const string& stringList);
};