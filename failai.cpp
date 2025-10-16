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
        std::string proName = base + "_protinguliai.txt";
        std::string kvaName = base + "_kvailiukai.txt";

        std::ofstream outPro(proName), outKva(kvaName);
        if (!outPro || !outKva) {
            std::cout << "Klaida: nepavyko sukurti rezultatų failų\n";
            fclose(open_f);
            continue;
        }

        auto spausdinkAntraste = [&](std::ofstream& out) {
            out << std::left << std::setw(15) << "Vardas" << std::setw(15) << "Pavarde";
            if (rezPasirinkimas == 1)
                out << std::setw(15) << "Galutinis(Vid.)";
            else if (rezPasirinkimas == 2)
                out << std::setw(15) << "Galutinis(Med.)";
            else
                out << std::setw(15) << "Galutinis(Vid.)"
                << std::setw(15) << "Galutinis(Med.)";
            out << "\n" << std::string(15 + 15 + (rezPasirinkimas == 3 ? 30 : 15), '-') << "\n";
            };
        spausdinkAntraste(outPro);
        spausdinkAntraste(outKva);

        char eil_r[500];
        int lineCounter = 0;

        // Vector & List
        std::vector<Studentas> protingiVector, kvailiVector;
        std::list<Studentas> protingiList, kvailiList;

        double readTimeVector = 0, calcTimeVector = 0, splitTimeVector = 0, sortTimeVector = 0;
        double readTimeList = 0, calcTimeList = 0, splitTimeList = 0, sortTimeList = 0;

        // Nauji atskiri rašymo laikai
        double writeTimeVectorProtingi = 0, writeTimeVectorKvaili = 0;
        double writeTimeListProtingi = 0, writeTimeListKvaili = 0;

        while (fgets(eil_r, sizeof(eil_r), open_f) != nullptr) {
            lineCounter++;
            if (lineCounter <= 2) continue;

            std::string eil(eil_r);

            // Vector skaitymas
            auto t1v = std::chrono::high_resolution_clock::now();
            Studentas sVector;
            std::stringstream ssV(eil);
            ssV >> sVector.vard >> sVector.pav;
            for (int i = 0; i < 5; i++) { int x; ssV >> x; sVector.paz.push_back(x); }
            ssV >> sVector.egzas;
            auto t2v = std::chrono::high_resolution_clock::now();
            readTimeVector += std::chrono::duration<double>(t2v - t1v).count();

            auto t3v = std::chrono::high_resolution_clock::now();
            skaiciuokRezultatus(sVector);
            auto t4v = std::chrono::high_resolution_clock::now();
            calcTimeVector += std::chrono::duration<double>(t4v - t3v).count();

            auto tSplitV1 = std::chrono::high_resolution_clock::now();
            if (sVector.rezVid >= 5 && sVector.rezMed >= 5)
                protingiVector.push_back(sVector);
            else
                kvailiVector.push_back(sVector);
            auto tSplitV2 = std::chrono::high_resolution_clock::now();
            splitTimeVector += std::chrono::duration<double>(tSplitV2 - tSplitV1).count();

            // List skaitymas
            auto t1l = std::chrono::high_resolution_clock::now();
            Studentas sList;
            std::stringstream ssL(eil);
            ssL >> sList.vard >> sList.pav;
            for (int i = 0; i < 5; i++) { int x; ssL >> x; sList.paz.push_back(x); }
            ssL >> sList.egzas;
            auto t2l = std::chrono::high_resolution_clock::now();
            readTimeList += std::chrono::duration<double>(t2l - t1l).count();

            auto t3l = std::chrono::high_resolution_clock::now();
            skaiciuokRezultatus(sList);
            auto t4l = std::chrono::high_resolution_clock::now();
            calcTimeList += std::chrono::duration<double>(t4l - t3l).count();

            auto tSplitL1 = std::chrono::high_resolution_clock::now();
            if (sList.rezVid >= 5 && sList.rezMed >= 5)
                protingiList.push_back(sList);
            else
                kvailiList.push_back(sList);
            auto tSplitL2 = std::chrono::high_resolution_clock::now();
            splitTimeList += std::chrono::duration<double>(tSplitL2 - tSplitL1).count();
        }

        fclose(open_f);

        // Rikiavimai
        auto sortStartV = std::chrono::high_resolution_clock::now();
        std::sort(protingiVector.begin(), protingiVector.end(), [](auto& a, auto& b) { return a.vard < b.vard; });
        std::sort(kvailiVector.begin(), kvailiVector.end(), [](auto& a, auto& b) { return a.vard < b.vard; });
        auto sortEndV = std::chrono::high_resolution_clock::now();
        sortTimeVector = std::chrono::duration<double>(sortEndV - sortStartV).count();

        auto sortStartL = std::chrono::high_resolution_clock::now();
        protingiList.sort([](auto& a, auto& b) { return a.vard < b.vard; });
        kvailiList.sort([](auto& a, auto& b) { return a.vard < b.vard; });
        auto sortEndL = std::chrono::high_resolution_clock::now();
        sortTimeList = std::chrono::duration<double>(sortEndL - sortStartL).count();

        // Spausdinimas
        auto spausdinkVector = [&](std::ofstream& out, const std::vector<Studentas>& v) {
            for (auto& s : v) {
                out << std::left << std::setw(15) << s.vard
                    << std::setw(15) << s.pav;
                if (rezPasirinkimas == 1)
                    out << std::setw(15) << s.rezVid;
                else if (rezPasirinkimas == 2)
                    out << std::setw(15) << s.rezMed;
                else
                    out << std::setw(15) << s.rezVid
                    << std::setw(15) << s.rezMed;
                out << "\n";
            }
            };
        auto spausdinkList = [&](std::ofstream& out, const std::list<Studentas>& lst) {
            for (auto& s : lst) {
                out << std::left << std::setw(15) << s.vard
                    << std::setw(15) << s.pav;
                if (rezPasirinkimas == 1)
                    out << std::setw(15) << s.rezVid;
                else if (rezPasirinkimas == 2)
                    out << std::setw(15) << s.rezMed;
                else
                    out << std::setw(15) << s.rezVid
                    << std::setw(15) << s.rezMed;
                out << "\n";
            }
            };

        // --- RAŠYMO LAIKO MATAVIMAS ---
        auto tVPro1 = std::chrono::high_resolution_clock::now();
        spausdinkVector(outPro, protingiVector);
        auto tVPro2 = std::chrono::high_resolution_clock::now();
        writeTimeVectorProtingi = std::chrono::duration<double>(tVPro2 - tVPro1).count();

        auto tVKva1 = std::chrono::high_resolution_clock::now();
        spausdinkVector(outKva, kvailiVector);
        auto tVKva2 = std::chrono::high_resolution_clock::now();
        writeTimeVectorKvaili = std::chrono::duration<double>(tVKva2 - tVKva1).count();

        auto tLPro1 = std::chrono::high_resolution_clock::now();
        spausdinkList(outPro, protingiList);
        auto tLPro2 = std::chrono::high_resolution_clock::now();
        writeTimeListProtingi = std::chrono::duration<double>(tLPro2 - tLPro1).count();

        auto tLKva1 = std::chrono::high_resolution_clock::now();
        spausdinkList(outKva, kvailiList);
        auto tLKva2 = std::chrono::high_resolution_clock::now();
        writeTimeListKvaili = std::chrono::duration<double>(tLKva2 - tLKva1).count();

        outPro.close();
        outKva.close();

        // --- IŠVESTIS ---
        if (protingiVector.size() == protingiList.size() && kvailiVector.size() == kvailiList.size())
            std::cout << " Rezultatai sutampa (" << protingiVector.size() + kvailiVector.size() << " įrašų)\n";

        std::cout << "Vector: Skaitymas=" << readTimeVector
            << "s, Skaičiavimas=" << calcTimeVector
            << "s, Skirstymas=" << splitTimeVector
            << "s, Rikiavimas=" << sortTimeVector << "s\n";
        std::cout << "   Rašymas į protingus: " << writeTimeVectorProtingi << "s\n";
        std::cout << "   Rašymas į kvailiukus: " << writeTimeVectorKvaili << "s\n";

        std::cout << "List:   Skaitymas=" << readTimeList
            << "s, Skaičiavimas=" << calcTimeList
            << "s, Skirstymas=" << splitTimeList
            << "s, Rikiavimas=" << sortTimeList << "s\n";
        std::cout << "   Rašymas į protingus: " << writeTimeListProtingi << "s\n";
        std::cout << "   Rašymas į kvailiukus: " << writeTimeListKvaili << "s\n";
    }
}
pridek reservavima

