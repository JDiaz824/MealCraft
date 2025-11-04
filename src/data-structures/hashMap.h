//Hash Map-based Inverted Index data structure, using polymorphism

#pragma once

#include "src/invertedIndex.h"

using namespace std;

// Entry struct for individual key-value pair
struct Entry {
    string key;
    vector<int> ids;
    Entry* next;

    // constructors
    Entry(string& k, int id) : key(k), ids({id}), next(nullptr) {}

    Entry(string& k, vector<int>& vec) : key(k), ids(vec), next(nullptr) {}
    // destructor
    ~Entry() {
        delete next;
    }
};

class HashMap: public invertedIndex {
    private:
        Entry** buckets; // array of Entry* pointers
        size_t capacity; // array size
        size_t size; // num of entries

        int hashFunction(string& key);
        void resize();
    public:
        // Constructor/Deconstructor
        HashMap(int initialCap = 16);
        ~HashMap();

        // hashMap specific functions
        void insert(string& ingredient, int recipeID);
        vector<int> find(string& key);

        // inherited functions
        void buildIndex(vector<Recipe>& recipes) override;
        vector<int> findRecipes(vector<string>& ingredients) override;
        string getIndexType() const override;
};