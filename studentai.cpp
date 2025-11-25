#define _CRT_SECURE_NO_WARNINGS
#include "studentas.h"
#include <iomanip>
#include <list>
#include "failai.h"


// ===================== MEDIANA =====================
double mediana(std::vector<int> v) {
    if (v.empty()) return 0.0;

    std::sort(v.begin(), v.end());
    size_t n = v.size();

    if (n % 2 == 1) return v[n / 2];
    return (v[n / 2 - 1] + v[n / 2]) / 2.0;
}

// ===================== GALUTINIAI =====================
void skaiciuokRezultatus(Studentas& s) {
    const auto& paz = s.getPaz();
    int egzas = s.getEgzas();

    if (paz.empty()) {
        s.setRezVid(0.6 * egzas);
        s.setRezMed(0.6 * egzas);
        return;
    }

    double suma = std::accumulate(paz.begin(), paz.end(), 0.0);
    double vid = suma / paz.size();

    s.setRezVid(0.4 * vid + 0.6 * egzas);
    s.setRezMed(0.4 * mediana(paz) + 0.6 * egzas);
}

// ===================== OPERATOR >> =====================
std::istream& operator>>(std::istream& is, Studentas& s) {

    // Skaitymas iš failo (stringstream)
    if (&is != &std::cin) {
        std::string line;
        std::getline(is, line);
        if (line.empty()) return is;

        std::stringstream ss(line);
        std::string vard, pav;

        ss >> vard >> pav;
        s.setVard(vard);
        s.setPav(pav);

        int x;
        std::vector<int> temp;

        while (ss >> x) temp.push_back(x);

        if (!temp.empty()) {
            s.setEgzas(temp.back());
            temp.pop_back();
            s.setPazymiai(temp);
        }

        skaiciuokRezultatus(s);
        return is;
    }

    // Interaktyvus įvedimas
    std::string input, vard, pav;

    while (true) {
        std::cout << "Iveskite varda: ";
        is >> vard;
        if (std::all_of(vard.begin(), vard.end(), ::isalpha))
            break;
        std::cout << "Vardas gali tureti tik raides!\n";
    }
    s.setVard(vard);

    while (true) {
        std::cout << "Iveskite pavarde: ";
        is >> pav;
        if (std::all_of(pav.begin(), pav.end(), ::isalpha))
            break;
        std::cout << "Pavarde gali tureti tik raides!\n";
    }
    s.setPav(pav);

    std::vector<int> paz;
    is.ignore(10000, '\n');
    std::cout << "Iveskite pazymius vienas per eilute (enter baigti):\n";

    while (true) {
        getline(is, input);
        if (input.empty()) break;

        std::stringstream ss(input);
        int x;
        if (ss >> x && x >= 0 && x <= 10)
            paz.push_back(x);
        else
            std::cout << "Bloga ivestis. Pazymys turi buti 0-10.\n";
    }
    s.setPazymiai(paz);

    int egz;
    while (true) {
        std::cout << "Iveskite egzamino rezultata (0-10): ";
        is >> egz;

        if (!is.fail() && egz >= 0 && egz <= 10)
            break;

        is.clear();
        is.ignore(10000, '\n');
        std::cout << "Blogas egzamino ivestis!\n";
    }
    s.setEgzas(egz);

    skaiciuokRezultatus(s);
    return is;
}

// ===================== OPERATOR << =====================
std::ostream& operator<<(std::ostream& os, const Studentas& s) {
    os << std::left << std::setw(15) << s.getVard()
        << std::setw(15) << s.getPav()
        << "Galutinis (Vid.): " << std::setw(6) << std::fixed << std::setprecision(2) << s.getRezVid()
        << "  Galutinis (Med.): " << std::setw(6) << std::fixed << std::setprecision(2) << s.getRezMed();

    return os;
}

// ===================== Studento įvedimas =====================
Studentas ivesk() {
    Studentas s;
    int pasirinkimas;

    std::cout << "1 - ivesti ranka, 2 - generuoti: ";
    std::cin >> pasirinkimas;
    std::cin.ignore(10000, '\n');

    if (pasirinkimas == 2) {

        s.setVard("Vardas" + std::to_string(rand() % 100));
        s.setPav("Pavarde" + std::to_string(rand() % 100));

        std::vector<int> paz;
        for (int i = 0; i < 5; i++)
            paz.push_back(rand() % 11);

        s.setPazymiai(paz);
        s.setEgzas(rand() % 11);

        skaiciuokRezultatus(s);
        return s;
    }

    std::cin >> s;
    return s;
}

// ===================== Rezultatai =====================
void rodytiRezultatus(const std::vector<Studentas>& Grupe) {
    if (Grupe.empty()) {
        std::cout << "Nera studentu.\n";
        return;
    }

    for (const auto& s : Grupe)
        std::cout << s << "\n";
}

// ===================== Testai =====================
void testasRuleOfThreeIrIO() {
    std::cout << "\n===== Testuojame Rule of Three ir IO operatorius =====\n\n";

    // Copy konstruktorius
    std::vector<int> paz1 = { 8, 9, 10 };
    Studentas s1("Jonas", "Jonaitis", paz1, 9);
    skaiciuokRezultatus(s1);

    Studentas s2(s1);
    std::cout << "Copy konstruktoriaus testas:\n";
    std::cout << "Originalas: " << s1 << "\n";
    std::cout << "Kopija:     " << s2 << "\n\n";

    // Copy assignment
    std::vector<int> paz2 = { 6, 7, 8 };
    Studentas s3("Ona", "Onute", paz2, 10);
    skaiciuokRezultatus(s3);

    Studentas s4;
    s4 = s3;
    std::cout << "Copy assignment testas:\n";
    std::cout << "Originalas: " << s3 << "\n";
    std::cout << "Priskyrimas: " << s4 << "\n\n";

    // IO operatoriai
    std::string testInput = "Petras Petraitis 10 8 9 10";
    std::stringstream ss(testInput);

    Studentas s5;
    ss >> s5;
    skaiciuokRezultatus(s5);

    std::cout << "IO operatoriu testas:\n";
    std::cout << "Isvedimas: " << s5 << "\n";

    std::cout << "\n===== Testai baigti =====\n";
}
