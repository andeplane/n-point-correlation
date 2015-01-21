#include "filemanager.h"
#include "cpelapsedtimer.h"
#include <fstream>
using std::ifstream;

FileManager::FileManager()
{

}

FileManager::~FileManager()
{

}

void FileManager::loadBinaryPositions(string filename, vector<float> &x, vector<float> &y, vector<float> &z, vec3 &systemSize)
{
    CPElapsedTimer::readFile().start();
    ifstream file(filename, std::ios::binary);
    unsigned int numberOfAtoms;
    file.read((char*)&numberOfAtoms, sizeof(unsigned int));

    float *phaseSpace = new float[3*numberOfAtoms];
    file.read((char*)phaseSpace, 3*numberOfAtoms*sizeof(float));

    double systemSizeDouble[3];
    file.read((char*)systemSizeDouble, 3*sizeof(double));
    systemSize[0] = systemSizeDouble[0];
    systemSize[1] = systemSizeDouble[1];
    systemSize[2] = systemSizeDouble[2];

    x.resize(numberOfAtoms);
    y.resize(numberOfAtoms);
    z.resize(numberOfAtoms);

    for(unsigned int i=0; i<numberOfAtoms; i++) {
        x[i] = phaseSpace[3*i+0];
        y[i] = phaseSpace[3*i+1];
        z[i] = phaseSpace[3*i+2];
    }

    delete phaseSpace;
    file.close();
    CPElapsedTimer::readFile().stop();
}

