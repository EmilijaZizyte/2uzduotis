#include <iostream>
#include <vector>
#include <ctime>
#include "studentas.h"
#include "failai.h"

int main() {
    std::srand(static_cast<unsigned>(std::time(0)));
    std::vector<Studentas> Grupe;

    while (true) {
        std::cout << "\nPasirinkite:\n";
        std::cout << "1 - Prideti viena studenta\n";
        std::cout << "2 - Rodyti studentu rezultatus\n";
        std::cout << "3 - Baigti programa\n";
        std::cout << "4 - Generuoti testinius failus\n";
        std::cout << "5 - Nuskaityti visus failus\n";
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
            pridetiStudenta(Grupe);
        }
        else if (pasirinkimas == 2) {
            rodytiRezultatus(Grupe);
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
        else {
            std::cout << "Netinkamas pasirinkimas. Bandykite dar karta.\n";
        }
    }

    return 0;
}
