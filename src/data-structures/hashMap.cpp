//Hash map-based Inverted Index data structure, using polymorphism
#include <unordered_set>

/**
 * Constructor with intialCap = 16
 */
HashMap::HashMap(int initialCap) : capacity(initialCap), size(0) {
    buckets = new Entry*[capacity];
    for (int i = 0l i < capacity; i++) {
        buckets[i] = nullptr;
    }
}

/**
 * Destructor
 */
HashMap::~HashMap() {
    for (int i = 0; i < capacity; i++) {
        Entry* current = buckets[i];
        while (current) {
            Entry* temp = current;
            current = current-next;
            delete temp;
        }
    }
    delete[] buckets;
}

/**
 * Calculates hash value
 */
int HashMap::hashFunction(string& key) {
    size_t hash = 0;
    for (char c: key) {
        hash = (hash*31 + c) % capacity;
    }
    return static_cast<int>(hash);
}

/**
 * Doubles capacity of bucket array for resizing
 */
void HashMap::resize() {
    int oldCapacity = capacity;
    capacity *= 2;
    Entry** newBuckets = new Entry*[capacity]();

    for (int i = 0; i < oldCapacity; i++) {
        Entry* current = buckets[i];
        while (current) {
            Entry* next = current->next;
            int newIndex = hashFunction(current->key);
            current->next = newBuckets[newIndex];
            newBuckets[newIndex] = current;
            current = next;
        }
    }

    delete[] buckets;
    buckets = newBuckets;
}

/**
 * Inserts a key-value pair into the hash map
 * Can trigger resize() if capacity exceeds load factor (0.75)
 */
void HashMap::insert(string& key, int value) {
    int index = hashFunction(key);
    Entry* current = buckets[index];

    while (current) {
        if (current->key == key) {
            current->ids.push_back(value);
            return;
        }
        current = current->next;
    }

    Entry* newEntry = new Entry(key, value);
    newEntry->next = buckets[index];
    buckets[index] = newEntry;
    ++size;

    if (size > capacity*0.75) {
        resize();
    }
}

/**
 * Retrieves list of recipe IDs based on key (ingredient)
 * Returns empty vector if ingredient is not found
 */
vector<int> HashMap::find(string& key) {
    int index = hashFunction(key);
    Entry* current = buckets[index];
    while (current) {
        if (current->key == key) {
            return current->ids;
        }
        current = current->next;
    }
    return {};
}

/**
 * Processes list of recipes to build HashMap<string, vector<int>>,
 * mapping each ingredient to all recipe IDs associated with it
 */
void HashMap::buildIndex(const vector<Recipe>& recipes) {
    cout << "Building Map Index..." << '\n';
    for (const auto& recipe: recipes) {
        for (const auto& ingredient: recipe.getIngredients()) {
            insert(ingredient, recipe.getRecipeNum());
        }
    }
    cout << "Hash Map Index Built!" << '\n';
}

/**
 * Given a list of ingredients, returns a vector of recipe IDs containing all ingredients
 */
vector<int> HashMap::findRecipes(const vector<string>& ingredients) {
    if (ingredients.empty()) {
        return {};
    }

    // get all recipe IDs of first ingredient and insert them into a set
    vector<int> intialRecipes = find(ingredients[0]);
    unordered_set<int> commonRecipes(intialRecipes.begin(), intialRecipes.end());

    // only get common reciep IDs
    for (int i = 1; i < ingredients.size(); i++) {
        vector<int> temp = find(ingredients[i]);
        unordered_set<int> currentRecipes(temp.begin(), temp.end());
        for (auto it = commonRecipes.begin(); it != commonRecipes.end();) {
            if (currentRecipes.find(*it) == currentRecipes.end()) {
                it = commonRecipes.erase(it);
            }
            else {
                ++it;
            }
        }
    }
    vector<int> recipeList(commonRecipes.begin(), commonRecipes.end());
    return recipeList;
}

/**
 * Returns index type
 */
string HashMap::getIndexType() const {
    return "Hash Map";
}