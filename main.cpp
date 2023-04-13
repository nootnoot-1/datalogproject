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


//    // predicate names for fake rules
//    // first is name for head predicate
//    // second is names for body predicates
//    pair<string,vector<string>> ruleNames[] = {
//            { "A", { "A"} },
//            { "B", { "B", "C" } },
//            { "C", {} },
//    };
//
//    vector<Rule> rules;
//
//    for (auto& rulePair : ruleNames) {
//        string headName = rulePair.first;
//        Rule rule = Rule(Predicate(headName));
//        vector<string> bodyNames = rulePair.second;
//        for (auto& bodyName : bodyNames)
//            rule.addPredicate(Predicate(bodyName));
//        rules.push_back(rule);
//    }
//
//
//
//    Graph graph = Interpreter::makeGraph(rules);
//    cout << "GRAPH: " << endl << graph.toString() << endl;
//    graph = graph.reverse();
//    cout << "REVERSE GRAPH: " << endl << graph.toString();
//    graph.dfsForest();

}
