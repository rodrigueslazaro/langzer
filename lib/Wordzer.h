#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "rapidjson/document.h"
using namespace std;

struct pieces {
    string singlecon;
    string doublecon;
    string triplecon;
    string singlevow;
    string doublevow;
    string triplevow;
    string begginings;
    string endings;
};

class Wordzer {
public:
    Wordzer(){};
    void makeLang(string file);
    void genWords(int num = 10, int size=5);
private:
    rapidjson::Document wordsdb;
    string langname;
    vector<struct pieces> wordspieces;
    bool isvowel(string letter);
    bool isconso(string letter);
};