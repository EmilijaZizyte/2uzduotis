#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <numeric>
#include "zmogus.h"

/**
 * @class Studentas
 * @brief Studentą reprezentuojanti klasė, paveldinti iš Zmogus.
 *
 * Saugo pažymius, egzamino rezultatą, galutinius balus
 * (vidurkį ir medianą) ir leidžia atlikti su jais operacijas.
 */
class Studentas : public Zmogus {
public:
    /// Studentų pažymių sąrašas.
    std::vector<int> paz;

    /// Egzamino pažymys.
    int egzas{};

    /// Galutinis balas pagal vidurkį.
    double rezVid{};

    /// Galutinis balas pagal medianą.
    double rezMed{};

    // ======== KONSTRUKTORIAI ========

    /**
     * @brief Tuščias konstruktorius.
     *
     * Inicializuoja tuščius vardą, pavardę ir 0 dydžio pažymių vektorių.
     */
    Studentas()
        : Zmogus( "", ""), paz(), egzas(0), rezVid(0.0), rezMed(0.0)
    {
    }

    /**
     * @brief Konstruktorius su parametrais.
     *
     * @param v Vardas.
     * @param p Pavardė.
     * @param paz_ Pažymių vektorius.
     * @param e Egzamino pažymys.
     */
    Studentas(const std::string& v, const std::string& p,
        const std::vector<int>& paz_, int e)
        : Zmogus(v, p), paz(paz_), egzas(e)
    {
    }

    /**
     * @brief Kopijavimo konstruktorius.
     *
     * @param other Kitas Studentas objektas.
     */
    Studentas(const Studentas& other)
        : Zmogus(other.vard, other.pav),
        paz(other.paz),
        egzas(other.egzas),
        rezVid(other.rezVid),
        rezMed(other.rezMed)
    {
    }

    /**
     * @brief Perkėlimo konstruktorius.
     *
     * @param other Objektas, iš kurio atliekamas perkėlimas.
     */
    Studentas(Studentas&& other) noexcept
        : Zmogus(std::move(other.vard), std::move(other.pav)),
        paz(std::move(other.paz)),
        egzas(other.egzas),
        rezVid(other.rezVid),
        rezMed(other.rezMed)
    {
    }

    /**
     * @brief Destruktorius.
     *
     * Išvalo pažymius ir atstato kitus laukus į 0.
     */
    ~Studentas() {
        paz.clear();
        egzas = 0;
        rezVid = 0;
        rezMed = 0;
    }

    // ======== PERKĖLIMO IR KOPIJAVIMO OPERATORIAI ========

    /**
     * @brief Kopijavimo priskyrimo operatorius.
     *
     * @param other Objektas, iš kurio kopijuojama.
     * @return Nuoroda į esamą objektą.
     */
    Studentas& operator=(const Studentas& other) {
        if (this != &other) {
            Zmogus::operator=(other);
            paz = other.paz;
            egzas = other.egzas;
            rezVid = other.rezVid;
            rezMed = other.rezMed;
        }
        return *this;
    }

    /**
     * @brief Perkėlimo priskyrimo operatorius.
     *
     * @param other Objektas, iš kurio perkeliama.
     * @return Nuoroda į esamą objektą.
     */
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

    /**
     * @brief Grąžina pažymių vektorių.
     * @return Pažymių vektorius.
     */
    const std::vector<int> getPaz() const { return paz; }

    /**
     * @brief Grąžina egzamino balą.
     * @return Egzamino balas.
     */
    int getEgzas() const { return egzas; }

    /**
     * @brief Grąžina galutinį balą pagal vidurkį.
     * @return Galutinis balas.
     */
    double getRezVid() const { return rezVid; }

    /**
     * @brief Grąžina galutinį balą pagal medianą.
     * @return Galutinis balas.
     */
    double getRezMed() const { return rezMed; }

    // ======== SETTERIAI ========

    /**
     * @brief Nustato pažymių vektorių.
     * @param p Pažymiai.
     */
    void setPazymiai(const std::vector<int>& p) { paz = p; }

    /**
     * @brief Nustato egzamino balą.
     * @param e Egzamino balas.
     */
    void setEgzas(int e) { egzas = e; }

    /**
     * @brief Nustato galutinį balą pagal vidurkį.
     * @param r Reikšmė.
     */
    void setRezVid(double r) { rezVid = r; }

    /**
     * @brief Nustato galutinį balą pagal medianą.
     * @param r Reikšmė.
     */
    void setRezMed(double r) { rezMed = r; }

    // ======== VIRTUAL FUNCTION IMPLEMENTATION ========

    /**
     * @brief Studentų informacijos spausdinimo funkcija.
     *
     * Perrašo Zmogus::spausdinti().
     */
    void spausdinti() const override {
        std::cout << vard << " " << pav
            << " Egz: " << egzas
            << " Vid: " << rezVid
            << " Med: " << rezMed << std::endl;
    }

    // ======== I/O FRIENDS ========

    /**
     * @brief Draugo funkcija – skaičiuoja galutinius rezultatus.
     * @param s Studentas, kuriam skaičiuojami rezultatai.
     */
    friend void skaiciuokRezultatus(Studentas& s);

    /**
     * @brief Srautinis išvedimo operatorius.
     * @param os Išvedimo srautas.
     * @param s Studentas.
     * @return Tas pats srautas.
     */
    friend std::ostream& operator<<(std::ostream& os, const Studentas& s);

    /**
     * @brief Srautinis įvedimo operatorius.
     * @param is Įvedimo srautas.
     * @param s Studentas.
     * @return Tas pats srautas.
     */
    friend std::istream& operator>>(std::istream& is, Studentas& s);
};

// ======== IŠORINĖS FUNKCIJOS ========

/**
 * @brief Funkcija, kuri interaktyviai sukuria Studentas objektą.
 * @return Sukurtas Studentas.
 */
Studentas ivesk();

/**
 * @brief Išveda visų studentų rezultatus lentelėje.
 * @param Grupe Studentų vektorius.
 */
void rodytiRezultatus(const std::vector<Studentas>& Grupe);

/**
 * @brief Testuoja Rule of Three/Rule of Five ir I/O veikimą.
 */
void testasRuleOfThreeIrIO();

double mediana(std::vector<int> v);
