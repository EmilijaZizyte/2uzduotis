#define _CRT_SECURE_NO_WARNINGS
#include "failai.h"
#pragma execution_character_set("utf-8")
#include <fstream>
#include <list>

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
    std::vector<std::string> failai = {
        "studentai1000.txt",
        "studentai10000.txt",
        "studentai100000.txt",
        "studentai1000000.txt",
        "studentai10000000.txt"
    };

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

    for (const std::string& failas : failai) {
        std::cout << "\n=== Apdorojamas failas: " << failas << " ===\n";

        FILE* open_f = fopen(failas.c_str(), "r");
        if (!open_f) {
            std::cout << "Nepavyko atidaryti failo!\n";
            continue;
        }

        std::string base = failas.substr(0, failas.find(".txt"));

        // Failai vector rezultatams
        std::string proNameVector = base + "_protinguliai_vector.txt";
        std::string kvaNameVector = base + "_kvailiukai_vector.txt";
        std::ofstream outProV(proNameVector), outKvaV(kvaNameVector);

        // Failai list rezultatams
        std::string proNameList = base + "_protinguliai_list.txt";
        std::string kvaNameList = base + "_kvailiukai_list.txt";
        std::ofstream outProL(proNameList), outKvaL(kvaNameList);

        if (!outProV || !outKvaV || !outProL || !outKvaL) {
            std::cout << "Klaida: nepavyko sukurti rezultatų failų\n";
            fclose(open_f);
            continue;
        }

        auto spausdinkAntraste = [&](std::ofstream& out) {
            out << std::left << std::setw(15) << "Vardas" << std::left << std::setw(15) << "Pavarde";
            if (rezPasirinkimas == 1)
                out << std::right << std::setw(15) << "Galutinis(Vid.)";
            else if (rezPasirinkimas == 2)
                out << std::right << std::setw(15) << "Galutinis(Med.)";
            else
                out << std::right << std::setw(15) << "Galutinis(Vid.)"
                    << std::right << std::setw(15) << "Galutinis(Med.)";
            out << "\n" << std::string(15 + 15 + (rezPasirinkimas == 3 ? 30 : 15), '-') << "\n";
        };

        // Antraštės visiems failams
        spausdinkAntraste(outProV);
        spausdinkAntraste(outKvaV);
        spausdinkAntraste(outProL);
        spausdinkAntraste(outKvaL);

        char eil_r[500];
        int lineCounter = 0;

        // Laikini kintamieji
        double readTimeV = 0, calcTimeV = 0;
        double readTimeL = 0, calcTimeL = 0;

        std::vector<Studentas> protingiV, kvailiV;
        std::list<Studentas> protingiL, kvailiL;

        // ✅ REZERVAVIMAS (10 milijonų elementų vietos)
        protingiV.reserve(10000000);
        kvailiV.reserve(10000000);

        while (fgets(eil_r, sizeof(eil_r), open_f) != nullptr) {
            lineCounter++;
            if (lineCounter <= 2) continue;

            std::string eil(eil_r);

            // Vector
            auto t1v = std::chrono::high_resolution_clock::now();
            std::stringstream ssV(eil);
            Studentas sV;
            ssV >> sV.vard >> sV.pav;
            for (int i = 0; i < 5; i++) { int x; ssV >> x; sV.paz.push_back(x); }
            ssV >> sV.egzas;
            auto t2v = std::chrono::high_resolution_clock::now();
            readTimeV += std::chrono::duration<double>(t2v - t1v).count();

            auto t3v = std::chrono::high_resolution_clock::now();
            skaiciuokRezultatus(sV);
            auto t4v = std::chrono::high_resolution_clock::now();
            calcTimeV += std::chrono::duration<double>(t4v - t3v).count();

            if (sV.rezVid >= 5 && sV.rezMed >= 5) protingiV.push_back(sV);
            else kvailiV.push_back(sV);

            // List
            auto t1l = std::chrono::high_resolution_clock::now();
            std::stringstream ssL(eil);
            Studentas sL;
            ssL >> sL.vard >> sL.pav;
            for (int i = 0; i < 5; i++) { int x; ssL >> x; sL.paz.push_back(x); }
            ssL >> sL.egzas;
            auto t2l = std::chrono::high_resolution_clock::now();
            readTimeL += std::chrono::duration<double>(t2l - t1l).count();

            auto t3l = std::chrono::high_resolution_clock::now();
            skaiciuokRezultatus(sL);
            auto t4l = std::chrono::high_resolution_clock::now();
            calcTimeL += std::chrono::duration<double>(t4l - t3l).count();

            if (sL.rezVid >= 5 && sL.rezMed >= 5) protingiL.push_back(sL);
            else kvailiL.push_back(sL);
        }

        fclose(open_f);

        // Rikiavimas vector
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

        // Rikiavimas list
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

        // Rašymas su laiko matavimu
        auto writeV = [&](std::ofstream& out, const std::vector<Studentas>& v) {
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
            return writeTime;
        };

        auto writeL = [&](std::ofstream& out, const std::list<Studentas>& l) {
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
            return writeTime;
        };

        double writeTimeVPro = writeV(outProV, protingiV);
        double writeTimeVKva = writeV(outKvaV, kvailiV);

        double writeTimeLPro = writeL(outProL, protingiL);
        double writeTimeLKva = writeL(outKvaL, kvailiL);

        outProV.close(); outKvaV.close();
        outProL.close(); outKvaL.close();

        // Išvedimas
        std::cout << "Vector: Skaitymas=" << readTimeV
            << "s, Skaiciavimas=" << calcTimeV
            << "s\n  Rašymas į protingus: " << writeTimeVPro
            << "s\n  Rašymas į kvailiukus: " << writeTimeVKva << "s\n";

        std::cout << "List:   Skaitymas=" << readTimeL
            << "s, Skaiciavimas=" << calcTimeL
            << "s\n  Rašymas į protingus: " << writeTimeLPro
            << "s\n  Rašymas į kvailiukus: " << writeTimeLKva << "s\n";

        std::cout << "Failas apdorotas!\n";
        std::cout << "  -> Vector failai: " << proNameVector << ", " << kvaNameVector << "\n";
        std::cout << "  -> List failai: " << proNameList << ", " << kvaNameList << "\n";
    }
}

pridek reservavima

