#include "studentas.h"
#pragma execution_character_set("utf-8")

Studentas ivesk() {
    Studentas Laik;
    std::string input;

    while (true) {
        std::cout << "Įveskite vardą: ";
        std::cin >> Laik.vard;
        bool valid = std::all_of(Laik.vard.begin(), Laik.vard.end(), ::isalpha);
        if (valid) break;
        std::cout << "Vardas gali turėti tik raides. Bandykite dar kartą.\n";
    }

    while (true) {
        std::cout << "Įveskite pavardę: ";
        std::cin >> Laik.pav;
        bool valid = std::all_of(Laik.pav.begin(), Laik.pav.end(), ::isalpha);
        if (valid) break;
        std::cout << "Pavardė gali turėti tik raides. Bandykite dar kartą.\n";
    }

    std::cout << "Įveskite namų darbų pažymius (vienas per eilutę).\n"
              << "Baigti – tuščia eilutė (spauskite Enter):\n";

    std::cin.ignore();
    while (true) {
        std::getline(std::cin, input);
        if (input.empty()) break;

        std::stringstream ss(input);
        int m;
        std::string extra;

        if (ss >> m && !(ss >> extra) && m >= 0 && m <= 10)
            Laik.paz.push_back(m);
        else
            std::cout << "Bloga įvestis! Įveskite skaičių 0–10 arba tuščią eilutę pabaigai.\n";
    }

    while (true) {
        std::cout << "Įveskite egzamino rezultatą (0–10): ";
        std::cin >> Laik.egzas;
        if (!std::cin.fail() && Laik.egzas >= 0 && Laik.egzas <= 10) break;

        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Egzamino rezultatas turi būti tarp 0 ir 10! Bandykite dar kartą.\n";
    }

    return Laik;
}

double mediana(const std::vector<int>& v) {
    std::vector<int> t = v;
    std::sort(t.begin(), t.end());
    int n = static_cast<int>(t.size());
    if (n == 0) return 0;
    return n % 2 ? t[n / 2] : (t[n / 2 - 1] + t[n / 2]) / 2.0;
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

void pridetiStudenta(std::vector<Studentas>& Grupe) {
    Studentas Laik;
    int metode;
    std::cout << "Ar norite įvesti ranka (1) ar generuoti atsitiktinai (2)? ";
    std::cin >> metode;

    if (metode == 2) {
        int vardSkaicius = std::rand() % 100;
        int pavSkaicius = std::rand() % 100;
        Laik.vard = "vardas" + std::to_string(vardSkaicius);
        Laik.pav = "pavarde" + std::to_string(pavSkaicius);
        for (int i = 0; i < 5; i++) Laik.paz.push_back(std::rand() % 11);
        Laik.egzas = std::rand() % 11;
    } else {
        Laik = ivesk();
    }

    skaiciuokRezultatus(Laik);
    Grupe.push_back(Laik);
    std::cout << "Studentas pridėtas sėkmingai!\n";
}

void rodytiRezultatus(const std::vector<Studentas>& Grupe) {
    if (Grupe.empty()) {
        std::cout << "Sąrašas tuščias.\n";
        return;
    }

    std::cout << std::left << std::setw(15) << "Vardas"
              << std::left << std::setw(15) << "Pavarde"
              << std::right << std::setw(15) << "Galutinis(Vid.)"
              << std::right << std::setw(15) << "Galutinis(Med.)" << "\n";
    std::cout << std::string(60, '-') << "\n";

    for (const auto& s : Grupe) {
        std::cout << std::left << std::setw(15) << s.vard
                  << std::left << std::setw(15) << s.pav
                  << std::right << std::setw(15) << std::fixed << std::setprecision(2) << s.rezVid
                  << std::right << std::setw(15) << std::fixed << std::setprecision(2) << s.rezMed << "\n";
    }
}
