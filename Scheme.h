#ifndef DATALOGPROJECT_SCHEME_H
#define DATALOGPROJECT_SCHEME_H
#include <vector>

class Scheme : public vector<string> {
public:
    Scheme(vector<string> names) : vector<string>(names) {}
};

#endif //DATALOGPROJECT_SCHEME_H
