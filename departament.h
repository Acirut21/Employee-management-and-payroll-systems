#ifndef DEPARTAMENT_H
#define DEPARTAMENT_H

#include <vector>
#include <string>

using namespace std;

class Departament
{
private:
	string nume;
	vector<unsigned int>coduriAngajati;
	double costTotalSalarii;

public:
    Departament(const std::string& nume = "", double costSalarii = 0.0)
        : nume(nume), costTotalSalarii(costSalarii) {}

    
    const std::string& getNume() const { return nume; }
    void setNume(const std::string& numeNou) { nume = numeNou; }

    const std::vector<unsigned int>& getCoduriAngajati() const { return coduriAngajati; }
    void adaugaCodAngajat(unsigned int cod) { coduriAngajati.push_back(cod); }

    double getCostTotalSalarii() const { return costTotalSalarii; }
    void adaugaLaCostSalarii(double salariu) { costTotalSalarii += salariu; }
};

#endif