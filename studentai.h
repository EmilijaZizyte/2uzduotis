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
	//parametrinis konstruktorius, naudojamas kai mes norime sukurti nauja objekta su 
	// nurodytais duomenimis, mano kode jis naudojamas funkcijoje ivesk()
    Studentas(const std::string& v, const std::string& p,
        const std::vector<int>& paz_, int e)
        : vard(v), pav(p), paz(paz_), egzas(e) {
    }
	//kopijavimo konstruktorius, naudojamas kai mes norime sukurti nauja objekta, 
    // naudojame kai norime sukurti ka? nauja objekta is esamo objekto, mano kode jis naudojamas
    // kai mes priskiriame viena objekta kitam,
    // pvz: Studentas s2 = s1;
    Studentas(const Studentas& other)
        : vard(other.vard), pav(other.pav), paz(other.paz),
        egzas(other.egzas), rezVid(other.rezVid), rezMed(other.rezMed) {
    }
	//move konstruktorius, jis naudojamas kai objektas yra laikinasis arba kai jis yra perkeliamas is 
    // vienos vietos i kita, mano kode jis naudojamas kai mes naudojame std::move funkcija, o ji yra
    // naudojama kai mes norime perkelti objekta is vienos vietos i kita vieta,
    // o ne kopijuoti ji, tai yra efektyviau, nes nereikia kurti naujo objekto ir kopijuoti duomenu 
    // i ji, vietoj to mes tiesiog perkeliam duomenis i nauja vieta, 
    // naudojama funkcijoje pavadinimu ivesk()
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
	//kopijavimo priskyrimo operatorius, naudojamas kai mes norime priskirti viena objekta kitam, pvz:    
	// s2 = s1 naudojame mano kode funkcijoje testasRuleOfThreeIrIO() ir ivesk()
	// priskirimo operatorius turi patikrinti ar mes nepriskiriam objekto sau paciam, kode: if (this != &other) {}, 
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
	//move priskyrimo operatorius, naudojamas kai mes norime perkelti objekta is vienos vietos i kita,
    // naudojame mano kode funkcijoje ivesk()
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
    friend std::ostream& operator<<(std::ostream& os, const Studentas& s);
    friend std::istream& operator>>(std::istream& is, Studentas& s);
};

// ======== IŠORINĖS FUNKCIJOS DEKLARACIJOS ========
Studentas ivesk();
void rodytiRezultatus(const std::vector<Studentas>& Grupe);
void testasRuleOfThreeIrIO();
