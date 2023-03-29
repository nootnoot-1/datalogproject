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
public:
    Interpreter(DatalogProgram datalogProgram) : datalogProgram(datalogProgram) {}
    void loadDatabase();
    Relation evaluateQuery(Predicate query);
    void evaluateAllQ();
    void tester() {
        Relation r = database.getRelation(queries.at(0).getName());
        r = r.rename(0,"COLLIN");
        cout << r.toString();
    }
};

void Interpreter::evaluateAllQ() {
    for (int i=0; i<queries.size(); ++i) {
        evaluateQuery(queries.at(i));
    }
}

Relation Interpreter::evaluateQuery(Predicate query) {
    bool flag = true;
    bool isSpecific = true;
    vector<int> indexes;
    map<string, int> map;
    vector<string> key;
    Relation r = database.getRelation(query.getName());
    vector<Parameter> qparams = query.getParameters();
    for (int i=0; i<qparams.size(); ++i) {
        if (qparams.at(i).isConstant()) {
            r = r.select1(i,qparams.at(i).toString());
        } else { isSpecific = false;
            if (key.empty()) {
                map.insert(pair<string,int> (qparams.at(i).toString(),i));
                key.push_back(qparams.at(i).toString());
            } else {
                for (int j=0; j<key.size(); ++j){
                    if (key.at(j) == qparams.at(i).toString()) {
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

    cout << query.toString() << "? ";
    if (r.isempty()) {cout << "No" << endl; return r;}
    if (isSpecific) {
        cout << "Yes(" << r.tuSize() << ")" << endl;
    } else {
        cout << "Yes(" << r.tuSize() << ")" << endl;
        cout << r.toString();
    }
    return r;
}

void Interpreter::loadDatabase() {
    for (int i=0; i<schemes.size(); ++i) {
        database.addRelation(Relation(schemes.at(i).getName(), schemes.at(i).getStrings()));
        //std::cout << schemes.at(i).getSchemeStrings().at(0);
    }
    for (int i=0; i<facts.size(); ++i) {
        for (int j=0; j<schemes.size(); ++j) {
            if (facts.at(i).getName() == schemes.at(j).getName()) {
                database.addTuple(facts.at(i).getName(), facts.at(i).getStrings());
            }
        }
    }
    //std::cout << "FULL DATABASE FOR REL 0:\n" << database.getRelation(facts.at(0).getName()).toString() << std::endl;

}

#endif //DATALOGPROJECT_INTERPRETER_H
