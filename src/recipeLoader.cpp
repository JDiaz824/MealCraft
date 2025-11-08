//Loads all recipes from dataset
#include "recipeLoader.h"
#include <fstream> 
#include <sstream> 
#include <iostream>
#include <algorithm>
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
        size_t first = item.find_first_of('"');
        size_t last = item.find_last_of('"');
        
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
    string record;

    // read and ignore header line
    if (!getline(file, line)) {
        cerr << "Error: Empty file or no header line." << endl;
        return allRecipes;
    }

    // main loop to read full records (which may span multiple lines)
    while (getline(file, line)) {
        record += line + "\n";

        // count quote chars to see if record is complete
        int quoteCount = count(record.begin(), record.end(), '"');

        if (quoteCount % 2 == 0) {
            // record has balanced quotes, process this line

            stringstream ss(record);
            string word;

            vector<string> row;

            // parse CSV fields, handling commas inside quotes
            while(getline(ss, word, ',')){
                if (!word.empty() && word.front() == '"' && word.back() != '"') {
                    string nextWord;
                    while (getline(ss, nextWord, ',')) {
                        word += "," + nextWord;
                        if (!nextWord.empty() && nextWord.back() == '"') {
                            break;
                        }
                    }
                }

                // remove surrounding quotes
                if (!word.empty() && word.front() == '"' && word.back() == '"') {
                    word = word.substr(1, word.length() - 2);
                }
                
                row.push_back(word);
            }

            // parse row entries safely
            try {
                if (row.size() >= 7) {
                    int recipeNum = stoi(row[0]);
                    string title = row[1];
                    vector<string> ingredientsExact = parseStringList(row[2]);
                    vector<string> instructions = parseStringList(row[3]);
                    string link = row[4];
                    string source = row[5];
                    vector<string> ingredients = parseStringList(row[6]);

                    allRecipes.emplace_back(recipeNum, title, ingredientsExact, instructions, link, source, ingredients);
                } else {
                    cerr << "Error: Malformed row (expected at least 7 fields), skipping: " << record << endl;
                }
            }
            catch (const std::exception& e) {
                cerr << "Error parsing line, skipping: " << record << endl;
            }
            
            record.clear();  // reset for next record
        }
        // if quotes not balanced, continue accumulating lines
    }

    file.close();
    
    cout << "Successfully loaded " << allRecipes.size() << " recipes." << endl;
    return allRecipes;
}
