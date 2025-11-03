//Hash map-based Inverted Index data structure, using polymorphism
HashMap::HashMap(int initialCap) : capacity(initialCap), size(0) {
    buckets = new Entry*[capacity];
    for (int i = 0l i < capacity; i++) {
        buckets[i] = nullptr;
    }
}

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

int HashMap::hashFunction(string& key) {
    size_t hash = 0;
    for (char c: key) {
        hash = (hash*31 + c) % capacity;
    }
    return static_cast<int>(hash);
}

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

void HashMap::buildIndex(const vector<Recipe>& recipes) {
    cout << "Building Map Index..." << '\n';
    for (const auto& recipe: recipes) {
        for (const auto& ingredient: recipe.getIngredients()) {
            insert(ingredient, recipe.getRecipeNum());
        }
    }
    cout << "Map Index Built!" << '\n';
}

vector<int> HashMap::findRecipes(const vector<)