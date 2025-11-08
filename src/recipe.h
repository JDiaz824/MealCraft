//Declares the Recipe class: used for recipe objects

#pragma once

#include <iostream>
#include <vector>
#include <string>
using namespace std;

//This is the Recipe object class, which is able to contain all the data from a given recipe from the dataset.
class Recipe{
private:
    //These are the different data in a given recipe:
    int recipeNum; // ID # given to a recipe
    string title;
    vector<string> ingredientsExact; // numbers of each ingredient (ex. 2 eggs)
    vector<string> instructions;
    string linkToRecipe;
    string source; // which database the recipe came from (gathered or recipe1m)
    vector<string> ingredients; // raw ingredients (ex. eggs)

public:
    Recipe(int recipeNum, string title, vector<string> ingredientsExact, vector<string> instructions, string linkToRecipe, string source, vector<string> ingredients);
    const int getRecipeNum() const;
    const string getTitle() const;
    const vector<string> getIngredientsExact() const;
    const vector<string> getInstructions() const;
    const string getLinkToRecipe() const;
    const string getSource() const;
    const vector<string> getIngredients() const;
};