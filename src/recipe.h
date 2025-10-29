//Declares the Recipe class: used for recipe objects

#include <iostream>
#include <string>
using namespace std;

class Recipe{
private:
    int recipeNum;
    string title;
    string ingredientsExact;
    string instructions;
    string linkToRecipe;
    string source;
    string ingredients;

public:
    Recipe(int recipeNum, string title, string ingredientsExact, string instructions, string linktoRecipe, string source, string ingredients);
};