#ifndef UTILIZATOR_H
#define UTILIZATOR_H

#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>

using namespace std;

class Utilizator
{
protected:
	string nume;
	string prenume;
	string username;
	string parola;
	unsigned cod;

public:
	Utilizator();
	Utilizator(const string& nume, const string& prenume, const string& username, const string& parola, const unsigned& cod);
	virtual ~Utilizator()=default;

	string getNume() const;
	string getPrenume() const;
	string getUsername() const;
	string getParola() const;
	unsigned getCod() const;
	virtual string getDepartament() const = 0;

	void setNume(const string& nume);
	void setPrenume(const string& prenume);
	void setUsername(const string& username);
	void setParola(const string& parola);
	void setCod(const unsigned& cod);
};

#endif
