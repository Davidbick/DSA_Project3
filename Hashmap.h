//
// Created by Vishal on 11/28/2024.
//
#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <functional>
#include <stdexcept>

using namespace std;

#ifndef DSA_PROJECT3_HASHMAP_H
#define DSA_PROJECT3_HASHMAP_H

struct Book {
    string title;
    string authors;
    string description;
    string category;
    string publisher;
    string priceStarting;
    string publishMonth;
    string publishYear;
};

struct HashEntry {
    string key;       // book title
    Book value;       // The associated book object
    bool isOccupied;  // Indicates if the entry is occupied

    HashEntry() : key(""), isOccupied(false) {}
    HashEntry(const string& k, const Book& v) : key(k), value(v), isOccupied(true) {}
};

class Hashmap {
private:
    vector<HashEntry> table;  // The hash table
    size_t tableSize;         // Current size of the hash table
    size_t count;             // Number of elements in the table

    // Custom hash function
    size_t hashFunction(const string& key) const {
        size_t hash = 0;
        for (char ch : key) {
            hash = (hash * 31 + ch) % tableSize;
        }
        return hash;
    }

    // Resize and rehash the table when load factor exceeds threshold
    void rehash() {
        vector<HashEntry> oldTable = table;
        tableSize *= 2;
        table = vector<HashEntry>(tableSize);
        count = 0;

        for (const auto& entry : oldTable) {
            if (entry.isOccupied) {
                insert(entry.key, entry.value);
            }
        }
    }

    float loadFactor() const {
        return static_cast<float>(count) / tableSize;
    }

public:
    // Constructor
    Hashmap(size_t size = 101) : tableSize(size), count(0) {
        table = vector<HashEntry>(tableSize);
    }

    // Insert a key-value pair
    void insert(const string& key, const Book& value) {
        if (loadFactor() > 0.7) {
            rehash();
        }

        size_t index = hashFunction(key);
        while (table[index].isOccupied) {
            if (table[index].key == key) {
                table[index].value = value;  // Update value if key exists
                return;
            }
            index = (index + 1) % tableSize;  // Linear probing
        }

        table[index] = HashEntry(key, value);
        count++;
    }

    // Retrieve a value by key
    Book get(const string& key) const {
        size_t index = hashFunction(key);
        size_t startIndex = index;

        while (table[index].isOccupied) {
            if (table[index].key == key) {
                return table[index].value;
            }
            index = (index + 1) % tableSize;
            if (index == startIndex) {
                break;  // Prevent infinite loop
            }
        }
        throw runtime_error("Key not found");
    }

    // Remove a key-value pair
    void remove(const string& key) {
        size_t index = hashFunction(key);
        size_t startIndex = index;

        while (table[index].isOccupied) {
            if (table[index].key == key) {
                table[index].isOccupied = false;
                count--;
                return;
            }
            index = (index + 1) % tableSize;
            if (index == startIndex) {
                break;  // Prevent infinite loop
            }
        }
        throw runtime_error("Key not found");
    }

    // Check if the hashmap contains a key
    bool contains(const string& key) const {
        size_t index = hashFunction(key);
        size_t startIndex = index;

        while (table[index].isOccupied) {
            if (table[index].key == key) {
                return true;
            }
            index = (index + 1) % tableSize;
            if (index == startIndex) {
                break;
            }
        }
        return false;
    }

    // Get the size of the hashmap
    size_t size() const {
        return count;
    }
};
#endif //DSA_PROJECT3_HASHMAP_H





