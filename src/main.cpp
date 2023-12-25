#include "Wordzer.h"
#include <iostream>

int main() {
    Wordzer* wordzerpt = new Wordzer();
    cout << "---=== PORTUGUESE ===---" << endl;
    wordzerpt->makeLang("portuguese");
    wordzerpt->genWords(100, "castalese");
    // Wordzer* wordzeren = new Wordzer();
    // cout << "---=== ENGLISH ===---" << endl;
    // wordzeren->makeLang("english");
    // wordzeren->genWords();
    // Wordzer* wordzerrs = new Wordzer();
    // cout << "---=== RUSSIAN ===---" << endl;
    // wordzerrs->makeLang("russian");
    // wordzerrs->genWords();
    // Wordzer* wordzerjp = new Wordzer();
    // cout << "---=== JAPANESE ===---" << endl;
    // wordzerjp->makeLang("japanese");
    // wordzerjp->genWords();
    return 0;
}