#pragma once
#include "studentas.h"
#include <fstream>
#include <chrono>
#include <vector>
#include <list>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <functional>

// ======== KLASĖ REZULTATAI ========
class Rezultatai {
public:
    double readTime;
    double splitTime;
    double writeTime;
    double memMB;

    double readTimeVector;
    double splitTimeVector;
    double writeTimeVector;
    double memMBVector;

    double readTimeList;
    double splitTimeList;
    double writeTimeList;
    double memMBList;


    // ======== Konstruktorius ========
    Rezultatai()
        : readTime(0), splitTime(0), writeTime(0), memMB(0),
        readTimeVector(0), splitTimeVector(0), writeTimeVector(0), memMBVector(0),
        readTimeList(0), splitTimeList(0), writeTimeList(0), memMBList(0) {
    }
    ~Rezultatai() {
        readTime = 0;
        splitTime = 0;
        writeTime = 0;
        memMB = 0;
        readTimeVector = 0;
        splitTimeVector = 0;
        writeTimeVector = 0;
        memMBVector = 0;
        readTimeList = 0;
        splitTimeList = 0;
        writeTimeList = 0;
        memMBList = 0;
    }

    // ======== Setteriai ========
    void setReadTime(double val) { readTime = val; }
    void setSplitTime(double val) { splitTime = val; }
    void setWriteTime(double val) { writeTime = val; }
    void setMemMB(double val) { memMB = val; }

    void setReadTimeVector(double val) { readTimeVector = val; }
    void setSplitTimeVector(double val) { splitTimeVector = val; }
    void setWriteTimeVector(double val) { writeTimeVector = val; }
    void setMemMBVector(double val) { memMBVector = val; }

    void setReadTimeList(double val) { readTimeList = val; }
    void setSplitTimeList(double val) { splitTimeList = val; }
    void setWriteTimeList(double val) { writeTimeList = val; }
    void setMemMBList(double val) { memMBList = val; }

    // ======== Getteriai ========
    double getReadTime() const { return readTime; }
    double getSplitTime() const { return splitTime; }
    double getWriteTime() const { return writeTime; }
    double getMemMB() const { return memMB; }

    double getReadTimeVector() const { return readTimeVector; }
    double getSplitTimeVector() const { return splitTimeVector; }
    double getWriteTimeVector() const { return writeTimeVector; }
    double getMemMBVector() const { return memMBVector; }

    double getReadTimeList() const { return readTimeList; }
    double getSplitTimeList() const { return splitTimeList; }
    double getWriteTimeList() const { return writeTimeList; }
    double getMemMBList() const { return memMBList; }
};

// ======== FUNKCIJŲ DEKLARACIJOS ========


void generuokFailus();
void analizuokVisusFailusMinimaliai();
Rezultatai strategija1_skaidymas(const std::string& failas);
Rezultatai Strategija2(const std::string& failas);
Rezultatai strategija1_STL_vectoriui(const std::string& failas);
void Strategija3(const std::string& failas);
Rezultatai strategija2_STL_vectoriui(const std::string& failas);
