#pragma once
#include "vec3.h"
#include <vector>
#include <string>

using std::vector; using std::string;

class FileManager
{
public:
    FileManager();
    ~FileManager();
    void loadBinaryPositions(string filename, vector<float> &x, vector<float> &y, vector<float> &z, vec3 &systemSize);
};
