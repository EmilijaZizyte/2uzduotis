#  Įvesties/išvesties operatorius V1.2

   **1**. operator>> (įvestis). Įgyvendinta studentas.cpp faile. Šis operatorius leidžia patogiai nuskaityti studento duomenis, atliekant įvesties validaciją ir automatiškai apskaičiuojant galutinius rezultatus. Galima naudoti tiek su std::cin, tiek su ifstream. 
  **2**. operator<< (išvestis). Įgyvendinta studentas.cpp faile. Šis operatorius suteikia galimybę tvarkingai ir aiškiai formatuoti išvestį tiek į konsolę, tiek į failą per ofstream.
  **3**. Rankinė įvestis. Rankinė studento informacijos įvestis įgyvendinama funkcijoje „Studentas ivesk();“
     Vartotojas gali pasirinkti:
  1 – rankinė įvestis, kviečiamas operator>> (įvedami vardas, pavardė, ND, egzaminas)
  2 – automatinė generacija, sugeneruojamas atsitiktinis studento įrašas
  **4.** Automatinė generacija. Sugeneruotas studentas kuriamas funkcijoje „Studentas ivesk();“ pasirinkus režimą 2 – generuoti.
  **5.**  Išvestis į failą. Studentų išvedimas į ekraną ar failą atliekamas per „void rodytiRezultatus(const std::vector<Studentas>& Grupe);“ Ji naudoja operator<< kiekvienam studentui:
  for (auto& s : Grupe)
      std::cout << s << "\n";
  Ši funkcija gali būti naudojama ir su ifstream/ofstream, todėl lengvai pritaikoma failų rašymui.

  | Metodas | Paskirtis |
|---------|-----------|
| `Studentas(const Studentas& other)` | Kopijavimo konstruktorius – sukuria naują objektą kopijuojant kitą `Studentas` objektą. |
| `Studentas& operator=(const Studentas& other)` | Kopijavimo priskyrimo operatorius – kopijuoja reikšmes į jau egzistuojantį objektą. |
| `Studentas(Studentas&& other) noexcept` | Perkelimo konstruktorius – perkelia (move) kito objekto duomenis, užtikrina efektyvumą. |
| `Studentas& operator=(Studentas&& other) noexcept` | Perkelimo priskyrimo operatorius – perkelia duomenis į jau sukurtą objektą. |
| `~Studentas()` | Destruktorius – išvalo objekto vidinius resursus. |

  **IO operatoriai**
operator>> leidzia nuskaityti studenta is srauto.
operator<< leidzia isvesti studenta i srauta.

  
# Studentų apdorojimo rezultatu palyginimas V1.1

  Testai atlikti su vector konteineriu, greičiausiai strategijai, t.y. 1, dviejų failų dydžiams:
  studentai1000000.txt
  studentai10000000.txt

**KLASĖ 1.000.000 STUDENTŲ**
| Optimizacija | Nuskaitymas | Skaidymas   | Rašymas    | Atmintis   | EXE dydis |
|--------------|-------------|-------------|------------|------------|-----------|
| O1           | 4.85238 s   | 0.143274 s  | 2.17749 s  | 213.62 MB  | 107 KB    |
| O2           | 4.42977 s   | 0.128982 s  | 2.08829 s  | 213.62 MB  | 137 KB    |
| O3           | 4.37301 s   | 0.126603 s  | 2.20001 s  | 213.62 MB  | 139 KB    |

**KLASĖ 10.000.000 STUDENTŲ**
| Optimizacija | Nuskaitymas | Skaidymas | Rašymas   | Atmintis    | EXE dydis |
|--------------|-------------|-----------|-----------|-------------|-----------|
| O1           | 71.04 s     | 5.68 s    | 29.97 s   | 2136.23 MB  | 107 KB    |
| O2           | 48.39 s     | 1.48 s    | 22.37 s   | 2136.23 MB  | 137 KB    |
| O3           | 50.13 s     | 1.52 s    | 22.47 s   | 2136.23 MB  | 139 KB    |


**STRUKTŪRA 1.000.000 STUDENTŲ**
| Optimizacija | Nuskaitymas | Skaidymas   | Rašymas    | Atmintis   | EXE dydis |
|--------------|-------------|-------------|------------|------------|-----------|
| O1           | 4.46482 s   | 0.147022 s  | 2.11217 s  | 213.62 MB  | 105 KB    |
| O2           | 4.39 s      | 0.13 s      | 2.01 s     | 213.62 MB  | 134 KB    |
| O3           | 4.33 s      | 0.13 s      | 2.18 s     | 213.62 MB  | 136 KB    |

**STRUKTŪRA 10.000.000 STUDENTŲ**
| Optimizacija | Nuskaitymas | Skaidymas | Rašymas   | Atmintis    | EXE dydis |
|--------------|-------------|-----------|-----------|-------------|-----------|
| O1           | 47.53 s     | 10.04 s   | 27.27 s   | 2136.23 MB  | 105 KB    |
| O2           | 55.617 s    | 3.12562 s | 22.4109 s | 2136.23 MB  | 134 KB    |
| O3           | 54.16 s     | 4.74 s    | 29.19 s   | 2136.23 MB  | 136 KB    |

***IŠVADOS***
  01: Didelių duomenų kiekių O1 testas parodo, kad klasė efektyviau skaido duomenis, todėl dideliems vektoriams klasė yra geresnis pasirinkimas.

  02: Skaidymas klasėje žymiai greitesnis (1.48 s vs 10.04 s), rašymas klasėje šiek tiek greitesnis nei struktūroje dideliems duomenims (22.37 s vs 27.27 s). O2     testui dideliam duomenų kiekiui klasė efektyvesnė.

   03: Maži duomenys (1M): klasė ir struktūra praktiškai nesiskiria. Dideli duomenys: klasė spartesnė skaidyme ir rašyme, dideliems duomenims naudoti klasę.

**EXE FAILO DYDIS**
***KLASĖS EXE dydžiai:***
107 KB – 139 KB
***STRUKTŪROS EXE dydžiai:*** 
105 KB – 136 KB
EXE dydžių skirtumai minimalūs (tik keli KB).

# Studentų apdorojimo rezultatu palyginimas V1.0




| Studentų kiekis | Struktūra | Strategija | Nuskaitymas (s) | Skaidymas (s) | Rašymas (s) | Atmintis (MB) | Kietiakai | Vargsiukai |
|----------------:|:----------|:-----------|-----------------:|---------------:|-------------:|---------------:|-----------:|-----------:|
| **1 000** | Vector | 1 | 0.00429 | 0.00016 | 0.00396 | 0.21 | 507 | 493 |
|  | List | 1 | 0.00 | 0.00 | 0.01 | 0.24 | 507 | 493 |
|  | Vector | 2 | 0.00 | 0.00 | 0.00 | 0.13 | 507 | 493 |
|  | List | 2 | 0.01 | 0.00 | 0.01 | 0.14 | 507 | 493 |
|  | Vector (STL) | 1 | 0.01 | 0.00 | 0.00 | 0.11 | 507 | 493 |
| **10 000** | Vector | 1 | 0.04243 | 0.00134 | 0.02151 | 2.14 | 4754 | 5246 |
|  | List | 1 | 0.05 | 0.00 | 0.02 | 2.44 | 4754 | 5246 |
|  | Vector | 2 | 0.05 | 0.36 | 0.02 | 1.26 | 4754 | 5246 |
|  | List | 2 | 0.04 | 0.00 | 0.02 | 1.41 | 4754 | 5246 |
|  | Vector (STL) | 1 | 0.04 | 0.00 | 0.02 | 1.07 | 4754 | 5246 |
| **100 000** | Vector | 1 | 0.41221 | 0.01044 | 0.18965 | 21.36 | 48113 | 51887 |
|  | List | 1 | 0.43 | 0.02 | 0.19 | 24.41 | 48113 | 51887 |
|  | Vector | 2 | 0.46 | 42.13 | 0.20 | 12.59 | 48113 | 51887 |
|  | List | 2 | 0.44 | 0.01 | 0.20 | 14.11 | 48113 | 51887 |
|  | Vector (STL) | 1 | 0.43 | 0.02 | 0.21 | 10.68 | 48113 | 51887 |
| **1 000 000** | Vector | 1 | 4.25 | 0.13 | 1.95 | 210 | 501210 | 498790 |
|  | List | 1 | 4.70 | 0.15 | 2.10 | 238 | 501210 | 498790 |
|  | Vector | 2 | 4.85 | 4325 | 2.05 | 125 | 501210 | 498790 |
|  | List | 2 | 4.60 | 0.12 | 2.00 | 142 | 501210 | 498790 |
|  | Vector (STL) | 1 | 4.15 | 0.10 | 1.90 | 110 | 501210 | 498790 |
| **10 000 000** | Vector        | 1 | 86.417 | 281.539 | 39.884 | 2100 | 4 012 050 | 4 927 954 |
|                | List          | 1 | 90.125 | 295.210 | 42.000 | 2380 | 4 012 050 | 4 927 954 |
|                | Vector        | 2 | 88.500 | 4345.000 | 41.500 | 1250 | 4 012 050 | 4 927 954 |
|                | List          | 2 | 87.000 | 280.000 | 40.800 | 1445 | 4 012 050 | 4 927 954 |
|                | Vector (STL) | 1 | 85.200 | 270.500 | 38.900 | 1100 | 4 012 050 | 4 927 954 |



## 1. CMake diegimas Windows sistemoje naudojant .msi paketą

1. Eikite į oficialų CMake atsisiuntimo puslapį:  
   https://cmake.org/download/

2. Pasirinkite tinkamą paketą:  
   - Windows ×64 Installer (.msi) versija  
   - Pavyzdžiui: `cmake-3.25-windows-x86_64.msi`

3. Paleiskite diegimo failą:  
   - Dukart spustelėkite atsisiųstą `.msi` failą  
   
4. Diegimo metu nustatykite parametrus:  
   - Pažymėkite „Add CMake to the system PATH for all users“  
   - Pasirinkite diegimo vietą (pagal nutylėjimą: `C:\Program Files\CMake\`)  
   - Spauskite „Next“ -> „Install“ ir palaukite, kol diegimas baigsis

5. Patikrinkite diegimą:  
   -Atidarykite „Command Prompt“ arba „PowerShell“ ir įveskite:
   -cmake --version

   
## Kaip sukompiliuoti ir paleisti programą

1. Iš šios github repozitorijos, atsisiųskite CMakeFiles.txt, failai.h, studentai.h, failai.cpp, pagrindinis.cpp, studentai.cpp failus.

2. Susikurkite darbinį aplankalą, kuriame norėsite vykdyti programą. Į šį aplanką įdėkite visus parsisiųstusfailus iš github. Šiame aplankale sukurkite dar du aplankalus: src ir Include (būtinai tokiais pavadinimais). Į src aplanką perkelkite visus .cpp failus (failai.cpp, pagrindinis.cpp, studentai.cpp), o į Include visus .h failus (failai.h, studentai.h).

3.Atidarykite komandų eilutę (cmd) ir eikite į projekto katalogą, kuriame yra CMakeLists.txt. 
- Pavyzdžiui:
- cd C:\Users\computer\Desktop\cmake

4.Sugeneruokite build failus su CMake komanda:
- cmake .\CMakeLists.txt

5.Skompiliuokite projektą:
- cmake --build 

6.Pereikite į katalogą, kuriame sukurtas vykdomasis failas:
- cd C:\Users\computer\Desktop\cmake\build\Debug

5.Paleiskite programą:
- Studentu_programa.exe



## V0.1 trumpas aprašas
Programa dirba su studentų sąrašu: leidžia įvesti arba sugeneruoti studentus, skaičiuoti galutinius balus pagal vidurkį ar medianą, ir saugoti rezultatus į failą. Ji palaiko tiek mažų, tiek labai didelių failų nuskaitymą. Didelių failų atveju rezultatai automatiškai išsaugomi į failą, kad nebūtų spausdinama milijonai eilučių į konsolę. Programa turi meniu su pasirinkimais pridėti studentą, rodyti rezultatus, skaityti failą ir skaičiuoti egzaminų išlaikymą/neišlaikymą. Papildomos funkcijos tikrina įvesties teisingumą (vardai, pavardės, pažymiai) ir skaičiuoja mediana bei vidurkį, užtikrindamos patikimus rezultatus.

## V0.2 trumpas aprašas
Programa valdo studentų duomenis: leidžia įvesti arba generuoti studentus, skaičiuoja galutinį vidurkį ir medianą, rodo rezultatus konsolėje, generuoja tekstinius failus su atsitiktiniais duomenimis ir analizuoja juos, rūšiuodama pagal vardą, pavardę, vidurkį arba medianą bei skirstydama studentus į „protingus“ ir „kvailiukus“. Nuo praeito releaso skiriasi, nes yra pridėtas spartos rezultatai, yra pridėtas matavimas du kartus ir matavimas kitame kompiuteryje

## V0.3 trumpas aprašas
Ši programa padeda tvarkyti studentų rezultatus. Joje galima įvesti studentų duomenis ranka arba sugeneruoti atsitiktinius, o programa apskaičiuoja galutinius pažymius pagal namų darbų vidurkį ir medianą. Rezultatus galima peržiūrėti lentelėje arba sugeneruoti testinius failus su tūkstančiais studentų. Programa taip pat gali nuskaityti tokius failus, apdoroti visus studentus, rikiuoti pagal vardą, pavardę ar galutinį pažymį ir padalinti į grupes „protingi“ ir „kvailiukai“, kurių rezultatai įrašomi į naujus failus. Visa tai valdomas paprastu meniu, todėl lengva tvarkyti tiek mažą, tiek didelę duomenų apimtį.
