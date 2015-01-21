#include <iostream>
#include <vector>
#include "cpelapsedtimer.h"
#include "celllist.h"
#include "filemanager.h"
#include "vec3.h"
#include "twopointcorrelationfunction.h"
#include <string>
#include <utility>

using namespace std;

int main()
{
    TwoPointCorrelationFunction twoPoint;
    vector<float> kValues;

#ifdef SINGLEK
    kValues.push_back(7.2);
    unsigned int numberOfTimesteps = 199;
#else
    for(unsigned int i=0; i<50; i++) {
        kValues.push_back(0.4*i + 1.0);
    }
    unsigned int numberOfTimesteps = 8;
#endif

    float cellSize = 15;
#ifdef SINGLEK
    // vector<vector<pair<float, float> > > result = twoPoint.calculate("/projects/build-molecular-dynamics-fys3150-GCC4_9-Release/states/", numberOfTimesteps, 0, kValues, cellSize);
    for(unsigned int i=0; i<result[0].size(); i++) {
        cout << i << " " << result[0][i].first << " " << result[0][i].second << endl;
    }
#else
    // vector<vector<pair<float, float> > > result = twoPoint.calculate("/projects/build-molecular-dynamics-fys3150-GCC4_9-Release/states/", numberOfTimesteps, 0, kValues, cellSize);
    vector<float> result = twoPoint.calculateStaticStructureFactor("/projects/build-molecular-dynamics-fys3150-GCC4_9-Release/states/", numberOfTimesteps, kValues, cellSize);
    for(unsigned int k=0; k<result.size(); k++) {
        cout << kValues[k] << " " << result[k] << endl;
    }
#endif

    float readFileFraction = CPElapsedTimer::readFile().elapsedTime() / CPElapsedTimer::totalTime();
    float cellListFraction = CPElapsedTimer::cellList().elapsedTime() / CPElapsedTimer::totalTime();
    float twoPointCorrelationFraction = CPElapsedTimer::twoPointCorrelation().elapsedTime() / CPElapsedTimer::totalTime();
    float twoPointCorrelationNormalizeFraction = CPElapsedTimer::twoPointCorrelationNormalize().elapsedTime() / CPElapsedTimer::totalTime();

    cout << endl << "Program finished after " << CPElapsedTimer::totalTime() << " seconds. Time analysis:" << endl;
    cout << fixed
         << "      Read file         : " << CPElapsedTimer::readFile().elapsedTime() << " s ( " << 100*readFileFraction << "%)" <<  endl
         << "      Cell list         : " << CPElapsedTimer::cellList().elapsedTime() << " s ( " << 100*cellListFraction << "%)" <<  endl
         << "      Two point         : " << CPElapsedTimer::twoPointCorrelation().elapsedTime() << " s ( " << 100*twoPointCorrelationFraction << "%)" <<  endl
         << "      Two point norm    : " << CPElapsedTimer::twoPointCorrelationNormalize().elapsedTime() << " s ( " << 100*twoPointCorrelationNormalizeFraction << "%)" <<  endl << endl;

    cout << twoPoint.numberOfComputedPairs() << " computed pairs (" << twoPoint.numberOfComputedPairs()/CPElapsedTimer::totalTime() << " per second)" << endl;
    float flops = (6*twoPoint.numberOfComputedPairs() + twoPoint.numberOfComputedPairs()*kValues.size()*(7+42)) / CPElapsedTimer::totalTime();
    cout << "which gives " << flops/1e9 << " gigaflops." << endl;

    return 0;
}

