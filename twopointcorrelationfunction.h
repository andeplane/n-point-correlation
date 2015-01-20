#pragma once
#include "vec3.h"
#include <vector>
#include <string>
#include <utility>

using std::pair;
using std::vector;
using std::string;
class TwoPointCorrelationFunction
{
private:
    unsigned long m_numberOfComputedPairs;
public:
    TwoPointCorrelationFunction();
    ~TwoPointCorrelationFunction();
    vector<vector<pair<float, float> > > calculate(string baseFolder, unsigned int numberOfTimesteps, vector<float> kValues, float cellSize);
    unsigned long numberOfComputedPairs() { return m_numberOfComputedPairs; }
};
