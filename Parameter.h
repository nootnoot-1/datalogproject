#ifndef DATALOGPROJECT_PARAMETER_H
#define DATALOGPROJECT_PARAMETER_H
#include <string>
#include <sstream>


class Parameter {
private:
    string value;

public:
    Parameter(string value) : value(value) {}

    string toString() const;
};

string Parameter::toString() const {
    return value;
}

#endif //DATALOGPROJECT_PARAMETER_H
