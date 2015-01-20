#pragma once
#include "vec3.h"

#include <vector>
using std::vector;

class Cell
{
public:
    vector<float> x;
    vector<float> y;
    vector<float> z;
    vector<unsigned int> particleIndex;

    Cell();
    ~Cell();
    unsigned int numberOfParticles();
    void resize(unsigned int size);
    void addParticle(float x, float y, float z, unsigned int particleIndex);
    void clear();
};

class CellList
{
private:
    bool m_isInitialized;
    vec3 m_systemSize;
    vec3 m_numberOfCells;
    vec3 m_cellSize;
    vec3 m_oneOverCellSize;
    vector<vector<vector<Cell> > > m_cells;

public:
    CellList();
    ~CellList();
    unsigned int totalNumberOfCells();
    void initialize(vec3 systemSize, vec3 numberOfCells);
    void addParticles(vector<float> x, vector<float> y, vector<float> z);
    void clearCells();

    vector<vector<vector<Cell> > > &cells() { return m_cells; }
    vec3 systemSize() const;
    vec3 numberOfCells() const;
    vec3 cellSize() const;
    vec3 oneOverCellSize() const;
    bool isInitialized() { return m_isInitialized; }
};
