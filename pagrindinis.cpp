#include <iostream>
#include <vector>
#include <list>
#include <ctime>
#include <sstream> 
#include "studentas.h"
#include "failai.h"

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
        std::cout << "Jusu pasirinkimas: ";
        int pasirinkimas;
        std::cin >> pasirinkimas;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Bandykite dar karta.\n";
            continue;
        }

        std::cin.ignore(10000, '\n');
        if (pasirinkimas == 1) {
            std::cout << "\n=== Ivedimas ir issaugojimas ===\n";
            Studentas s = ivesk();

            GrupeVector.push_back(s);
            std::cout << "Studentas '" << s.vard << " " << s.pav
                << "' issaugotas vectoriuje adresu: " << &GrupeVector.back() << "\n";

            GrupeList.push_back(s);
            std::cout << "Studentas '" << s.vard << " " << s.pav
                << "' issaugotas liste adresu: " << &GrupeList.back() << "\n";
        }

        else if (pasirinkimas == 2) {
			rodytiRezultatus(GrupeVector);
        }
        else if (pasirinkimas == 3) break;
        else if (pasirinkimas == 4) generuokFailus();
        else if (pasirinkimas == 5) analizuokVisusFailusMinimaliai();
        else if (pasirinkimas == 6) {
            std::string failas;
            int strategija;
            std::cout << "Iveskite failo pavadinima: ";
            std::cin >> failas;
            std::cout << "Kurios strategijos noretumet (1-3): ";
            std::cin >> strategija;
            if (strategija == 1) strategija1_skaidymas(failas);
            else if (strategija == 2) Strategija2(failas);
            else if (strategija == 3) Strategija3(failas);
            else std::cout << "Netinkamas pasirinkimas.\n";
        }
        else std::cout << "Netinkamas pasirinkimas.\n";
    }
    return 0;
}
