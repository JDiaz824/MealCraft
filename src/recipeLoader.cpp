//Loads all recipes from dataset
#include "recipeLoader.h"
#include <fstream> 
#include <sstream> 
#include <iostream>
#include <algorithm>
using namespace std;

vector<string> RecipeLoader::parseQuotedList(const string& stringList) {
    vector<string> items;
    if (stringList.length() < 3) {
        return items;
    }

    // Gets rid of the opening and closing bracket []
    string content = stringList.substr(1, stringList.length() - 2);
    
    stringstream ss(content);
    char c;
    string current_item;
    bool in_quotes = false;

    while (ss.get(c)) {
        if (c == '"') {
            if (in_quotes && ss.peek() == '"') {
                // This is an escaped quote ""
                current_item += '"';
                ss.get(); // Consume the peeked quote
            } else {
                // This is a real quote, toggle state
                in_quotes = !in_quotes;
                if (!in_quotes) {
                    // We just *finished* a quoted item
                    items.push_back(current_item);
                    current_item.clear();
                }
            }
        } else if (in_quotes) {
            current_item += c;
        }
    }
    return items;
}

// helper function to parse strings 
vector<string> RecipeLoader::parseStringList(const string& stringList){
    vector<string> items;

    // checks if string is too short 
    if(stringList.length() < 3){
        return items; 
    }

    // gets rid of the opening and closing bracket []
    string recipes = stringList.substr(1, stringList.length() - 2);

    // uses stringstream to split by commas
    stringstream ss(recipes);
    string item; 
    while(getline(ss, item, ',')){
        size_t first = item.find_first_of('"');
        size_t last = item.find_last_of('"');
        
        if(first != string::npos && last != string::npos && first != last){
            string fixedItem = item.substr(first + 1, last - first - 1);
            
            // --- ADD THIS FIX ---
            // This handles the case where fixedItem is ""brown sugar""
            // or any other item that is still wrapped in quotes
            if (!fixedItem.empty() && fixedItem.front() == '"' && fixedItem.back() == '"') {
                 fixedItem = fixedItem.substr(1, fixedItem.length() - 2);
            }
            // --- END FIX ---
            
            // Also, let's trim any leading/trailing spaces
            size_t start = fixedItem.find_first_not_of(" \t");
            size_t end = fixedItem.find_last_not_of(" \t");
            if (string::npos != start && string::npos != end) {
                 items.push_back(fixedItem.substr(start, end - start + 1));
            }
        }
    }
    return items;
}

// loads all recipes from the csv file
vector<Recipe> RecipeLoader::loadRecipes(const string& csvPath){
    vector<Recipe> allRecipes;
    ifstream file(csvPath);

    // checks if file is opened
    if(!file.is_open()){
        cerr << "Error: Could not open file: " << csvPath << endl;
        return allRecipes;
    }

    string line;
    string record;

    getline(file, line);

    int recipeCount = 0;

    // handles main loop and reads from file and stores in line string
    while(getline(file, line)){
        stringstream ss(line);
        string word;

            vector<string> row;

        // handles commas inside the quotes by using stringstream
        string cell;
    bool in_quotes = false;
    char c;

    while (ss.get(c)) {
        if (c == '"') {
            if (in_quotes && ss.peek() == '"') {
                // This is an escaped quote "" (e.g., in ""brown sugar"")
                cell += '"';
                ss.get(); // Consume the peeked quote
            } else {
                // This is a regular quote, toggle the state
                in_quotes = !in_quotes;
            }
        } else if (c == ',' && !in_quotes) {
            // End of a cell
            row.push_back(cell);
            cell.clear();
        } else {
            // Any other character
            cell += c;
        }
    }
    // Add the last cell to the row
    row.push_back(cell);
// try and catch block to help prevent program from crashing
// converts all data from row vector 
try {
            int recipeNum = stoi(row[0]);
            
            string title = row[1];

            vector<string> ingredientsExact = parseQuotedList(row[2]);
            vector<string> instructions = parseQuotedList(row[3]);
            
            string link = row[4];
            string source = row[5];
        
            vector<string> ingredients = parseStringList(row[6]);

            // pushes recipes back to main vector 
            allRecipes.emplace_back(recipeNum, title, ingredientsExact, instructions, link, source, ingredients);

            recipeCount++;

            if(recipeCount >= 100000){
                break;
            }

        } catch (const std::exception& e) {
            // if try block failed, prints an error
            cerr << "Error parsing line, skipping: " << line << endl;
        }
    }

    file.close();
    
    cout << "Successfully loaded " << allRecipes.size() << " recipes." << endl;
    return allRecipes;
}
