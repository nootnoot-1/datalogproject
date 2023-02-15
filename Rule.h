#ifndef DATALOGPROJECT_RULE_H
#define DATALOGPROJECT_RULE_H
#include "Predicate.h"
#include <sstream>
#include <utility>
#include <vector>

class Rule {
private:
    Predicate headpredi;
    vector<Predicate> predicates;

public:
    explicit Rule(Predicate headpredi) : headpredi(std::move(headpredi)) {}
    Rule() = default;

    string toString() const;
    void addPredicate(const Predicate& predicate);
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

void Rule::addPredicate(const Predicate& predicate) {
    predicates.push_back(predicate);
}

void Rule::setheadpredi(Predicate predicate) {
    headpredi = std::move(predicate);
}

#endif //DATALOGPROJECT_RULE_H
