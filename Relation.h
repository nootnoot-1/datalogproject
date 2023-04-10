#ifndef DATALOGPROJECT_RELATION_H
#define DATALOGPROJECT_RELATION_H
#include <set>
#include <sstream>
#include <utility>
#include "Scheme.h"
#include "Tuple.h"

class Relation {
private:
    string name;
    Scheme scheme;
    set<Tuple> tuples;
public:
    Relation(string  name, Scheme  scheme) : name(std::move(name)), scheme(std::move(scheme)) {}
    void addTuple(const Tuple& tuple) {
        tuples.insert(tuple);
    }
    string toString();
    string getName() {return name;}
    Relation select1(int index, const string& value) const;
    Relation select2(int index1, int index2) const;
    Relation project(vector<string> values, vector<int> indexes) const;
    Relation rename(int index, const string& newvalue) const;
    bool isempty() {if(tuples.empty()){return true;} else {return false;}}
    unsigned int tuSize() {return tuples.size();}
    static bool joinable(const Scheme& leftScheme, const Scheme& rightScheme, const Tuple& leftTuple, const Tuple& rightTuple);
    Relation join(const Relation& right);
    Scheme joinSchemes(const Scheme& rightScheme);
    Scheme getScheme() {return scheme;}
    Tuple joinTuples(const Scheme& leftScheme, const Scheme& rightScheme, const Tuple& leftTuple, const Tuple& rightTuple);
    void unionize(const Relation& r);
    void setname(string value) {name = std::move(value);}
    void rename2(vector<string> newscheme) {scheme = std::move(newscheme);}
};

void Relation::unionize(const Relation& r) {
    for (const auto& it : r.tuples) {
        if(tuples.insert(it).second) {
            cout << "  " << it.toString(r.scheme) << endl;
        }
        tuples.insert(it);
    }
}

Relation Relation::join(const Relation& right){
    Scheme newscheme = joinSchemes(right.scheme);
    Relation r = Relation(name, newscheme);
//    for (const Tuple& leftTuple : tuples) {
//        cout << "left tuple: " << leftTuple.toString(scheme) << endl;
//        for (const Tuple& rightTuple : right.tuples) {
//            cout << "right tuple: " << rightTuple.toString(right.scheme) << endl;
//        }
//    }
    for (const Tuple& leftTuple : tuples) {
        for (const Tuple& rightTuple : right.tuples) {
            if (joinable(scheme,right.scheme,leftTuple,rightTuple)) {
                Tuple t = joinTuples(scheme,right.scheme,leftTuple,rightTuple);
                r.addTuple(t);
            }
        }
    }
    return r;
}

Tuple Relation::joinTuples(const Scheme& leftScheme, const Scheme& rightScheme, const Tuple& leftTuple, const Tuple& rightTuple) {
    vector<string> newTuple;
    Scheme newscheme = joinSchemes(rightScheme);
//    for (int i=0; i<newscheme.size(); ++i) {
//        cout << newscheme.at(i);
//    }
    for (auto& newit : newscheme) {
        bool flag = false;
        for (long unsigned int i=0; i<leftScheme.size(); ++i) {
            if (newit == leftScheme.at(i)) {
                newTuple.push_back(leftTuple.at(i));
                flag = true;
            }
            if (flag) {break;}
        }
        if (flag) {continue;}
        for (long unsigned int i=0; i<rightScheme.size(); ++i) {
            if (newit == rightScheme.at(i)) {
                newTuple.push_back(rightTuple.at(i));
            }
        }
    }
//    for (int i=0; i<newTuple.size(); ++i) {
//        cout << newTuple.at(i);
//    }
    return newTuple;
}

Scheme Relation::joinSchemes(const Scheme& rightScheme) {
    Scheme newscheme = scheme;
    for (auto& rightit : rightScheme) {
        bool flag = false;
        for (auto& leftit : scheme) {
            if (leftit == rightit) {
                flag = true;
            }
        }
        if (!flag) {
            newscheme.push_back(rightit);
        }
    }
//    for (int i=0; i<newscheme.size(); ++i) {
//        cout << newscheme.at(i);
//    }
    return newscheme;
}

bool Relation::joinable(const Scheme& leftScheme, const Scheme& rightScheme, const Tuple& leftTuple, const Tuple& rightTuple) {
//    for (unsigned leftIndex = 0; leftIndex < leftScheme.size(); leftIndex++) {
//        const string& leftName = leftScheme.at(leftIndex);
//        const string& leftValue = leftTuple.at(leftIndex);
//        cout << "left name: " << leftName << " value: " << leftValue << endl;
//        for (unsigned rightIndex = 0; rightIndex < rightScheme.size(); rightIndex++) {
//            const string& rightName = rightScheme.at(rightIndex);
//            const string& rightValue = rightTuple.at(rightIndex);
//            cout << "right name: " << rightName << " value: " << rightValue << endl;
//        }
//    }
    for (long unsigned int i=0; i<leftScheme.size(); ++i) {
        for (long unsigned int j=0; j<rightScheme.size(); ++j) {
            if (leftScheme.at(i) == rightScheme.at(j)) {
                if (leftTuple.at(i) != rightTuple.at(j)) {
                    return false;
                }
            }
        }
    }
    return true;
}

string Relation::toString() {
    stringstream out;
    for (auto& tuple : tuples) {
        out << "  " << tuple.toString(scheme) << endl;
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
    for (long unsigned int i=0; i<values.size(); ++i) {
        newscheme.push_back(values.at(i));
    }
    Relation result(name, newscheme);
    for (auto it : tuples) {
        vector<string> newTuple;
        for (long unsigned int j=0; j<indexes.size(); ++j) {
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
    for (const auto& it : tuples) {
        result.addTuple(it);
    }
    return result;
}

#endif //DATALOGPROJECT_RELATION_H
