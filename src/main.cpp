#include <iostream>
#include <vector>
#include <string>
#include <limits> // Used for clearing error-state input
#include <cctype>   // Used for tolower()

// Project Headers
#include "recipeLoader.h"
#include "recipe.h"
#include "invertedIndex.h"
#include "trie.h"
#include "hashMap.h"

// Benchmarking Headers
#include <chrono>
#include <iomanip>

using namespace std;

// Helper function to find a Recipe object by its ID
Recipe* findRecipeById(vector<Recipe>& allRecipes, int recipeId) {
    // Loop through all recipes
    for (int i = 0; i < allRecipes.size(); ++i) {
        // Return a pointer to the recipe if the ID matches
        if (allRecipes[i].getRecipeNum() == recipeId) {
            return &allRecipes[i];
        }
    }
    return nullptr; // No recipe found
}

// Prints all the details of a single recipe in a clean format
void displayRecipeDetails(const Recipe& recipe) {
    cout << "\n--- " << recipe.getTitle() << " ---" << endl;
    
    // Print list of exact ingredients
    cout << "\nIngredients:" << endl;
    vector<string> ingredients = recipe.getIngredientsExact();
    for (int i = 0; i < ingredients.size(); ++i) {
        cout << " - " << ingredients[i] << endl;
    }

    // Print list of instructions
    cout << "\nInstructions:" << endl;
    vector<string> instructions = recipe.getInstructions();
    for (int i = 0; i < instructions.size(); ++i) {
        cout << " " << (i + 1) << ". " << instructions[i] << endl;
    }

    // Print metadata
    cout << "\nSource: " << recipe.getSource() << endl;
    cout << "Link: " << recipe.getLinkToRecipe() << endl;
    cout << "-----------------------------------" << endl;
}

// Safely gets a number from the user within a specific range
int getMenuChoice(int min, int max) {
    int choice;
    cout << "Enter your choice: ";

    // Loop until the user gives valid input
    // Checks for non-numbers OR numbers out of range
    while (!(cin >> choice) || choice < min || choice > max) {
        cout << "Invalid input. Please enter a number between " << min << " and " << max << "." << endl;
        
        // Clears the error flag (e.g., if user typed "abc")
        cin.clear();
        // Flushes the bad input from the stream
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        cout << "Enter your choice: ";
    }

    // Clear the leftover newline character from the input buffer
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return choice;
}

// Helper function to convert a string to all lowercase
string toLower(string s) {
    for (int i = 0; i < s.length(); ++i) {
        s[i] = tolower(s[i]);
    }
    return s;
}

// Runs the main UI loop for finding recipes with a *specific* index
void runRecipeFinder(invertedIndex* index, vector<Recipe>& allRecipes) {
    vector<string> userIngredients; // Stores the user's current list
    
    // This is the sub-menu loop
    while (true) {
        // Display the menu, showing which index is active
        cout << "\n--- Recipe Finder (" << index->getIndexType() << ") ---" << endl;
        cout << "1. Add an ingredient you have" << endl;
        cout << "2. View your current ingredients" << endl;
        cout << "3. Find recipes!" << endl;
        cout << "4. Clear ingredients and start over" << endl;
        cout << "5. Back to main menu" << endl;
        
        // Get a safe choice from the user
        int choice = getMenuChoice(1, 5);
        
        // Add Ingredient
        if (choice == 1) {
            cout << "\nEnter ingredient name: ";
            string ingredient;
            getline(cin, ingredient); // Use getline to allow spaces

            // "Normalize" the input to lowercase
            string normalized = toLower(ingredient);
            
            // Skip if the user just pressed enter
            if (normalized.empty()) {
                continue;
            }

            // Check if the ingredient is in our database
            // We do this by searching for it as a single-item list
            vector<int> validationCheck = index->findRecipes({normalized});

            // If the list is empty, the ingredient isn't valid
            if (validationCheck.empty()) {
                cout << "\n'" << normalized << "' is not a valid ingredient. Please try again." << endl;
            } 
            // Otherwise, the ingredient is valid
            else {
                // Add the cleaned-up ingredient to the list
                userIngredients.push_back(normalized);
                cout << "'" << normalized << "' added." << endl;
            }
        } 
        // View Ingredients
        else if (choice == 2) {
            if (userIngredients.empty()) {
                cout << "\nYou have no ingredients yet." << endl;
            } else {
                // Print the user's list in a formatted way
                cout << "\nYour ingredients: [";
                for (size_t i = 0; i < userIngredients.size(); ++i) {
                    cout << userIngredients[i];
                    if (i < userIngredients.size() - 1) {
                        cout << ", ";
                    }
                }
                cout << "]" << endl;
            }
        } 
        // Find Recipes
        else if (choice == 3) {
            if (userIngredients.empty()) {
                cout << "\nPlease add some ingredients first." << endl;
                continue; // Skip back to the start of the loop
            }

            cout << "\nSearching..." << endl;
            
            // Call findRecipes on the current index (Trie or HashMap)
            vector<int> recipeIDs = index->findRecipes(userIngredients);
            
            if (recipeIDs.empty()) {
                cout << "Found 0 recipes you can make with all those ingredients." << endl;
            } else {
                cout << "Found " << recipeIDs.size() << " recipes you can make:" << endl;
                
                // Store pointers to the found recipes
                vector<Recipe*> foundRecipes;
                for (int i = 0; i < recipeIDs.size(); ++i) {
                    Recipe* recipe = findRecipeById(allRecipes, recipeIDs[i]);
                    if (recipe != nullptr) {
                        foundRecipes.push_back(recipe);
                        // Print the list of matching recipe titles
                        cout << (i + 1) << ". " << recipe->getTitle() << endl;
                    }
                }

                // Let the user view details
                cout << "\nEnter a recipe number to view details, or 0 to go back: ";
                int recipeChoice = getMenuChoice(0, foundRecipes.size());
                
                if (recipeChoice > 0) {
                    // Display the full details for the chosen recipe
                    displayRecipeDetails(*foundRecipes[recipeChoice - 1]);
                }
            }
        } 
        // Clear Ingredients
        else if (choice == 4) {
            userIngredients.clear(); // Empty the vector
            cout << "\nYour ingredient list has been cleared." << endl;
        } 
        // Back to Main Menu
        else if (choice == 5) {
            cout << "\nReturning to main menu..." << endl;
            break; // Exit the sub-menu loop
        }
    }
}

// Runs a performance test on both data structures
void runBenchmarks(string& csvPath) {
    cout << "\n--- Running Performance Benchmarks ---" << endl;

    // Load the dataset and time it
    cout << "Loading dataset..." << endl;
    auto startLoad = chrono::high_resolution_clock::now(); // Start timer
    RecipeLoader loader;
    vector<Recipe> recipes = loader.loadRecipes(csvPath);
    auto endLoad = chrono::high_resolution_clock::now(); // Stop timer
    chrono::duration<double> loadTime = endLoad - startLoad;
    
    if (recipes.empty()) {
        cerr << "Cannot run benchmarks: Dataset not loaded." << endl;
        return;
    }
    // Set precision for printing decimal seconds
    cout << "Loaded " << recipes.size() << " recipes in " << fixed << setprecision(4) << loadTime.count() << " seconds." << endl;


    // Test the build time for both indexes
    cout << "\n--- Time to Build Index ---" << endl;
    
    // Time HashMap Build
    auto startMapBuild = chrono::high_resolution_clock::now();
    HashMap* mapIndex = new HashMap(); // Create new index
    mapIndex->buildIndex(recipes);
    auto endMapBuild = chrono::high_resolution_clock::now();
    chrono::duration<double> mapBuildTime = endMapBuild - startMapBuild;
    cout << "HashMap Build Time: " << fixed << setprecision(4) << mapBuildTime.count() << " seconds." << endl;

    // Time Trie Build
    auto startTrieBuild = chrono::high_resolution_clock::now();
    trie* trieIndex = new trie(); // Create new index
    trieIndex->buildIndex(recipes);
    auto endTrieBuild = chrono::high_resolution_clock::now();
    chrono::duration<double> trieBuildTime = endTrieBuild - startTrieBuild;
    cout << "Trie Build Time:    " << fixed << setprecision(4) << trieBuildTime.count() << " seconds." << endl;

    // Test the average query time
    cout << "\n--- Average Query Time (1000 iterations) ---" << endl;
    
    // A list of sample queries to test
    vector<vector<string>> testQueries = {
        {"chicken", "garlic", "onion"}, // Common query
        {"beef", "potato", "carrot", "celery", "onion"}, // Medium query
        {"flour", "sugar", "eggs", "butter", "milk", "vanilla", "salt"} // Long query (baking)
    };

    const int ITERATIONS = 1000; // Run each query 1000 times for a stable average
    cout << fixed << setprecision(8); // Use more precision for fast query times

    // Loop over each test query
    for (int i = 0; i < testQueries.size(); ++i) {
        vector<string> query = testQueries[i];

        // Print which query we're testing
        cout << "\nQuery (" << query.size() << " ingredients): [";
        for (size_t j = 0; j < query.size(); ++j) cout << query[j] << (j == query.size() - 1 ? "" : ", ");
        cout << "]" << endl;

        // Time HashMap Query
        auto startMapQuery = chrono::high_resolution_clock::now();
        for (int k = 0; k < ITERATIONS; ++k) {
            mapIndex->findRecipes(query); // Run the search
        }
        auto endMapQuery = chrono::high_resolution_clock::now();
        // Calculate the average time per search
        double mapQueryTime = chrono::duration<double>(endMapQuery - startMapQuery).count() / ITERATIONS;
        cout << "HashMap Avg. Query: " << mapQueryTime << " seconds." << endl;

        // Time Trie Query
        auto startTrieQuery = chrono::high_resolution_clock::now();
        for (int k = 0; k < ITERATIONS; ++k) {
            trieIndex->findRecipes(query); // Run the search
        }
        auto endTrieQuery = chrono::high_resolution_clock::now();
        // Calculate the average time per search
        double trieQueryTime = chrono::duration<double>(endTrieQuery - startTrieQuery).count() / ITERATIONS;
        cout << "Trie Avg. Query:    " << trieQueryTime << " seconds." << endl;
    }

    // Note on memory usage
    cout << "\n--- Memory Usage ---" << endl;
    cout << "Note: To check memory, please use an external tool like 'top' (Linux/Mac) or Task Manager (Windows) while the program is running." << endl;
    cout << "----------------------------------------" << endl;

    // Clean up memory from the benchmark
    delete mapIndex;
    delete trieIndex;
}

// Main entry point for the MealCraft application
int main() {
    cout << "Welcome to MealCraft!" << endl;
    cout << "Loading recipe dataset..." << endl;
    
    RecipeLoader loader;
    
    // Define the path to the CSV file
    string csvPath = "../data/RecipeNLG_dataset.csv";
    vector<Recipe> allRecipes = loader.loadRecipes(csvPath);

    // Fail if the dataset isn't found
    if (allRecipes.empty()) {
        cerr << "\nFATAL ERROR: Could not load '" << csvPath << "'." << endl;
        cerr << "Please make sure it is downloaded to the 'data/' folder as per data/README.md." << endl;
        return 1; // Exit with an error code
    }

    cout << "Building search indexes..." << endl;

    // Creates both indexes at the start so the user can swap
    invertedIndex* mapIndex = new HashMap();
    mapIndex->buildIndex(allRecipes); // Build the map

    invertedIndex* trieIndex = new trie();
    trieIndex->buildIndex(allRecipes); // Build the trie
    
    cout << "All systems ready!" << endl;

    // Main Menu Loop
    while (true) {
        cout << "\n========== Main Menu ==========" << endl;
        cout << "1. Find Recipes (using Hash Map)" << endl;
        cout << "2. Find Recipes (using Trie)" << endl;
        cout << "3. Run Performance Benchmarks" << endl;
        cout << "4. Exit" << endl;
        
        // Get a safe choice from the user
        int choice = getMenuChoice(1, 4);
        
        // Run the UI using the HashMap index
        if (choice == 1) {
            runRecipeFinder(mapIndex, allRecipes);
        }
        // Run the UI using the Trie index
        else if (choice == 2) {
            runRecipeFinder(trieIndex, allRecipes);
        }
        // Run the benchmark tests
        else if (choice == 3) {
            runBenchmarks(csvPath);
        }
        // Exit the program
        else if (choice == 4) {
            cout << "\nThank you for using MealCraft! Goodbye." << endl;
            break; // Exit the main menu loop
        }
    }

    // Clean up memory
    delete mapIndex;
    delete trieIndex;

    return 0; // Success
}