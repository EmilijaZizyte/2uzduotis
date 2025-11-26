#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <numeric>
#include "zmogus.h"

class Studentas : public Zmogus {
public:
    std::vector<int> paz;
    int egzas{};
    double rezVid{};
    double rezMed{};

    // ======== KONSTRUKTORIAI ========
    Studentas()
        : Zmogus("", ""), paz(0, 0), egzas(0), rezVid(0.0), rezMed(0.0)
    {
    }

    Studentas(const std::string& v, const std::string& p,
        const std::vector<int>& paz_, int e)
        : Zmogus(v, p), paz(paz_), egzas(e)
    {
    }

    Studentas(const Studentas& other)
        : Zmogus(other.vard, other.pav),
        paz(other.paz),
        egzas(other.egzas),
        rezVid(other.rezVid),
        rezMed(other.rezMed)
    {
    }

    Studentas(Studentas&& other) noexcept
        : Zmogus(std::move(other.vard), std::move(other.pav)),
        paz(std::move(other.paz)),
        egzas(other.egzas),
        rezVid(other.rezVid),
        rezMed(other.rezMed)
    {
    }

    ~Studentas() {
        paz.clear();
        egzas = 0;
        rezVid = 0;
        rezMed = 0;
    }

    // ======== PERKĖLIMO IR KOPIJAVIMO OPERATORIAI ========
    Studentas& operator=(const Studentas& other) {
        if (this != &other) {
            Zmogus::operator=(other);  // <--- svarbu
            paz = other.paz;
            egzas = other.egzas;
            rezVid = other.rezVid;
            rezMed = other.rezMed;
        }
        return *this;
    }

    Studentas& operator=(Studentas&& other) noexcept {
        if (this != &other) {
            Zmogus::operator=(std::move(other));
            paz = std::move(other.paz);
            egzas = other.egzas;
            rezVid = other.rezVid;
            rezMed = other.rezMed;
        }
        return *this;
    }

    // ======== GETTERIAI ========
    const std::vector<int> getPaz() const { return paz; }
    int getEgzas() const { return egzas; }
    double getRezVid() const { return rezVid; }
    double getRezMed() const { return rezMed; }

    // ======== SETTERIAI ========
    void setPazymiai(const std::vector<int>& p) { paz = p; }
    void setEgzas(int e) { egzas = e; }
    void setRezVid(double r) { rezVid = r; }
    void setRezMed(double r) { rezMed = r; }

    // ======== VIRTUAL FUNCTION IMPLEMENTATION ========
    void spausdinti() const override {
        std::cout << vard << " " << pav
            << " Egz: " << egzas
            << " Vid: " << rezVid
            << " Med: " << rezMed << std::endl;
    }

    // ======== I/O FRIENDS ========
    friend void skaiciuokRezultatus(Studentas& s);
    friend std::ostream& operator<<(std::ostream& os, const Studentas& s);
    friend std::istream& operator>>(std::istream& is, Studentas& s);
};

// ======== IŠORINĖS FUNKCIJOS ========
Studentas ivesk();
void rodytiRezultatus(const std::vector<Studentas>& Grupe);
void testasRuleOfThreeIrIO();
