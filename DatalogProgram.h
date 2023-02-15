#ifndef DATALOGPROJECT_DATALOGPROGRAM_H
#define DATALOGPROJECT_DATALOGPROGRAM_H
#include "Predicate.h"
#include "Rule.h"
#include "Parameter.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <set>

using namespace std;

class DatalogProgram {
private:
    vector<Predicate> schemes;
    vector<Predicate> facts;
    vector<Predicate> queries;
    vector<Rule> rules;
    set<string> Domain;
    vector<Parameter> tempDomain;

public:
    DatalogProgram() = default;

    void toString();
    void fillDomain();
    void addscheme(const Predicate& scheme);
    void addfact(const Predicate& fact);
    void addrule(const Rule& rule);
    void addquery(const Predicate& query);
};

void DatalogProgram::toString() {
    std::cout << "Success!" << std::endl;
    if (!schemes.empty()) {
        cout << "Schemes(" << schemes.size() << "):" << endl;
        for (auto & it : schemes) {
            cout << "  " << it.toString() << endl;
        }
    }
    if (!facts.empty()) {
        cout << "Facts(" << facts.size() << "):" << endl;
        for (auto & it : facts) {
            cout << "  " << it.toString() << endl;
        }
    }
    if (!rules.empty()) {
        cout << "Rules(" << rules.size() << "):" << endl;
        for (auto & it : rules) {
            cout << "  " << it.toString() << endl;
        }
    }
    if (!queries.empty()) {
        cout << "Queries(" << queries.size() << "):" << endl;
        for (auto & it : queries) {
            cout << "  " << it.toString() << endl;
        }
    }
    if (!Domain.empty()) {
        cout << "Domain(" << Domain.size() << "):" << endl;
        for (auto & it : Domain) {cout << "  " << it << endl;}
    }
}

void DatalogProgram::fillDomain() {
    for (auto & it : facts) {
        tempDomain = it.getParameters();
        for (auto & jt : tempDomain) {
            Domain.insert(jt.toString());
        }
    }
}

void DatalogProgram::addscheme(const Predicate& scheme) {
    schemes.push_back(scheme);
}

void DatalogProgram::addfact(const Predicate& fact) {
    facts.push_back(fact);
}

void DatalogProgram::addrule(const Rule& rule) {
    rules.push_back(rule);
}

void DatalogProgram::addquery(const Predicate& query) {
    queries.push_back(query);
}

#endif //DATALOGPROJECT_DATALOGPROGRAM_H
