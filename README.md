#  UNIT TESTAI
<img width="1386" height="923" alt="image" src="https://github.com/user-attachments/assets/a61cead1-9a9f-41fb-83e5-03cebe9966f2" />


Šiame faile realizuojami testai, skirti tikrinti atskirų programos funkcijų ir klasių veikimą naudojant „Google Test“ karkasą. Pirmoji testų dalis tikrina funkciją mediana, pateikiant tris skirtingus scenarijus: kai elementų skaičius nelyginis, kai lyginis ir kai likęs tik vienas elementas. Tokiu būdu užtikrinama, kad funkcija teisingai apskaičiuoja medianą įvairiomis sąlygomis. Antroji dalis skirta klasei Studentas: tikrinami konstruktoriai, getter ir setter metodai, duomenų inicializavimas bei kopijavimo konstruktoriaus veikimas. Testai užtikrina, kad objektas sukuriamas su numatytomis reikšmėmis, set’eriai korektiškai priskiria duomenis, o kopijavimo konstruktorius teisingai perkelia visus laukus į naują objektą. Failo pabaigoje pateiktas main metodas inicijuoja Google Test aplinką ir paleidžia visus aprašytus testus.
Įkeltoje ekrano nuotraukoje, matyti sėkmingas testų vykdymas

## Testų paleidimas

Projektas naudoja Visual Studio įdiegtą Google Test aplinką. Testams sugeneruoti buvo pasirinktas
Google Test projekto šablonas, todėl jokių papildomų install nereikia.

### Kaip prijungti testus prie programos kodo
1. Atidarykite **Google Testai** -> *References*.
2. Pasirinkite **Add Reference**.
3. Pažymėkite pagrindinį projekto modulį (pvz. 'V2.0').

Taip testų projektas gali naudoti 'studentas.h', 'zmogus.h' ir kitus '.cpp' bei '.h' failus.

### Kaip paleisti testus
Viršutiniame meniu pasirinkite **Test -> Run All Tests**, 

  arba
  
Atidarykite Test Explorer -> **Run All**.

Testai paleidžiami ir išspausdinami rezultatai

#  Abstrakti klasė Zmogus

Dėl abstrakčių funkcijų neįmanoma sukurti Žmogus objekto, tik išvestinę klasę. Demonstracija kompiliavimo metu (rezultatas, ką gauname paleidus programą):

<img width="1082" height="737" alt="image" src="https://github.com/user-attachments/assets/26595a89-d84b-43b7-aced-eb7fda10bb35" />


Rezultatas: negalima sukurti Žmogus objekto, galima tik išvestinį Studentas, klasė Zmogus, turi būti užkomentuota, kitaip, programos veikimo metu bus spausdinama klaida.


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

**Rule of Three demonstracija**


<img width="837" height="212" alt="image" src="https://github.com/user-attachments/assets/a9165aee-2627-4d4f-abb4-58b24cfd49e2" />


Pagrindiniame main.cpp galima vartotojui leidžiama pasirinkti (8), ar nori patikrinti Rule of three taisykę, ir įsitikinti, kad operatoriai veikia teisingai, prisikiriama funkcija testasRuleOfThreeIrIO() skirta patikrinti Studentas klasės kopijavimo, priskyrimo ir IO operatorių veikimą. Pirmiausia sukuriamas studentas s1, kurio duomenys kopijuojami į s2 naudojant kopijavimo konstruktorių, taip pat išvedamas originalas ir kopija, kad patikrintų duomenų teisingumą. Tada testuojamas kopijavimo priskyrimas, kai egzistuojančiam objektui s4 priskiriami duomenys iš s3, o rezultatai išvedami ekrane. Galiausiai tikrinami IO operatoriai: naudojant stringstream įvedami studento duomenys į s5, paskaičiuojami galutiniai rezultatai ir išvedami, kad įsitikinti operatorių teisingu veikimu. Tokiu būdu patikrinama, kad kopijavimas, priskyrimas ir įvedimas/išvedimas veikia teisingai ir nekelia klaidų.

 **Destruktorius**

<img width="166" height="172" alt="image" src="https://github.com/user-attachments/assets/9c3cb44f-3f9f-420c-b3dd-0f2e48359e27" />

Destruktorius rankiniu būdu išvalo visus Studentas objekto duomenis, kai objektas sunaikinamas. Tai užtikrina, kad visi resursai būtų tinkamai atlaisvinti. 

**Kopijavimo konstruktorius**


<img width="677" height="83" alt="image" src="https://github.com/user-attachments/assets/4674a896-149d-4dc9-81c4-7b137f1ddac9" />

Kopijavimo konstruktorius, naudojamas kai mes norime sukurti nauja objekta, naudojame kai norime sukurti ka? nauja objekta is esamo objekto, mano kode jis naudojamas kai mes priskiriame viena objekta kitam, pvz: Studentas s2 = s1;

**Priskyrimo operatorius**

<img width="457" height="237" alt="image" src="https://github.com/user-attachments/assets/174d09c1-b2ff-426e-9abd-ce0fa0e7ec57" />

 Priskirimo operatorius turi patikrinti ar mes nepriskiriam objekto sau paciam, kode: if (this != &other) {} 


**Perdengti įvesties ir išvesties operatoriai**

Įvesties ranka operatorius (operator>>)

Skaito studento duomenis iš įvesties srauto

 <img width="727" height="482" alt="image" src="https://github.com/user-attachments/assets/e88dae81-6466-431d-a883-05502f7b32f3" />
 <img width="637" height="506" alt="image" src="https://github.com/user-attachments/assets/8d65f8e3-04d1-4700-b0df-bffe953bf46a" />

 **Išvesties operatorius**

 <img width="972" height="172" alt="image" src="https://github.com/user-attachments/assets/2bcd56e0-d050-4f30-befe-4b4b11a96572" />
 

  
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
