#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>

#include "angajat.h"
#include "utilizator.h"
#include "admin.h"
#include "aplicatie.h"

extern unordered_map<unsigned, shared_ptr<Utilizator>> utilizatori;
extern Angajat angajati;
extern Admin admini;
extern Aplicatie sistem;

Angajat::Angajat()
{
	departament="";
	varsta=0;
	clasa_risc=0;
	vechime_angajat=0;
}

Angajat::~Angajat() {
	
}

unsigned Angajat::getVechimeAngajat() const
{
	return this->vechime_angajat;
}

unsigned Angajat::getClasaRisc() const
{
	return this->clasa_risc;
}

unsigned Angajat::getVarsta() const
{
	return this->varsta;
}

void Angajat::setDepartament(const string& departament)
{
	this->departament = departament;
}

void Angajat::setVarsta(const unsigned& varsta)
{
	this->varsta = varsta;
}

void Angajat::setClasaRisc(const unsigned& clasarisc)
{
	this->clasa_risc = clasarisc;
}

void Angajat::setVechime(const unsigned& vechime)
{
	this->vechime_angajat = vechime;
}

void Angajat::afisare_info_angajat(unsigned& cod)
{
	//TO DO Salariul
	auto it = utilizatori.find(cod);
	if (it != utilizatori.end())
	{
		auto utilizatorPtr = it->second;
		if (auto angajatPtr = dynamic_pointer_cast<Angajat>(utilizatorPtr))
		{
			cout << "Cod: " << utilizatorPtr->getCod() << "\n"
				<< "Nume: " << utilizatorPtr->getNume() << "\n"
				<< "Prenume: " << utilizatorPtr->getPrenume() << "\n"
				<< "Username: " << utilizatorPtr->getUsername() << "\n"
				<< "Parola: " << angajatPtr->getParola() << "\n"
				<< "Varsta: " << angajatPtr->getVarsta() << "\n"
				<< "Departament: " << angajatPtr->getDepartament() << "\n";
		}
		else
		{
			if (auto adminPtr = dynamic_pointer_cast<Admin>(utilizatorPtr))
			{
				cout << "Cod: " << utilizatorPtr->getCod() << "\n"
					<< "Nume: " << utilizatorPtr->getNume() << "\n"
					<< "Prenume: " << utilizatorPtr->getPrenume() << "\n"
					<< "Username: " << utilizatorPtr->getUsername() << "\n"
					<< "Parola: " << adminPtr->getParola() << "\n"
					<< "Varsta: " << adminPtr->getVarsta() << "\n"
					<< "Departament: " << adminPtr->getDepartament() << "\n";
			}
		}
	}
	else cout << "Utilizatorul cu codul " << cod << " nu a fost gasit.\n";
}

void Angajat::schimbare_user(unsigned& cod)
{
	string username = "";

	auto it = utilizatori.find(cod);
	if (it != utilizatori.end())
	{
		auto utilizatorPtr = it->second;
		if (auto angajatPtr = dynamic_pointer_cast<Angajat>(utilizatorPtr))
		{
			system("cls");
			cout << "Usernameul vechi este: " << angajatPtr->getUsername() << " Introduceti nou username: ";
			cin >> username;
			angajatPtr->setUsername(username);
		}
		else
		{
			if (auto adminPtr = dynamic_pointer_cast<Admin>(utilizatorPtr))
			{
				system("cls");
				cout << "Usernameul vechi este: " << adminPtr->getUsername() << " Introduceti nou username: ";
				cin >> username;
				adminPtr->setUsername(username);
			}
		}
	}
	else cout << "Utilizatorul cu codul " << cod << " nu a fost gasit.\n";

	sistem.salvare_date("date_angajati.txt");
}

void Angajat::schimbare_parola(unsigned& cod)
{
	string parola="";

	auto it = utilizatori.find(cod);
	if (it != utilizatori.end())
	{
		auto utilizatorPtr = it->second;
		if (auto angajatPtr = dynamic_pointer_cast<Angajat>(utilizatorPtr))
		{
			system("cls");
			cout << "Parola veche este: " << angajatPtr->getParola() << " Introduceti noua parola: ";
			cin >> parola;
			angajatPtr->setParola(parola);
		}
		else
		{
			if (auto adminPtr = dynamic_pointer_cast<Admin>(utilizatorPtr))
			{
				system("cls");
				cout << "Parola veche este: " << adminPtr->getUsername() << " Introduceti noua parola: ";
				cin >> parola;
				adminPtr->setParola(parola);
			}
		}
	}
	else cout << "Utilizatorul cu codul " << cod << " nu a fost gasit.\n";

	sistem.salvare_date("date_angajati.txt");
}