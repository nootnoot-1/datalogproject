#ifndef DATALOGPROJECT_DATABASE_H
#define DATALOGPROJECT_DATABASE_H
#include "Relation.h"
#include "Tuple.h"
#include "Scheme.h"
#include <map>
#include <string>
#include <vector>
#include <iostream>

class Database {
private:
    map<string, Relation> relations;
public:
    Database() = default;
    void addRelation(Relation relation){
        relations.insert(pair<string, Relation> (relation.getName(), relation));
        //std::cout << "Relation Name: " << relation.getName() << std::endl;
    }
    void addTuple(string relName, Tuple tuple) {
        relations.at(relName).addTuple(tuple);
    }
    Relation getRelation(string relName) {
        return relations.at(relName);
    }
    void changeRelation(Relation r, string value) {
        relations.at(value) = r;
    }
    bool doesmatch(Relation r, string value){
        if (r.tuSize() > relations.at(value).tuSize()) {
            return false;
        }
        return true;
    }

};

#endif //DATALOGPROJECT_DATABASE_H
