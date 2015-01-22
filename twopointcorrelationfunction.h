#pragma once
#include "vec3.h"
#include <vector>
#include <string>
#include <utility>
// #define SINGLEK

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
    vector<vector<float> > calculate(string baseFolder, unsigned int numberOfTimesteps, unsigned int maxDeltaT, vector<float> kValues, float cellSize);
    vector<float> calculateStaticStructureFactor(string baseFolder, unsigned int numberOfTimesteps, vector<float> kValues, unsigned int numberOfKValues, float cellSize);
    unsigned long numberOfComputedPairs() { return m_numberOfComputedPairs; }
};
