//Trie-based Inverted Index data structure, using polymorphism

#include "trie.h"
#include <iostream>
#include <set>

using namespace std;

trie::trie(){
    root = new trieNode;
}

trie::~trie(){
    clear(root);
}

void trie::clear(trieNode* node){
    if(node == nullptr){
        return;
    }

    for(auto& child : node->children){
        clear(child.second);
    }

    delete node;
}

void trie::insert(string ingredient, int recipeNum){
    trieNode* current = root;

    for(auto c : ingredient){
        if(current->children.find(c) == current->children.end()){
            current->children[c] = new trieNode();
        }
        current = current->children[c];
    }

    current->isWord = true;

    bool found = false;
    for(int num : current->recipeNums){
        if(num == recipeNum){
            found = true;
            break;
        }
    }
    if(!found){
        current->recipeNums.push_back(recipeNum);
    }
}

trie::trieNode* trie::search(string ingredient){
    trieNode* current = root;

    for(char c : ingredient){
      if(current->children.find(c) == current->children.end()){
        return nullptr;
      }
      current = current->children[c];
    }

    if(current->isWord){
      return current;
    }
    return nullptr;
}

void trie::buildIndex(vector<Recipe>& recipes){
    cout << "Building Trie Index..." << endl;

    for(const Recipe& recipe : recipes){
        for(const string& ingredient : recipe.getIngredients()){
            insert(ingredient, recipe.getRecipeNum());
        }
    }

    cout << "Trie Index Built!" << endl;
}

vector<int> trie::findRecipes(const vector<std::string>& ingredients){
    set<int> commonRecipeNums;

    if(ingredients.empty()){
        return {};
    }

    trieNode* node = search(ingredients[0]);
    if(node == nullptr){
        return {};
    }

    commonRecipeNums.insert(node->recipeNums.begin(), node->recipeNums.end());

    for(auto i = 1; i < ingredients.size(); i++){
        if(node == nullptr){
            return {};
        }
        set<int> currentRecipeNums(node->recipeNums.begin(), node->recipeNums.end());

        for(auto it = commonRecipeNums.begin(); it != commonRecipeNums.end(); ){
            if(currentRecipeNums.find(*it) == currentRecipeNums.end()){
                it = commonRecipeNums.erase(it);
            }
            else{
                ++it;
            }
        }
    }
    vector<int> recipeList(commonRecipeNums.begin(), commonRecipeNums.end());
    return recipeList;
}

string trie::getIndexType() const{
    return "Trie";
}