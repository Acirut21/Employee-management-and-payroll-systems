#ifndef APLICATIE_H
#define APLICATIE_H

#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>

using namespace std;

class Aplicatie
{
private:
	string user;
	string parola;
	unsigned control;
	unsigned cod;
public:
	Aplicatie();
	~Aplicatie();
	bool login();
	bool initializare_sistem();
	void meniu();
	bool salvare_date(const string& fisier);
};

#endif // !APLICATIE_H

