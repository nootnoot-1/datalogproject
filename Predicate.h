#ifndef DATALOGPROJECT_PREDICATE_H
#define DATALOGPROJECT_PREDICATE_H
#include <string>
#include <sstream>
#include <vector>
#include "Parameter.h"

class Predicate {
private:
    string name;
    vector<Parameter> parameters;

public:
    Predicate(string name) : name(name) {}

    Predicate() {}

    string toString() const;
    void addParameter(string value);
    string getName() const;
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
    out << ")";
    return out.str();
}

void Predicate::addParameter(string value) {
    parameters.push_back(Parameter(value));
}

string Predicate::getName() const {
    return name;
}



#endif //DATALOGPROJECT_PREDICATE_H
