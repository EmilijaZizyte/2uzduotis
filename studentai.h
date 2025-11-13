#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <numeric>
#include <sstream> 

class Studentas {
private:
    std::string vard;
    std::string pav;
    std::vector<int> paz;
    int egzas{};
    double rezVid{};
    double rezMed{};

public:
    Studentas() = default;

    // Setters
    void setVard(const std::string& v) { vard = v; }
    void setPav(const std::string& p) { pav = p; }
    void setPazymiai(const std::vector<int>& p) { paz = p; }
    void setEgzas(int e) { egzas = e; }
    void setRezVid(double r) { rezVid = r; }
    void setRezMed(double r) { rezMed = r; }

    // Getters
    std::string getVard() const { return vard; }
    std::string getPav() const { return pav; }
    std::vector<int> getPaz() const { return paz; }
    int getEgzas() const { return egzas; }
    double getRezVid() const { return rezVid; }
    double getRezMed() const { return rezMed; }

   
    
    friend void skaiciuokRezultatus(Studentas& s);
};
Studentas ivesk();
