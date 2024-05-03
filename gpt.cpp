#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <cstring>

// Custom hash function for C-style strings
struct CharPtrHash {
    std::size_t operator()(const char* str) const {
        // Use a simple hash function for demonstration purposes
        std::size_t hash = 0;
        while (*str) {
            hash = (hash * 31) + (*str++);
        }
        return hash;
    }
};

// Custom equality function for C-style strings
struct CharPtrEqual {
    bool operator()(const char* a, const char* b) const {
        return std::strcmp(a, b) == 0;
    }
};

void add_fruits(std::unordered_map<const char*, std::unordered_set<int>, CharPtrHash, CharPtrEqual>& myMap)
{
    const char * fruit = "apple";
    myMap[fruit].insert(2);
    const char * other_pointer = "apple";
    std::string hola = "apple";
    char* key = (char *)malloc(hola.size() + 1);
    strcpy(key, hola.c_str());
    myMap[key].insert(5);
    fruit = "banana";

    myMap[fruit].insert(10);
    myMap["orange"].insert(7);
}

int main() {
    std::unordered_map<const char*, std::unordered_set<int>, CharPtrHash, CharPtrEqual> myMap;

    // Inserting values into the map
    add_fruits(myMap);

    // Accessing values in the map

    for (const auto& doc : myMap["apple"]) {
        std::cout << " - " << doc << std::endl;
    }
    /*
    std::cout << "Number of apples: " << myMap["apple"] << std::endl;
    std::cout << "Number of bananas: " << myMap["banana"] << std::endl;
    std::cout << "Number of oranges: " << myMap["orange"] << std::endl;

    // Modifying values in the map
    myMap["banana"] = 20;
    std::cout << "Updated number of bananas: " << myMap["banana"] << std::endl;
    */
    std::cout << myMap.size() << '\n';
/*
    // Checking if a key exists in the map
    if (myMap.find("grape") == myMap.end()) {
        std::cout << "Grape not found in the map" << std::endl;
    }
    */

    return 0;
}