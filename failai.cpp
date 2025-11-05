#define _CRT_SECURE_NO_WARNINGS
#include "studentas.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <chrono>
#include <numeric> // accumulate


void skaiciuokRezultatusFailui(Studentas& s) {
    skaiciuokRezultatus(s);
}


void strategija1_skaidymas() {
    std::string failas;
    std::cout << "Iveskite failo pavadinima: ";
    std::cin >> failas;

    FILE* open_f = fopen(failas.c_str(), "r");
    if (!open_f) {
        std::cout << "Nepavyko atidaryti failo!\n";
        return;
    }

    std::string base = failas.substr(0, failas.find(".txt"));
    char eil_r[500];
    int lineCounter = 0;
    
    // === VECTOR VERSIJA ============
    auto tReadStartV = std::chrono::high_resolution_clock::now();

    std::vector<Studentas> visiStudentai;
    visiStudentai.reserve(10'000'000);

    while (fgets(eil_r, sizeof(eil_r), open_f) != nullptr) {
        lineCounter++;
        if (lineCounter <= 2) continue;

        std::stringstream ss(eil_r);
        Studentas s;
        ss >> s.vard >> s.pav;
        for (int i = 0; i < 5; i++) { int x; ss >> x; s.paz.push_back(x); }
        ss >> s.egzas;
        skaiciuokRezultatus(s);
        visiStudentai.push_back(s);
    }
    fclose(open_f);

    auto tReadEndV = std::chrono::high_resolution_clock::now();
    double readTimeV = std::chrono::duration<double>(tReadEndV - tReadStartV).count();

    // --- Skaidymas (kopijavimas į du konteinerius) ---
    auto tSplitStartV = std::chrono::high_resolution_clock::now();

    std::vector<Studentas> kietiakaiV;
    std::vector<Studentas> vargsiukaiV;
    kietiakaiV.reserve(visiStudentai.size());
    vargsiukaiV.reserve(visiStudentai.size());

    for (const auto& s : visiStudentai) {
        if (s.rezVid >= 5 && s.rezMed >= 5)
            kietiakaiV.push_back(s);
        else
            vargsiukaiV.push_back(s);
    }

    auto tSplitEndV = std::chrono::high_resolution_clock::now();
    double splitTimeV = std::chrono::duration<double>(tSplitEndV - tSplitStartV).count();

    // --- Rašymas į failus ---
    auto tWriteStartV = std::chrono::high_resolution_clock::now();

    std::ofstream outKiet(base + "_kietiakai_vector.txt");
    std::ofstream outVarg(base + "_vargsiukai_vector.txt");

    for (auto& s : kietiakaiV)
        outKiet << std::left << std::setw(15) << s.vard
        << std::setw(15) << s.pav
        << std::setw(10) << s.rezVid
        << std::setw(10) << s.rezMed << "\n";

    for (auto& s : vargsiukaiV)
        outVarg << std::left << std::setw(15) << s.vard
        << std::setw(15) << s.pav
        << std::setw(10) << s.rezVid
        << std::setw(10) << s.rezMed << "\n";

    outKiet.close();
    outVarg.close();

    auto tWriteEndV = std::chrono::high_resolution_clock::now();
    double writeTimeV = std::chrono::duration<double>(tWriteEndV - tWriteStartV).count();

    // --- Atminties skaičiavimas (apytiksliai MB) ---
    auto bytesV = sizeof(Studentas) * visiStudentai.size() +
        sizeof(Studentas) * (kietiakaiV.size() + vargsiukaiV.size());
    double memMB_V = bytesV / (1024.0 * 1024.0);

    std::cout << "\n=== VECTOR STRATEGIJA 1 ===\n";
    std::cout << "  Studentu viso: " << visiStudentai.size() << "\n";
    std::cout << "  Kietiakai:     " << kietiakaiV.size() << "\n";
    std::cout << "  Vargsiukai:    " << vargsiukaiV.size() << "\n";
    std::cout << "  Nuskaitymas:   " << readTimeV << " s\n";
    std::cout << "  Skaidymas:     " << splitTimeV << " s\n";
    std::cout << "  Rasymas:       " << writeTimeV << " s\n";
    std::cout << "  Bendra atmintis: " << std::fixed << std::setprecision(2) << memMB_V << " MB\n";

    // === LIST VERSIJA ==============
    
    FILE* open_f2 = fopen(failas.c_str(), "r");
    if (!open_f2) {
        std::cout << "Nepavyko atidaryti failo (list versijai)!\n";
        return;
    }

    std::list<Studentas> visiStudentaiL;
    lineCounter = 0;

    auto tReadStartL = std::chrono::high_resolution_clock::now();
    while (fgets(eil_r, sizeof(eil_r), open_f2) != nullptr) {
        lineCounter++;
        if (lineCounter <= 2) continue;

        std::stringstream ss(eil_r);
        Studentas s;
        ss >> s.vard >> s.pav;
        for (int i = 0; i < 5; i++) { int x; ss >> x; s.paz.push_back(x); }
        ss >> s.egzas;
        skaiciuokRezultatus(s);
        visiStudentaiL.push_back(s);
    }
    fclose(open_f2);
    auto tReadEndL = std::chrono::high_resolution_clock::now();
    double readTimeL = std::chrono::duration<double>(tReadEndL - tReadStartL).count();

    auto tSplitStartL = std::chrono::high_resolution_clock::now();
    std::list<Studentas> kietiakaiL;
    std::list<Studentas> vargsiukaiL;

    for (const auto& s : visiStudentaiL) {
        if (s.rezVid >= 5 && s.rezMed >= 5)
            kietiakaiL.push_back(s);
        else
            vargsiukaiL.push_back(s);
    }

    auto tSplitEndL = std::chrono::high_resolution_clock::now();
    double splitTimeL = std::chrono::duration<double>(tSplitEndL - tSplitStartL).count();

    auto tWriteStartL = std::chrono::high_resolution_clock::now();

    std::ofstream outKietL(base + "_kietiakai_list.txt");
    std::ofstream outVargL(base + "_vargsiukai_list.txt");

    for (auto& s : kietiakaiL)
        outKietL << std::left << std::setw(15) << s.vard
        << std::setw(15) << s.pav
        << std::setw(10) << s.rezVid
        << std::setw(10) << s.rezMed << "\n";

    for (auto& s : vargsiukaiL)
        outVargL << std::left << std::setw(15) << s.vard
        << std::setw(15) << s.pav
        << std::setw(10) << s.rezVid
        << std::setw(10) << s.rezMed << "\n";

    outKietL.close();
    outVargL.close();

    auto tWriteEndL = std::chrono::high_resolution_clock::now();
    double writeTimeL = std::chrono::duration<double>(tWriteEndL - tWriteStartL).count();

    auto bytesL = sizeof(Studentas) * visiStudentaiL.size() +
        sizeof(Studentas) * (kietiakaiL.size() + vargsiukaiL.size());
    double memMB_L = bytesL / (1024.0 * 1024.0);

    std::cout << "\n=== LIST STRATEGIJA 1 ===\n";
    std::cout << "  Studentu viso: " << visiStudentaiL.size() << "\n";
    std::cout << "  Kietiakai:     " << kietiakaiL.size() << "\n";
    std::cout << "  Vargsiukai:    " << vargsiukaiL.size() << "\n";
    std::cout << "  Nuskaitymas:   " << readTimeL << " s\n";
    std::cout << "  Skaidymas:     " << splitTimeL << " s\n";
    std::cout << "  Rasymas:       " << writeTimeL << " s\n";
    std::cout << "  Bendra atmintis: " << std::fixed << std::setprecision(2) << memMB_L << " MB\n";
}






void Strategija2() {
    std::string failas;
    std::cout << "Iveskite failo pavadinima: ";
    std::cin >> failas;

    std::string base = failas.substr(0, failas.find(".txt"));
    char eil_r[500];
    int lineCounter = 0;

    // ================= VECTOR =================
    FILE* open_f = fopen(failas.c_str(), "r");
    if (!open_f) { std::cout << "Nepavyko atidaryti failo!\n"; return; }

    auto tReadStartV = std::chrono::high_resolution_clock::now();
    std::vector<Studentas> visiStudentaiV;
    visiStudentaiV.reserve(10'000'000);

    while (fgets(eil_r, sizeof(eil_r), open_f) != nullptr) {
        lineCounter++;
        if (lineCounter <= 2) continue;

        std::stringstream ss(eil_r);
        Studentas s;
        ss >> s.vard >> s.pav;
        for (int i = 0; i < 5; i++) { int x; ss >> x; s.paz.push_back(x); }
        ss >> s.egzas;
        skaiciuokRezultatus(s);
        visiStudentaiV.push_back(s);
    }
    fclose(open_f);
    auto tReadEndV = std::chrono::high_resolution_clock::now();
    double readTimeV = std::chrono::duration<double>(tReadEndV - tReadStartV).count();

    // --- 2 STRATEGIJA: vienas papildomas konteineris vargšiukams ---
    auto tSplitStartV = std::chrono::high_resolution_clock::now();
    std::vector<Studentas> vargsiukaiV;
    for (auto it = visiStudentaiV.begin(); it != visiStudentaiV.end(); ) {
        if (it->rezVid < 5 || it->rezMed < 5) {
            vargsiukaiV.push_back(*it);
            it = visiStudentaiV.erase(it);
        }
        else ++it;
    }
    auto tSplitEndV = std::chrono::high_resolution_clock::now();
    double splitTimeV = std::chrono::duration<double>(tSplitEndV - tSplitStartV).count();

    // --- Rašymas į failus ---
    auto tWriteStartV = std::chrono::high_resolution_clock::now();
    std::ofstream outKietV(base + "_kietiakai_vector_2strategija.txt");
    std::ofstream outVargV(base + "_vargsiukai_vector_2strategija.txt");

    for (auto& s : visiStudentaiV)
        outKietV << std::left << std::setw(15) << s.vard
        << std::setw(15) << s.pav
        << std::setw(10) << s.rezVid
        << std::setw(10) << s.rezMed << "\n";

    for (auto& s : vargsiukaiV)
        outVargV << std::left << std::setw(15) << s.vard
        << std::setw(15) << s.pav
        << std::setw(10) << s.rezVid
        << std::setw(10) << s.rezMed << "\n";

    outKietV.close();
    outVargV.close();
    auto tWriteEndV = std::chrono::high_resolution_clock::now();
    double writeTimeV = std::chrono::duration<double>(tWriteEndV - tWriteStartV).count();

    double memMB_KietV = sizeof(Studentas) * visiStudentaiV.size() / (1024.0 * 1024.0);
    double memMB_VargV = sizeof(Studentas) * vargsiukaiV.size() / (1024.0 * 1024.0);
    double memMB_V = memMB_KietV + memMB_VargV;

    std::cout << "\n=== VECTOR STRATEGIJA 2 ===\n";
    std::cout << "  Studentu viso: " << (visiStudentaiV.size() + vargsiukaiV.size()) << "\n";
    std::cout << "  Kietiakai:     " << visiStudentaiV.size() << " (" << std::fixed << std::setprecision(2) << memMB_KietV << " MB)\n";
    std::cout << "  Vargsiukai:    " << vargsiukaiV.size() << " (" << memMB_VargV << " MB)\n";
    std::cout << "  Nuskaitymas:   " << readTimeV << " s\n";
    std::cout << "  Skaidymas:     " << splitTimeV << " s\n";
    std::cout << "  Rasymas:       " << writeTimeV << " s\n";
    std::cout << "  Bendra atmintis: " << memMB_V << " MB\n";

    // ================= LIST =================
    FILE* open_f2 = fopen(failas.c_str(), "r");
    if (!open_f2) { std::cout << "Nepavyko atidaryti failo (list)!\n"; return; }

    std::list<Studentas> visiStudentaiL;
    lineCounter = 0;
    auto tReadStartL = std::chrono::high_resolution_clock::now();
    while (fgets(eil_r, sizeof(eil_r), open_f2) != nullptr) {
        lineCounter++;
        if (lineCounter <= 2) continue;

        std::stringstream ss(eil_r);
        Studentas s;
        ss >> s.vard >> s.pav;
        for (int i = 0; i < 5; i++) { int x; ss >> x; s.paz.push_back(x); }
        ss >> s.egzas;
        skaiciuokRezultatus(s);
        visiStudentaiL.push_back(s);
    }
    fclose(open_f2);
    auto tReadEndL = std::chrono::high_resolution_clock::now();
    double readTimeL = std::chrono::duration<double>(tReadEndL - tReadStartL).count();

    auto tSplitStartL = std::chrono::high_resolution_clock::now();
    std::list<Studentas> vargsiukaiL;
    for (auto it = visiStudentaiL.begin(); it != visiStudentaiL.end(); ) {
        if (it->rezVid < 5 || it->rezMed < 5) {
            vargsiukaiL.push_back(*it);
            it = visiStudentaiL.erase(it);
        }
        else ++it;
    }
    auto tSplitEndL = std::chrono::high_resolution_clock::now();
    double splitTimeL = std::chrono::duration<double>(tSplitEndL - tSplitStartL).count();

    auto tWriteStartL = std::chrono::high_resolution_clock::now();
    std::ofstream outKietL(base + "_kietiakai_list_2strategija.txt");
    std::ofstream outVargL(base + "_vargsiukai_list_2strategija.txt");

    for (auto& s : visiStudentaiL)
        outKietL << std::left << std::setw(15) << s.vard
        << std::setw(15) << s.pav
        << std::setw(10) << s.rezVid
        << std::setw(10) << s.rezMed << "\n";

    for (auto& s : vargsiukaiL)
        outVargL << std::left << std::setw(15) << s.vard
        << std::setw(15) << s.pav
        << std::setw(10) << s.rezVid
        << std::setw(10) << s.rezMed << "\n";

    outKietL.close();
    outVargL.close();
    auto tWriteEndL = std::chrono::high_resolution_clock::now();
    double writeTimeL = std::chrono::duration<double>(tWriteEndL - tWriteStartL).count();

    double memMB_KietL = sizeof(Studentas) * visiStudentaiL.size() / (1024.0 * 1024.0);
    double memMB_VargL = sizeof(Studentas) * vargsiukaiL.size() / (1024.0 * 1024.0);
    double memMB_L = memMB_KietL + memMB_VargL;

    std::cout << "\n=== LIST STRATEGIJA 2 ===\n";
    std::cout << "  Studentu viso: " << (visiStudentaiL.size() + vargsiukaiL.size()) << "\n";
    std::cout << "  Kietiakai:     " << visiStudentaiL.size() << " (" << memMB_KietL << " MB)\n";
    std::cout << "  Vargsiukai:    " << vargsiukaiL.size() << " (" << memMB_VargL << " MB)\n";
    std::cout << "  Nuskaitymas:   " << readTimeL << " s\n";
    std::cout << "  Skaidymas:     " << splitTimeL << " s\n";
    std::cout << "  Rasymas:       " << writeTimeL << " s\n";
    std::cout << "  Bendra atmintis: " << memMB_L << " MB\n";
}




void strategija1_STL_vectoriui() {
    std::string failas;
    std::cout << "Iveskite failo pavadinima: ";
    std::cin >> failas;

    FILE* open_f = fopen(failas.c_str(), "r");
    if (!open_f) {
        std::cout << "Nepavyko atidaryti failo!\n";
        return;
    }

    std::string base = failas.substr(0, failas.find(".txt"));
    char eil_r[500];
    int lineCounter = 0;

    // === VECTOR VERSIJA ============  
    auto tReadStartV = std::chrono::high_resolution_clock::now();

    std::vector<Studentas> visiStudentai;
    visiStudentai.reserve(10'000'000);

    while (fgets(eil_r, sizeof(eil_r), open_f) != nullptr) {
        lineCounter++;
        if (lineCounter <= 2) continue;

        std::stringstream ss(eil_r);
        Studentas s;
        ss >> s.vard >> s.pav;
        for (int i = 0; i < 5; i++) { int x; ss >> x; s.paz.push_back(x); }
        ss >> s.egzas;
        skaiciuokRezultatus(s);
        visiStudentai.push_back(s);
    }
    fclose(open_f);

    auto tReadEndV = std::chrono::high_resolution_clock::now();
    double readTimeV = std::chrono::duration<double>(tReadEndV - tReadStartV).count();

    // --- Skaidymas naudojant std::partition ---
    auto tSplitStartV = std::chrono::high_resolution_clock::now();

    std::vector<Studentas> kietiakaiV = visiStudentai; // kopijuojam visus
    // Partition: kietiakai priekyje, vargsiukai gale
    auto it = std::partition(kietiakaiV.begin(), kietiakaiV.end(), [](const Studentas& s) {
        return s.rezVid >= 5 && s.rezMed >= 5;
        });

    std::vector<Studentas> vargsiukaiV(it, kietiakaiV.end()); // gale esantys
    kietiakaiV.erase(it, kietiakaiV.end()); // pašalinam vargšius iš pirmo vectoriaus

    auto tSplitEndV = std::chrono::high_resolution_clock::now();
    double splitTimeV = std::chrono::duration<double>(tSplitEndV - tSplitStartV).count();

    // --- Rašymas į failus naudojant std::copy + ostream_iterator ---
    auto tWriteStartV = std::chrono::high_resolution_clock::now();

    std::ofstream outKiet(base + "_kietiakai_vector.txt");
    std::ofstream outVarg(base + "_vargsiukai_vector.txt");

    auto writeStudent = [](std::ofstream& out, const Studentas& s) {
        out << std::left << std::setw(15) << s.vard
            << std::setw(15) << s.pav
            << std::setw(10) << s.rezVid
            << std::setw(10) << s.rezMed << "\n";
        };

    std::for_each(kietiakaiV.begin(), kietiakaiV.end(), [&](const Studentas& s) { writeStudent(outKiet, s); });
    std::for_each(vargsiukaiV.begin(), vargsiukaiV.end(), [&](const Studentas& s) { writeStudent(outVarg, s); });

    outKiet.close();
    outVarg.close();

    auto tWriteEndV = std::chrono::high_resolution_clock::now();
    double writeTimeV = std::chrono::duration<double>(tWriteEndV - tWriteStartV).count();

    // --- Atminties skaičiavimas (apytiksliai MB) ---
    auto bytesV = sizeof(Studentas) * visiStudentai.size() +
        sizeof(Studentas) * (kietiakaiV.size() + vargsiukaiV.size());
    double memMB_V = bytesV / (1024.0 * 1024.0);

    std::cout << "\n=== VECTOR STRATEGIJA 1 (su algoritmais) ===\n";
    std::cout << "  Studentu viso: " << visiStudentai.size() << "\n";
    std::cout << "  Kietiakai:     " << kietiakaiV.size() << "\n";
    std::cout << "  Vargsiukai:    " << vargsiukaiV.size() << "\n";
    std::cout << "  Nuskaitymas:   " << readTimeV << " s\n";
    std::cout << "  Skaidymas:     " << splitTimeV << " s\n";
    std::cout << "  Rasymas:       " << writeTimeV << " s\n";
    std::cout << "  Bendra atmintis: " << std::fixed << std::setprecision(2) << memMB_V << " MB\n";
}


void Strategija2_STL_vectoriui() {
    std::string failas;
    std::cout << "Iveskite failo pavadinima: ";
    std::cin >> failas;

    std::string base = failas.substr(0, failas.find(".txt"));
    char eil_r[500];
    int lineCounter = 0;

    // ================= VECTOR =================
    FILE* open_f = fopen(failas.c_str(), "r");
    if (!open_f) { std::cout << "Nepavyko atidaryti failo!\n"; return; }

    auto tReadStartV = std::chrono::high_resolution_clock::now();
    std::vector<Studentas> visiStudentaiV;
    visiStudentaiV.reserve(10'000'000);

    while (fgets(eil_r, sizeof(eil_r), open_f) != nullptr) {
        lineCounter++;
        if (lineCounter <= 2) continue;

        std::stringstream ss(eil_r);
        Studentas s;
        ss >> s.vard >> s.pav;
        for (int i = 0; i < 5; i++) { int x; ss >> x; s.paz.push_back(x); }
        ss >> s.egzas;
        skaiciuokRezultatus(s);
        visiStudentaiV.push_back(s);
    }
    fclose(open_f);
    auto tReadEndV = std::chrono::high_resolution_clock::now();
    double readTimeV = std::chrono::duration<double>(tReadEndV - tReadStartV).count();

    // --- 2 STRATEGIJA su STL: remove_copy_if ---
    auto tSplitStartV = std::chrono::high_resolution_clock::now();

    std::vector<Studentas> vargsiukaiV;
    vargsiukaiV.reserve(visiStudentaiV.size());

    // Naudojame std::remove_copy_if, kad nukopijuotume vargšiukus į kitą konteinerį
    std::remove_copy_if(
        visiStudentaiV.begin(), visiStudentaiV.end(),
        std::back_inserter(vargsiukaiV),
        [](const Studentas& s) { return s.rezVid >= 5 && s.rezMed >= 5; }
    );

    // Pašaliname vargšius iš pagrindinio vectoriaus su std::remove_if + erase
    visiStudentaiV.erase(
        std::remove_if(
            visiStudentaiV.begin(), visiStudentaiV.end(),
            [](const Studentas& s) { return s.rezVid < 5 || s.rezMed < 5; }
        ),
        visiStudentaiV.end()
    );

    auto tSplitEndV = std::chrono::high_resolution_clock::now();
    double splitTimeV = std::chrono::duration<double>(tSplitEndV - tSplitStartV).count();

    // --- Rašymas į failus su std::for_each ---
    auto tWriteStartV = std::chrono::high_resolution_clock::now();

    std::ofstream outKietV(base + "_kietiakai_vector_2strategija_STL.txt");
    std::ofstream outVargV(base + "_vargsiukai_vector_2strategija_STL.txt");

    auto writeStudent = [](std::ofstream& out, const Studentas& s) {
        out << std::left << std::setw(15) << s.vard
            << std::setw(15) << s.pav
            << std::setw(10) << s.rezVid
            << std::setw(10) << s.rezMed << "\n";
        };

    std::for_each(visiStudentaiV.begin(), visiStudentaiV.end(), [&](const Studentas& s) { writeStudent(outKietV, s); });
    std::for_each(vargsiukaiV.begin(), vargsiukaiV.end(), [&](const Studentas& s) { writeStudent(outVargV, s); });

    outKietV.close();
    outVargV.close();

    auto tWriteEndV = std::chrono::high_resolution_clock::now();
    double writeTimeV = std::chrono::duration<double>(tWriteEndV - tWriteStartV).count();

    double memMB_KietV = sizeof(Studentas) * visiStudentaiV.size() / (1024.0 * 1024.0);
    double memMB_VargV = sizeof(Studentas) * vargsiukaiV.size() / (1024.0 * 1024.0);
    double memMB_V = memMB_KietV + memMB_VargV;

    std::cout << "\n=== VECTOR STRATEGIJA 2 (su STL algoritmais) ===\n";
    std::cout << "  Studentu viso: " << (visiStudentaiV.size() + vargsiukaiV.size()) << "\n";
    std::cout << "  Kietiakai:     " << visiStudentaiV.size() << " (" << std::fixed << std::setprecision(2) << memMB_KietV << " MB)\n";
    std::cout << "  Vargsiukai:    " << vargsiukaiV.size() << " (" << memMB_VargV << " MB)\n";
    std::cout << "  Nuskaitymas:   " << readTimeV << " s\n";
    std::cout << "  Skaidymas:     " << splitTimeV << " s\n";
    std::cout << "  Rasymas:       " << writeTimeV << " s\n";
    std::cout << "  Bendra atmintis: " << memMB_V << " MB\n";
}


void strategija3() {
    std::string failas;
    std::cout << "Įveskite failo pavadinimą: ";
    std::cin >> failas;

    std::cout << "\n=== STRATEGIJA 3: Automatinis palyginimas ===\n";
    std::cout << "Naudojamas failas: " << failas << "\n";

    double v1_time, v2_time, l1_time, l2_time;

    // --- 1. Strategija 1: vector ---
    auto t1v_start = std::chrono::high_resolution_clock::now();
    strategija1_skaidymas();  // dirba su vector
    auto t1v_end = std::chrono::high_resolution_clock::now();
    v1_time = std::chrono::duration<double>(t1v_end - t1v_start).count();

    // --- 2. Strategija 1: list ---
    auto t1l_start = std::chrono::high_resolution_clock::now();
    strategija1_skaidymas();  // ta pati funkcija, bet viduje turi list dalį
    auto t1l_end = std::chrono::high_resolution_clock::now();
    l1_time = std::chrono::duration<double>(t1l_end - t1l_start).count();

    // --- 3. Strategija 2: vector ---
    auto t2v_start = std::chrono::high_resolution_clock::now();
    Strategija2();  // dirba su vector
    auto t2v_end = std::chrono::high_resolution_clock::now();
    v2_time = std::chrono::duration<double>(t2v_end - t2v_start).count();

    // --- 4. Strategija 2: list ---
    auto t2l_start = std::chrono::high_resolution_clock::now();
    Strategija2();  // turi ir list dalį
    auto t2l_end = std::chrono::high_resolution_clock::now();
    l2_time = std::chrono::duration<double>(t2l_end - t2l_start).count();

    // --- 5. Rezultatų lentelė ---
    std::cout << "\n=== LAIKO PALYGINIMAS ===\n";
    std::cout << std::left << std::setw(12) << " "
        << std::setw(15) << "Vector"
        << std::setw(15) << "List" << "\n";
    std::cout << std::setw(12) << "Strategija1"
        << std::setw(15) << v1_time
        << std::setw(15) << l1_time << "\n";
    std::cout << std::setw(12) << "Strategija2"
        << std::setw(15) << v2_time
        << std::setw(15) << l2_time << "\n";

    // --- 6. Nustatome greitesnes strategijas ---
    std::string greitesneVector = (v1_time <= v2_time) ? "Strategija1" : "Strategija2";
    std::string greitesneList = (l1_time <= l2_time) ? "Strategija1" : "Strategija2";

    std::cout << "\nGreitesnė strategija VECTORIUI: " << greitesneVector << "\n";
    std::cout << "Greitesnė strategija LISTUI: " << greitesneList << "\n";

    // --- 7. Paleidžiam greitesnes versijas ---
    if (greitesneVector == "Strategija1") {
        std::cout << "\n>> Paleidžiama STL optimizuota Strategija1 (vector)\n";
        strategija1_STL_vectoriui();
    }
    else {
        std::cout << "\n>> Paleidžiama STL optimizuota Strategija2 (vector)\n";
        Strategija2_STL_vectoriui();
    }

    if (greitesneList == "Strategija1") {
        std::cout << "\n>> Paleidžiama paprasta Strategija1 list versija\n";
        strategija1_skaidymas();
    }
    else {
        std::cout << "\n>> Paleidžiama paprasta Strategija2 list versija\n";
        Strategija2();
    }

    std::cout << "\n=== STRATEGIJA 3 BAIGTA ===\n";
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
