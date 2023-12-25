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

            // Get all single consonant and vowel sounds in the language
            struct pieces newpieces;
            string scon;
            for (auto con : consonants) {
                scon = con;
                newpieces.cons.push_back(scon);
            }
            for (auto vow : vowels) {
                scon = vow;
                newpieces.vows.push_back(scon);
            }
            wordpc = newpieces;

            // Access the "words" array
            const rapidjson::Value& wordsArray = wordsdb[j]["words"];

            // Loop through each word and add to corresponding letter's vector
            for (rapidjson::SizeType i = 0; i < wordsArray.Size(); ++i) {
                string word = wordsArray[i].GetString();
                /* finds new consonant sequences in the word */
                findletseq("consonants", word);
                /* finds new vowel sequences in the word */
                findletseq("vowels", word);
                /* finds possible word endings */
                char newc  = word[word.size()-1];
                if (wordpc.end.find(newc) == string::npos)
                    wordpc.end += newc;
                /* finds possible word begginings */
                newc = word[0];
                if (wordpc.beg.find(newc) == string::npos)
                    wordpc.beg += newc;
            }
        }
    }

    // cout << "consonants" << endl;
    // for (auto c : wordpc.cons) {
    //     cout << c << " ";
    // }
    // cout << endl;
    // cout << "vowels" << endl;
    // for (auto c : wordpc.vows) {
    //     cout << c << " ";
    // }
    // cout << endl;
    // cout << "endings" << endl;
    // for (auto c : wordpc.end) {
    //     cout << c << " ";
    // }
    // cout << endl;
}

string Wordzer::checklet(string opt, string c, string word) {
    string follow = "";
    string seq = "";
    bool search = true;
    if (c.size() == 1) {
        size_t pos = word.find(c);
        if (pos != string::npos) {
            seq = c;
            for (long unsigned int i=pos+1; i<word.size() and search; i++) {
                follow = word[i];
                if (istype(opt, follow)) {
                    seq += follow;
                } else {
                    search = false;
                }
            }
            return seq;
        }
    }
    return "";
}

void Wordzer::findletseq(string opt, string word) {
    bool found = false;
    if (opt == "consonants") {
        for (auto c : wordpc.cons) {
            string seq = checklet(opt, c, word);
            if (seq.size() > 1) {
                found = false;
                for (auto c : wordpc.cons)
                    if (seq == c)
                        found = true;
                if (not found)
                    wordpc.cons.push_back(seq);
            }
        }
    } else if (opt == "vowels") {
        for (auto c : wordpc.vows) {
            string seq = checklet(opt, c, word);
            if (seq.size() > 1) {
                found = false;
                for (auto c : wordpc.vows)
                    if (seq == c)
                        found = true;
                if (not found)
                    wordpc.vows.push_back(seq);
            }
        }
    }
} 

bool Wordzer::istype(string opt, string letter) {
    for (rapidjson::SizeType j=0; j<wordsdb.Size(); j++) {
        if (wordsdb[j]["language"].GetString() == langname) {
            string vowels = wordsdb[j][opt.c_str()].GetString();
            if (vowels.find(letter) != string::npos)
                return true;
        }
    }
    return false;
}

void Wordzer::genWords(int num, string newlangname) {
    ofstream csvLangFile(langname+".csv");
    if (!csvLangFile.is_open()) {
        cerr << "Error opening file for writing." << endl;
    }
    csvLangFile << "language,1-len,2-len,3-len,4-len,5-len,6-len" << endl << langname << ",";
    random_device rd;
    mt19937 gen(rd());
    string newword = "";
    uniform_int_distribution<> randcon(0, wordpc.cons.size()-1);
    uniform_int_distribution<> randvow(0, wordpc.vows.size()-1);
    uniform_int_distribution<> randend(0, wordpc.end.size()-1);
    uniform_int_distribution<> randbeg(0, wordpc.beg.size()-1);
    uniform_int_distribution<> init(0, 1);
    int swap = 0;
    for (int size=1; size<6; size++) {
        for (int i=0; i<num; i++) {
            newword += wordpc.beg[randbeg(gen)];
            if (istype("consonants", newword))
                swap = 0;
            else 
                swap = 1;
            for (int j=0; j<size; j++) {
                if (swap == 0) {
                    newword += wordpc.vows[randvow(gen)];
                } else {
                    newword += wordpc.cons[randcon(gen)];
                }
                swap ^= 1;
            }
            newword += wordpc.end[randend(gen)];
            csvLangFile << newword + " ";
            newword = "";
        }
        csvLangFile << ",";
    }
}