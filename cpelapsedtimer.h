#ifndef CPELAPSEDTIMER_H
#define CPELAPSEDTIMER_H
#include <time.h>

class CPTimingObject {
private:
    double m_timeElapsed;
    clock_t m_startedAt;
public:
    CPTimingObject() : m_timeElapsed(0), m_startedAt(0) { }

    void start() {
         m_startedAt = clock();
    }

    double stop() {
        double t = double(clock() - m_startedAt)/CLOCKS_PER_SEC;
        m_timeElapsed += t;
        return t;
    }

    double elapsedTime() { return m_timeElapsed; }
};

class CPElapsedTimer
{
public:
    CPElapsedTimer();

    static CPElapsedTimer& getInstance()
    {
        static CPElapsedTimer instance; // Guaranteed to be destroyed.
                                 // Instantiated on first use.
        return instance;
    }

    clock_t        m_startedAt;
    clock_t        m_lastPing;
    CPTimingObject m_readFile;
    CPTimingObject m_cellList;
    CPTimingObject m_twoPointCorrelation;
    CPTimingObject m_twoPointCorrelationNormalize;

    static CPTimingObject &readFile() { return CPElapsedTimer::getInstance().m_readFile; }
    static CPTimingObject &cellList() { return CPElapsedTimer::getInstance().m_cellList; }
    static CPTimingObject &twoPointCorrelation() { return CPElapsedTimer::getInstance().m_twoPointCorrelation; }
    static CPTimingObject &twoPointCorrelationNormalize() { return CPElapsedTimer::getInstance().m_twoPointCorrelationNormalize; }

    static double totalTime() { return double(clock() - CPElapsedTimer::getInstance().m_startedAt)/ CLOCKS_PER_SEC; }
    static double ping();
};

#endif // CPELAPSEDTIMER_H
