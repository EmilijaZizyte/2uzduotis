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

    // ======== SKAITYMAS (stringstream, failai) ========
    if (&is != &std::cin) {
        s.paz.clear();
        std::string line;
        std::getline(is, line);
        if (line.empty()) return is;

        std::stringstream ss(line);
        ss >> s.vard >> s.pav;

        int x;
        std::vector<int> temp;

        while (ss >> x) temp.push_back(x);

        if (!temp.empty()) {
            s.egzas = temp.back();
            temp.pop_back();
            s.paz = temp;
        }

        skaiciuokRezultatus(s);
        return is;
    }

    // ======== INTERAKTYVUS ĮVEDIMAS (cin) ========

    std::string input;
    while (true) {
        std::cout << "Iveskite varda: ";
        is >> s.vard;

        if (std::all_of(s.vard.begin(), s.vard.end(), ::isalpha))
            break;

        std::cout << "Vardas gali tureti tik raides!\n";
    }
    while (true) {
        std::cout << "Iveskite pavarde: ";
        is >> s.pav;

        if (std::all_of(s.pav.begin(), s.pav.end(), ::isalpha))
            break;

        std::cout << "Pavarde gali tureti tik raides!\n";
    }
    s.paz.clear();
    is.ignore(10000, '\n');
    std::cout << "Iveskite pazymius vienas per eilute (enter baigti):\n";

    while (true) {
        getline(is, input);
        if (input.empty()) break;

        std::stringstream ss(input);
        int x;
        if (ss >> x && x >= 0 && x <= 10)
            s.paz.push_back(x);
        else
            std::cout << "Bloga ivestis. Pazymys turi buti 0-10.\n";
    }

    while (true) {
        std::cout << "Iveskite egzamino rezultata (0-10): ";
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
    int pasirinkimas;

    std::cout << "1 - ivesti ranka, 2 - generuoti: ";
    std::cin >> pasirinkimas;
    std::cin.ignore(10000, '\n');

    if (pasirinkimas == 2) {
        s.vard = "Vardas" + std::to_string(rand() % 100);
        s.pav = "Pavarde" + std::to_string(rand() % 100);

        for (int i = 0; i < 5; i++)
            s.paz.push_back(rand() % 11);

        s.egzas = rand() % 11;

        skaiciuokRezultatus(s);

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





void testasRuleOfThreeIrIO() {
    std::cout << "\n===== Testuojame Rule of Three ir IO operatorius =====\n\n";

    // ---- Copy konstruktoriaus testas ----
    std::vector<int> paz1 = { 8, 9, 10 };
    Studentas s1("Jonas", "Jonaitis", paz1, 9);
    skaiciuokRezultatus(s1);

    Studentas s2(s1); // copy konstruktorius
    std::cout << "Copy konstruktoriaus testas:\n";
    std::cout << "Originalas: " << s1 << "\n";
    std::cout << "Kopija:     " << s2 << "\n\n";

    // ---- Copy assignment testas ----
    std::vector<int> paz2 = { 6, 7, 8 };
    Studentas s3("Ona", "Onute", paz2, 10);
    skaiciuokRezultatus(s3);

    Studentas s4;
    s4 = s3; // copy assignment
    std::cout << "Copy assignment testas:\n";
    std::cout << "Originalas: " << s3 << "\n";
    std::cout << "Priskyrimas: " << s4 << "\n\n";

    // ---- IO operatorių testas ----
    // Naudojame stringstream, kad nebūtų laukimo įvedimo
    std::string testInput = "Petras Petraitis 10 8 9 10";
    std::stringstream ss(testInput);

    Studentas s5;
    ss >> s5; // operator>>
    skaiciuokRezultatus(s5);

    std::cout << "IO operatoriu testas:\n";
    std::cout << "Isvedimas: " << s5 << "\n";

    std::cout << "\n===== Testai baigti =====\n";
}

