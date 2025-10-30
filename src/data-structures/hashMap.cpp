//Hash map-based Inverted Index data structure, using polymorphism
int hashMap::hashFunction(string& key) {
    size_t hash = 0;
    for (char c: hash) {
        hash = (hash*31 + c) % capacity;
    }
    return static_cast<int>(hash);
}

void hashMap::resize() {
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

void hashMap::insert(string& key, int value) {
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

vector<int> hashMap::find(string& key) {
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

void hashMap::buildINdex(vecotr<Recipe>& recipes) {
    cout << "Buidling Map Index..." << endl;

    for (auto& recipe: recipes) {
        for (string& ingredient: recipe.getIngredients()) {
            insert(ingredient)
        } 
    }
}