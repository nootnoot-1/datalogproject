#ifndef DATALOGPROJECT_TUPLE_H
#define DATALOGPROJECT_TUPLE_H
#include <vector>
#include <sstream>
#include "Scheme.h"

class Tuple : public vector<string> {
public:
    Tuple(vector<string> values) : vector<string>(values) {}
    string toString(const Scheme& scheme) const;
};

string Tuple::toString(const Scheme& scheme) const{
    const Tuple& tuple = *this;
    stringstream out;
    //LOOP
    for (int i=0; i < scheme.size(); ++i){
        out << scheme.at(i) << "=";
        out << tuple.at(i);
        if (i<scheme.size()-1){
            out << ", ";
        }
    }
//    out << scheme.size();
//    out << scheme.at(0);
//    out << tuple.size();
//    out << tuple.at(0);
    return out.str();
}

#endif //DATALOGPROJECT_TUPLE_H
