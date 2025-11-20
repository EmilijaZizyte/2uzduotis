#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <list>

class Studentas {
public:
    std::string vard;
    std::string pav;
    std::vector<int> paz;
    int egzas{};
    double rezVid{};
    double rezMed{};

    // Konstruktorius
    Studentas()
        : vard(" "), pav(" "), paz(), egzas(0), rezVid(0.0), rezMed(0.0) {
    }
    ~Studentas() {
        vard.clear();
        pav.clear();
        paz.clear();
        rezVid = 0;
        egzas = 0;
        rezMed = 0;
    }

    // Member funkcijos
	double galBalas(double (*f)(std::vector<double>) = nullptr) const; // „f yra rodykle i funkcija, kuri priima std::vector<double> ir grazina double“
    void skaiciuokRezultatus();
	std::istream& readStudent(std::istream& is); // istream – įvesties srautas leidzia skaityti is std::cin arba failo

    // Setteriai
    void setVard(const std::string& v) { vard = v; }
    void setPav(const std::string& p) { pav = p; }
    void addPazymys(int p) { paz.push_back(p); }
    void setEgzas(int e) { egzas = e; }

    // Getteriai
    std::string getVard() const { return vard; }
    std::string getPav() const { return pav; }
    std::vector<int> getPazymiai() const { return paz; }
    int getEgzas() const { return egzas; }
    double getRezVid() const { return rezVid; }
    double getRezMed() const { return rezMed; }
};

// Papildomos funkcijos darbui su grupe
double mediana(const std::vector<int>& v);
void pridetiStudenta(std::vector<Studentas>& Grupe);
void rodytiRezultatus(const std::vector<Studentas>& Grupe);
void skaiciuokRezultatus(Studentas& s);
Studentas ivesk();
