#include "studentas.h"
#include <iomanip>
#include <list>

// ======== MEDIANA ========
double mediana(std::vector<int> v) {
    if (v.empty()) return 0.0;

    std::sort(v.begin(), v.end());
    size_t n = v.size();

    if (n % 2 == 1) return v[n / 2];
    return (v[n / 2 - 1] + v[n / 2]) / 2.0;
}

// ======== GALUTINIŲ SKAIČIAVIMAS ========
void skaiciuokRezultatus(Studentas& s) {
    if (s.paz.empty()) {
        s.rezVid = s.rezMed = 0.6 * s.egzas;
        return;
    }

    double suma = std::accumulate(s.paz.begin(), s.paz.end(), 0.0);
    double vid = suma / s.paz.size();

    s.rezVid = 0.4 * vid + 0.6 * s.egzas;
    s.rezMed = 0.4 * mediana(s.paz) + 0.6 * s.egzas;
}

// ======== OPERATORIUS >> (ĮVESTIS) ========
std::istream& operator>>(std::istream& is, Studentas& s) {
    std::string input;

    // ---- Vardas ----
    while (true) {
        std::cout << "Iveskite varda: ";
        is >> s.vard;

        if (std::all_of(s.vard.begin(), s.vard.end(), ::isalpha))
            break;

        std::cout << "Vardas gali tureti tik raides!\n";
    }

    // ---- Pavardė ----
    while (true) {
        std::cout << "Iveskite pavarde: ";
        is >> s.pav;

        if (std::all_of(s.pav.begin(), s.pav.end(), ::isalpha))
            break;

        std::cout << "Pavarde gali tureti tik raides!\n";
    }

    // ---- Pažymiai ----
    s.paz.clear();
    is.ignore(10000, '\n');
    std::cout << "Iveskite pazymius vienas per eilute (tuscia eilute - baigti):\n";

    while (true) {
        getline(is, input);
        if (input.empty()) break;

        std::stringstream ss(input);
        int x;
        if (ss >> x && x >= 0 && x <= 10)
            s.paz.push_back(x);
        else
            std::cout << "Bloga ivestis. Pazymys turi buti 0–10.\n";
    }

    // ---- Egzaminas ----
    while (true) {
        std::cout << "Iveskite egzamino rezultata (0–10): ";
        is >> s.egzas;

        if (!is.fail() && s.egzas >= 0 && s.egzas <= 10)
            break;

        is.clear();
        is.ignore(10000, '\n');
        std::cout << "Blogas egzamino ivestis!\n";
    }

    skaiciuokRezultatus(s);
    return is;
}

// ======== OPERATORIUS << (IŠVESTIS) ========
std::ostream& operator<<(std::ostream& os, const Studentas& s) {
    os << std::left << std::setw(15) << s.vard
        << std::setw(15) << s.pav
        << "Galutinis (Vid.): " << std::setw(6) << std::fixed << std::setprecision(2) << s.rezVid
        << "  Galutinis (Med.): " << std::setw(6) << std::fixed << std::setprecision(2) << s.rezMed;

    return os;
}

// ======== Studento įvedimas ========
Studentas ivesk() {
    Studentas s;
    int mode;

    std::cout << "1 – ivesti ranka, 2 – generuoti: ";
    std::cin >> mode;
    std::cin.ignore(10000, '\n');

    if (mode == 2) {
        s.vard = "Vardas" + std::to_string(rand() % 100);
        s.pav = "Pavarde" + std::to_string(rand() % 100);

        for (int i = 0; i < 5; i++)
            s.paz.push_back(rand() % 11);

        s.egzas = rand() % 11;

        skaiciuokRezultatus(s);

        std::cout << "Sugeneruotas studentas: " << s << "\n";
        return s;
    }

    std::cin >> s;
    return s;
}

// ======== Rezultatų rodymas ========
void rodytiRezultatus(const std::vector<Studentas>& Grupe) {
    if (Grupe.empty()) {
        std::cout << "Nera studentu.\n";
        return;
    }

    for (auto& s : Grupe)
        std::cout << s << "\n";
}
