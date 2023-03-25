#ifndef DATALOGPROJECT_RELATION_H
#define DATALOGPROJECT_RELATION_H
#include <set>
#include <sstream>
#include "Scheme.h"
#include "Tuple.h"

class Relation {
private:
    string name;
    Scheme scheme;
    set<Tuple> tuples;
public:
    Relation(const string& name, const Scheme& scheme) : name(name), scheme(scheme) {}
    void addTuple(const Tuple& tuple) {
        tuples.insert(tuple);
    }
    string toString();
    string getName() {return name;}
    Relation select1(int index, const string& value) const;
    Relation select2(int index1, int index2) const;
    Relation project(vector<string> values, vector<int> indexes) const;
    Relation rename(int index, const string& newvalue) const;
};

string Relation::toString() {
    stringstream out;
    for (auto& tuple : tuples) {
        out << tuple.toString(scheme) << endl;
    }
    return out.str();
}
Relation Relation::select1(int index, const string& value) const {
    Relation result(name, scheme);
    for (auto& it : tuples) {
        if (it.at(index) == value) {
            result.addTuple(it);
        }
    }
    return result;
}

Relation Relation::select2(int index1, int index2) const {
    Relation result(name, scheme);
    for (auto& it : tuples) {
        if (it.at(index1) == it.at(index2)) {
            result.addTuple(it);
        }
    }
    return result;
}

Relation Relation::project(vector<string> values, vector<int> indexes) const {
    vector<string> newscheme;
    for (int i=0; i<values.size(); ++i) {
        newscheme.push_back(values.at(i));
    }
    Relation result(name, newscheme);
    for (auto it : tuples) {
        vector<string> newTuple;
        for (int j=0; j<indexes.size(); ++j) {
            newTuple.push_back(it.at(indexes.at(j)));
        }
        result.addTuple(newTuple);
    }
    return result;
}

Relation Relation::rename(int index, const string& newvalue) const {
    vector<string> newscheme = scheme;
    newscheme.at(index) = newvalue;
    Relation result(name, newscheme);
    return result;
}

#endif //DATALOGPROJECT_RELATION_H
