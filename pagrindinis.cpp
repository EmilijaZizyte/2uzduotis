#include <iostream>
#include <vector>
#include <ctime>
#include "studentas.h"
#include "failai.h"

using namespace std;

int main() {
    srand(static_cast<unsigned>(time(0)));
    vector<Studentas> Grupe;

    while (true) {
        cout << "\nPasirinkite:\n";
        cout << "1 - Prideti viena studenta\n";
        cout << "2 - Rodyti studentu rezultatus\n";
        cout << "3 - Baigti programa\n";
        cout << "4 - Generuoti testinius failus\n";
        cout << "5 - Nuskaityti visus failus\n";
        cout << "Jusu pasirinkimas: ";

        int pasirinkimas;
        cin >> pasirinkimas;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Bandykite dar karta.\n";
            continue;
        }

        cin.ignore(10000, '\n'); 

        if (pasirinkimas == 1) {
            pridetiStudenta(Grupe);
        }
        else if (pasirinkimas == 2) {
            rodytiRezultatus(Grupe);
        }
        else if (pasirinkimas == 3) {
            cout << "Programa baigta.\n";
            break;
        }
        else if (pasirinkimas == 4) {
            generuokFailus();
        }
        else if (pasirinkimas == 5) {
            analizuokVisusFailusMinimaliai();
        }
        else {
            cout << "Netinkamas pasirinkimas. Bandykite dar karta.\n";
        }
    }

    return 0;
}
