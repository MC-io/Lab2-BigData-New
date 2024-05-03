#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cstring>
using namespace std;

// Custom allocator for const char* keys
struct CharPtrAllocator {
    char* allocate(size_t n) const {
        return new char[n];
    }

    void deallocate(char* p, size_t) const noexcept {
        delete[] p;
    }
};

// Custom hash function for const char* keys
struct CharPtrHash {
    size_t operator()(const char* str) const {
        size_t hash = 5381;
        int c;
        while ((c = *str++))
            hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
        return hash;
    }
};

// Custom equality function for const char* keys
struct CharPtrEqual {
    bool operator()(const char* a, const char* b) const {
        return strcmp(a, b) == 0;
    }
};

// Define unordered map type with const char* keys
using InvertedIndex = unordered_map<const char*, unordered_set<int>, CharPtrHash, CharPtrEqual, CharPtrAllocator>;

InvertedIndex build_inverted_index(const vector<string>& files)
{
    InvertedIndex invertedIndex;

    const int size = files.size();
    for (int i = 0; i < size; i++) {
        ifstream inFile(files[i]);
        if (!inFile.is_open()) {
            cerr << "Failed to open file: " << files[i] << endl;
            continue;
        }

        string word;
        while (inFile >> word) {
            char* key = new char[word.length() + 1];
            strcpy(key, word.c_str());
            invertedIndex[key].insert(i + 1);
        }

        inFile.close();
        cout << "Archivo " << to_string(i + 1) << " procesado exitosamente\n";
    }

    return invertedIndex;
}

// Function to search the inverted index
void search(const InvertedIndex& invertedIndex, const string& query) {
    const char* key = query.c_str();

    auto it = invertedIndex.find(key);
    if (it != invertedIndex.end()) {
        cout << "Documentos que contienen \"" << query << "\":" << endl;
        for (const auto& doc : it->second) {
            cout << " - " << doc << endl;
        }
    } else {
        cout << "Ningun documento tiene la palabra \"" << query << "\"" << endl;
    }
}

int main() {
    vector<string> files;
    for (int i = 0; i < 10; i++)
    {
        files.push_back("zdoc" + to_string(i + 1) + ".txt");
    }
    std::clock_t start = std::clock();
    InvertedIndex invertedIndex = build_inverted_index(files);
    std::clock_t end = std::clock();
    std::cout << "Word count completed in " << (end - start) / (double)CLOCKS_PER_SEC << " seconds\n";
    string query;
    cout << "Enter a word to search for in the documents: ";
    while (cin >> query)
    {
        search(invertedIndex, query);
    }

    return 0;
}