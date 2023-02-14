#ifndef DATALOGPROJECT_RULE_H
#define DATALOGPROJECT_RULE_H
#include "Predicate.h"
#include <sstream>
#include <vector>

class Rule {
private:
    Predicate headpredi;
    vector<Predicate> predicates;

public:
    Rule(Predicate headpredi) : headpredi(headpredi) {}
    Rule() {}

    string toString() const;
    void addPredicate(Predicate predicate);
    void setheadpredi(Predicate predicate);
};

string Rule::toString() const {
    std::stringstream out;
    out << headpredi.toString() << " :- ";
    for (int i=0; i<predicates.size(); i++) {
        out << predicates.at(i).toString();
        if (i < predicates.size()-1) {
            out << ",";
        }
    }
    out << ".";
    return out.str();
}

void Rule::addPredicate(Predicate predicate) {
    predicates.push_back(predicate);
}

void Rule::setheadpredi(Predicate predicate) {
    headpredi = predicate;
}

#endif //DATALOGPROJECT_RULE_H
