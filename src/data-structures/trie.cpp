//Trie-based Inverted Index data structure, using polymorphism

#include "trie.h"
#include <iostream>
#include <set>

using namespace std;

//Constructor
trie::trie(){
    root = new trieNode;
}

//Destructor
trie::~trie(){
    clear(root);
}

//Helper for deleting a trie through the destructor
void trie::clear(trieNode* node){
    if(node == nullptr){
        return;
    }

    for(auto& child : node->children){
        clear(child.second);
    }

    delete node;
}

//Inserts ingredient and corresponding recipeNum
void trie::insert(string ingredient, int recipeNum){
    trieNode* current = root;

    //Iterates through each character in the ingredient
    for(auto c : ingredient){
        if(current->children.find(c) == current->children.end()){
            current->children[c] = new trieNode(); //Creates new node if path doesn't exist
        }
        current = current->children[c];
    }

    //Marks ingredient as valid when the end is reached
    current->isWord = true;

    //Checks for duplicate recipeNums
    bool found = false;
    for(int num : current->recipeNums){
        if(num == recipeNum){
            found = true;
            break;
        }
    }

    //Pushes back recipeNum to ingredient if unique
    if(!found){
        current->recipeNums.push_back(recipeNum);
    }
}

//Helper function for finding an ingredient's end node
trie::trieNode* trie::search(string ingredient){
    trieNode* current = root; //Start at root

    for(char c : ingredient){
        if(current->children.find(c) == current->children.end()){
            return nullptr; //Returns null if not found
        }
        current = current->children[c]; //Continues down the path
    }

    if(current->isWord){
        return current; //Return node if it's a valid word
    }
    return nullptr; //Returns null if the ingredient is not valid
}

//Builds index by inserting every ingredient from every recipe
void trie::buildIndex(vector<Recipe>& recipes){

    for(const Recipe& recipe : recipes){ //Loops through all recipes
        for(const string& ingredient : recipe.getIngredients()){ //Loops through each ingredient
            insert(ingredient, recipe.getRecipeNum()); //Inserts the data into the trie
        }
    }

    cout << "Trie Index Built!" << endl;
}

//Finds recipes that have all the specified ingredients
vector<int> trie::findRecipes(const vector<std::string>& ingredients){
    set<int> commonRecipeNums; //Used set to find intersection

    if(ingredients.empty()){
        return {}; //Returns nothing if no ingredients are provided
    }

    //Gets the list of recipes for the first ingredient
    trieNode* node = search(ingredients[0]);
    if(node == nullptr){
        return {}; //Returns nothing if first ingredient not found
    }

    //Adds first ingredient's recipes into set
    commonRecipeNums.insert(node->recipeNums.begin(), node->recipeNums.end());

    //Loops through the rest of the ingredients to find common recipes
    for(auto i = 1; i < ingredients.size(); i++){
        //Searches for next ingredient in the list
        node = search(ingredients[i]);

        if(node == nullptr){
            return {}; //Returns nothing if there's no ingredients in the trie
        }

        //Adds the current ingredient's recipes into a set
        set<int> currentRecipeNums(node->recipeNums.begin(), node->recipeNums.end());

        //Finds and keeps the intersection (common recipes) between both sets
        for(auto it = commonRecipeNums.begin(); it != commonRecipeNums.end(); ){
            if(currentRecipeNums.find(*it) == currentRecipeNums.end()){
                //Removes recipe if not found in current set
                it = commonRecipeNums.erase(it);
            }
            else{
                //Recipe found in both sets: keep it and continue
                ++it;
            }
        }
    }

    //Converts the set of all common recipes into a vector
    vector<int> recipeList(commonRecipeNums.begin(), commonRecipeNums.end());
    return recipeList;
}

//Returns the index type currently being used
string trie::getIndexType() const{
    return "Trie";
}