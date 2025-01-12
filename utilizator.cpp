#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>

#include "utilizator.h"

using namespace std;

Utilizator::Utilizator()
{
	nume = "";
	prenume = "";
	username = "";
	parola = "";
	cod = 0;
}

Utilizator::Utilizator(const string& nume, const string& prenume, const string& username, const string& parola, const unsigned& cod)
	: nume(nume), prenume(prenume), username(username), parola(parola), cod(cod)
{

}

string Utilizator::getNume() const
{
	return nume;
}

string Utilizator::getPrenume() const
{
	return prenume;
}

string Utilizator::getUsername() const
{
	return username;
}

string Utilizator::getParola() const
{
	return parola;
}

unsigned Utilizator::getCod() const
{
	return cod;
}

void Utilizator::setNume(const string& nume)
{
	this->nume = nume;
}

void Utilizator::setPrenume(const string& prenume)
{
	this->prenume = prenume;
}

void Utilizator::setUsername(const string& username)
{
	this->username = username;
}

void Utilizator::setParola(const string& parola)
{
	this->parola = parola;
}

void Utilizator::setCod(const unsigned& cod)
{
	this->cod = cod;
}