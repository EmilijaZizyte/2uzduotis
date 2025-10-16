#define _CRT_SECURE_NO_WARNINGS
#include "failai.h"
#pragma execution_character_set("utf-8")
#include <fstream>

void generuokFailus() {
    std::vector<long long> dydziai = { 1000, 10000, 100000, 1000000, 10000000 };
    std::cout << "\nPradedamas testiniu failu generavimas...\n";

    auto viso_pradzia = std::chrono::high_resolution_clock::now();

    for (long long kiekis : dydziai) {
        std::string pavadinimas = "studentai" + std::to_string(kiekis) + ".txt";

        auto pradzia = std::chrono::high_resolution_clock::now();
        std::ofstream out(pavadinimas);
        if (!out) {
            std::cout << "Nepavyko sukurti failo: " << pavadinimas << std::endl;
            continue;
        }

        out << std::left << std::setw(15) << "Vardas" << std::left << std::setw(15) << "Pavarde";
        for (int i = 1; i <= 5; i++)
            out << std::right << std::setw(6) << ("ND" + std::to_string(i));
        out << std::right << std::setw(6) << "Egz" << "\n";
        out << std::string(15 + 15 + 6 * 6, '-') << "\n";

        for (long long i = 0; i < kiekis; i++) {
            int vardSkaicius = std::rand() % 10000;
            int pavSkaicius = std::rand() % 10000;
            out << std::left << std::setw(15) << ("vardas" + std::to_string(vardSkaicius))
                << std::left << std::setw(15) << ("pavarde" + std::to_string(pavSkaicius));
            for (int j = 0; j < 5; j++)
                out << std::right << std::setw(6) << (std::rand() % 11);
            out << std::right << std::setw(6) << (std::rand() % 11) << "\n";
        }

        out.close();
        auto pabaiga = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> trukme = pabaiga - pradzia;

        std::cout << "Sugeneruota: " << pavadinimas
            << "  (" << kiekis << " irasu) per "
            << std::fixed << std::setprecision(3) << trukme.count() << " s\n";
    }

    auto viso_pabaiga = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> viso_trukme = viso_pabaiga - viso_pradzia;

    std::cout << "\nFailu generavimas baigtas per "
        << std::fixed << std::setprecision(3) << viso_trukme.count() << " s.\n";
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
