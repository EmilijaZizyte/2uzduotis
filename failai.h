#pragma once
#include "studentas.h"
#include <vector>
#include <list>
#include <string>
#include <iostream>
#include <iomanip>

class Rezultatai {
public:
    // ================= Laikų kintamieji =================
    double readTime = 0;
    double splitTime = 0;
    double writeTime = 0;
    double memMB = 0;

    double readTimeVector = 0;
    double splitTimeVector = 0;
    double writeTimeVector = 0;
    double memMBVector = 0;

    double readTimeList = 0;
    double splitTimeList = 0;
    double writeTimeList = 0;
    double memMBList = 0;

    // ================= Konstruktoriai =================
    Rezultatai() = default;

    Rezultatai(double rT, double sT, double wT, double m)
        : readTime(rT), splitTime(sT), writeTime(wT), memMB(m) {
    }

    // ================= Pagalbiniai metodai =================
    void printVectorResults() const {
        std::cout << "Vector nuskaitymas: " << readTimeVector << " s\n";
        std::cout << "Vector skaidymas: " << splitTimeVector << " s\n";
        std::cout << "Vector rasymas: " << writeTimeVector << " s\n";
        std::cout << "Vector atmintis: " << std::fixed << std::setprecision(2) << memMBVector << " MB\n";
    }

    void printListResults() const {
        std::cout << "List nuskaitymas: " << readTimeList << " s\n";
        std::cout << "List skaidymas: " << splitTimeList << " s\n";
        std::cout << "List rasymas: " << writeTimeList << " s\n";
        std::cout << "List atmintis: " << std::fixed << std::setprecision(2) << memMBList << " MB\n";
    }
};

// ================= Funkcijų deklaracijos =================
void generuokFailus();
void analizuokVisusFailusMinimaliai();
Rezultatai strategija1_skaidymas(const std::string& failas);
Rezultatai Strategija2(const std::string& failas);
Rezultatai strategija1_STL_vectoriui(const std::string& failas);
void Strategija3(const std::string& failas);
Rezultatai strategija2_STL_vectoriui(const std::string& failas);
