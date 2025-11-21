#pragma once
#include <string>
#include <iostream>

class Zmogus {
protected:
    std::string vard;
    std::string pav;

public:
    Zmogus() : vard(""), pav("") {}
    Zmogus(const std::string& v, const std::string& p) : vard(v), pav(p) {}

    virtual ~Zmogus() = default;

    // Abstrakti funkcija — privalo b?ti perrašyta Studentas klas?je
    virtual void spausdinti() const = 0;

    // Getteriai
    std::string getVard() const { return vard; }
    std::string getPav() const { return pav; }

    // Setteriai
    void setVard(const std::string& v) { vard = v; }
    void setPav(const std::string& p) { pav = p; }
};
