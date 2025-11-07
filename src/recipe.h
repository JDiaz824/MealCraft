//Declares the Recipe class: used for recipe objects

#pragma once

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Recipe{
private:
    int recipeNum;
    string title;
    vector<string> ingredientsExact; // numbers of each ingredient (ex. 2 eggs)
    vector<string> instructions;
    string linkToRecipe;
    string source;
    vector<string> ingredients; // raw ingredients (ex. eggs)

public:
    Recipe(int recipeNum, string title, vector<string> ingredientsExact, vector<string> instructions, string linktoRecipe, string source, vector<string> ingredients);
    const int getRecipeNum() const;
    const string getTitle() const;
    const vector<string> getIngredientsExact() const;
    const vector<string> getInstructions() const;
    const string getLinkToRecipe() const;
    const string getSource() const;
    const vector<string> getIngredients() const;
};