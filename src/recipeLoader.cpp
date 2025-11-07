//Loads all recipes from dataset
#include "recipeLoader.h"
#include <fstream> 
#include <sstream> 
#include <iostream>

using namespace std;

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
        // cleans up item string by getting rid of quotes 
        size_t first = item.find_first_of('\'');
        size_t last = item.find_last_of('\'');
        
        // if both quotes are found, the text between the quotes are fixed and returned as a vector
        if(first != string::npos && last != string::npos && first != last){
            string fixedItem = item.substr(first + 1, last - first - 1);
            items.push_back(fixedItem);
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

    getline(file, line);

    // handles main loop and reads from file and stores in line string
    while(getline(file, line)){
        stringstream ss(line);
        string word;

        vector<string> row;

        // handles commas inside the quotes by using stringstream
        while(getline(ss, word, ',')){
            if (!word.empty() && word.front() == '"' && word.back() != '"') {
                
                string nextWord;
                // adds the next parts until we find closing quote
                while (getline(ss, nextWord, ',')) {
                    word = word + "," + nextWord; 
                    if (!nextWord.empty() && nextWord.back() == '"') {
                        break; 
                    }
                }
            }

            // removes the surrounding quotes
            if (!word.empty() && word.front() == '"' && word.back() == '"') {
                word = word.substr(1, word.length() - 2);
            }
            
            row.push_back(word);
        }
// try and catch block to help prevent program from crashing
// converts all data from row vector 
try {
            int recipeNum = stoi(row[0]);
            
            string title = row[1];

            vector<string> ingredientsExact = parseStringList(row[2]);
            vector<string> instructions = parseStringList(row[3]);
            
            string link = row[4];
            string source = row[5];
        
            vector<string> ingredients = parseStringList(row[6]);

            // pushes recipes back to main vector 
            allRecipes.emplace_back(recipeNum, title, ingredientsExact, instructions, link, source, ingredients);

        } catch (const std::exception& e) {
            // if try block failed, prints an error
            cerr << "Error parsing line, skipping: " << line << endl;
        }
    }

    file.close(); 
    
    cout << "Successfully loaded " << allRecipes.size() << " recipes." << endl;
    return allRecipes; 
}