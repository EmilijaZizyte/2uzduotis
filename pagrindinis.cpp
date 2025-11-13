#include <iostream>
#include <vector>
#include <list>
#include <ctime>
#include "studentas.h"
#include "failai.h"

// ======== Template funkcija rezultatams rodyti ========
template <typename T>
void rodytiRezultatus(const T& container) {
    std::cout << "\n=== Studentu rezultatai ===\n";
    for (const auto& s : container) {
        std::cout << "Vardas: " << s.getVard()
            << ", Pavarde: " << s.getPav()
            << ", Egzaminas: " << s.getEgzas()
            << ", Vidurkis: " << s.getRezVid()
            << ", Mediana: " << s.getRezMed() << "\n";
    }
}

// ======== Main funkcija ========
int main() {
    std::srand(static_cast<unsigned>(std::time(0)));

    std::vector<Studentas> GrupeVector;
    std::list<Studentas> GrupeList;

    while (true) {
        std::cout << "\nPasirinkite:\n";
        std::cout << "1 - Prideti viena studenta\n";
        std::cout << "2 - Rodyti studentu rezultatus\n";
        std::cout << "3 - Baigti programa\n";
        std::cout << "4 - Generuoti testinius failus\n";
        std::cout << "5 - Nuskaityti visus failus\n";
        std::cout << "6 - Testuoti strategijas\n";
        std::cout << "7 - 1mln 10mln vektoriui testavimas\n";
        std::cout << "Jusu pasirinkimas: ";

        int pasirinkimas;
        std::cin >> pasirinkimas;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Bloga ivestis. Bandykite dar karta.\n";
            continue;
        }

        std::cin.ignore(10000, '\n');

        if (pasirinkimas == 1) {
            std::cout << "\n=== Ivedimas ir issaugojimas ===\n";
            Studentas s = ivesk();

            GrupeVector.push_back(s);
            std::cout << "Studentas '" << s.getVard() << " " << s.getPav()
                << "' issaugotas vectoriuje adresu: " << &GrupeVector.back() << "\n";

            GrupeList.push_back(s);
            std::cout << "Studentas '" << s.getVard() << " " << s.getPav()
                << "' issaugotas liste adresu: " << &GrupeList.back() << "\n";
        }
        else if (pasirinkimas == 2) {
            rodytiRezultatus(GrupeVector);
            rodytiRezultatus(GrupeList);
        }
        else if (pasirinkimas == 3) {
            std::cout << "Programa baigta.\n";
            break;
        }
        else if (pasirinkimas == 4) {
            generuokFailus();
        }
        else if (pasirinkimas == 5) {
            analizuokVisusFailusMinimaliai();
        }
        else if (pasirinkimas == 6) {
            int strategija;
            std::string failas;
            std::cout << "Iveskite failo pavadinima: ";
            std::cin >> failas;

            std::cout << "Kurios strategijos noretumet: \n"
                << "1 - Skaidymas i du konteinerius\n"
                << "2 - Vieno naujo konteinerio naudojimas\n"
                << "3 - Greiciausios strategijos nustatymas ir STL vector pritaikymas\n";
            std::cin >> strategija;

            if (strategija == 1) {
                strategija1_skaidymas(failas);
            }
            else if (strategija == 2) {
                Strategija2(failas);
            }
            else if (strategija == 3) {
                Strategija3(failas);
            }
            else {
                std::cout << "Netinkamas pasirinkimas. Bandykite dar karta.\n";
            }
        }
        else if (pasirinkimas == 7) {
            std::string failas;
            std::cout << "Iveskite failo pavadinima: ";
            std::cin >> failas;
            strategija1_STL_vectoriui(failas);
        }
        else {
            std::cout << "Netinkamas pasirinkimas. Bandykite dar karta.\n";
        }
    }

    return 0;
}
