#include "Wordzer.h"
#include <iostream>
#include <fstream>
#include <random>

void Wordzer::makeLang(string lang) {
    langname = lang;
    /* read the file with rapidjson */
    ifstream wordsfile("data/languages.json");
    if (wordsfile.is_open()) {
        string jsonData;
        string line;
        while (getline(wordsfile, line))
            jsonData += line + "\n";
        wordsdb.Parse(jsonData.c_str());
        if (wordsdb.HasParseError())
            cerr << "Error parsing JSON." << endl;
        if (!wordsdb.IsArray())
            cerr << "JSON is not an array." << endl;
    } else
        cerr << "Species file does not exist!" << endl;
    /* find firsts and follows */
    string word;
    for (rapidjson::SizeType j=0; j<wordsdb.Size(); j++) {
        if (wordsdb[j]["language"].GetString() == lang) {
            // Access the "letters" array
            string consonants = wordsdb[j]["consonants"].GetString();
            string vowels = wordsdb[j]["vowels"].GetString();

            // Loop through each letter
            for (auto con : consonants) {
                struct possible_follows newpf;
                newpf.from = con;
                sequences.push_back(newpf); // Ensure the letter exists as a key in the map
            }
            for (auto vow : vowels) {
                struct possible_follows newpf;
                newpf.from = vow;
                sequences.push_back(newpf); // Ensure the letter exists as a key in the map
            }
            // Access the "words" array
            const rapidjson::Value& wordsArray = wordsdb[j]["words"];

            // Loop through each word and add to corresponding letter's vector
            bool isnew = true;
            for (rapidjson::SizeType i = 0; i < wordsArray.Size(); ++i) {
                string word = wordsArray[i].GetString();
                int wsize = word.size();
                for (int c=0; c<wsize; c++) {
                    string index_letter = word.substr(c,1);
                    string follow = word.substr(c+1,1);
                    isnew = true; 
                    for (auto s : sequences)
                        if (s.from == index_letter and (s.tovow.find(follow) != string::npos
                                                   or s.tocon.find(follow) != string::npos))
                            isnew = false;
                    if (isnew) {
                        for (auto& s : sequences) {
                            if (s.from == index_letter) {
                                if (vowels.find(follow) != string::npos)
                                    s.tovow += follow;
                                else
                                    s.tocon += follow;
                            }
                        }
                    }
                }
            }
        }
    }

    for (auto s : sequences) {
        cout << s.from << ": ( ";
        for (auto l : s.tovow) {
            cout << l << " ";
        }
        cout << ") [ ";
        for (auto l : s.tocon) {
            cout << l << " ";
        }
        cout << " ]" << endl;
    }
}

bool Wordzer::isvowel(string letter) {
    for (rapidjson::SizeType j=0; j<wordsdb.Size(); j++) {
        if (wordsdb[j]["language"].GetString() == langname) {
            string vowels = wordsdb[j]["vowels"].GetString();
            if (vowels.find(letter) != string::npos)
                return true;
        }
    }
    return false;
}

bool Wordzer::isconso(string letter) {
    for (rapidjson::SizeType j=0; j<wordsdb.Size(); j++) {
        if (wordsdb[j]["language"].GetString() == langname) {
            string consonants = wordsdb[j]["consonants"].GetString();
            if (consonants.find(letter) != string::npos)
                return true;
        }
    }
    return false;
}

void Wordzer::genWords(int num, int size) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> randchar(0, sequences.size()-1);
    string newword = "";
    string keyletter = "";
    for (int i=0; i<num; i++) {
        for (int j=0; j<size; j++) {
            keyletter = sequences[randchar(gen)].from;
            for (auto s : sequences) {
                if (s.from == keyletter) {

                }
            }
        }
        cout << "new word: " << newword << endl;
        newword = "";
    }
}