#include "studentas.h"
#pragma execution_character_set("utf-8")
using namespace std;

Studentas ivesk() {
    Studentas Laik;
    string input;

    
    while (true) {
        cout << "Įveskite vardą: ";
        cin >> Laik.vard;
        bool valid = all_of(Laik.vard.begin(), Laik.vard.end(), ::isalpha);
        if (valid) break;
        cout << "Vardas gali turėti tik raides. Bandykite dar kartą.\n";
    }

    
    while (true) {
        cout << "Įveskite pavardę: ";
        cin >> Laik.pav;
        bool valid = all_of(Laik.pav.begin(), Laik.pav.end(), ::isalpha);
        if (valid) break;
        cout << "Pavardė gali turėti tik raides. Bandykite dar kartą.\n";
    }

    
    cout << "Įveskite namų darbų pažymius (vienas per eilutę).\n"
        << "Baigti – tuščia eilutė (spauskite Enter):\n";

    cin.ignore();
    while (true) {
        getline(cin, input);
        if (input.empty()) break;

        stringstream ss(input);
        int m;
        string extra;

        if (ss >> m && !(ss >> extra) && m >= 0 && m <= 10)
            Laik.paz.push_back(m);
        else
            cout << "Bloga įvestis! Įveskite skaičių 0–10 arba tuščią eilutę pabaigai.\n";
    }

    
    while (true) {
        cout << "Įveskite egzamino rezultatą (0–10): ";
        cin >> Laik.egzas;
        if (!cin.fail() && Laik.egzas >= 0 && Laik.egzas <= 10) break;

        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Egzamino rezultatas turi būti tarp 0 ir 10! Bandykite dar kartą.\n";
    }

    return Laik;
}

double mediana(const vector<int>& v) {
    vector<int> t = v;
    sort(t.begin(), t.end());
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

void pridetiStudenta(vector<Studentas>& Grupe) {
    Studentas Laik;
    int metode;
    cout << "Ar norite įvesti ranka (1) ar generuoti atsitiktinai (2)? ";
    cin >> metode;

    if (metode == 2) {
        int vardSkaicius = rand() % 100;
        int pavSkaicius = rand() % 100;
        Laik.vard = "vardas" + to_string(vardSkaicius);
        Laik.pav = "pavarde" + to_string(pavSkaicius);
        for (int i = 0; i < 5; i++) Laik.paz.push_back(rand() % 11);
        Laik.egzas = rand() % 11;
    }
    else {
        Laik = ivesk();
    }

    skaiciuokRezultatus(Laik);
    Grupe.push_back(Laik);
    cout << "Studentas pridėtas sėkmingai!\n";
}

void rodytiRezultatus(const vector<Studentas>& Grupe) {
    if (Grupe.empty()) {
        cout << "Sąrašas tuščias.\n";
        return;
    }

    cout << left << setw(15) << "Vardas"
        << left << setw(15) << "Pavarde"
        << right << setw(15) << "Galutinis(Vid.)"
        << right << setw(15) << "Galutinis(Med.)" << "\n";
    cout << string(60, '-') << "\n";

    for (const auto& s : Grupe) {
        cout << left << setw(15) << s.vard
            << left << setw(15) << s.pav
            << right << setw(15) << fixed << setprecision(2) << s.rezVid
            << right << setw(15) << fixed << setprecision(2) << s.rezMed << "\n";
    }
}
