#include <iostream>
#include <vector>
#include <string>
#include <limits> 
#include <cctype>   


#include "recipeLoader.h"     
#include "recipe.h"           
#include "invertedIndex.h"    
#include "trie.h"             
#include "hashMap.h"          

#include <chrono> 
#include <iomanip> 

using namespace std;

Recipe* findRecipeById(vector<Recipe>& allRecipes, int recipeId) {
    for (int i = 0; i < allRecipes.size(); ++i) {
        if (allRecipes[i].getRecipeNum() == recipeId) { 
            return &allRecipes[i]; 
        }
    }
    return nullptr; 
}

void displayRecipeDetails(const Recipe& recipe) {
    cout << "\n--- " << recipe.getTitle() << " ---" << endl; 
    
    cout << "Ingredients:" << endl;
    vector<string> ingredients = recipe.getIngredientsExact(); 
    for (int i = 0; i < ingredients.size(); ++i) {
        cout << " - " << ingredients[i] << endl;
    }

    cout << "\nInstructions:" << endl;
    vector<string> instructions = recipe.getInstructions(); 
    for (int i = 0; i < instructions.size(); ++i) {
        cout << " " << (i + 1) << ". " << instructions[i] << endl;
    }

    cout << "\nSource: " << recipe.getSource() << endl; 
    cout << "Link: " << recipe.getLinkToRecipe() << endl; 
    cout << "-----------------------------------" << endl;
}

int getMenuChoice(int min, int max) {
    int choice;
    cout << "Enter your choice: ";

    while (!(cin >> choice) || choice < min || choice > max) {
        cout << "Invalid input. Please enter a number between " << min << " and " << max << "." << endl;
        
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        cout << "Enter your choice: ";
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return choice;
}

string toLower(string s) {
    for (int i = 0; i < s.length(); ++i) {
        s[i] = tolower(s[i]);
    }
    return s;
}

void runRecipeFinder(invertedIndex* index, vector<Recipe>& allRecipes) {
    vector<string> userIngredients;
    
    while (true) {
        cout << "\n--- Recipe Finder (" << index->getIndexType() << ") ---" << endl; 
        cout << "1. Add an ingredient you have" << endl;
        cout << "2. View your current ingredients" << endl;
        cout << "3. Find recipes!" << endl;
        cout << "4. Clear ingredients and start over" << endl;
        cout << "5. Back to main menu" << endl;
        
        int choice = getMenuChoice(1, 5);
        
        if (choice == 1) { 
            cout << "Enter ingredient name: ";
            string ingredient;
            getline(cin, ingredient); 

            string normalized = toLower(ingredient);
            
            if (!normalized.empty()) {
                userIngredients.push_back(normalized);
                cout << "'" << normalized << "' added." << endl;
            }
        } 
        else if (choice == 2) { 
            if (userIngredients.empty()) {
                cout << "You have no ingredients yet." << endl;
            } else {
                cout << "Your ingredients: [";
                for (size_t i = 0; i < userIngredients.size(); ++i) {
                    cout << userIngredients[i];
                    if (i < userIngredients.size() - 1) {
                        cout << ", ";
                    }
                }
                cout << "]" << endl;
            }
        } 
        else if (choice == 3) { 
            if (userIngredients.empty()) {
                cout << "Please add some ingredients first." << endl;
                continue; 
            }

            cout << "Searching..." << endl;
            
            vector<int> recipeIDs = index->findRecipes(userIngredients);
            
            if (recipeIDs.empty()) {
                cout << "Found 0 recipes you can make with all those ingredients." << endl;
            } else {
                cout << "Found " << recipeIDs.size() << " recipes you can make:" << endl;
                vector<Recipe*> foundRecipes;
                for (int i = 0; i < recipeIDs.size(); ++i) {
                    Recipe* recipe = findRecipeById(allRecipes, recipeIDs[i]);
                    if (recipe != nullptr) {
                        foundRecipes.push_back(recipe);
                        cout << (i + 1) << ". " << recipe->getTitle() << endl; 
                    }
                }

                cout << "\nEnter a recipe number to view details, or 0 to go back: ";
                int recipeChoice = getMenuChoice(0, foundRecipes.size());
                
                if (recipeChoice > 0) {
                    displayRecipeDetails(*foundRecipes[recipeChoice - 1]);
                }
                
            }
        } 
        else if (choice == 4) { 
            userIngredients.clear();
            cout << "Your ingredient list has been cleared." << endl;
        } 
        else if (choice == 5) { 
            cout << "Returning to main menu..." << endl;
            break; 
        }
    }
}

void runBenchmarks(string& csvPath) {
    cout << "\n--- Running Performance Benchmarks ---" << endl;

    cout << "Loading dataset..." << endl;
    auto startLoad = chrono::high_resolution_clock::now();
    RecipeLoader loader;
    vector<Recipe> recipes = loader.loadRecipes(csvPath); 
    auto endLoad = chrono::high_resolution_clock::now();
    chrono::duration<double> loadTime = endLoad - startLoad;
    
    if (recipes.empty()) {
        cerr << "Cannot run benchmarks: Dataset not loaded." << endl;
        return;
    }
    cout << "Loaded " << recipes.size() << " recipes in " << fixed << setprecision(4) << loadTime.count() << " seconds." << endl;


    cout << "\n--- Time to Build Index ---" << endl;
    
    auto startMapBuild = chrono::high_resolution_clock::now();
    HashMap* mapIndex = new HashMap();
    mapIndex->buildIndex(recipes); 
    auto endMapBuild = chrono::high_resolution_clock::now();
    chrono::duration<double> mapBuildTime = endMapBuild - startMapBuild;
    cout << "HashMap Build Time: " << fixed << setprecision(4) << mapBuildTime.count() << " seconds." << endl;

    auto startTrieBuild = chrono::high_resolution_clock::now();
    trie* trieIndex = new trie();
    trieIndex->buildIndex(recipes); 
    auto endTrieBuild = chrono::high_resolution_clock::now();
    chrono::duration<double> trieBuildTime = endTrieBuild - startTrieBuild;
    cout << "Trie Build Time:    " << fixed << setprecision(4) << trieBuildTime.count() << " seconds." << endl;

    cout << "\n--- Average Query Time (1000 iterations) ---" << endl;
    
    vector<vector<string>> testQueries = {
        {"chicken", "garlic", "onion"},
        {"beef", "potato", "carrot", "celery", "onion"},
        {"flour", "sugar", "eggs", "butter", "milk", "vanilla", "salt"}
    };

    const int ITERATIONS = 1000;
    cout << fixed << setprecision(8); 

    for (int i = 0; i < testQueries.size(); ++i) {
        vector<string> query = testQueries[i];

        cout << "\nQuery (" << query.size() << " ingredients): [";
        for (size_t j = 0; j < query.size(); ++j) cout << query[j] << (j == query.size() - 1 ? "" : ", ");
        cout << "]" << endl;

        auto startMapQuery = chrono::high_resolution_clock::now();
        for (int k = 0; k < ITERATIONS; ++k) {
            mapIndex->findRecipes(query); //
        }
        auto endMapQuery = chrono::high_resolution_clock::now();
        double mapQueryTime = chrono::duration<double>(endMapQuery - startMapQuery).count() / ITERATIONS;
        cout << "HashMap Avg. Query: " << mapQueryTime << " seconds." << endl;

        auto startTrieQuery = chrono::high_resolution_clock::now();
        for (int k = 0; k < ITERATIONS; ++k) {
            trieIndex->findRecipes(query); //
        }
        auto endTrieQuery = chrono::high_resolution_clock::now();
        double trieQueryTime = chrono::duration<double>(endTrieQuery - startTrieQuery).count() / ITERATIONS;
        cout << "Trie Avg. Query:    " << trieQueryTime << " seconds." << endl;
    }

    cout << "\n--- Memory Usage ---" << endl;
    cout << "Note: To check memory, please use an external tool like 'top' (Linux/Mac) or Task Manager (Windows) while the program is running." << endl;
    cout << "----------------------------------------" << endl;

    delete mapIndex;
    delete trieIndex;
}


int main() {
    cout << "Welcome to MealCraft!" << endl;
    cout << "Loading recipe dataset..." << endl;
    
    RecipeLoader loader;
    
    string csvPath = "../data/RecipeNLG_dataset.csv";
    vector<Recipe> allRecipes = loader.loadRecipes(csvPath);

    if (allRecipes.empty()) {
        cerr << "\nFATAL ERROR: Could not load '" << csvPath << "'." << endl;
        cerr << "Please make sure it is downloaded to the 'data/' folder as per data/README.md." << endl;
        return 1;
    }

    cout << "Building search indexes..." << endl;

    invertedIndex* mapIndex = new HashMap();
    mapIndex->buildIndex(allRecipes); 

    // invertedIndex* trieIndex = new trie();
    // trieIndex->buildIndex(allRecipes); 
    
    cout << "All systems ready!" << endl;

    while (true) {
        cout << "\n========== Main Menu ==========" << endl;
        cout << "1. Find Recipes (using Hash Map)" << endl;
        cout << "2. Find Recipes (using Trie)" << endl;
        cout << "3. Run Performance Benchmarks" << endl;
        cout << "4. Exit" << endl;
        
        int choice = getMenuChoice(1, 4);
        
        if (choice == 1) {
            runRecipeFinder(mapIndex, allRecipes);
        }
        else if (choice == 2) {
            // runRecipeFinder(trieIndex, allRecipes);
        }
        else if (choice == 3) {
            runBenchmarks(csvPath);
        }
        else if (choice == 4) {
            cout << "Thank you for using MealCraft! Goodbye." << endl;
            break; 
        }
    }

    delete mapIndex;
    // delete trieIndex;

    return 0;
}