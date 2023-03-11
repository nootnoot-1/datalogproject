#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Token.h"
#include "Scanner.h"
#include "Parser.h"
#include "Scheme.h"
#include "Tuple.h"
#include "Relation.h"
using namespace std;

int main(int argc, char* argv[]) {

    // READS INPUT FILE AND STORES IN fileInput
//    string fileName = argv[1];
//    ifstream input(fileName);
//    if (!input.is_open()) {
//        cout << "File " << fileName << " could not be found or opened." << endl; return 1;
//    }
//    string fileInput;
//    istreambuf_iterator<char> fileIt(input), emptyFileIt;
//    back_insert_iterator<string> stringIn(fileInput);
//    copy(fileIt, emptyFileIt, stringIn);
//
//    Scanner s = Scanner(fileInput);
//    s.scanInput();
//    Parser p = Parser(s.gettokens());
//    p.datalogProgram();

    vector<string> names = { "ID", "Name", "Major" };

    Scheme scheme(names);

    Relation relation("student", scheme);

    vector<string> values[] = {
            {"'42'", "'Ann'", "'CS'"},
            {"'32'", "'Bob'", "'CS'"},
            {"'64'", "'Ned'", "'EE'"},
            {"'16'", "'Jim'", "'EE'"},
    };

    for (auto& value : values) {
        Tuple tuple(value);
        cout << tuple.toString(scheme) << endl;
        relation.addTuple(tuple);
    }

    cout << "relation:" << endl;
    cout << relation.toString();

    Relation result = relation.select(2, "'CS'");

    cout << "select Major='CS' result:" << endl;
    cout << result.toString();
}
