#ifndef ANGAJAT_H
#define ANGAJAT_H

#include <iostream>

#include "utilizator.h"

using namespace std;

class Angajat : public Utilizator
{
private:
	string departament;
	unsigned varsta;
	unsigned clasa_risc;
	unsigned vechime_angajat;
public:
	Angajat();
	Angajat(const string& nume, const string& prenume, const string& username, const string& parola,
		const string& departament, unsigned varsta, unsigned cod, unsigned vechime, unsigned risc)
		: Utilizator(nume, prenume, username, parola, cod), // Apelăm constructorul de bază
		departament(departament), varsta(varsta), vechime_angajat(vechime), clasa_risc(risc)
	{

	}
	~Angajat();
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

	void afisare_info_angajat(unsigned& cod);
	void schimbare_user(unsigned& cod);
	void schimbare_parola(unsigned& cod);
};

#endif
