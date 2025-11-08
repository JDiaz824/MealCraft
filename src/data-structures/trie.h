//Trie-based Inverted Index data structure, using polymorphism

#pragma once

#include <vector>
#include <string>
#include <map>
#include <set>
#include "..\recipe.h"
#include "invertedIndex.h"


class trie : public invertedIndex{
    //Struct for a node in the trie
    struct trieNode{
        map<char, trieNode*> children;
        bool isWord;
        set<int> recipeNums;
        trieNode(){
            isWord = false;
        }
    };

    trieNode* root;

    //Helper function for finding ingredients
    trieNode* search(std::string ingredient);

    //Helper function for destructor
    void clear(trieNode* node);

public:
    //Constructor
    trie();

    //Destructor
    ~trie();

    //Inserts an item into a trie node
    void insert(std::string ingredient, int recipeNum);

    //InvertedIndex override functions to simplify parsing
    void buildIndex(vector<Recipe>& recipes) override;
    vector<int> findRecipes(const vector<std::string>& ingredients) override;
    std::string getIndexType() const override;
};