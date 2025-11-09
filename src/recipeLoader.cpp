//Loads all recipes from dataset
#include "recipeLoader.h"
#include <fstream> 
#include <sstream> 
#include <iostream>
#include <algorithm>
using namespace std;

// Parses a string that is a list of quoted items (e.g., ["item1", "item2"])
// This handles commas inside the quotes
vector<string> RecipeLoader::parseList(const string& stringList) {
    vector<string> items;
    // Return empty if the string is too short to be a list
    if (stringList.length() < 3) {
        return items;
    }

    // Gets rid of the opening and closing bracket []
    string content = stringList.substr(1, stringList.length() - 2);
    
    stringstream ss(content);
    char c;
    string current_item;
    bool in_quotes = false; // Tracks if we are inside a quoted item

    // Read the string character by character
    while (ss.get(c)) {
        if (c == '"') {
            // Check for an escaped quote (e.g., "")
            if (in_quotes && ss.peek() == '"') {
                current_item += '"'; // Add a single quote
                ss.get(); // Consume the peeked quote
            } else {
                // This is a real quote, toggle the state
                in_quotes = !in_quotes;
                if (!in_quotes) {
                    // Just finished a quoted item, add it
                    items.push_back(current_item);
                    current_item.clear(); // Clear for the next item
                }
            }
        // Only add characters if we are inside quotes
        } else if (in_quotes) {
            current_item += c;
        }
    }
    return items;
}

// loads all recipes from the csv file
vector<Recipe> RecipeLoader::loadRecipes(const string& csvPath){
    vector<Recipe> allRecipes;
    ifstream file(csvPath);

    if(!file.is_open()){
        cerr << "Error: Could not open file: " << csvPath << endl;
        return allRecipes;
    }

    // COUNT LINES (excluding header)
    int totalLines = 0;
    string tempLine;
    getline(file, tempLine); // discard header
    while(getline(file, tempLine)) {
        totalLines++;
    } 
    file.clear();
    file.seekg(0);
    
    string line;
    getline(file, line); // discard header again
    int recipeCount = 0;

    int progress25 = 250000;
    int progress50 = 500000;
    int progress75 = 750000;

    bool isPrinted25 = false;
    bool isPrinted50 = false;
    bool isPrinted75 = false;
    while(getline(file, line)){
        stringstream ss(line);
        vector<string> row;
        string cell;
        bool in_quotes = false;
        char c;

        while (ss.get(c)) {
            if (c == '"') {
                if (in_quotes && ss.peek() == '"') {
                    cell += '"';
                    ss.get();
                } else {
                    in_quotes = !in_quotes;
                }
            } else if (c == ',' && !in_quotes) {
                row.push_back(cell);
                cell.clear();
            } else {
                cell += c;
            }
        }
        row.push_back(cell);

        try {
            int recipeNum = stoi(row[0]);
            string title = row[1];
            vector<string> ingredientsExact = parseList(row[2]);
            vector<string> instructions = parseList(row[3]);
            string link = row[4];
            string source = row[5];
            vector<string> ingredients = parseList(row[6]);

            allRecipes.emplace_back(recipeNum, title, ingredientsExact, instructions, link, source, ingredients);

            recipeCount++;

            // Display progress at intervals
            if (recipeCount >= progress25 && !isPrinted25) {
                cout << "[===.............] 25% loaded" << endl;
                cout << "A quarter there!" << endl;
                isPrinted25 = true;
            }
            if (recipeCount >= progress50 && !isPrinted50) {
                cout << "[=======........] 50% loaded" << endl;
                cout << "Halfway there!!" << endl;
                isPrinted50 = true;
            }
            if (recipeCount >= progress75 && !isPrinted75) {
                cout << "[==========....] 75% loaded" << endl;
                cout << "Almost there!!!" << endl;
                isPrinted75 = true;
            }

            // Limit recipes to 1 million for testing
            if (recipeCount >= 1000000){
                break;
            }

        } catch (const std::exception& e) {
            cerr << "Error parsing line, skipping: " << line << endl;
        }
    }

    file.close();
    cout << "[==============] 100% loaded\n";
    cout << "Successfully loaded " << allRecipes.size() << " recipes." << endl;
    return allRecipes;
}
