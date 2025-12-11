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
 * @brief Studenta reprezentuojanti klase, paveldinti is Zmogus.
 *
 * Saugo pazymius, egzamino rezultata, galutinius balus
 * (vidurki ir mediana) ir leidzia atlikti su jais operacijas.
 */
class Studentas : public Zmogus {
public:
    /// Studentu pazymiu sarasas.
    std::vector<int> paz;

    /// Egzamino pazymys.
    int egzas{};

    /// Galutinis balas pagal vidurki.
    double rezVid{};

    /// Galutinis balas pagal mediana.
    double rezMed{};

    // ======== KONSTRUKTORIAI ========

    /**
     * @brief Tuscias konstruktorius.
     *
     * Inicializuoja tuscius varda, pavarde ir 0 dydzio pazymiu vektoriu.
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
     * @param paz_ Pazymiu vektorius.
     * @param e Egzamino pazymys.
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
     * @brief Perkelimo konstruktorius.
     *
     * @param other Objektas, is kurio atliekamas perkelimas.
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
     * Isvalo pazymius ir atstato kitus laukus i 0.
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
     * @param other Objektas, is kurio kopijuojama.
     * @return Nuoroda i esama objekta.
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
     * @brief Perkelimo priskyrimo operatorius.
     *
     * @param other Objektas, is kurio perkeliama.
     * @return Nuoroda i esama objekta.
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
     * @brief Grazina pazymiu vektoriu.
     * @return Pazymiu vektorius.
     */
    const std::vector<int> getPaz() const { return paz; }

    /**
     * @brief Grazina egzamino bala.
     * @return Egzamino balas.
     */
    int getEgzas() const { return egzas; }

    /**
     * @brief Grazina galutini bala pagal vidurki.
     * @return Galutinis balas.
     */
    double getRezVid() const { return rezVid; }

    /**
     * @brief Grazina galutini bala pagal mediana.
     * @return Galutinis balas.
     */
    double getRezMed() const { return rezMed; }

    // ======== SETTERIAI ========

    /**
     * @brief Nustato pazymiu vektoriu.
     * @param p Pazymiai.
     */
    void setPazymiai(const std::vector<int>& p) { paz = p; }

    /**
     * @brief Nustato egzamino bala.
     * @param e Egzamino balas.
     */
    void setEgzas(int e) { egzas = e; }

    /**
     * @brief Nustato galutini bala pagal vidurki.
     * @param r Reiksme.
     */
    void setRezVid(double r) { rezVid = r; }

    /**
     * @brief Nustato galutini bala pagal mediana.
     * @param r Reiksme.
     */
    void setRezMed(double r) { rezMed = r; }

    // ======== VIRTUAL FUNCTION IMPLEMENTATION ========

    /**
     * @brief Studentu informacijos spausdinimo funkcija.
     *
     * Perraso Zmogus::spausdinti().
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
     * @param s Studentas, kuriam skaiciuojami rezultatai.
     */
    friend void skaiciuokRezultatus(Studentas& s);

    /**
     * @brief Srautinis isvedimo operatorius.
     * @param os Isvedimo srautas.
     * @param s Studentas.
     * @return Tas pats srautas.
     */
    friend std::ostream& operator<<(std::ostream& os, const Studentas& s);

    /**
     * @brief Srautinis ivedimo operatorius.
     * @param is ivedimo srautas.
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
 * @brief Isveda visų studentu rezultatus lenteleje.
 * @param Grupe Studentu vektorius.
 */
void rodytiRezultatus(const std::vector<Studentas>& Grupe);

/**
 * @brief Testuoja Rule of Three/Rule of Five ir I/O veikimą.
 */
void testasRuleOfThreeIrIO();

double mediana(std::vector<int> v);
