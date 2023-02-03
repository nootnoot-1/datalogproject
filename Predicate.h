#ifndef DATALOGPROJECT_PREDICATE_H
#define DATALOGPROJECT_PREDICATE_H
#include <string>
#include <sstream>
#include <vector>
#include "Parameter.h"

enum PredicateType {
    SCHEME,
    FACT,
    QUERY,
};

class Predicate {
private:
    PredicateType type;
    string name;
    vector<Parameter> parameters;

public:
    Predicate(PredicateType type, string name) : type(type), name(name) {}
    Predicate();

    string toString() const;
    void addParameter(string value);
};

string Predicate::toString() const {
    std::stringstream out;
    out << name << "(";
    for (int i=0; i<parameters.size(); i++) {
        out << parameters.at(i).toString();
        if (i < parameters.size() - 1) {
            out << ",";
        }
    }
    out << ")" << std::endl;
    return out.str();
}

void Predicate::addParameter(string value) {
    parameters.push_back(Parameter(value));
}


#endif //DATALOGPROJECT_PREDICATE_H
