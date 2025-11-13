#include "studentas.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <ctime>


Studentas ivesk() {
    Studentas Laik;
    std::string input;
    int metode;
    std::cout << "Ar norite ivesti studenta ranka (1) ar generuoti atsitiktinai (2)? ";
    std::cin >> metode;
    std::cin.ignore(10000, '\n');

    if (metode == 2) {
        int vardSkaicius = std::rand() % 100;
        int pavSkaicius = std::rand() % 100;
        Laik.setVard("vardas" + std::to_string(vardSkaicius));
        Laik.setPav("pavarde" + std::to_string(pavSkaicius));
        std::vector<int> nd;
        for (int i = 0; i < 5; i++) nd.push_back(std::rand() % 11);
        Laik.setPazymiai(nd);
        Laik.setEgzas(std::rand() % 11);
        std::cout << "Sugeneruotas studentas: " << Laik.getVard() << " " << Laik.getPav() << "\n";
    }
    else {
        while (true) {
            std::cout << "Iveskite varda: ";
            std::cin >> input;
            bool valid = std::all_of(input.begin(), input.end(), ::isalpha);
            if (valid) { Laik.setVard(input); break; }
            std::cout << "Vardas gali tureti tik raides. Bandykite dar karta.\n";
        }
        while (true) {
            std::cout << "Iveskite pavarde: ";
            std::cin >> input;
            bool valid = std::all_of(input.begin(), input.end(), ::isalpha);
            if (valid) { Laik.setPav(input); break; }
            std::cout << "Pavarde gali tureti tik raides. Bandykite dar karta.\n";
        }
        std::vector<int> nd;
        std::cout << "Iveskite namu darbu pazymius (vienas per eilute). Baigti tuscia eilute (Enter):\n";
        std::cin.ignore();
        while (true) {
            getline(std::cin, input);
            if (input.empty()) break;
            std::stringstream ss(input);
            int m;
            std::string extra;
            if (ss >> m && !(ss >> extra) && m >= 0 && m <= 10)
                nd.push_back(m);
            else
                std::cout << "Bloga ivestis! Iveskite skaiciu 0–10 arba tuscia eilute pabaigai.\n";
        }
        Laik.setPazymiai(nd);
        while (true) {
            std::cout << "Iveskite egzamino rezultata : ";
            int egz;
            std::cin >> egz;
            if (!std::cin.fail() && egz >= 0 && egz <= 10) { Laik.setEgzas(egz); break; }
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Egzamino rezultatas turi buti tarp 0 ir 10! Bandykite dar karta.\n";
        }
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
    auto paz = s.getPaz();
    if (paz.empty()) { s.setRezVid(0); s.setRezMed(0); return; }
    double suma = std::accumulate(paz.begin(), paz.end(), 0);
    double vid = suma / paz.size();
    s.setRezVid(0.4 * vid + 0.6 * s.getEgzas());
    s.setRezMed(0.4 * mediana(paz) + 0.6 * s.getEgzas());
}
