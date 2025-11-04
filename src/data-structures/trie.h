//Trie-based Inverted Index data structure, using polymorphism

#pragma once

#include <vector>
#include <string>
#include <map>
#include "..\recipe.h"
#include "invertedIndex.h"


class trie : public invertedIndex{
    struct trieNode{
        map<char, trieNode*> children;
        bool isWord;
        vector<int> recipeNums;
        trieNode(){
            isWord = false;
        }
    };

    trieNode* root;
    trieNode* search(std::string ingredient);
    void clear(trieNode* node);

public:
    trie();
    ~trie();

    void insert(std::string ingredient, int recipeNum);
    void buildIndex(vector<Recipe>& recipes) override;
    vector<int> findRecipes(const vector<std::string>& ingredients) override;
    std::string getIndexType() const override;
};