<p align="center">
  <img width="980" height="130" alt="text-1761200277051" src="https://github.com/user-attachments/assets/ded77e8a-728f-4f19-8d62-00afbcd670f1" />
</p>
&nbsp;
<p align="center">
  <img width="714" height="74" alt="text-1761200475055" src="https://github.com/user-attachments/assets/b9adf012-e13d-4531-a4b3-cff2d70beb3d" />
</p>

<hr>

Team Name: The Meal Crafters  
Team Members: Johan Diaz, Nathaniel Flores, Patrick Ouano

Problem: Deciding what to cook every day is a common challenge. People often forget what ingredients they have at home, leading to food waste, or they fall into a routine of          eating the same few meals. Planning meals for a week and generating a shopping list is a manual and time-consuming process.

Motivation: This problem leads to food waste, which is both costly and environmentally harmful. It also contributes to less healthy eating habits, as people default to                   ordering takeout when they can't decide what to cook. A smart tool can make home cooking easier and more efficient.

Features: We will know we have solved the problem when our application successfully:  
            - Allows a user to input a list of available ingredients with a filter for allergies.  
            - Processes this input against the dataset.  
            - Returns a list of all recipes that can be made with the given ingredients.  
            - Allows the user to select a recipe from the list and view its full details (name, required ingredients, and instructions).  
            - Analyze the performance of our two chosen data structures.  
    
Data: This project’s data will use a public data set.  
            - Public Data Set: RecipeNLG  
            - Datatypes/Columns: Recipe # (int), Recipe Title (string), Ingredients with quantity (string), Directions (string), Recipe Link (string), Source (string),                     Ingredients without quantities for parsing aka NER (string)  

Tools:  
    - Programming Languages: C++  
    - Backend: fstream, sstream, data structures (vector/map std libraries)  
    - Frontend/Visuals: command line interface or SFML  
    - Version Control: Git/GitHub  
    
Strategy: Our core strategy is to implement and compare two different versions of an Inverted Index data structure to map ingredients to recipes.  
            - Data Representation: We will create a Recipe class in C++ to hold the parsed data (title, ingredients, directions).  
            - Implementation 1: Hash Map-based Inverted Index: We will implement a class that uses an unordered_map of strings and a vector of integers. The key will be the                ingredient name, and the value will be a vector of integer indices corresponding to recipes in our master vector.  
            - Implementation 2: Trie-based Inverted Index: We will design and implement a Trie data structure from scratch. Each node in the Trie will represent a character.               A node marking the end of a valid ingredient name will store a vector of integers of recipe indices.  
            - Comparison: We will write a benchmarking program that measures time and space complexity of both data structures.  

Distribution of Responsibility:  
    - Johan Diaz (Trie Implementation): Responsible for designing and implementing the Trie class from scratch, including node structures, insertion logic, and the recipe                                            query function.  
    - Nathaniel Flores (Hash Map Implementation): Responsible for designing and implementing the HashMap class, including the functions to build the index and to query for                                                     recipes.  
    - Patrick Ouano (Data & Core Logic): Responsible for writing the CSV parser to read the dataset and populate the main recipe objects. Will also set up the main program                                            loop and user interface logic.  
    - Team Responsibilities: All three members will collaborate on the benchmarking/testing framework, debugging, and the final analysis and video presentation.  
