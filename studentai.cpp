#include "studentas.h"
#pragma execution_character_set("utf-8")
#include <ctime>
#include <list>
#include <sstream>
#include <algorithm>

double mediana(const std::vector<int>& v) {
    std::vector<int> t = v;
    std::sort(t.begin(), t.end());
    int n = static_cast<int>(t.size());
    if (n == 0) return 0;
    return n % 2 ? t[n / 2] : (t[n / 2 - 1] + t[n / 2]) / 2.0;
}

// ================= Skaiciuoti rezultatus =================
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

// ================= Operatoriai =================
std::istream& operator>>(std::istream& is, Studentas& s) {
    std::string input;

    // Vardas
    while (true) {
        std::cout << "Iveskite varda: ";
        is >> s.vard;
        if (std::all_of(s.vard.begin(), s.vard.end(), ::isalpha)) break;
        std::cout << "Vardas gali tureti tik raides. Bandykite dar karta.\n";
    }

    // Pavarde
    while (true) {
        std::cout << "Iveskite pavarde: ";
        is >> s.pav;
        if (std::all_of(s.pav.begin(), s.pav.end(), ::isalpha)) break;
        std::cout << "Pavarde gali tureti tik raides. Bandykite dar karta.\n";
    }

    // Namu darbu pazymiai
    s.paz.clear();
    std::cout << "Iveskite namu darbu pazymius (vienas per eilute, 0-10).\n"
        "Baigti tuscia eilute (Enter):\n";

    is.ignore(10000, '\n'); // kad suvalgytu newline po pavardės
    while (true) {
        getline(is, input);
        if (input.empty()) break;

        std::stringstream ss(input);
        int p;
        std::string extra;
        if (ss >> p && !(ss >> extra) && p >= 0 && p <= 10)
            s.paz.push_back(p);
        else
            std::cout << "Bloga ivestis! Iveskite skaiciu 0–10 arba tuscia eilute pabaigai.\n";
    }

    // Egzaminas
    while (true) {
        std::cout << "Iveskite egzamino rezultata (0-10): ";
        is >> s.egzas;
        if (!is.fail() && s.egzas >= 0 && s.egzas <= 10) break;

        is.clear();
        is.ignore(10000, '\n');
        std::cout << "Egzamino rezultatas turi buti tarp 0 ir 10! Bandykite dar karta.\n";
    }

    // Apskaiciuojame rezultatus
    skaiciuokRezultatus(s);

    return is;
}

std::ostream& operator<<(std::ostream& os, const Studentas& s) {
    os << std::left << std::setw(15) << s.vard
        << std::left << std::setw(15) << s.pav
        << "| Pažymiai: ";
    for (int p : s.paz) os << p << " ";
    os << "| Egzaminas: " << s.egzas
        << " | Vidurkis: " << std::fixed << std::setprecision(2) << s.rezVid
        << " | Mediana: " << std::fixed << std::setprecision(2) << s.rezMed;
    return os;
}


// ======== Studento įvedimas ========
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
        std::cin >> Laik;
    }

    skaiciuokRezultatus(Laik);
    return Laik;
}

// ======== Pridėti studentą į kolekcijas ========
void pridetiStudenta(std::vector<Studentas>& Grupe) {
    Studentas Laik = ivesk();
    Grupe.push_back(Laik);
    std::cout << "Studentas pridetas sekmingai! Adresas vektoriuje: "
        << &Grupe.back() << "\n";
}

void pridetiStudenta(std::list<Studentas>& Grupe) {
    Studentas Laik = ivesk();
    Grupe.push_back(Laik);
    std::cout << "Studentas pridetas sekmingai! Adresas liste: "
        << &Grupe.back() << "\n";
}

// ======== Rezultatų atvaizdavimas ========
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
        std::cout << s.vard << " " << s.pav
            << std::right << std::setw(15) << std::fixed << std::setprecision(2) << s.rezVid
            << std::right << std::setw(15) << std::fixed << std::setprecision(2) << s.rezMed
            << "\n";
    }
}
