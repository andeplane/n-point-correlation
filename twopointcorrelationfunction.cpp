#include "twopointcorrelationfunction.h"
#include "celllist.h"
#include "cpelapsedtimer.h"
#include "filemanager.h"
#include <cmath>
#include <iostream>
using namespace std;

TwoPointCorrelationFunction::TwoPointCorrelationFunction() :
    m_numberOfComputedPairs(0)
{

}

TwoPointCorrelationFunction::~TwoPointCorrelationFunction()
{

}

vector<vector<pair<float, float> > > TwoPointCorrelationFunction::calculate(string baseFolder, unsigned int numberOfTimesteps, vector<float> kValues, float cellSize)
{
    vector<vector<pair<float, float> > > result;
    vector<vector<unsigned int> > resultCount;
    result.resize(kValues.size());
    resultCount.resize(kValues.size());
    for(unsigned int i=0; i<kValues.size(); i++) {
        result[i].resize(numberOfTimesteps);
        resultCount[i].resize(numberOfTimesteps, 0);
    }

    FileManager fileManager;

    vector<float> x;
    vector<float> y;
    vector<float> z;
    vec3 systemSize;
    CellList state0;
    CellList state1;
    char *filename = new char[1000];
    unsigned int numberOfParticles = 0;

    for(unsigned int t0=0; t0<numberOfTimesteps; t0++) {
        sprintf(filename, "%s/%04d.bin", baseFolder.c_str(), t0);
        fileManager.loadBinaryPositions(filename, x,y,z,systemSize);
        if(!state0.isInitialized()) {
            vec3 numberOfCells = systemSize / cellSize;

            state0.initialize(systemSize, numberOfCells);
            state1.initialize(systemSize, numberOfCells);
        }

        state0.clearCells();
        state0.addParticles(x,y,z);
        int numberOfCells[3];
        numberOfCells[0] = state0.numberOfCells()[0];
        numberOfCells[1] = state0.numberOfCells()[1];
        numberOfCells[2] = state0.numberOfCells()[2];

        vector<vector<vector<Cell> > > &cells0 = state0.cells();

        for(unsigned int t1=t0; t1<numberOfTimesteps; t1++) {
            cout << "Working on time pair (" << t0 << ", " << t1 << ")" << endl;
            sprintf(filename, "%s/%04d.bin", baseFolder.c_str(), t1);
            fileManager.loadBinaryPositions(filename, x,y,z,systemSize);
            state1.clearCells();
            state1.addParticles(x,y,z);
            numberOfParticles = x.size();
            vector<vector<vector<Cell> > > &cells1 = state1.cells();
            unsigned int deltaT = t1 - t0;
            for(unsigned int k=0; k<kValues.size(); k++){
                resultCount[k][deltaT]++; // Another sample of this timestep combination
            }

            CPElapsedTimer::twoPointCorrelation().start();
            for(int c1x=0; c1x<numberOfCells[0]; c1x++) {
                for(int c1y=0; c1y<numberOfCells[1]; c1y++) {
                    for(int c1z=0; c1z<numberOfCells[2]; c1z++) {
                        Cell &cell0 = cells0[c1x][c1y][c1z];

                        for(int dx=-1; dx<=1; dx++) {
                            for(int dy=-1; dy<=1; dy++) {
                                for(int dz=-1; dz<=1; dz++) {
                                    int c2x = (c1x + dx + numberOfCells[0]) % numberOfCells[0];
                                    int c2y = (c1y + dy + numberOfCells[1]) % numberOfCells[1];
                                    int c2z = (c1z + dz + numberOfCells[2]) % numberOfCells[2];
                                    Cell &cell1 = cells1[c2x][c2y][c2z];

                                    for(unsigned int i=0; i<cell0.numberOfParticles(); i++) {
                                        float x0 = cell0.x[i];
                                        float y0 = cell0.y[i];
                                        float z0 = cell0.z[i];

                                        for(unsigned int j=0; j<cell1.numberOfParticles(); j++) {
                                            m_numberOfComputedPairs++;
                                            float x1 = cell1.x[j];
                                            float y1 = cell1.y[j];
                                            float z1 = cell1.z[j];

                                            float dx = x0 - x1;
                                            float dy = y0 - y1;
                                            float dz = z0 - z1;
                                            if(dx > 0.5*systemSize[0]) dx -= systemSize[0];
                                            else if(dx < -0.5*systemSize[0]) dx += systemSize[0];

                                            if(dy > 0.5*systemSize[1]) dy -= systemSize[1];
                                            else if(dy < -0.5*systemSize[1]) dy += systemSize[1];

                                            if(dz > 0.5*systemSize[2]) dz -= systemSize[2];
                                            else if(dz < -0.5*systemSize[2]) dz += systemSize[2];
                                            for(unsigned int k=0; k<kValues.size(); k++) {
                                                // Use 3 k values along the 3 standard axes to average
                                                float contribution = 0.3333333333*(kValues[k]*dx + kValues[k]*dy + kValues[k]*dz);
                                                float real = cos(contribution);
                                                float imag = sin(contribution);
                                                result[k][deltaT].first += real;
                                                result[k][deltaT].second += imag;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            CPElapsedTimer::twoPointCorrelation().stop();
        }
    }

    CPElapsedTimer::twoPointCorrelationNormalize().start();
    CPElapsedTimer::twoPointCorrelation().start();
    unsigned int numberOfParticlesSquared = numberOfParticles*numberOfParticles;
    for(unsigned int k=0; k<kValues.size(); k++) {
        for(unsigned int t=0; t<numberOfTimesteps; t++) {
            result[k][t].first /= numberOfParticlesSquared;
            result[k][t].second /= numberOfParticlesSquared;
            result[k][t].first /= (resultCount[k][t] > 0) ? resultCount[k][t] : 1.0;
            result[k][t].second /= (resultCount[k][t] > 0) ? resultCount[k][t] : 1.0;
        }
    }
    CPElapsedTimer::twoPointCorrelationNormalize().stop();
    CPElapsedTimer::twoPointCorrelation().stop();
    cout << "Finished computing the two point correlation function with a total of " << m_numberOfComputedPairs << " pairs computed." << endl;
    return result;
}

