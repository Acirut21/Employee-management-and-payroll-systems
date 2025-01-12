#ifndef SALARIZARE_H
#define SALARIZARE_H

#include <iostream>
#include <deque>
#include <string>
#include <sstream>

using namespace std;

class Salarizare
{
private:
    unsigned cod;
    unsigned zile_lucrate;
    unsigned zile_absente;
    float salariu_baza;
    float bonus;
    float norma_hrana;
    float salariu_brut;
    float salariu_net;
    float CAS;
    float CASS;
    float impozit;
    deque<float> salarii_lunare;

public:
	Salarizare();
    Salarizare(unsigned zile_lucrate, unsigned zile_absente, float salariu_baza, float bonus,
        float norma_hrana);
	~Salarizare();
	bool initializare_date_salarii();
	int calculare_salariu(unsigned& cod);
    int editare_salariu();
    void adauga_salariu(float salariu_net);
    int crestere_salariu_departament(unsigned& x,string& dep);
    int adaugare_salariu();
    int eliminare_salariu();
    int getter_salariu(unsigned& cod);
	void afisare_salariu(unsigned& cod);

    string date_salarii() const
    {
        stringstream ss;
        ss << zile_lucrate << " "
            << zile_absente << " "
            << salariu_baza << " "
            << bonus << " "
            << norma_hrana;

        return ss.str();
    }
};

#endif
