#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>
#include <fstream>
#include <sstream>

#include "salarizare.h"
#include "aplicatie.h"
#include "departament.h"
#include "companie.h"

using namespace std;

extern unordered_multimap<unsigned, Salarizare> salarii;

extern Companie companii;
extern Aplicatie sistem;

Salarizare::Salarizare()
{
    salariu_baza = 0;
    bonus = 0;
    zile_lucrate = 0;
    zile_absente = 0;
    norma_hrana = 0;
    salariu_brut = 0;
    salariu_net = 0;
    CAS = 0;
    CASS = 0;
    impozit = 0;
}

Salarizare::Salarizare(unsigned zile_lucrate, unsigned zile_absente, float salariu_baza, float bonus,
    float norma_hrana)
    : zile_lucrate(zile_lucrate), zile_absente(zile_absente), salariu_baza(salariu_baza), bonus(bonus),
    norma_hrana(norma_hrana)
{

}

Salarizare::~Salarizare()
{

}

bool Salarizare::initializare_date_salarii()
{
    ifstream file("date_salarii_angajati.txt");
    if (!file.is_open())
    {
        cerr << "Nu s-a putut deschide fisierul date_salarii_angajati.txt!";
        return false;
    }

    salarii.clear();
    string linie;

    while (getline(file, linie))
    {
        try
        {
            stringstream ss(linie);
            float salariu_baza, bonus, norma_hrana, salariu_brut;
            unsigned zile_lucrate,zile_absente,cod;

            ss >> cod >> zile_lucrate >> zile_absente >> salariu_baza >> bonus >> norma_hrana;

            if (ss.fail())
            {
                throw runtime_error("Date invalide în linie: " + linie);
                return false;
            }

            Salarizare salariu(zile_lucrate, zile_absente, salariu_baza, bonus, norma_hrana);
            salarii.insert({ cod, salariu});

        }
        catch (const exception& e)
        {
            cerr << "Eroare: " << e.what() << endl;
        }
    }

    file.close();
    return true;
}

int Salarizare::calculare_salariu(unsigned& cod)
{
    auto range = salarii.equal_range(cod);

    // Creăm o listă temporară pentru noile date, astfel încât să nu modificăm mapa în timpul iterării
    vector<Salarizare> salarii_actualizate;

    for (auto it = range.first; it != range.second; ++it)
    {
        Salarizare& salariu = it->second;

        salariu.salariu_brut = salariu.salariu_baza + salariu.bonus + salariu.norma_hrana;

        float salariu_ajustat = salariu.salariu_brut *
            (static_cast<float>(salariu.zile_lucrate) /
                (salariu.zile_lucrate + salariu.zile_absente));

        // Calculăm contribuțiile și impozitul
        salariu.CASS = 0.10f * salariu_ajustat;
        salariu.CAS = 0.25f * salariu_ajustat;
        salariu.impozit = 0.10f * (salariu_ajustat - salariu.CAS - salariu.CASS);

        // Calculăm salariul net
        salariu.salariu_net = salariu_ajustat - salariu.CAS - salariu.CASS - salariu.impozit;

        // Adăugăm salariul calculat în lista temporară
        salarii_actualizate.push_back(salariu);

        adauga_salariu(salarii_actualizate.back().salariu_net);
    }

    // Ștergem vechile date și le adăugăm pe cele actualizate
    salarii.erase(range.first, range.second);
    for (auto& salariu : salarii_actualizate)
    {
        salarii.insert({ cod, salariu });
    }

    return 0;
}

void Salarizare::adauga_salariu(float salariu_net)
{
    if (salarii_lunare.size() >= 6)
    {
        salarii_lunare.pop_front();
    }
    salarii_lunare.push_back(salariu_net);
}

void Salarizare::afisare_salariu(unsigned& cod)
{
    calculare_salariu(cod);
    
    cout << "Salariile nete pe ultimele 6 luni: \n";
    for (const auto& salariu : salarii_lunare)
    {
        cout << salariu << "\n";
    }
    cout << "\n";

    auto range = salarii.equal_range(cod);

    if (range.first != salarii.end())
    {
        auto it = range.first;

        const Salarizare& salariu_rec = it->second;

        // Afișăm fluturașul pentru cel mai recent salariu
        cout << "Fluturasul de salariu pentru cel mai recent salariu: \n";
        cout << "Zile lucrate: " << salariu_rec.zile_lucrate << endl;
        cout << "Zile absente: " << salariu_rec.zile_absente << endl;
        cout << "Salariu baza: " << salariu_rec.salariu_baza << endl;
        cout << "Bonus: " << salariu_rec.bonus << endl;
        cout << "Norma de hrana: " << salariu_rec.norma_hrana << endl;
        cout << "Salariu brut: " << salariu_rec.salariu_brut << endl;
        cout << "CASS (10%): " << salariu_rec.CASS << endl;
        cout << "CAS (25%): " << salariu_rec.CAS << endl;
        cout << "Impozit (10%): " << salariu_rec.impozit << endl;
        cout << "Salariu net: " << salariu_rec.salariu_net << endl;
    }
    else
    {
        cout << "Nu există date pentru codul angajatului specificat.\n";
    }

}

int Salarizare::editare_salariu()
{
    unsigned nr_angajati;
    unsigned zile_lucrate, zile_absente;
    float salariu_baza, bonus, norma_hrana;

    system("cls");

    cout << "Numarul de salarii care trebuie modificate: ";
    cin >> nr_angajati;
    cout << "\n";

    for (int i = 0; i < nr_angajati; i++)
    {
        cout << "Introduceti codul angajatului pentru editare: ";
        cin >> cod;
        cout << "\n";

        auto range = salarii.equal_range(cod);

        if (range.first != salarii.end())
        {
            auto it = range.first;

            const Salarizare& salariu_rec = it->second;
            Salarizare& salariu = it->second;

            // Afișăm fluturașul pentru cel mai recent salariu
            cout << "Fluturasul de salariu pentru cel mai recent salariu: \n";
            cout << "Introduceti zile lucrate(actual: " << salariu_rec.zile_lucrate << "): ";
            cin >> zile_lucrate;
            salariu.zile_lucrate = zile_lucrate;
            cout << "Introduceti zile absente (actual: " << salariu_rec.zile_absente << "): ";
            cin >> zile_absente;
            salariu.zile_absente = zile_absente;
            cout << "Introduceti salariu baza (actual: " << salariu_rec.salariu_baza << "): ";
            cin >> salariu_baza;
            salariu.salariu_baza = salariu_baza;
            cout << "Introduceti bonus (actual: " << salariu_rec.bonus << "): ";
            cin >> bonus;
            salariu.bonus = bonus;
            cout << "Introduceti norma de hrana (actual: " << salariu_rec.norma_hrana << "): ";
            cin >> norma_hrana;
            salariu.norma_hrana = norma_hrana;
        }
        else
        {
            cout << "Nu există date pentru codul angajatului specificat.\n";
        }

        if (sistem.salvare_date("date_salarii_angajati.txt") == true)
        {
            cout << "Date au fost salvate cu succes!";
        }
        else
        {
            cout << "Eroare la salvarea datelor!";
        }
    }
    return 0;
}

int Salarizare::adaugare_salariu()
{
    float salariu_baza, bonus, norma_hrana, salariu_brut;
    unsigned zile_lucrate, zile_absente, cod,nr_salarii=0;

    cout << "Numarul de salarii care trebuie adaugate: ";
    cin >> nr_salarii;

    for (unsigned i = 1; i <= nr_salarii; i++)
    {
        try
        {
            cout << "Introduceti datele pentru salariul " << i << ":\n"
                << "Format: \nCod Zile lucrate Zile absente Salariu de baza Bonus Norma de hrana\n";

            cin >> cod >> zile_lucrate >> zile_absente >> salariu_baza >> bonus >> norma_hrana;

            if (cin.fail())
            {
                throw runtime_error("Datele introduse sunt invalide. Reincercati.");
            }

            Salarizare salariu(zile_lucrate, zile_absente, salariu_baza, bonus, norma_hrana);

            salarii.insert({ cod,salariu });
        }
        catch (const exception& e)
        {
            cerr << "Eroare: " << e.what() << endl;
            cin.clear();             // Resetează starea fluxului
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Curăță intrarea
        }
    }

    if (sistem.salvare_date("date_salarii_angajati.txt")==true)
    {
        cout << "Datele au fost salvate cu succes!";
        return 0;
    }
    else
    {
        cout << "Eroare la salvarea datelor in fisier!";
        return 1;
    }
}

int Salarizare::eliminare_salariu()
{
    unsigned cod = 0, nr_salarii = 0;

    cout << "Numarul de salarii care trebuie sterse: ";
    cin >> nr_salarii;

    for (int i = 0; i < nr_salarii; i++)
    {
        string confirmare = "";
        cout << "\nCodul angajatului: ";
        cin >> cod;

        cout << "\nInformati existente despre salariul angajatului " << cod << ":\n\n";
        afisare_salariu(cod);

        cout << "\n\nDatele pentru angajatul: \nNr: " << (i + 1) << " Cod: " << cod << ". Sunt pe cale sa fie eliminate. Continuati? YES/NO\n\n";
        cin >> confirmare;

        if (confirmare == "YES" || confirmare == "yes")
        {
            salarii.erase(cod);
        }
    }

    if (sistem.salvare_date("date_salarii_angajati.txt") == true)
    {
        cout << "Datele au fost salvate cu succes!";
        return 0;
    }
    else
    {
        cout << "Eroare la salvarea datelor in fisier!";
        return 1;
    }
}

int Salarizare::getter_salariu(unsigned& cod)
{
    calculare_salariu(cod);

    auto range = salarii.equal_range(cod);

    if (range.first != salarii.end())
    {
        auto it = range.first;

        const Salarizare& salariu_rec = it->second;

        return salariu_rec.salariu_net;
    }
}

int Salarizare::crestere_salariu_departament(unsigned& x,string& dep)
{
    const auto& departamente = companii.getDepartamente();

    for (const auto& pair : departamente)
    {
        const string& nume = pair.first;           // Cheia map-ului
        const Departament& departament = pair.second;   // Valoarea map-ului

        if (dep == nume)
        {
            cout << "Departament: " << nume << "\n";
            for (const auto& cod : departament.getCoduriAngajati())
            {
                //cout << cod << " ";
                auto range = salarii.equal_range(cod);

                if (range.first != salarii.end())
                {
                    auto it = range.first;

                    const Salarizare& salariu_rec = it->second;
                    Salarizare& salariu = it->second;

                    cout << "Salariu baza (actual: " << salariu_rec.salariu_baza << ")\n";
                    cout << "Salariu baza dupa marirea de " << x << "%: ";
                    float salariu_baza = salariu.salariu_baza;
                    salariu.salariu_baza = salariu_baza + (salariu_baza * (x / 100.0f));
                    cout << salariu.salariu_baza<<"\n\n";
                }
            }
            if (sistem.salvare_date("date_salarii_angajati.txt") == true)
            {
                cout << "Date au fost salvate cu succes!";
            }
            else
            {
                cout << "Eroare la salvarea datelor!";
            }
        }
        //cout << "\nCost total salarii: " << departament.getCostTotalSalarii() << "\n\n";
    }
    return 0;
}
