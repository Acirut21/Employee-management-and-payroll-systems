#include <fstream>
#include <iostream>
#include <unordered_map>

#include "companie.h"
#include "departament.h"
#include "salarizare.h"

extern Departament departament;
extern Salarizare salariul;

Salarizare salariul;

using namespace std;

void Companie::adauga_departament(const string& numeDep)
{
	if (departamente.find(numeDep) == departamente.end())
	{
		departamente[numeDep] = Departament(numeDep);
	}
}

void Companie::adauga_angajat_departament(const string& numeDep, unsigned int codAngajat,double salariu)
{
	adauga_departament(numeDep); // Creează departamentul dacă nu există
	departamente[numeDep].adaugaCodAngajat(codAngajat);
	departamente[numeDep].adaugaLaCostSalarii(salariu);
}

int Companie::incarca_datele(const string& numeFisier)
{
	ifstream fisier(numeFisier);
	
	if (!fisier.is_open())
	{
		cerr << "Eroare la deschiderea fisierului " << numeFisier << "!\n";
		return false;
	}

	string nume, prenume, username, parola, departament;
	unsigned varsta, cod, vechime, risc,salariu=0;

	while (fisier >> nume >> prenume >> username >> parola >> varsta >> cod >> vechime >> risc >> departament)
	{
		salariu = salariul.getter_salariu(cod);
		adauga_angajat_departament(departament, cod, salariu);
	}

	fisier.close();
	return true;
}

void Companie::afiseaza_date_departament()
{
	for (const auto& pair : departamente) 
	{
		const string& nume = pair.first;           // Cheia map-ului
		const Departament& departament = pair.second;   // Valoarea map-ului

		cout << "Departament: " << nume << "\n";
		cout << "Angajati: ";
		for (const auto& cod : departament.getCoduriAngajati()) 
		{
			cout << cod << " ";
		}
		cout << "\nCost total salarii: " << departament.getCostTotalSalarii() << "\n\n";
	}
}
