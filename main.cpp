#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Token.h"
#include "Scanner.h"
#include "Parser.h"
using namespace std;

int main(int argc, char* argv[]) {

    // READS INPUT FILE AND STORES IN fileInput
    string fileName = argv[1];
    ifstream input(fileName);
    if (!input.is_open()) {
        cout << "File " << fileName << " could not be found or opened." << endl; return 1;
    }
    string fileInput;
    istreambuf_iterator<char> fileIt(input), emptyFileIt;
    back_insert_iterator<string> stringIn(fileInput);
    copy(fileIt, emptyFileIt, stringIn);

    Scanner s = Scanner(fileInput);
    s.scanInput();
    vector<Token> tokens;
    int limit = s.getTokensSize();
    for (int i=0; i<limit; i++){
        tokens.at(i) = s.getToken(i);
    }

    Parser p = Parser(tokens);

}
