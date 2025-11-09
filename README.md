<p align="center">
  <img width="980" height="130" alt="MealCraft Banner" src="https://github.com/user-attachments/assets/ded77e8a-728f-4f19-8d62-00afbcd670f1" />
</p>
&nbsp;
<p align="center">
  <img width="714" height="74" alt="Find Recipes By Ingredient" src="https://github.com/user-attachments/assets/b9adf012-e13d-4531-a4b3-cff2d70beb3d" />
</p>

## About The Project

**MealCraft** is a C++ recipe suggestion engine that finds recipes based on the ingredients you have on hand. It is designed to reduce food waste and make home cooking more efficient.

This project also serves as a technical comparison between two inverted index data structures, a custom **Hash Map** and a custom **Trie**, both built from scratch to map ingredients to recipes.

---

### Key Features
* **Ingredient-Based Search:** Find recipes using a list of available ingredients.
* **Data Structure Comparison:** Implements both a `HashMap` and `Trie` for performance analysis.
* **Recipe Details:** View full recipe details (ingredients, instructions) from search results.
---

## Built With

* **Core Language:** C++14
* **Build System:** CMake
* **Core Data Structures:**
    * Custom `HashMap` class
    * Custom `Trie` class
    * C++ Standard Library (vector, map, set)
* **Data Parsing:** `fstream` and `sstream` for CSV processing.

---

## Set Up

To get a local copy up and running, follow these steps.

### Prerequisites

You will need a C++ compiler (like g++ or clang) and CMake installed on your system.

* **CMake**
    ```
    # Example on macOS with Homebrew
    brew install cmake
    ```

### 1. Clone the Repo

   
    ```
    git clone https://github.com/your-username/MealCraft.git
    cd MealCraft
    ```


### 2. Build with CMake

We use an out-of-source build, which is standard practice for CMake projects.

In terminal:
    1. Create a build directory inside the project folder
    ```
    mkdir build
    ```
    2. Move into the build directory
    ```
    cd build
    ```
    3. Configure the project with CMake
    ```
    cmake ..
    ```
    4. Compile the project
    
    On Linux/macOS
    ```
    make
    ```
    On Windows (or cross-platform)
    ```
    cmake --build
    ```

This will create an executable named `MealCraft` inside the `build/` directory.

---

## Usage

Once built, you can run the application from the `build/` directory.
  ```
  PS C:\Users\..\MealCraft\build ./MealCraft.exe
  ```
The program will launch an interactive command-line interface. Based on the project goals, it will:

1.  Prompt you to choose the data structure to use (**Trie** or **Hash Map**).
2.  Build the recipe index from the `.csv` file (this may take a moment).
3.  Prompt you to enter ingredients.
4.  Display a list of recipes that can be made using *all* the ingredients you provided.
5.  Allow you to select a recipe by its ID to see the full instructions.

---

## Authors

* **Johan Diaz:** Trie Implementation
* **Nathaniel Flores:** Hash Map Implementation
* **Patrick Ouano:** Data & Core Logic
