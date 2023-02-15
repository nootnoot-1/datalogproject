#ifndef DATALOGPROJECT_PARAMETER_H
#define DATALOGPROJECT_PARAMETER_H
#include <string>
#include <sstream>
#include <utility>


class Parameter {
private:
    string value;

public:
    explicit Parameter(string value) : value(std::move(value)) {}

    string toString() const;
};

string Parameter::toString() const {
    return value;
}

#endif //DATALOGPROJECT_PARAMETER_H
