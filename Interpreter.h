#ifndef DATALOGPROJECT_INTERPRETER_H
#define DATALOGPROJECT_INTERPRETER_H
#include "DatalogProgram.h"
#include "Database.h"

class Interpreter {
private:
    DatalogProgram datalogProgram;
    Database database;
    vector<Predicate> schemes = datalogProgram.getschemes();
    vector<Predicate> facts = datalogProgram.getfacts();
    vector<Predicate> queries = datalogProgram.getqueries();
    vector<Rule> rules = datalogProgram.getrules();
    bool isSpecific = true;
    int passes = 0;
    bool passagain = false;
public:
    Interpreter(DatalogProgram datalogProgram) : datalogProgram(datalogProgram) {}
    void loadDatabase();
    void evaluate();
    Relation evaluatePredicate(Predicate query);
    void evaluateRule(Rule rule);
    void evaluateAllR();
    void evaluateAllQ();
    void tester() {
        Relation r = database.getRelation(queries.at(0).getName());
        r = r.rename(0,"COLLIN");
        cout << r.toString();
    }
};

void Interpreter::evaluate() {
    loadDatabase();
    cout << "Rule Evaluation" << endl;
    do {passagain = false; evaluateAllR();} while(passagain);
    cout << endl << "Schemes populated after " << passes << " passes through the Rules." << endl;
    cout << endl << "Query Evaluation" << endl;
    evaluateAllQ();
}

void Interpreter::evaluateRule(Rule rule) {
    //evaluatePredicate
    //join
    //project
    //rename
    //union
    vector<Predicate> predicates = rule.getpredicates();
    vector<Relation> relations;
    for (const auto& it : predicates) {
        relations.push_back(evaluatePredicate(it));
    }
    while (relations.size() > 1) {
        relations.at(0) = relations.at(0).join(relations.at(1));
        relations.erase(relations.begin()+1);
    } //tested with ints in main
    Relation r = relations.at(0); // DECLARE RELATION EARLIER SO IT HAS THE CORRECT NAME AND SCHEME?
    r.setname(rule.getheadpredi().getName());
    vector<int> indexes;
    vector<string> headscheme = rule.getheadpredi().getStrings();
    vector<string> bodyscheme = r.getScheme();
    for (auto & i : headscheme) {
        for (long unsigned int j=0; j<bodyscheme.size(); ++j) {
            if (i == bodyscheme.at(j)) {
                indexes.push_back(j);
            }
        }
    }
    r = r.project(headscheme,indexes);

    vector<string> renamescheme;
    for (auto& it : schemes) {
        if (rule.getheadpredi().getName() == it.getName()) {
            renamescheme = it.getStrings();
        }
    }
//    for (int i=0; i<renamescheme.size(); ++i) {
//        cout << renamescheme.at(i) << " : " << r.getScheme().at(i) << endl;
//        r.rename(i,renamescheme.at(i));
//    }
    r.rename2(renamescheme);

    Relation dr = database.getRelation(r.getName());
    //cout << "\n\n dr after " << passes << " pass:\n" << dr.toString();
    dr.unionize(r);
    if (!database.doesmatch(dr, r.getName())) {
        database.changeRelation(dr,r.getName());
        passagain = true;
    }
}

void Interpreter::evaluateAllR() {
    for (auto & rule : rules) {
        cout << rule.toString() << endl;
        evaluateRule(rule);
    }
    ++passes;
}

void Interpreter::evaluateAllQ() {
    for (auto & query : queries) {
        Relation r = evaluatePredicate(query);
        cout << query.toString() << "? ";
        if (r.isempty()) {cout << "No" << endl; continue;}
        if (isSpecific) {
            cout << "Yes(" << r.tuSize() << ")" << endl;
        } else {
            cout << "Yes(" << r.tuSize() << ")" << endl;
            cout << r.toString();
        }
    }
}

Relation Interpreter::evaluatePredicate(Predicate query) {
    bool flag = true;
    isSpecific = true;
    vector<int> indexes;
    map<string, int> map;
    vector<string> key;
    Relation r = database.getRelation(query.getName());
    vector<Parameter> qparams = query.getParameters();
    for (long unsigned int i=0; i<qparams.size(); ++i) {
        flag = true;
        if (qparams.at(i).isConstant()) {
            r = r.select1(i,qparams.at(i).toString());
        } else { isSpecific = false;
            if (key.empty()) {
                map.insert(pair<string,int> (qparams.at(i).toString(),i));
                key.push_back(qparams.at(i).toString());
            } else {
                for (auto & j : key){
                    if (j == qparams.at(i).toString()) {
                        r = r.select2(map.at(qparams.at(i).toString()),i);
                        flag = false;
                    }
                }
                if (flag) {
                    map.insert(pair<string,int> (qparams.at(i).toString(),i));
                    key.push_back(qparams.at(i).toString());
                }
            }
        }
    }
    for (auto & i : key) {
        indexes.push_back(map.at(i));
    }
    r = r.project(key,indexes);

//    for (auto & i : key) {
//        r = r.rename(map.at(i), i);
//    }

//    cout << query.toString() << "? ";
//    if (r.isempty()) {cout << "No" << endl; return r;}
//    if (isSpecific) {
//        cout << "Yes(" << r.tuSize() << ")" << endl;
//    } else {
//        cout << "Yes(" << r.tuSize() << ")" << endl;
//        cout << r.toString();
//    }
    return r;
}

void Interpreter::loadDatabase() {
    for (long unsigned int i=0; i<schemes.size(); ++i) {
        database.addRelation(Relation(schemes.at(i).getName(), schemes.at(i).getStrings()));
        //std::cout << schemes.at(i).getSchemeStrings().at(0);
    }
    for (long unsigned int i=0; i<facts.size(); ++i) {
        for (long unsigned int j=0; j<schemes.size(); ++j) {
            if (facts.at(i).getName() == schemes.at(j).getName()) {
                database.addTuple(facts.at(i).getName(), facts.at(i).getStrings());
            }
        }
    }
    //std::cout << "FULL DATABASE FOR REL 0:\n" << database.getRelation(facts.at(0).getName()).toString() << std::endl;

}

#endif //DATALOGPROJECT_INTERPRETER_H
