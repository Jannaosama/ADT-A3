#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "binaryTree.h"
#include <string>
using namespace std;

struct CityEntry {
    string cityName;
    double latitude;
    double longitude;
    string country;
};

class Dictionary {
public:
    Dictionary();
    ~Dictionary();

    void generateDic(const string& filename);
    void saveDic(const string& filename);
    void downloadDic(const string& filename);
    void updateDic(const CityEntry& city);
    bool searchCity(const string& cityName, CityEntry& result);
    void list();
};

#endif