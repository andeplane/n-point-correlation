#include "celllist.h"
#include "cpelapsedtimer.h"
#include <iostream>
using namespace std;


vec3 CellList::systemSize() const
{
    return m_systemSize;
}

vec3 CellList::numberOfCells() const
{
    return m_numberOfCells;
}

vec3 CellList::cellSize() const
{
    return m_cellSize;
}

vec3 CellList::oneOverCellSize() const
{
    return m_oneOverCellSize;
}

CellList::CellList() :
    m_isInitialized(false)
{

}

CellList::~CellList()
{

}

unsigned int CellList::totalNumberOfCells()
{
    return m_numberOfCells[0]*m_numberOfCells[1]*m_numberOfCells[2];
}

void CellList::initialize(vec3 systemSize, vec3 numberOfCells)
{
    m_isInitialized = true;
    m_systemSize = systemSize;
    // Cast to int
    numberOfCells[0] = int(numberOfCells[0]);
    numberOfCells[1] = int(numberOfCells[1]);
    numberOfCells[2] = int(numberOfCells[2]);

    m_numberOfCells = numberOfCells;
    m_cellSize = systemSize/numberOfCells;
    m_oneOverCellSize = m_cellSize.inverse();
    m_cells.clear();
    m_cells.resize((unsigned int)m_numberOfCells[0], vector<vector<Cell> >((unsigned int)m_numberOfCells[1], vector<Cell>((unsigned int)m_numberOfCells[2])));
    cout << "Initializing cell list with " << m_numberOfCells << " number of cells and cell size " << m_cellSize << endl;
}

void CellList::addParticles(vector<float> x, vector<float> y, vector<float> z)
{
    if(!m_isInitialized) {
        cout << "CellList not initialized, aborting!" << endl;
        exit(1);
    }
    CPElapsedTimer::cellList().start();
    for(unsigned int n=0; n<x.size(); n++) {
        unsigned int i = x[n] * m_oneOverCellSize[0];
        unsigned int j = y[n] * m_oneOverCellSize[1];
        unsigned int k = z[n] * m_oneOverCellSize[2];
        m_cells[i][j][k].addParticle(x[n], y[n], z[n], n);
    }
    CPElapsedTimer::cellList().stop();
}

void CellList::clearCells()
{
    for(unsigned int i=0; i<m_cells.size(); i++) {
        vector<vector<Cell> > &c1 = m_cells[i];
        for(unsigned int j=0; j< c1.size(); j++) {
            vector<Cell> &c2 = c1[j];
            for(unsigned int k=0; k< c2.size(); k++) {
                Cell &cell = c2[k];
                cell.clear();
            }
        }
    }
}

Cell::Cell()
{
    resize(100);
}

Cell::~Cell()
{
    x.clear();
    y.clear();
    z.clear();
}

unsigned int Cell::numberOfParticles()
{
    return x.size();
}

void Cell::resize(unsigned int size)
{
    x.reserve(size);
    y.reserve(size);
    z.reserve(size);
}

void Cell::addParticle(float x_, float y_, float z_, unsigned int particleIndex_)
{
    x.push_back(x_);
    y.push_back(y_);
    z.push_back(z_);
    particleIndex.push_back(particleIndex_);
}

void Cell::clear()
{
    x.clear();
    y.clear();
    z.clear();
    particleIndex.clear();
}
