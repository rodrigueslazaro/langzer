#include "Wordzer.h"
#include <iostream>

int main() {
    Wordzer* wordzerpt = new Wordzer();
    cout << "---=== PORTUGUESE ===---" << endl;
    wordzerpt->makeLang("portuguese");
    wordzerpt->genWords();
    Wordzer* wordzeren = new Wordzer();
    cout << "---=== ENGLISH ===---" << endl;
    wordzeren->makeLang("english");
    wordzeren->genWords();
    return 0;
}