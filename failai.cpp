#include "failai.h"
#include "studentas.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <list>
#include <algorithm>
#include <numeric>
#include <chrono>
#include <cstdlib>
#include <cstdio>

// Funkcija sugeneruoti testinius failus
void generuokFailus() {
    int dydziai[] = { 10, 100, 1000, 10000 };
    for (int d : dydziai) {
        std::string fname = "kursiokai_" + std::to_string(d) + ".txt";
        std::ofstream out(fname);
        if (!out) { std::cout << "Nepavyko sukurti failo " << fname << "\n"; continue; }
        out << "Vardas Pavarde ND1 ND2 ND3 ND4 ND5 Egzaminas\n";
        for (int i = 0; i < d; i++) {
            out << "V" << i << " P" << i;
            for (int j = 0; j < 5; j++) out << " " << rand() % 11;
            out << " " << rand() % 11 << "\n";
        }
        out.close();
        std::cout << "Sugeneruotas failas: " << fname << "\n";
    }
}


// ================= STRATEGIJA 1 =================
// Skaito failą eilutė po eilutės ir skirsto į du failus pagal galutinį rezultatą
Rezultatai strategija1_skaidymas(const std::string& failas) {
    Rezultatai rez{};
    std::ifstream in(failas);
    if (!in) { std::cout << "Nepavyko atidaryti failo " << failas << "\n"; return rez; }

    std::ofstream galV("galV.txt");
    std::ofstream galN("galN.txt");

    std::string eilute;
    getline(in, eilute); // praleidžiame antraštę

    auto tStart = std::chrono::high_resolution_clock::now();

    std::vector<Studentas> visiStudentai;
    std::string vard, pav;
    int nd[5], egz;
    while (in >> vard >> pav >> nd[0] >> nd[1] >> nd[2] >> nd[3] >> nd[4] >> egz) {
        Studentas s;
        s.setVard(vard);
        s.setPav(pav);
        s.setPazymiai({ nd[0], nd[1], nd[2], nd[3], nd[4] });
        s.setEgzas(egz);
        skaiciuokRezultatus(s);
        visiStudentai.push_back(s);
    }
    auto tEnd = std::chrono::high_resolution_clock::now();
    rez.readTime = std::chrono::duration<double>(tEnd - tStart).count();

    tStart = std::chrono::high_resolution_clock::now();
    for (auto& s : visiStudentai) {
        if (s.getRezVid() >= 5)
            galV << s.getVard() << " " << s.getPav() << " " << std::fixed << std::setprecision(2) << s.getRezVid() << "\n";
        else
            galN << s.getVard() << " " << s.getPav() << " " << std::fixed << std::setprecision(2) << s.getRezVid() << "\n";
    }
    tEnd = std::chrono::high_resolution_clock::now();
    rez.writeTime = std::chrono::duration<double>(tEnd - tStart).count();

    in.close();
    galV.close();
    galN.close();
    return rez;
}

// ================= STRATEGIJA 2 =================
// Naudoja list struktūrą
Rezultatai Strategija2(const std::string& failas) {
    Rezultatai rez{};
    std::ifstream in(failas);
    if (!in) { std::cout << "Nepavyko atidaryti failo " << failas << "\n"; return rez; }

    std::list<Studentas> visiStudentai;
    std::string eilute;
    getline(in, eilute); // praleidžiame antraštę

    auto tStart = std::chrono::high_resolution_clock::now();
    std::string vard, pav;
    int nd[5], egz;
    while (in >> vard >> pav >> nd[0] >> nd[1] >> nd[2] >> nd[3] >> nd[4] >> egz) {
        Studentas s;
        s.setVard(vard);
        s.setPav(pav);
        s.setPazymiai({ nd[0], nd[1], nd[2], nd[3], nd[4] });
        s.setEgzas(egz);
        skaiciuokRezultatus(s);
        visiStudentai.push_back(s);
    }
    auto tEnd = std::chrono::high_resolution_clock::now();
    rez.readTimeList = std::chrono::duration<double>(tEnd - tStart).count();

    tStart = std::chrono::high_resolution_clock::now();
    std::ofstream galV("galV_list.txt");
    std::ofstream galN("galN_list.txt");
    for (auto& s : visiStudentai) {
        if (s.getRezVid() >= 5)
            galV << s.getVard() << " " << s.getPav() << " " << std::fixed << std::setprecision(2) << s.getRezVid() << "\n";
        else
            galN << s.getVard() << " " << s.getPav() << " " << std::fixed << std::setprecision(2) << s.getRezVid() << "\n";
    }
    tEnd = std::chrono::high_resolution_clock::now();
    rez.writeTimeList = std::chrono::duration<double>(tEnd - tStart).count();

    in.close();
    galV.close();
    galN.close();
    return rez;
}

// ================= STRATEGIJA 3 =================
// Tiesiog skaitymas į vector ir rašymas į vieną failą (nebūtina skirstyti)
void Strategija3(const std::string& failas) {
    std::ifstream in(failas);
    if (!in) { std::cout << "Nepavyko atidaryti failo " << failas << "\n"; return; }

    std::vector<Studentas> visiStudentai;
    std::string eilute;
    getline(in, eilute); // praleidžiame antraštę

    std::string vard, pav;
    int nd[5], egz;
    while (in >> vard >> pav >> nd[0] >> nd[1] >> nd[2] >> nd[3] >> nd[4] >> egz) {
        Studentas s;
        s.setVard(vard);
        s.setPav(pav);
        s.setPazymiai({ nd[0], nd[1], nd[2], nd[3], nd[4] });
        s.setEgzas(egz);
        skaiciuokRezultatus(s);
        visiStudentai.push_back(s);
    }

    std::ofstream out("visi_studentai.txt");
    for (auto& s : visiStudentai) {
        out << s.getVard() << " " << s.getPav() << " "
            << std::fixed << std::setprecision(2) << s.getRezVid() << "\n";
    }
    in.close();
    out.close();
}

// ================= VECTOR STRATEGIJOS =================
Rezultatai strategija1_STL_vectoriui(const std::string& failas) {
    return strategija1_skaidymas(failas);
}

Rezultatai strategija2_STL_vectoriui(const std::string& failas) {
    Rezultatai rez{};
    std::ifstream in(failas);
    if (!in) return rez;

    std::vector<Studentas> visiStudentai;
    std::string eilute;
    getline(in, eilute);

    std::string vard, pav;
    int nd[5], egz;
    while (in >> vard >> pav >> nd[0] >> nd[1] >> nd[2] >> nd[3] >> nd[4] >> egz) {
        Studentas s;
        s.setVard(vard);
        s.setPav(pav);
        s.setPazymiai({ nd[0], nd[1], nd[2], nd[3], nd[4] });
        s.setEgzas(egz);
        skaiciuokRezultatus(s);
        visiStudentai.push_back(s);
    }

    std::ofstream galV("galV_vector.txt");
    std::ofstream galN("galN_vector.txt");
    for (auto& s : visiStudentai) {
        if (s.getRezVid() >= 5)
            galV << s.getVard() << " " << s.getPav() << " " << std::fixed << std::setprecision(2) << s.getRezVid() << "\n";
        else
            galN << s.getVard() << " " << s.getPav() << " " << std::fixed << std::setprecision(2) << s.getRezVid() << "\n";
    }

    return rez;
}

// ================= ANALIZUOTI VISUS FAILUS =================
void analizuokVisusFailusMinimaliai() {
    std::string failai[] = { "kursiokai_10.txt", "kursiokai_100.txt", "kursiokai_1000.txt", "kursiokai_10000.txt" };
    for (auto& f : failai) {
        std::cout << "Analizuojamas failas: " << f << "\n";
        Rezultatai r1 = strategija1_skaidymas(f);
        Rezultatai r2 = Strategija2(f);
        std::cout << "Vector: skaitymas " << r1.readTime << "s, rasymas " << r1.writeTime << "s\n";
        std::cout << "List: skaitymas " << r2.readTimeList << "s, rasymas " << r2.writeTimeList << "s\n";
    }
}
