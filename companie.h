#ifndef COMPANIE_H
#define COMPANIE_H

#include <fstream>
#include <iostream>
#include <unordered_map>
#include "departament.h"

using namespace std;

class Companie
{
private:
	string nume;
	unordered_map<string, Departament> departamente;

public:
    const unordered_map<string, Departament>& getDepartamente() const
    {
        return departamente;
    }
	Companie(const string& nume=""):nume(nume){}
	void adauga_departament(const string& numeDep);
	void adauga_angajat_departament(const string& numeDep, unsigned int codAngajat,double salariu);
	int incarca_datele(const string& numeFisier);
	void afiseaza_date_departament();
    void sterge_departament(const string& numeDep)
    {
        auto it = departamente.find(numeDep);
        if (it != departamente.end())  // Verificăm dacă departamentul există
        {
            departamente.erase(it);  // Ștergem departamentul din map
            cout << "Departamentul " << numeDep << " a fost șters.\n";
        }
        else
        {
            cout << "Departamentul " << numeDep << " nu există.\n";
        }
    }
};

#endif
