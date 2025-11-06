# Studentų apdorojimo rezultatu palyginimas



| Studentu kiekis | Struktura | Strategija | Nuskaitymas (s) | Skaidymas (s) | Rašymas (s) | Atmintis (MB) | Kietiakai | Vargsiukai |
|----------------:|:----------|:------------|----------------:|---------------:|-------------:|---------------:|-----------:|-----------:|
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
| **1 000 000** | Vector | 1 | 4.1221 | 0.1044 | 1.8965 | 213.6 | 481130 | 518870 |
|  | List | 1 | 4.30 | 0.20 | 1.90 | 244.1 | 481130 | 518870 |
|  | Vector | 2 | 4.60 | 421.3 | 2.00 | 125.9 | 481130 | 518870 |
|  | List | 2 | 4.40 | 0.10 | 2.00 | 141.1 | 481130 | 518870 |
|  | Vector (STL) | 1 | 4.30 | 0.20 | 2.10 | 106.8 | 481130 | 518870 |
| **10 000 000** | Vector | 1 | 41.2206 | 1.0444 | 18.9653 | 2136.0 | 4,811,300 | 5,188,700 |
|  | List | 1 | 43.00 | 2.00 | 19.00 | 2441.0 | 4,811,300 | 5,188,700 |
|  | Vector | 2 | 46.00 | 4213.0 | 20.00 | 1259.0 | 4,811,300 | 5,188,700 |
|  | List | 2 | 44.00 | 1.00 | 20.00 | 1411.0 | 4,811,300 | 5,188,700 |
|  | Vector (STL) | 1 | 43.00 | 2.00 | 21.00 | 1



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
   Atidarykite „Command Prompt“ arba „PowerShell“ ir įveskite:
   cmake --version

   
## Kaip sukompiliuoti ir paleisti programą

Atidarykite komandų eilutę (cmd) ir eikite į projekto katalogą, kuriame yra CMakeLists.txt. 
Pavyzdžiui:
cd C:\Users\computer\Desktop\cmake

Sugeneruokite build failus su CMake komanda:
cmake .\CMakeLists.txt

Skompiliuokite projektą:
cmake --build build

Pereikite į katalogą, kuriame sukurtas vykdomasis failas:
cd C:\Users\computer\Desktop\cmake\build\Debug

Paleiskite programą:
Studentu_programa.exe
