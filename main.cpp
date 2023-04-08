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
#include "Interpreter.h"
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
    Parser p = Parser(s.gettokens());
    p.datalogProgram();

    Interpreter jiso = Interpreter(p.getDatalogProgram());
    jiso.evaluate();

//    Relation studentRelation("students", Scheme( {"ID", "Name", "Major"} ));
//
//    vector<string> studentValues[] = {
//            {"'42'", "'Ann'", "'CS'"},
//            {"'64'", "'Ned'", "'EE'"},
//    };
//
//    for (auto& value : studentValues) {
//        studentRelation.addTuple(Tuple(value));
//    }
//
//    Relation courseRelation("courses", Scheme( {"ID", "Course"} ));
//
//    vector<string> courseValues[] = {
//            {"'42'", "'CS 100'"},
//            {"'32'", "'CS 232'"},
//    };
//
//    for (auto& value : courseValues) {
//        courseRelation.addTuple(Tuple(value));
//    }
//
//    studentRelation.join(courseRelation);

//    vector<string> courseScheme {"ID","Course"};
//    vector<int> courseIndexes {0,2};
//    cout << studentRelation.project(courseScheme,courseIndexes).toString();


}
