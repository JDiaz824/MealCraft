//Hash Map-based Inverted Index data structure, using polymorphism

#pragma once

#include "data-structures/invertedIndex.h"

using namespace std;

// Entry struct for individual key-value pair
struct Entry {
    string key;
    vector<int> ids;
    Entry* next;

    // constructors
    Entry(const string& k, int id) : key(k), ids({id}), next(nullptr) {}

    Entry(const string& k, vector<int>& vec) : key(k), ids(vec), next(nullptr) {}
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

        int hashFunction(const string& key);
        void resize();
    public:
        // Constructor/Deconstructor
        HashMap(int initialCap = 16);
        ~HashMap();

        // hashMap specific functions
        void insert(const string& ingredient, int recipeID);
        vector<int> find(const string& key);

        // inherited functions
        void buildIndex(vector<Recipe>& recipes) override;
        vector<int> findRecipes(const vector<std::string>& ingredients) override;
        std::string getIndexType() const override;
};