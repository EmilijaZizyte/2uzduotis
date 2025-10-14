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
        spausdinkAntraste(outPro);
        spausdinkAntraste(outKva);

        char eil_r[500];
        int lineCounter = 0;
        double readTime = 0, calcTime = 0, writeTime = 0;

        std::vector<Studentas> protingi, kvaili;

        while (fgets(eil_r, sizeof(eil_r), open_f) != nullptr) {
            lineCounter++;
            if (lineCounter <= 2) continue; 

            auto t1 = std::chrono::high_resolution_clock::now();
            std::string eil(eil_r);
            auto t2 = std::chrono::high_resolution_clock::now();
            readTime += std::chrono::duration<double>(t2 - t1).count();

            auto t3 = std::chrono::high_resolution_clock::now();
            std::stringstream ss(eil);
            Studentas s;
            ss >> s.vard >> s.pav;
            for (int i = 0; i < 5; i++) {
                int x;
                ss >> x;
                s.paz.push_back(x);
            }
            ss >> s.egzas;
            skaiciuokRezultatus(s);
            auto t4 = std::chrono::high_resolution_clock::now();
            calcTime += std::chrono::duration<double>(t4 - t3).count();

            if (s.rezVid >= 5 && s.rezMed >= 5)
                protingi.push_back(s);
            else
                kvaili.push_back(s);
        }

        fclose(open_f);

        auto rikiuok = [&](std::vector<Studentas>& v) {
            switch (rikiavimas) {
            case 1: std::sort(v.begin(), v.end(), [](auto& a, auto& b) { return a.vard < b.vard; }); break;
            case 2: std::sort(v.begin(), v.end(), [](auto& a, auto& b) { return a.pav < b.pav; }); break;
            case 3: std::sort(v.begin(), v.end(), [](auto& a, auto& b) { return a.rezVid < b.rezVid; }); break;
            case 4: std::sort(v.begin(), v.end(), [](auto& a, auto& b) { return a.rezVid > b.rezVid; }); break;
            case 5: std::sort(v.begin(), v.end(), [](auto& a, auto& b) { return a.rezMed < b.rezMed; }); break;
            case 6: std::sort(v.begin(), v.end(), [](auto& a, auto& b) { return a.rezMed > b.rezMed; }); break;
            default: break;
            }
        };

        rikiuok(protingi);
        rikiuok(kvaili);

        auto spausdink = [&](std::ofstream& out, const std::vector<Studentas>& v) {
            for (auto& s : v) {
                auto t5 = std::chrono::high_resolution_clock::now();
                out << std::left << std::setw(15) << s.vard << std::left << std::setw(15) << s.pav;
                if (rezPasirinkimas == 1)
                    out << std::right << std::setw(15) << std::fixed << std::setprecision(2) << s.rezVid;
                else if (rezPasirinkimas == 2)
                    out << std::right << std::setw(15) << std::fixed << std::setprecision(2) << s.rezMed;
                else
                    out << std::right << std::setw(15) << std::fixed << std::setprecision(2) << s.rezVid
                        << std::right << std::setw(15) << std::fixed << std::setprecision(2) << s.rezMed;
                out << "\n";
                auto t6 = std::chrono::high_resolution_clock::now();
                writeTime += std::chrono::duration<double>(t6 - t5).count();
            }
        };

        spausdink(outPro, protingi);
        spausdink(outKva, kvaili);

        outPro.close();
        outKva.close();

        std::cout << "Failas apdorotas!\n";
        std::cout << "  Nuskaitymas: " << std::fixed << std::setprecision(3) << readTime << " s\n";
        std::cout << "  Skaiciavimas: " << std::fixed << std::setprecision(3) << calcTime << " s\n";
        std::cout << "  irasymas i failus: " << std::fixed << std::setprecision(3) << writeTime << " s\n";
        std::cout << "  -> " << proName << "\n  -> " << kvaName << "\n";
    }
}
