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
    Relation select(int index, const string& value) const {
        Relation result(name, scheme);
        for (auto& it : tuples) {
            if (it.at(index) == value) {
                result.addTuple(it);
            }
        }
        return result;
    }
};

string Relation::toString() {
    stringstream out;
    for (auto& tuple : tuples) {
        out << tuple.toString(scheme) << endl;
    }
    return out.str();
}

#endif //DATALOGPROJECT_RELATION_H
