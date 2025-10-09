#define _CRT_SECURE_NO_WARNINGS
#include "failai.h"
#pragma execution_character_set("utf-8")
#include <fstream>
using namespace std;

void generuokFailus() {
    vector<long long> dydziai = { 1000, 10000, 100000, 1000000, 10000000 };
    cout << "\nPradedamas testiniu failu generavimas...\n";

    auto viso_pradzia = chrono::high_resolution_clock::now();

    for (long long kiekis : dydziai) {
        string pavadinimas = "studentai" + to_string(kiekis) + ".txt";

        auto pradzia = chrono::high_resolution_clock::now();
        ofstream out(pavadinimas);
        if (!out) {
            cout << "Nepavyko sukurti failo: " << pavadinimas << endl;
            continue;
        }

        
        out << left << setw(15) << "Vardas" << left << setw(15) << "Pavarde";
        for (int i = 1; i <= 5; i++)
            out << right << setw(6) << ("ND" + to_string(i));
        out << right << setw(6) << "Egz" << "\n";
        out << string(15 + 15 + 6 * 6, '-') << "\n";

        
        for (long long i = 0; i < kiekis; i++) {
            int vardSkaicius = rand() % 10000;
            int pavSkaicius = rand() % 10000;
            out << left << setw(15) << ("vardas" + to_string(vardSkaicius))
                << left << setw(15) << ("pavarde" + to_string(pavSkaicius));
            for (int j = 0; j < 5; j++)
                out << right << setw(6) << (rand() % 11);
            out << right << setw(6) << (rand() % 11) << "\n";
        }

        out.close();
        auto pabaiga = chrono::high_resolution_clock::now();
        chrono::duration<double> trukme = pabaiga - pradzia;

        cout << "Sugeneruota: " << pavadinimas
            << "  (" << kiekis << " irasu) per "
            << fixed << setprecision(3) << trukme.count() << " s\n";
    }

    auto viso_pabaiga = chrono::high_resolution_clock::now();
    chrono::duration<double> viso_trukme = viso_pabaiga - viso_pradzia;

    cout << "\nFailu generavimas baigtas per "
        << fixed << setprecision(3) << viso_trukme.count() << " s.\n";
}


void analizuokVisusFailusMinimaliai() {
    vector<string> failai = {
        "studentai1000.txt",
        "studentai10000.txt",
        "studentai100000.txt",
        "studentai1000000.txt",
        "studentai10000000.txt"
    };

    int rezPasirinkimas;
    cout << "\nKokius rezultatus spausdinti i failus?\n"
        << "1 - Tik vidurki\n2 - Tik mediana\n3 - Abu\nPasirinkimas: ";
    cin >> rezPasirinkimas;

    int rikiavimas;
    cout << "Pagal ka rikiuoti galutinius rezultatus?\n"
        << "1 - Vardas (A-Z)\n"
        << "2 - Pavarde (A-Z)\n"
        << "3 - Vidurkis didejimo tvarka\n"
        << "4 - Vidurkis mazejimo tvarka\n"
        << "5 - Mediana didejimo tvarka\n"
        << "6 - Mediana mazejimo tvarka\n"
        << "Pasirinkimas: ";
    cin >> rikiavimas;

    for (const string& failas : failai) {
        cout << "\n=== Apdorojamas failas: " << failas << " ===\n";

        FILE* open_f = fopen(failas.c_str(), "r");
        if (!open_f) {
            cout << "Nepavyko atidaryti failo!\n";
            continue;
        }

        string base = failas.substr(0, failas.find(".txt"));
        string proName = base + "_protinguliai.txt";
        string kvaName = base + "_kvailiukai.txt";

        ofstream outPro(proName), outKva(kvaName);
        if (!outPro || !outKva) {
            cout << "Klaida: nepavyko sukurti rezultatų failų\n";
            fclose(open_f);
            continue;
        }

        auto spausdinkAntraste = [&](ofstream& out) {
            out << left << setw(15) << "Vardas" << left << setw(15) << "Pavarde";
            if (rezPasirinkimas == 1)
                out << right << setw(15) << "Galutinis(Vid.)";
            else if (rezPasirinkimas == 2)
                out << right << setw(15) << "Galutinis(Med.)";
            else
                out << right << setw(15) << "Galutinis(Vid.)"
                << right << setw(15) << "Galutinis(Med.)";
            out << "\n" << string(15 + 15 + (rezPasirinkimas == 3 ? 30 : 15), '-') << "\n";
            };
        spausdinkAntraste(outPro);
        spausdinkAntraste(outKva);

        char eil_r[500];
        int lineCounter = 0;
        double readTime = 0, calcTime = 0, writeTime = 0;

        vector<Studentas> protingi, kvaili;

        
        while (fgets(eil_r, sizeof(eil_r), open_f) != nullptr) {
            lineCounter++;
            if (lineCounter <= 2) continue; 

            auto t1 = chrono::high_resolution_clock::now();
            string eil(eil_r);
            auto t2 = chrono::high_resolution_clock::now();
            readTime += chrono::duration<double>(t2 - t1).count();

            auto t3 = chrono::high_resolution_clock::now();
            stringstream ss(eil);
            Studentas s;
            ss >> s.vard >> s.pav;
            for (int i = 0; i < 5; i++) {
                int x;
                ss >> x;
                s.paz.push_back(x);
            }
            ss >> s.egzas;
            skaiciuokRezultatus(s);
            auto t4 = chrono::high_resolution_clock::now();
            calcTime += chrono::duration<double>(t4 - t3).count();

            if (s.rezVid >= 5 && s.rezMed >= 5)
                protingi.push_back(s);
            else
                kvaili.push_back(s);
        }

        fclose(open_f);

        
        auto rikiuok = [&](vector<Studentas>& v) {
            switch (rikiavimas) {
            case 1: sort(v.begin(), v.end(), [](auto& a, auto& b) { return a.vard < b.vard; }); break;
            case 2: sort(v.begin(), v.end(), [](auto& a, auto& b) { return a.pav < b.pav; }); break;
            case 3: sort(v.begin(), v.end(), [](auto& a, auto& b) { return a.rezVid < b.rezVid; }); break;
            case 4: sort(v.begin(), v.end(), [](auto& a, auto& b) { return a.rezVid > b.rezVid; }); break;
            case 5: sort(v.begin(), v.end(), [](auto& a, auto& b) { return a.rezMed < b.rezMed; }); break;
            case 6: sort(v.begin(), v.end(), [](auto& a, auto& b) { return a.rezMed > b.rezMed; }); break;
            default: break;
            }
            };

        rikiuok(protingi);
        rikiuok(kvaili);

        
        auto spausdink = [&](ofstream& out, const vector<Studentas>& v) {
            for (auto& s : v) {
                auto t5 = chrono::high_resolution_clock::now();
                out << left << setw(15) << s.vard << left << setw(15) << s.pav;
                if (rezPasirinkimas == 1)
                    out << right << setw(15) << fixed << setprecision(2) << s.rezVid;
                else if (rezPasirinkimas == 2)
                    out << right << setw(15) << fixed << setprecision(2) << s.rezMed;
                else
                    out << right << setw(15) << fixed << setprecision(2) << s.rezVid
                    << right << setw(15) << fixed << setprecision(2) << s.rezMed;
                out << "\n";
                auto t6 = chrono::high_resolution_clock::now();
                writeTime += chrono::duration<double>(t6 - t5).count();
            }
            };

        spausdink(outPro, protingi);
        spausdink(outKva, kvaili);

        outPro.close();
        outKva.close();

        cout << "Failas apdorotas!\n";
        cout << "  Nuskaitymas: " << fixed << setprecision(3) << readTime << " s\n";
        cout << "  Skaiciavimas: " << fixed << setprecision(3) << calcTime << " s\n";
        cout << "  irasymas i failus: " << fixed << setprecision(3) << writeTime << " s\n";
        cout << "  -> " << proName << "\n  -> " << kvaName << "\n";
    }
}

