#define _CRT_SECURE_NO_WARNINGS
#include "failai.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <chrono>
void generuokFailus() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    std::string failoVardas;
    int kiek;
    std::cout << "Iveskite failo pavadinima: ";
    std::cin >> failoVardas;
    std::cout << "Kiek studentu generuoti? ";
    std::cin >> kiek;

    std::ofstream out(failoVardas);
    if (!out) {
        std::cout << "Nepavyko sukurti failo!\n";
        return;
    }

    // Header
    out << std::left << std::setw(15) << "Vardas"
        << std::setw(15) << "Pavarde"
        << "ND1 ND2 ND3 ND4 ND5 Egzaminas\n";

    for (int i = 0; i < kiek; ++i) {
        std::string vard = "vardas" + std::to_string(rand() % 1000);
        std::string pav = "pavarde" + std::to_string(rand() % 1000);

        out << std::left << std::setw(15) << vard
            << std::setw(15) << pav;

        for (int j = 0; j < 5; ++j) out << rand() % 11 << " "; // ND
        out << rand() % 11 << "\n"; // Egzaminas
    }

    out.close();
    std::cout << "Failas '" << failoVardas << "' sugeneruotas su " << kiek << " studentu.\n";
}
void skaiciuokRezultatusFailui(Studentas& s) {
    if (s.paz.empty()) { s.rezVid = s.rezMed = 0; return; }
    double suma = std::accumulate(s.paz.begin(), s.paz.end(), 0.0);
    double vid = suma / s.paz.size();
    s.rezVid = 0.4 * vid + 0.6 * s.egzas;
    s.rezMed = 0.4 * mediana(s.paz) + 0.6 * s.egzas;
}

void testuokStrategijas() {
    using namespace std;

    int rezPasirinkimas;
    cout << "\nKokius rezultatus spausdinti?\n1 - Vidurkis\n2 - Mediana\n3 - Abu\nPasirinkimas: ";
    cin >> rezPasirinkimas;

    int rikiavimas;
    cout << "\nRikiavimas:\n1 - Vardas\n2 - Pavarde\n3 - Vidurkis ↑\n4 - Vidurkis ↓\n5 - Mediana ↑\n6 - Mediana ↓\nPasirinkimas: ";
    cin >> rikiavimas;

    int strategija;
    cout << "\nStrategija:\n1 - Pirma\n2 - Antra\n3 - Palyginti abi\nPasirinkimas: ";
    cin >> strategija;

    string failas;
    cout << "Failo pavadinimas: ";
    cin >> failas;

    ifstream in(failas);
    if (!in) {
        cout << "Nepavyko atidaryti failo!\n";
        return;
    }

    vector<Studentas> visiV;
    list<Studentas> visiL;
    string eil;
    int line = 0;

    while (getline(in, eil)) {
        line++;
        if (line <= 2) continue;

        stringstream ss(eil);
        Studentas s;
        s.paz.resize(5);
        ss >> s.vard >> s.pav;
        for (int i = 0; i < 5; i++) ss >> s.paz[i];
        ss >> s.egzas;
        skaiciuokRezultatusFailui(s);

        visiV.push_back(s);
        visiL.push_back(s);
    }

    auto cmp = [&](const Studentas& a, const Studentas& b) -> bool {
        switch (rikiavimas) {
        case 1: return a.vard < b.vard;
        case 2: return a.pav < b.pav;
        case 3: return a.rezVid < b.rezVid;
        case 4: return a.rezVid > b.rezVid;
        case 5: return a.rezMed < b.rezMed;
        case 6: return a.rezMed > b.rezMed;
        default: return a.vard < b.vard;
        }
        };

    auto paleisti = [&](int stratID, double& vecTime, double& listTime, bool useSTL = false) {
        vector<Studentas> v = visiV;
        list<Studentas> l = visiL;
        vector<Studentas> kietiV, vargsiV;
        list<Studentas> kietiL, vargsiL;

        auto tStart = chrono::high_resolution_clock::now();

        if (!useSTL) {
            if (stratID == 1) {
                for (auto& s : v) (s.rezVid >= 5 && s.rezMed >= 5 ? kietiV : vargsiV).push_back(s);
                for (auto& s : l) (s.rezVid >= 5 && s.rezMed >= 5 ? kietiL : vargsiL).push_back(s);
            }
            else {
                for (auto& s : v) if (s.rezVid < 5 || s.rezMed < 5) vargsiV.push_back(s);
                v.erase(remove_if(v.begin(), v.end(), [](const Studentas& s) { return s.rezVid < 5 || s.rezMed < 5; }), v.end());
                kietiV = v;

                for (auto it = l.begin(); it != l.end();) {
                    if (it->rezVid < 5 || it->rezMed < 5) { vargsiL.push_back(*it); it = l.erase(it); }
                    else ++it;
                }
                kietiL = l;
            }
        }
        else {
            copy_if(v.begin(), v.end(), back_inserter(kietiV), [](const Studentas& s) { return s.rezVid >= 5 && s.rezMed >= 5; });
            copy_if(v.begin(), v.end(), back_inserter(vargsiV), [](const Studentas& s) { return s.rezVid < 5 || s.rezMed < 5; });
            copy_if(l.begin(), l.end(), back_inserter(kietiL), [](const Studentas& s) { return s.rezVid >= 5 && s.rezMed >= 5; });
            copy_if(l.begin(), l.end(), back_inserter(vargsiL), [](const Studentas& s) { return s.rezVid < 5 || s.rezMed < 5; });
        }

        auto tEnd = chrono::high_resolution_clock::now();
        vecTime = chrono::duration<double>(tEnd - tStart).count();
        listTime = vecTime;

        tStart = chrono::high_resolution_clock::now();
        sort(kietiV.begin(), kietiV.end(), cmp);
        sort(vargsiV.begin(), vargsiV.end(), cmp);
        kietiL.sort(cmp);
        vargsiL.sort(cmp);
        tEnd = chrono::high_resolution_clock::now();
        vecTime += chrono::duration<double>(tEnd - tStart).count();
        listTime += chrono::duration<double>(tEnd - tStart).count();

        return make_pair(vecTime, listTime);
        };

    if (strategija == 1 || strategija == 2) {
        double v, l;
        auto times = paleisti(strategija, v, l);
        cout << "\nVECTOR: " << times.first << " s\nLIST: " << times.second << " s\n";
        return;
    }

    double v1 = 0, l1 = 0, v2 = 0, l2 = 0;

    cout << "--- 1 strategija ---\n";
    tie(v1, l1) = paleisti(1, v1, l1);
    cout << "VECTOR: " << v1 << " s\nLIST: " << l1 << " s\n";

    cout << "--- 2 strategija ---\n";
    tie(v2, l2) = paleisti(2, v2, l2);
    cout << "VECTOR: " << v2 << " s\nLIST:   " << l2 << " s\n";

    cout << "\nGreitesnė strategija VECTOR: " << (v1 < v2 ? "1" : "2") << "\n";
    cout << "Greitesnė strategija LIST: " << (l1 < l2 ? "1" : "2") << "\n";

    // Antras paleidimas su STL algoritmais
    cout << "\n--- Antras paleidimas su STL algoritmais ---\n";

    double vSTL = 0, lSTL = 0;
    if (v1 < v2) tie(vSTL, ignore) = paleisti(1, vSTL, lSTL, true);
    else tie(vSTL, ignore) = paleisti(2, vSTL, lSTL, true);

    double lSTLTime = 0;
    if (l1 < l2) tie(ignore, lSTLTime) = paleisti(1, vSTL, lSTLTime, true);
    else tie(ignore, lSTLTime) = paleisti(2, vSTL, lSTLTime, true);

    cout << "\nVECTOR (STL): " << vSTL << " s, greičiau nei be STL? " << (vSTL < min(v1, v2) ? "Taip" : "Ne") << "\n";
    cout << "LIST (STL): " << lSTLTime << " s, greičiau nei be STL? " << (lSTLTime < min(l1, l2) ? "Taip" : "Ne") << "\n";
}






void analizuokVisusFailusMinimaliai() {
    int rezPasirinkimas;
    std::cout << "\nKokius rezultatus spausdinti i failus?\n"
        << "1 - Tik vidurki\n2 - Tik mediana\n3 - Abu\nPasirinkimas: ";
    std::cin >> rezPasirinkimas;

    int rikiavimas;
    std::cout << "Pagal ka rikiuoti galutinius rezultatus?\n"
        << "1 - Vardas (A-Z)\n"
        << "2 - Pavarde (A-Z)\n"
        << "3 - Vidurkis didejimo tvarka\n"
        << "4 - Vidurkis mazejimo tvarka\n"
        << "5 - Mediana didejimo tvarka\n"
        << "6 - Mediana mazejimo tvarka\n"
        << "Pasirinkimas: ";
    std::cin >> rikiavimas;

    // --- Vartotojas įveda failą ---
    std::string failas;
    std::cout << "\nIveskite failo pavadinima: ";
    std::cin >> failas;

    std::cout << "\n=== Apdorojamas failas: " << failas << " ===\n";

    FILE* open_f = fopen(failas.c_str(), "r");
    if (!open_f) {
        std::cout << "Nepavyko atidaryti failo!\n";
        return;
    }

    std::string base = failas.substr(0, failas.find(".txt"));

    std::vector<Studentas> visiStudentai;
    visiStudentai.reserve(10'000'000);
    std::list<Studentas> visiStudentaiL;

    char eil_r[500];
    int lineCounter = 0;

    double readTimeV = 0, calcTimeV = 0, writeTimeV = 0;

    // --- Vector skaitymas ir apdorojimas ---
    while (fgets(eil_r, sizeof(eil_r), open_f) != nullptr) {
        lineCounter++;
        if (lineCounter <= 2) continue;

        auto t1 = std::chrono::high_resolution_clock::now();
        std::stringstream ss(eil_r);
        Studentas s;
        ss >> s.vard >> s.pav;
        for (int i = 0; i < 5; i++) { int x; ss >> x; s.paz.push_back(x); }
        ss >> s.egzas;
        auto t2 = std::chrono::high_resolution_clock::now();
        readTimeV += std::chrono::duration<double>(t2 - t1).count();

        auto t3 = std::chrono::high_resolution_clock::now();
        skaiciuokRezultatus(s);
        auto t4 = std::chrono::high_resolution_clock::now();
        calcTimeV += std::chrono::duration<double>(t4 - t3).count();

        visiStudentai.push_back(s);
    }
    fclose(open_f);

    std::cout << "Vector: Nuskaityta " << visiStudentai.size() << " studentu\n";

    // --- Skirstymas į protingus ir kvailius ---
    std::vector<Studentas> protingiV, kvailiV;
    protingiV.reserve(visiStudentai.size());
    kvailiV.reserve(visiStudentai.size());

    for (auto& s : visiStudentai) {
        if (s.rezVid >= 5 && s.rezMed >= 5) protingiV.push_back(s);
        else kvailiV.push_back(s);
    }

    auto rikiuokV = [&](std::vector<Studentas>& v) {
        switch (rikiavimas) {
        case 1: std::sort(v.begin(), v.end(), [](auto& a, auto& b) {return a.vard < b.vard; }); break;
        case 2: std::sort(v.begin(), v.end(), [](auto& a, auto& b) {return a.pav < b.pav; }); break;
        case 3: std::sort(v.begin(), v.end(), [](auto& a, auto& b) {return a.rezVid < b.rezVid; }); break;
        case 4: std::sort(v.begin(), v.end(), [](auto& a, auto& b) {return a.rezVid > b.rezVid; }); break;
        case 5: std::sort(v.begin(), v.end(), [](auto& a, auto& b) {return a.rezMed < b.rezMed; }); break;
        case 6: std::sort(v.begin(), v.end(), [](auto& a, auto& b) {return a.rezMed > b.rezMed; }); break;
        }
        };
    rikiuokV(protingiV);
    rikiuokV(kvailiV);


    std::string proNameVector = base + "_protinguliai_vector.txt";
    std::string kvaNameVector = base + "_kvailiukai_vector.txt";
    std::ofstream outProV(proNameVector), outKvaV(kvaNameVector);

    auto writeV = [&](std::ofstream& out, const std::vector<Studentas>& v, const std::string& fname) {
        double writeTime = 0;
        for (auto& s : v) {
            auto t1 = std::chrono::high_resolution_clock::now();
            out << std::left << std::setw(15) << s.vard
                << std::setw(15) << s.pav;
            if (rezPasirinkimas == 1) out << std::setw(15) << s.rezVid;
            else if (rezPasirinkimas == 2) out << std::setw(15) << s.rezMed;
            else out << std::setw(15) << s.rezVid << std::setw(15) << s.rezMed;
            out << "\n";
            auto t2 = std::chrono::high_resolution_clock::now();
            writeTime += std::chrono::duration<double>(t2 - t1).count();
        }
        std::cout << "Failas irasytas: " << fname << " (rasymo laikas: " << writeTime << " s)\n";
        return writeTime;
        };

    writeTimeV += writeV(outProV, protingiV, proNameVector);
    writeTimeV += writeV(outKvaV, kvailiV, kvaNameVector);
    outProV.close(); outKvaV.close();

    std::cout << "Vector rezultatai:\n";
    std::cout << "  Skaitymas: " << readTimeV << " s\n";
    std::cout << "  Skaiciavimas: " << calcTimeV << " s\n";
    std::cout << "  Rasymas: " << writeTimeV << " s\n";


    FILE* open_f2 = fopen(failas.c_str(), "r");
    if (!open_f2) {
        std::cout << "Nepavyko atidaryti failo antram skaitymui (list)!\n";
        return;
    }

    double readTimeL = 0, calcTimeL = 0, writeTimeL = 0;
    lineCounter = 0;

    while (fgets(eil_r, sizeof(eil_r), open_f2) != nullptr) {
        lineCounter++;
        if (lineCounter <= 2) continue;

        auto t1 = std::chrono::high_resolution_clock::now();
        std::stringstream ss(eil_r);
        Studentas s;
        ss >> s.vard >> s.pav;
        for (int i = 0; i < 5; i++) { int x; ss >> x; s.paz.push_back(x); }
        ss >> s.egzas;
        auto t2 = std::chrono::high_resolution_clock::now();
        readTimeL += std::chrono::duration<double>(t2 - t1).count();

        auto t3 = std::chrono::high_resolution_clock::now();
        skaiciuokRezultatus(s);
        auto t4 = std::chrono::high_resolution_clock::now();
        calcTimeL += std::chrono::duration<double>(t4 - t3).count();

        visiStudentaiL.push_back(s);
    }
    fclose(open_f2);

    std::list<Studentas> protingiL, kvailiL;
    for (auto& s : visiStudentaiL) {
        if (s.rezVid >= 5 && s.rezMed >= 5) protingiL.push_back(s);
        else kvailiL.push_back(s);
    }

    auto rikiuokL = [&](std::list<Studentas>& l) {
        switch (rikiavimas) {
        case 1: l.sort([](auto& a, auto& b) {return a.vard < b.vard; }); break;
        case 2: l.sort([](auto& a, auto& b) {return a.pav < b.pav; }); break;
        case 3: l.sort([](auto& a, auto& b) {return a.rezVid < b.rezVid; }); break;
        case 4: l.sort([](auto& a, auto& b) {return a.rezVid > b.rezVid; }); break;
        case 5: l.sort([](auto& a, auto& b) {return a.rezMed < b.rezMed; }); break;
        case 6: l.sort([](auto& a, auto& b) {return a.rezMed > b.rezMed; }); break;
        }
        };
    rikiuokL(protingiL);
    rikiuokL(kvailiL);

    std::string proNameList = base + "_protinguliai_list.txt";
    std::string kvaNameList = base + "_kvailiukai_list.txt";
    std::ofstream outProL(proNameList), outKvaL(kvaNameList);

    auto writeL = [&](std::ofstream& out, const std::list<Studentas>& l, const std::string& fname) {
        double writeTime = 0;
        for (auto& s : l) {
            auto t1 = std::chrono::high_resolution_clock::now();
            out << std::left << std::setw(15) << s.vard
                << std::setw(15) << s.pav;
            if (rezPasirinkimas == 1) out << std::setw(15) << s.rezVid;
            else if (rezPasirinkimas == 2) out << std::setw(15) << s.rezMed;
            else out << std::setw(15) << s.rezVid << std::setw(15) << s.rezMed;
            out << "\n";
            auto t2 = std::chrono::high_resolution_clock::now();
            writeTime += std::chrono::duration<double>(t2 - t1).count();
        }
        std::cout << "Failas irasytas: " << fname << " (rasymo laikas: " << writeTime << " s)\n";
        return writeTime;
        };

    writeTimeL += writeL(outProL, protingiL, proNameList);
    writeTimeL += writeL(outKvaL, kvailiL, kvaNameList);
    outProL.close(); outKvaL.close();

    std::cout << "List rezultatai:\n";
    std::cout << "  Skaitymas: " << readTimeL << " s\n";
    std::cout << "  Skaiciavimas: " << calcTimeL << " s\n";
    std::cout << "  Rasymas: " << writeTimeL << " s\n";
}
