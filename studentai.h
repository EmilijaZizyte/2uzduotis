#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <numeric>

class Studentas {
public:
    std::string vard;
    std::string pav;
    std::vector<int> paz;
    int egzas{};
    double rezVid{};
    double rezMed{};

    // ======== KONSTRUKTORIAI ========
    Studentas()
        : vard(" "), pav(" "), paz(0, 0), egzas(0), rezVid(0.0), rezMed(0.0)
    {
    }

    Studentas(const std::string& v, const std::string& p,
        const std::vector<int>& paz_, int e)
        : vard(v), pav(p), paz(paz_), egzas(e) {
    }

    Studentas(const Studentas& other)
        : vard(other.vard), pav(other.pav), paz(other.paz),
        egzas(other.egzas), rezVid(other.rezVid), rezMed(other.rezMed) {
    }

    Studentas(Studentas&& other) noexcept
        : vard(std::move(other.vard)), pav(std::move(other.pav)),
        paz(std::move(other.paz)), egzas(other.egzas),
        rezVid(other.rezVid), rezMed(other.rezMed) {
    }

    // ======== DESTRUKTORIUS ========
    ~Studentas() {
        vard.clear();
        pav.clear();
        paz.clear();
        rezVid = 0;
        egzas = 0;
        rezMed = 0;
    }

    // ======== KOPIJAVIMO IR PERKĖLIMO PRISKYRIMO OPERATORIAI ========
    Studentas& operator=(const Studentas& other) {
        if (this != &other) {
            vard = other.vard;
            pav = other.pav;
            paz = other.paz;
            egzas = other.egzas;
            rezVid = other.rezVid;
            rezMed = other.rezMed;
        }
        return *this;
    }

    Studentas& operator=(Studentas&& other) noexcept {
        if (this != &other) {
            vard = std::move(other.vard);
            pav = std::move(other.pav);
            paz = std::move(other.paz);
            egzas = other.egzas;
            rezVid = other.rezVid;
            rezMed = other.rezMed;
        }
        return *this;
    }

    // ======== SETTERIAI ========
    void setVard(const std::string& v) { vard = v; }
    void setPav(const std::string& p) { pav = p; }
    void setPazymiai(const std::vector<int>& p) { paz = p; }
    void setEgzas(int e) { egzas = e; }
    void setRezVid(double r) { rezVid = r; }
    void setRezMed(double r) { rezMed = r; }

    // ======== GETTERIAI ========
    std::string getVard() const { return vard; }
    std::string getPav() const { return pav; }
    std::vector<int> getPaz() const { return paz; }
    int getEgzas() const { return egzas; }
    double getRezVid() const { return rezVid; }
    double getRezMed() const { return rezMed; }

    // ======== PAGALBINĖ FUNKCIJA (DRAUGAS) ========
    friend void skaiciuokRezultatus(Studentas& s);
};

// ======== IŠORINĖS FUNKCIJOS DEKLARACIJOS ========
Studentas ivesk();
void rodytiRezultatus(const std::vector<Studentas>& Grupe);
