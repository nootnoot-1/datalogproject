#ifndef DATALOGPROJECT_PREDICATE_H
#define DATALOGPROJECT_PREDICATE_H
#include <string>
#include <sstream>
#include <utility>
#include <vector>
#include "Parameter.h"

class Predicate {
private:
    string name;
    vector<Parameter> parameters;

public:
    explicit Predicate(string name) : name(std::move(name)) {}

    Predicate() = default;

    vector<string> getStrings(){
        vector<string> schemestring;
        for (auto & parameter : parameters) {
             schemestring.push_back(parameter.toString());
        }
        return schemestring;
    }
    string toString() const;
    void addParameter(const string& value);
    vector<Parameter> getParameters() const {
        return parameters;
    }
    string getName() const {
        return name;
    }
    int getparamsize() const {
        return parameters.size();
    }
};

string Predicate::toString() const {
    std::stringstream out;
    out << name << "(";
    for (long unsigned int i=0; i<parameters.size(); i++) {
        out << parameters.at(i).toString();
        if (i < parameters.size() - 1) {
            out << ",";
        }
    }
    out << ")";
    return out.str();
}

void Predicate::addParameter(const string& value) {
    parameters.emplace_back(value);
}



#endif //DATALOGPROJECT_PREDICATE_H
