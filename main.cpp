#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Token.h"
#include "Scanner.h"
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

//    cout << fileName << endl;
//    cout << fileInput << endl;
//    cout << fileName << endl;

    Scanner s = Scanner(fileInput);
    s.scanInput();


}
//    Scanner s = Scanner(fileInput);
//    Token t = s.scanToken();
//    Token t2 = s.scanToken();
//    cout << t.toString() << endl;
//    cout << t2.toString() << endl;

//    string filename = argv[1];
//    ifstream in;
//    in.open(filename);
//    -------------------
//    ifstream in;
//    in.open("input.txt");
//    stringstream ss;
//    ss << in.rdbuf();
//    string input = ss.str();
//    in.close();
//    cout << input;