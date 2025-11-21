#define _CRT_SECURE_NO_WARNINGS
#include "studentas.h"
#include <iomanip>
#include <list>
#include "failai.h"


// ===================== MEDIANA =====================
double mediana(std::vector<int> v) {
    if (v.empty()) return 0.0;

    std::sort(v.begin(), v.end());
    size_t n = v.size();

    if (n % 2 == 1) return v[n / 2];
    return (v[n / 2 - 1] + v[n / 2]) / 2.0;
}

// ===================== GALUTINIAI =====================
void skaiciuokRezultatus(Studentas& s) {
    const auto& paz = s.getPaz();
    int egzas = s.getEgzas();

    if (paz.empty()) {
        s.setRezVid(0.6 * egzas);
        s.setRezMed(0.6 * egzas);
        return;
    }

    double suma = std::accumulate(paz.begin(), paz.end(), 0.0);
    double vid = suma / paz.size();

    s.setRezVid(0.4 * vid + 0.6 * egzas);
    s.setRezMed(0.4 * mediana(paz) + 0.6 * egzas);
}

// ===================== OPERATOR >> =====================
std::istream& operator>>(std::istream& is, Studentas& s) {

    // Skaitymas iš failo (stringstream)
    if (&is != &std::cin) {
        std::string line;
        std::getline(is, line);
        if (line.empty()) return is;

        std::stringstream ss(line);
        std::string vard, pav;

        ss >> vard >> pav;
        s.setVard(vard);
        s.setPav(pav);

        int x;
        std::vector<int> temp;

        while (ss >> x) temp.push_back(x);

        if (!temp.empty()) {
            s.setEgzas(temp.back());
            temp.pop_back();
            s.setPazymiai(temp);
        }

        skaiciuokRezultatus(s);
        return is;
    }

    // Interaktyvus įvedimas
    std::string input, vard, pav;

    while (true) {
        std::cout << "Iveskite varda: ";
        is >> vard;
        if (std::all_of(vard.begin(), vard.end(), ::isalpha))
            break;
        std::cout << "Vardas gali tureti tik raides!\n";
    }
    s.setVard(vard);

    while (true) {
        std::cout << "Iveskite pavarde: ";
        is >> pav;
        if (std::all_of(pav.begin(), pav.end(), ::isalpha))
            break;
        std::cout << "Pavarde gali tureti tik raides!\n";
    }
    s.setPav(pav);

    std::vector<int> paz;
    is.ignore(10000, '\n');
    std::cout << "Iveskite pazymius vienas per eilute (enter baigti):\n";

    while (true) {
        getline(is, input);
        if (input.empty()) break;

        std::stringstream ss(input);
        int x;
        if (ss >> x && x >= 0 && x <= 10)
            paz.push_back(x);
        else
            std::cout << "Bloga ivestis. Pazymys turi buti 0-10.\n";
    }
    s.setPazymiai(paz);

    int egz;
    while (true) {
        std::cout << "Iveskite egzamino rezultata (0-10): ";
        is >> egz;

        if (!is.fail() && egz >= 0 && egz <= 10)
            break;

        is.clear();
        is.ignore(10000, '\n');
        std::cout << "Blogas egzamino ivestis!\n";
    }
    s.setEgzas(egz);

    skaiciuokRezultatus(s);
    return is;
}

// ===================== OPERATOR << =====================
std::ostream& operator<<(std::ostream& os, const Studentas& s) {
    os << std::left << std::setw(15) << s.getVard()
        << std::setw(15) << s.getPav()
        << "Galutinis (Vid.): " << std::setw(6) << std::fixed << std::setprecision(2) << s.getRezVid()
        << "  Galutinis (Med.): " << std::setw(6) << std::fixed << std::setprecision(2) << s.getRezMed();

    return os;
}

// ===================== Studento įvedimas =====================
Studentas ivesk() {
    Studentas s;
    int pasirinkimas;

    std::cout << "1 - ivesti ranka, 2 - generuoti: ";
    std::cin >> pasirinkimas;
    std::cin.ignore(10000, '\n');

    if (pasirinkimas == 2) {

        s.setVard("Vardas" + std::to_string(rand() % 100));
        s.setPav("Pavarde" + std::to_string(rand() % 100));

        std::vector<int> paz;
        for (int i = 0; i < 5; i++)
            paz.push_back(rand() % 11);

        s.setPazymiai(paz);
        s.setEgzas(rand() % 11);

        skaiciuokRezultatus(s);
        return s;
    }

    std::cin >> s;
    return s;
}

// ===================== Rezultatai =====================
void rodytiRezultatus(const std::vector<Studentas>& Grupe) {
    if (Grupe.empty()) {
        std::cout << "Nera studentu.\n";
        return;
    }

    for (const auto& s : Grupe)
        std::cout << s << "\n";
}

// ===================== Testai =====================
void testasRuleOfThreeIrIO() {
    std::cout << "\n===== Testuojame Rule of Three ir IO operatorius =====\n\n";

    // Copy konstruktorius
    std::vector<int> paz1 = { 8, 9, 10 };
    Studentas s1("Jonas", "Jonaitis", paz1, 9);
    skaiciuokRezultatus(s1);

    Studentas s2(s1);
    std::cout << "Copy konstruktoriaus testas:\n";
    std::cout << "Originalas: " << s1 << "\n";
    std::cout << "Kopija:     " << s2 << "\n\n";

    // Copy assignment
    std::vector<int> paz2 = { 6, 7, 8 };
    Studentas s3("Ona", "Onute", paz2, 10);
    skaiciuokRezultatus(s3);

    Studentas s4;
    s4 = s3;
    std::cout << "Copy assignment testas:\n";
    std::cout << "Originalas: " << s3 << "\n";
    std::cout << "Priskyrimas: " << s4 << "\n\n";

    // IO operatoriai
    std::string testInput = "Petras Petraitis 10 8 9 10";
    std::stringstream ss(testInput);

    Studentas s5;
    ss >> s5;
    skaiciuokRezultatus(s5);

    std::cout << "IO operatoriu testas:\n";
    std::cout << "Isvedimas: " << s5 << "\n";

    std::cout << "\n===== Testai baigti =====\n";
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

    // ==================== VECTOR DALIS ====================
    while (fgets(eil_r, sizeof(eil_r), open_f) != nullptr) {
        lineCounter++;
        if (lineCounter <= 2) continue;

        auto t1 = std::chrono::high_resolution_clock::now();
        std::stringstream ss(eil_r);
        Studentas s;

        std::string vardas, pavarde;
        ss >> vardas >> pavarde;
        s.setVard(vardas);
        s.setPav(pavarde);

        for (int i = 0; i < 5; i++) {
            int x; ss >> x;
            s.paz.push_back(x);  // paz yra public, todėl galima tiesiogiai
        }
        int egz; ss >> egz;
        s.setEgzas(egz);

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

    // Skirstymas
    std::vector<Studentas> protingiV, kvailiV;
    protingiV.reserve(visiStudentai.size());
    kvailiV.reserve(visiStudentai.size());

    for (const auto& s : visiStudentai) {
        if (s.getRezVid() >= 5 && s.getRezMed() >= 5)
            protingiV.push_back(s);
        else
            kvailiV.push_back(s);
    }

    // Rikiavimas (vector)
    auto rikiuokV = [&](std::vector<Studentas>& v) {
        switch (rikiavimas) {
        case 1: std::sort(v.begin(), v.end(), [](const auto& a, const auto& b) { return a.getVard() < b.getVard(); }); break;
        case 2: std::sort(v.begin(), v.end(), [](const auto& a, const auto& b) { return a.getPav() < b.getPav(); }); break;
        case 3: std::sort(v.begin(), v.end(), [](const auto& a, const auto& b) { return a.getRezVid() < b.getRezVid(); }); break;
        case 4: std::sort(v.begin(), v.end(), [](const auto& a, const auto& b) { return a.getRezVid() > b.getRezVid(); }); break;
        case 5: std::sort(v.begin(), v.end(), [](const auto& a, const auto& b) { return a.getRezMed() < b.getRezMed(); }); break;
        case 6: std::sort(v.begin(), v.end(), [](const auto& a, const auto& b) { return a.getRezMed() > b.getRezMed(); }); break;
        }
        };
    rikiuokV(protingiV);
    rikiuokV(kvailiV);

    // Rašymas (vector)
    std::string proNameVector = base + "_protinguliai_vector.txt";
    std::string kvaNameVector = base + "_kvailiukai_vector.txt";
    std::ofstream outProV(proNameVector), outKvaV(kvaNameVector);

    auto writeV = [&](std::ofstream& out, const std::vector<Studentas>& v, const std::string& fname) {
        double writeTime = 0;
        for (const auto& s : v) {
            auto t1 = std::chrono::high_resolution_clock::now();
            out << std::left << std::setw(15) << s.getVard()
                << std::setw(15) << s.getPav();
            if (rezPasirinkimas == 1)      out << std::setw(15) << std::fixed << std::setprecision(2) << s.getRezVid();
            else if (rezPasirinkimas == 2) out << std::setw(15) << std::fixed << std::setprecision(2) << s.getRezMed();
            else                            out << std::setw(15) << std::fixed << std::setprecision(2) << s.getRezVid()
                << std::setw(15) << std::fixed << std::setprecision(2) << s.getRezMed();
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
    std::cout << " Skaitymas: " << readTimeV << " s\n";
    std::cout << " Skaiciavimas: " << calcTimeV << " s\n";
    std::cout << " Rasymas: " << writeTimeV << " s\n";

    // ==================== LIST DALIS  ====================
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

        std::string vardas, pavarde;
        ss >> vardas >> pavarde;
        s.setVard(vardas);
        s.setPav(pavarde);

        for (int i = 0; i < 5; i++) { int x; ss >> x; s.paz.push_back(x); }
        int egz; ss >> egz; s.setEgzas(egz);

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
    for (const auto& s : visiStudentaiL) {
        if (s.getRezVid() >= 5 && s.getRezMed() >= 5)
            protingiL.push_back(s);
        else
            kvailiL.push_back(s);
    }

    // Rikiavimas (list)
    auto rikiuokL = [&](std::list<Studentas>& l) {
        switch (rikiavimas) {
        case 1: l.sort([](const auto& a, const auto& b) { return a.getVard() < b.getVard(); }); break;
        case 2: l.sort([](const auto& a, const auto& b) { return a.getPav() < b.getPav(); }); break;
        case 3: l.sort([](const auto& a, const auto& b) { return a.getRezVid() < b.getRezVid(); }); break;
        case 4: l.sort([](const auto& a, const auto& b) { return a.getRezVid() > b.getRezVid(); }); break;
        case 5: l.sort([](const auto& a, const auto& b) { return a.getRezMed() < b.getRezMed(); }); break;
        case 6: l.sort([](const auto& a, const auto& b) { return a.getRezMed() > b.getRezMed(); }); break;
        }
        };
    rikiuokL(protingiL);
    rikiuokL(kvailiL);

    // Rašymas (list)
    std::string proNameList = base + "_protinguliai_list.txt";
    std::string kvaNameList = base + "_kvailiukai_list.txt";
    std::ofstream outProL(proNameList), outKvaL(kvaNameList);

    auto writeL = [&](std::ofstream& out, const std::list<Studentas>& l, const std::string& fname) {
        double writeTime = 0;
        for (const auto& s : l) {
            auto t1 = std::chrono::high_resolution_clock::now();
            out << std::left << std::setw(15) << s.getVard()
                << std::setw(15) << s.getPav();
            if (rezPasirinkimas == 1)      out << std::setw(15) << std::fixed << std::setprecision(2) << s.getRezVid();
            else if (rezPasirinkimas == 2) out << std::setw(15) << std::fixed << std::setprecision(2) << s.getRezMed();
            else                            out << std::setw(15) << std::fixed << std::setprecision(2) << s.getRezVid()
                << std::setw(15) << std::fixed << std::setprecision(2) << s.getRezMed();
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
    std::cout << " Skaitymas: " << readTimeL << " s\n";
    std::cout << " Skaiciavimas: " << calcTimeL << " s\n";
    std::cout << " Rasymas: " << writeTimeL << " s\n";
}
