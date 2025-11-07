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
| **10 000 000** | Vector | 1 | 42.8 | 1.45 | 19.4 | 2100 | 5 012 050 | 4 987 950 |
|  | List | 1 | 47.5 | 1.60 | 21.2 | 2380 | 5 012 050 | 4 987 950 |
|  | Vector | 2 | 49.0 | 4345 | 21.8 | 1250 | 5 012 050 | 4 987 950 |
|  | List | 2 | 46.0 | 1.35 | 20.7 | 1445 | 5 013 050 | 4 097 950 |
|  | Vector (STL) | 1 | 41.2 | 1.20 | 18.9 | 1100 | 5 012 050 | 4 987 950 |




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
