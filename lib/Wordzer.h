#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "rapidjson/document.h"
using namespace std;

struct pieces {
    vector<string> cons;
    vector<string> vows;
    string beg;
    string end;
};

class Wordzer {
public:
    Wordzer(){};
    void makeLang(string file);
    void genWords(int num, string newlangname);
private:
    rapidjson::Document wordsdb;
    string langname;
    struct pieces wordpc;
    bool istype(string opt, string letter);
    void findletseq(string opt, string word);
    string checklet(string opt, string c, string word);
};