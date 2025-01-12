#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>

#include "utilizator.h"

using namespace std;

class Admin : public Utilizator
{
private:
	string departament;
	unsigned varsta;
	unsigned clasa_risc;
	unsigned vechime_angajat;
public:
	Admin();
	Admin(const string& nume, const string& prenume, const string& username, const string& parola,
		const string& departament, unsigned varsta, unsigned cod, unsigned vechime, unsigned risc)
		: Utilizator(nume, prenume, username, parola, cod), // Apelăm constructorul de bază
		departament(departament), varsta(varsta), vechime_angajat(vechime), clasa_risc(risc)
	{

	}
	~Admin();
	string getDepartament() const override {
		return departament;
	}
	unsigned getVechimeAngajat() const;
	unsigned getClasaRisc() const;
	unsigned getVarsta() const;

	void setDepartament(const string& departament);
	void setVarsta(const unsigned& varsta);
	void setClasaRisc(const unsigned& clasarisc);
	void setVechime(const unsigned& vechime);

	int adaugare_angajat();
	int eliminare_angajat();
	int editare_angajat();
};

#endif