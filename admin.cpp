#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>
#include <fstream>
#include <sstream>

#include "admin.h"
#include "angajat.h"
#include "aplicatie.h"
using namespace std;

extern unordered_map<unsigned, shared_ptr<Utilizator>> utilizatori;
extern Angajat angajati;
extern Admin admini;
extern Aplicatie sistem;

Admin::Admin()
{
	departament = "";
	varsta = 0;
	clasa_risc = 0;
	vechime_angajat = 0;
}

Admin::~Admin() {
	
}

unsigned Admin::getVechimeAngajat() const
{
	return this->vechime_angajat;
}

unsigned Admin::getClasaRisc() const
{
	return this->clasa_risc;
}

unsigned Admin::getVarsta() const
{
	return this->varsta;
}

void Admin::setDepartament(const string& departament)
{
	this->departament = departament;
}

void Admin::setVarsta(const unsigned& varsta)
{
	this->varsta = varsta;
}

void Admin::setClasaRisc(const unsigned& clasarisc)
{
	this->clasa_risc = clasarisc;
}

void Admin::setVechime(const unsigned& vechime)
{
	this->vechime_angajat = vechime;
}

int Admin::adaugare_angajat()
{
	unsigned nr_angajati;
	string linie;
	string nume, prenume, username, parola, departament;
	unsigned varsta, cod, vechime, risc;

	cout << "Numarul de angajati care trebuie adaugati: ";
	cin >> nr_angajati;
	cin.ignore();

	for (unsigned i = 0; i < nr_angajati; ++i) 
	{
		try
		{
			cout << "Introduceti datele pentru angajatul " << (i + 1) << ":\n"
				<< "Format: \nNume Prenume Username Parola Varsta Cod Vechime ClasaRisc Departament\n";

			getline(cin, linie);
			stringstream ss(linie);

			ss >> nume >> prenume >> username >> parola >> varsta >> cod >> vechime >> risc >> departament;

			if (utilizatori.find(cod) != utilizatori.end())
			{
				throw runtime_error("Cod duplicat: " + to_string(cod));
			}

			if (departament == "HR")
			{
				auto adminPtr = make_shared<Admin>(nume, prenume, username, parola, departament, varsta, cod, vechime, risc);
				utilizatori.insert({ cod, adminPtr });
			}
			else
			{
				auto angajatPtr = make_shared<Angajat>(nume, prenume, username, parola, departament, varsta, cod, vechime, risc);
				utilizatori.insert({ cod, angajatPtr });
			}
		}
		catch (const exception& e)
		{
			cerr << "Eroare: " << e.what() << endl;
		}
	}

	if (sistem.salvare_date("date_angajati.txt") == true)
	{
		cout << "\nModificarile au fost salvate cu succes.\n";
		return 0;
	}
	else {
		cerr << "\nEroare la salvarea modificarilor.\n";
		return 1;
	}
}

int Admin::eliminare_angajat()
{
	unsigned cod=0,nr_angajati=0;

	cout << "Numarul de angajati care trebuie eliminati: ";
	cin >> nr_angajati;
	cout << "\n";

	for (int i = 0; i < nr_angajati; i++)
	{
		string confirmare = "";

		cout << "Codul angajatului care trebuie eliminat: ";
		cin >> cod;
		cin.ignore();
		cout << "\nInformati existente despre angajatul " << cod << ":\n";

		angajati.afisare_info_angajat(cod);

		cout << "\nDatele pentru angajatul: \nNr: " << (i + 1) << " Cod: " << cod << ". Sunt pe cale sa fie eliminate. Continuati? YES/NO\n\n";
		cin >> confirmare;

		if (confirmare == "YES" || confirmare == "yes")
		{
			utilizatori.erase(cod);
		}
	}

	if (sistem.salvare_date("date_angajati.txt") == true)
	{
		cout << "\nModificarile au fost salvate cu succes.\n";
		return 0;
	}
	else {
		cerr << "\nEroare la salvarea modificarilor.\n";
		return 1;
	}
}

int Admin::editare_angajat()
{
	unsigned nr_angajati;
	string linie;
	string nume, prenume, username, parola, departament;
	unsigned varsta, cod, vechime, risc;

	cout << "Numarul de angajati care trebuie modificati: ";
	cin >> nr_angajati;
	cout << "\n";

	for(int i=0;i<nr_angajati;i++)
	{
		cout << "Introduceti codul angajatului pentru editare: ";
		cin >> cod;

		auto it = utilizatori.find(cod);
		if (it != utilizatori.end())
		{
			auto utilizatorPtr = it->second;
			if (auto angajatPtr = dynamic_pointer_cast<Angajat>(utilizatorPtr))
			{
				cout << "Introduceti noul nume (actual: " << utilizatorPtr->getNume() << "): ";
				cin >> nume;
				angajatPtr->setNume(nume);

				cout << "Introduceti noul prenume (actual: " << utilizatorPtr->getPrenume() << "): ";
				cin >> prenume;
				angajatPtr->setPrenume(prenume);

				cout << "Introduceti noul departament (actual: " << angajatPtr->getDepartament() << "): ";
				cin >> departament;
				angajatPtr->setDepartament(departament);

				cout << "Introduceti noua varsta (actual: " << angajatPtr->getVarsta() << "): ";
				cin >> varsta;
				angajatPtr->setVarsta(varsta); 

				cout << "Introduceti noua vechime (actual: " << angajatPtr->getVechimeAngajat() << "): ";
				cin >> vechime;
				angajatPtr->setVechime(vechime);

				cout << "Introduceti noua clasa de risc (actual: " << angajatPtr->getClasaRisc() << "): ";
				cin >> risc;
				angajatPtr->setClasaRisc(risc);
			}
			else
			{
				if (auto adminPtr = dynamic_pointer_cast<Admin>(utilizatorPtr))
				{
					cout << "Introduceti noul nume (actual: " << utilizatorPtr->getNume() << "): ";
					cin >> nume;
					adminPtr->setNume(nume);

					cout << "Introduceti noul prenume (actual: " << utilizatorPtr->getPrenume() << "): ";
					cin >> prenume;
					adminPtr->setPrenume(prenume);

					cout << "Introduceti noul departament (actual: " << adminPtr->getDepartament() << "): ";
					cin >> departament;
					adminPtr->setDepartament(departament);

					cout << "Introduceti noua varsta (actual: " << adminPtr->getVarsta() << "): ";
					cin >> varsta;
					adminPtr->setVarsta(varsta);

					cout << "Introduceti noua vechime (actual: " << adminPtr->getVechimeAngajat() << "): ";
					cin >> vechime;
					adminPtr->setVechime(vechime);

					cout << "Introduceti noua clasa de risc (actual: " << adminPtr->getClasaRisc() << "): ";
					cin >> risc;
					adminPtr->setClasaRisc(risc);
				}
			}
		}
		else
		{
			cout << "Utilizatorul cu codul " << cod << " nu a fost gasit.\n";
		}
	}

	if (sistem.salvare_date("date_angajati.txt") == true)
	{
		cout << "\nModificarile au fost salvate cu succes.\n";
		return 0;
	}
	else {
		cerr << "\nEroare la salvarea modificarilor.\n";
		return 1;
	}
}