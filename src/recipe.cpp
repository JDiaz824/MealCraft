//Declares the Recipe class: used for recipe objects

#include <vector>
#include "recipe.h"
using namespace std;


Recipe::Recipe(int recipeNum, string title, vector<string> ingredientsExact, vector<string> instructions, string linktoRecipe, string source, vector<string> ingredients){
    this->recipeNum = recipeNum;
    this->title = title;
    this->ingredientsExact = ingredientsExact;
    this->instructions = instructions;
    this->linkToRecipe = linkToRecipe;
    this->source = source;
    this->ingredients = ingredients;
}

const int Recipe::getRecipeNum() const{
    return recipeNum;
}

const string Recipe::getTitle() const{
    return title;
}

const vector<string> Recipe::getIngredientsExact() const{
    return ingredientsExact;
}

const vector<string> Recipe::getInstructions() const{
    return instructions;
}

const string Recipe::getLinkToRecipe() const{
    return linkToRecipe;
}

const string Recipe::getSource() const{
    return source;
}

const vector<string> Recipe::getIngredients() const{
    return ingredients;
}