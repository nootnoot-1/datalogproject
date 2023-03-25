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
};

Relation Interpreter::evaluateQuery(Predicate query) {
    map<string, int> map;
    vector<string> key;
    Relation r = database.getRelation(query.getName());
    vector<Parameter> qparams = query.getParameters();
    for (int i=0; i<qparams.size(); ++i) {
        if (qparams.at(i).isConstant()) {
            r.select1(i,qparams.at(i).toString());
        } else {
            if (key.empty()) {
                map.insert(pair<string,int> (qparams.at(i).toString(),i));
                key.push_back(qparams.at(i).toString());
            } else {
                if (map.at(qparams.at(i).toString())) {
                    r.select2(map.at(qparams.at(i).toString()),i);
                } else {
                    map.insert(pair<string,int> (qparams.at(i).toString(),i));
                    key.push_back(qparams.at(i).toString());
                }
            }
        }
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
        std::cout << database.getRelation(facts.at(i).getName()).toString() << std::endl;
    }
}

#endif //DATALOGPROJECT_INTERPRETER_H
