#include "dictionary.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

Dictionary::Dictionary() {}

Dictionary::~Dictionary() {}

void Dictionary::generateDic(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (getline(file, line)) {
        istringstream iss(line);
        CityEntry entry;
        if (iss >> entry.cityName >> entry.latitude >> entry.longitude >> entry.country) {
            updateDic(entry);
        }
    }

    file.close();
}

void Dictionary::saveDic(const std::string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open file for saving: " << filename << std::endl;
        return;
    }

    binaryTree<string, CityEntry>::Node* root = Dictionary.getroot();
    saveDic(file, root);

    file.close();
}

void Dictionary::saveDic(std::ofstream& file, binaryTree<std::string, CityEntry>::Node* node) {
    if (node) {
        saveDictionaryToTextFileHelper(file, node->left);
        file << node->data.cityName << " " << node->data.latitude << " " << node->data.longitude << " " << node->data.country << "\n";
        saveDictionaryToTextFileHelper(file, node->right);
    }
}

void Dictionary::downloadDic(const std::string& filename) {
    binaryTree<string, CityEntry> newDictionary;

    std::ifstream file(filename);
    if (!file.open()) {
        cerr << "Failed to open file for downloading: " << filename << std::endl;
        return;
    }

    std::string line;
    while (getline(file, line)) {
        istringstream iss(line);
        CityEntry entry;
        if (iss >> entry.cityName >> entry.latitude >> entry.longitude >> entry.country) {
            newDictionary.insert(entry.cityName, entry);
        }
    }

    Dictionary = newDictionary;

    file.close();
}

void Dictionary::updateDictionary(const CityEntry& city) {
    Dictionary.insert(city.cityName, city);
}

bool Dictionary::searchCity(const std::string& cityName, CityEntry& result) {
    return Dictionary.retrieve(cityName, result);
}

void Dictionary::list() {
    Dictionary.traverse();
}