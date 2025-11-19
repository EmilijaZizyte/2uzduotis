#include "Studentas.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <string>
#include <list>

// ------------------ Galutinio balo skaičiavimas ------------------

double Studentas::galBalas(double (*f)(std::vector<double>)) const {
    if (paz.empty()) return 0.0;

    std::vector<double> dpaz(paz.begin(), paz.end());
    double rezultatas = 0.4 * (f ? f(dpaz) : mediana(paz)) + 0.6 * egzas;
    return rezultatas;
}

// ------------------ Skaiciuoti rezultatus ------------------

void Studentas::skaiciuokRezultatus() {
    if (paz.empty()) {
        rezVid = rezMed = 0;
        return;
    }

    double suma = std::accumulate(paz.begin(), paz.end(), 0.0);
    double vid = suma / paz.size();
    rezVid = 0.4 * vid + 0.6 * egzas;
    rezMed = 0.4 * mediana(paz) + 0.6 * egzas;
}

// ------------------ Įvestis ------------------

std::istream& Studentas::readStudent(std::istream& is) {
    std::string input;

    // Vardas
    while (true) {
        std::cout << "Iveskite varda: ";
        is >> vard;
        bool valid = std::all_of(vard.begin(), vard.end(), ::isalpha);
        if (valid) break;
        std::cout << "Vardas gali tureti tik raides. Bandykite dar karta.\n";
    }

    // Pavarde
    while (true) {
        std::cout << "Iveskite pavarde: ";
        is >> pav;
        bool valid = std::all_of(pav.begin(), pav.end(), ::isalpha);
        if (valid) break;
        std::cout << "Pavarde gali tureti tik raides. Bandykite dar karta.\n";
    }

    // Namu darbu pazymiai
    paz.clear();
    std::cout << "Iveskite namu darbu pazymius (vienas per eilute, 0-10).\n"
        << "Baigti tuscia eilute (Enter):\n";

    is.ignore(10000, '\n');
    while (true) {
        getline(is, input);
        if (input.empty()) break;
        std::stringstream ss(input);
        int p;
        std::string extra;
        if (ss >> p && !(ss >> extra) && p >= 0 && p <= 10)
            paz.push_back(p);
        else
            std::cout << "Bloga ivestis! Iveskite skaiciu 0–10 arba tuscia eilute pabaigai.\n";
    }

    // Egzaminas
    while (true) {
        std::cout << "Iveskite egzamino rezultata (0-10): ";
        is >> egzas;
        if (!is.fail() && egzas >= 0 && egzas <= 10) break;

        is.clear();
        is.ignore(10000, '\n');
        std::cout << "Egzamino rezultatas turi buti tarp 0 ir 10! Bandykite dar karta.\n";
    }

    skaiciuokRezultatus();
    return is;
}

// ------------------ Median funkcija ------------------

double mediana(const std::vector<int>& v) {
    if (v.empty()) return 0.0;
    std::vector<int> t = v;
    std::sort(t.begin(), t.end());
    int n = static_cast<int>(t.size());
    return n % 2 ? t[n / 2] : (t[n / 2 - 1] + t[n / 2]) / 2.0;
}

// ------------------ Laisvoji funkcija rikiavimui ------------------

bool compare(const Studentas& a, const Studentas& b) {
    return a.getPav() < b.getPav();
}

// ------------------ Rodymas vektoriuje ------------------

void rodytiRezultatus(const std::vector<Studentas>& Grupe) {
    if (Grupe.empty()) {
        std::cout << "Sarasas tuscias.\n";
        return;
    }

    std::cout << std::left << std::setw(15) << "Vardas"
        << std::left << std::setw(15) << "Pavarde"
        << std::right << std::setw(15) << "Galutinis(Vid.)"
        << std::right << std::setw(15) << "Galutinis(Med.)" << "\n";
    std::cout << std::string(60, '-') << "\n";

    for (const auto& s : Grupe) {
        std::cout << std::left << std::setw(15) << s.getVard()
            << std::left << std::setw(15) << s.getPav()
            << std::right << std::setw(15) << std::fixed << std::setprecision(2) << s.getRezVid()
            << std::right << std::setw(15) << std::fixed << std::setprecision(2) << s.getRezMed()
            << "\n";
    }
}

// ------------------ Prideti studenta ------------------

void pridetiStudenta(std::vector<Studentas>& Grupe) {
    Studentas s;
    s.readStudent(std::cin);
    Grupe.push_back(s);
    std::cout << "Studentas pridetas sekmingai!\n";
}
void skaiciuokRezultatus(Studentas& s) {
    if (s.paz.empty()) {
        s.rezVid = s.rezMed = 0;
        return;
    }

    double suma = 0;
    for (int p : s.paz) suma += p;
    double vid = suma / s.paz.size();

    s.rezVid = 0.4 * vid + 0.6 * s.egzas;
    s.rezMed = 0.4 * mediana(s.paz) + 0.6 * s.egzas;
}
Studentas ivesk() {
    Studentas Laik;
    std::string input;
    int metode;

    std::cout << "Ar norite ivesti studenta ranka (1) ar generuoti atsitiktinai (2)? ";
    std::cin >> metode;
    std::cin.ignore(10000, '\n');

    if (metode == 2) { // atsitiktinis studentas
        int vardSkaicius = std::rand() % 100;
        int pavSkaicius = std::rand() % 100;
        Laik.vard = "vardas" + std::to_string(vardSkaicius);
        Laik.pav = "pavarde" + std::to_string(pavSkaicius);
        for (int i = 0; i < 5; i++) Laik.paz.push_back(std::rand() % 11);
        Laik.egzas = std::rand() % 11;
        std::cout << "Sugeneruotas studentas: " << Laik.vard << " " << Laik.pav << "\n";
    }
    else { // rankinė įvestis
        while (true) {
            std::cout << "Iveskite varda: ";
            std::cin >> Laik.vard;
            bool valid = all_of(Laik.vard.begin(), Laik.vard.end(), ::isalpha);
            if (valid) break;
            std::cout << "Vardas gali tureti tik raides. Bandykite dar karta\n";
        }

        while (true) {
            std::cout << "Iveskite pavarde: ";
            std::cin >> Laik.pav;
            bool valid = std::all_of(Laik.pav.begin(), Laik.pav.end(), ::isalpha);
            if (valid) break;
            std::cout << "Pavarde gali tureti tik raides. Bandykite dar karta.\n";
        }

        std::cout << "Iveskite namu darbu pazymius (vienas per eilute).\n"
            << "Baigti tuscia eilute (spauskite Enter):\n";

        std::cin.ignore();
        while (true) {
            getline(std::cin, input);
            if (input.empty()) break;

            std::stringstream ss(input);
            int m;
            std::string extra;

            if (ss >> m && !(ss >> extra) && m >= 0 && m <= 10)
                Laik.paz.push_back(m);
            else
                std::cout << "Bloga ivestis! Iveskite skaiciu 0–10 arba tuscia eilute pabaigai.\n";
        }

        while (true) {
            std::cout << "Iveskite egzamino rezultata : ";
            std::cin >> Laik.egzas;
            if (!std::cin.fail() && Laik.egzas >= 0 && Laik.egzas <= 10) break;

            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Egzamino rezultatas turi buti tarp 0 ir 10! Bandykite dar karta.\n";
        }
    }

    // ----------------- APSKAIČIUOJAME VIDURKĮ IR MEDIANĄ -----------------
    if (!Laik.paz.empty()) {
        double suma = 0;
        for (int p : Laik.paz) suma += p;
        Laik.rezVid = 0.4 * (suma / Laik.paz.size()) + 0.6 * Laik.egzas; // jei galutinis pagal 40/60
        Laik.rezMed = 0.4 * mediana(Laik.paz) + 0.6 * Laik.egzas;
    }
    else {
        Laik.rezVid = Laik.egzas;
        Laik.rezMed = Laik.egzas;
    }

    return Laik;
}
