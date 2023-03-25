#ifndef DATALOGPROJECT_PARAMETER_H
#define DATALOGPROJECT_PARAMETER_H
#include <string>
#include <sstream>
#include <utility>


class Parameter {
private:
    string value;
    bool Constant = false;

public:
    explicit Parameter(string value) : value(std::move(value)) {
        if (this->value.at(0) == '\'') {
            Constant = true;
        }
    }

    string toString() const;
    bool isConstant() const {
        return Constant;
    }
};

string Parameter::toString() const {
    return value;
}


#endif //DATALOGPROJECT_PARAMETER_H
