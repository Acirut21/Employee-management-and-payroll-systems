#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>
#include <fstream>
#include <sstream>

#include "aplicatie.h"
#include "utilizator.h"
#include "angajat.h"
#include "admin.h"
#include "salarizare.h"
#include "companie.h"

extern unordered_map<unsigned, shared_ptr<Utilizator>> utilizatori;
extern unordered_multimap<unsigned, Salarizare> salarii;

extern Salarizare salariu;
extern Angajat angajati;
extern Admin admini;
extern Aplicatie sistem;
extern Companie companii;

Companie companii;

using namespace std;

Aplicatie::Aplicatie()
{
	this->user = "";
	this->parola = "";
	this->control = 0;
	this->cod = 0;
}

Aplicatie::~Aplicatie()
{

}

bool Aplicatie::initializare_sistem()
{
    bool eroare = true;

	ifstream file("date_angajati.txt");
	if (!file.is_open())
	{
		cerr << "Nu s-a putut deschide fisierul date_angajati.txt!";
		return false;
	}

	utilizatori.clear();
	string linie;

	while (getline(file, linie))
	{
        try
        {
            stringstream ss(linie);
            string nume, prenume, username, parola, departament;
            unsigned varsta, cod, vechime, risc;

            ss >> nume >> prenume >> username >> parola >> varsta >> cod >> vechime >> risc >> departament;

            if (ss.fail())
            {
                eroare = false;
                throw runtime_error("Date invalide în linie: " + linie);
            }
            
            if (utilizatori.find(cod) != utilizatori.end())
            {
                eroare = false;
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

	file.close();

    if (salariu.initializare_date_salarii() == true && companii.incarca_datele("date_angajati.txt")==true && eroare==true)
    {
        return true;
    }
    else
    {
        cout << "Eroare la incarcarea datelor angajatilor!\n";
        return false;
    }
}

bool Aplicatie::login()
{
    control = 999;
    cod = 999;
    
    cout << "Introduceti username: ";
    cin >> user;
    cout << "Introduceti parola: ";
    cin >> parola;

    for (auto it = utilizatori.begin(); it != utilizatori.end(); ++it)
    {
        unsigned key = it->first;                      
        shared_ptr<Utilizator> utilizator = it->second; 

        if (utilizator->getUsername() == user && utilizator->getParola() == parola)
        {
            if (utilizator->getDepartament() == "HR")
            {
                control = 1;
            }
            else
            {
                control = 0;
            }

            cod = utilizator->getCod();
            cout << "\nAutentificare reusita! Bine ai venit, " << utilizator->getNume() << "!" << endl;
            return true;
        }
    }
    cout << "\nAutentificare esuata! Username sau parola incorecte." << endl;
    return false;
}

void Aplicatie::meniu()
{
    unsigned comanda = 999;

    // 0 = Angajat fara atributii de admin
    // 1 = Angajat cu atributii de admin (HR)

    cout << "Bine ati venit, introduceti userul si parola pentru autentificare:\n\n";
    if (login() == true)
    {
        switch (control)
        {
        case 0:
            //system("cls");
            do
            {
                cout << "\nOperatiuni posibile:\n\n";
                cout << "1.Vizualizare date disponibile\n";
                cout << "2.Schimbare username\n";
                cout << "3.Schimbare parola\n";
                cout << "4.Vizualizare istoric salarial\n";
                cout << "5.Exit\n\n";
                cout << "Introduceti comanda: ";
                cin >> comanda;
                system("cls");
                switch (comanda)
                {
                case 1:
                    angajati.afisare_info_angajat(cod);
                    break;
                case 2:
                    angajati.schimbare_user(cod);
                    break;
                case 3:
                    angajati.schimbare_parola(cod);
                    break;
                case 4:
                    salariu.afisare_salariu(cod);
                    break;
                case 5:
                    break;
                default:
                {
                    cout << "Comanda invalida\n\n";
                    break;
                }
                }
            } while (comanda != 5); 
            break;

        case 1:
            //TO DO
            //system("cls");

            do
            {
                cout << "\nOperatiuni posibile:\n\n";
                cout << "1.Adaugare angajat\n";
                cout << "2.Eliminare angajat\n";
                cout << "3.Editare date angajat\n";
                cout << "4.Adaugare salariu angajat\n";
                cout << "5.Editare salariu angajat\n";
                cout << "6.Eliminare salariu angajat\n";
                cout << "7.Afisare cost salarial departament\n";
                cout << "8.Crestere salariala departament\n";
                cout << "9.Adaugare Departament\n";
                cout << "10.Stergere Departament\n";
                cout << "11.Vizualizare istoric salarial\n";
                cout << "12.Vizualizare date disponibile\n";
                cout << "13.Exit\n\n";
                cout << "Introduceti comanda: ";
                cin >> comanda;
                system("cls");
                switch (comanda)
                {
                case 1:
                    admini.adaugare_angajat();
                    break;
                case 2:
                    admini.eliminare_angajat();
                    break;
                case 3:
                    admini.editare_angajat();
                    break;
                case 4:
                    salariu.adaugare_salariu();
                    break;
                case 5:
                    salariu.editare_salariu();
                    break;
                case 6:
                    salariu.eliminare_salariu();
                    break;
                case 7:
                    companii.afiseaza_date_departament();
                    break;
                case 8:
                {
                    unsigned x;
                    string dep;
                    cout << "Procentul mariri salariale: ";
                    cin >> x;
                    cout << "\nNumele departamentului pentru care se aplica marirea: ";
                    cin >> dep;
                    cout << "\n";
                    salariu.crestere_salariu_departament(x, dep);
                    break;
                }
                case 9:
                {
                    cout << "Departamentul care trebuie adaugat: ";
                    string nume;
                    cin >> nume;
                    companii.adauga_departament(nume);
                    cout << "\n\n";
                    companii.afiseaza_date_departament();
                    break;
                }
                case 10:
                {
                    companii.afiseaza_date_departament();
                    cout << "\n\nDepartamentul care trebuie eliminat: ";
                    string nume;
                    cin >> nume;
                    companii.sterge_departament(nume);
                    break;
                }
                case 11:
                    salariu.afisare_salariu(cod);
                    break;
                case 12:
                    angajati.afisare_info_angajat(cod);
                    break;
                case 13:
                    break;
                default:
                {
                    cout << "Comanda invalida\n\n";
                    break;
                }
                }
            } while (comanda != 13);
            break;
        default:
            cout << "Eroare la stabilirea atributilor userului";
            break;
        }
    }
}

bool Aplicatie::salvare_date(const string& fisier)
{
    if (fisier == "date_angajati.txt")
    {
        ofstream file("date_angajati.txt");
        if (!file.is_open())
        {
            cerr << "Nu s-a putut deschide fisierul";
            return false;
        }

        for (const auto& pair : utilizatori)
        {
            const auto& utilizator = pair.second;

            if (auto adminPtr = dynamic_pointer_cast<Admin>(utilizator))
            {
                file << utilizator->getNume() << " " << utilizator->getPrenume() << " " << utilizator->getUsername() << " " << utilizator->getParola() << " " << adminPtr->getVarsta() << " " << adminPtr->getCod() << " " <<
                    adminPtr->getVechimeAngajat() << " " << adminPtr->getClasaRisc() << " " << adminPtr->getDepartament() << "\n";
            }

            if (auto angajatPtr = dynamic_pointer_cast<Angajat>(utilizator))
            {
                file << utilizator->getNume() << " " << utilizator->getPrenume() << " " << utilizator->getUsername() << " " << utilizator->getParola() << " " << angajatPtr->getVarsta() << " " << angajatPtr->getCod() << " " <<
                    angajatPtr->getVechimeAngajat() << " " << angajatPtr->getClasaRisc() << " " << angajatPtr->getDepartament() << "\n";
            }

        }

        file.close();
        return true; // Operațiunea a reușit
    }
    else
    {
        if (fisier == "date_salarii_angajati.txt")
        {
            ofstream file(fisier);
            if (!file.is_open())
            {
                cerr << "Nu s-a putut deschide fisierul: " << fisier << endl;
                return false;
            }

            for (const auto& entry : salarii)
            {
                const Salarizare& salariu = entry.second;

                file << entry.first << " " << salariu.date_salarii() << "\n";
            }

            file.close();
            return true;
        }
    }
}