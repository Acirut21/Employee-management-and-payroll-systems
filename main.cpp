// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>

#include "aplicatie.h"
#include "utilizator.h"
#include "admin.h"
#include "angajat.h"
#include "salarizare.h"

using namespace std;

unordered_map<unsigned, shared_ptr<Utilizator>> utilizatori;
unordered_multimap<unsigned, Salarizare> salarii;

Salarizare salariu;
Angajat angajati;
Admin admini;
Aplicatie sistem;


int main()
{
    //cout << "Hello World!\n";
    if (sistem.initializare_sistem() == true)
    {
        sistem.meniu();
    }
    else 
    {
        cout << "Eroare la incarcarea sistemului!";
        return 1;
    }

    return 0;
}

