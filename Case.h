// Version du 29/01/14

#pragma once
#include <string>
#include "Pion.h"
using namespace std;

class Case
{
	// Attributs
	private:
	string etat;		// Trois �tats: rouge, jaune ou vide.
	Pion pion;			// Le pion qui est �ventuellement dans la case.

	// M�thodes
	public:
	Case(void);
	~Case(void);
	string getEtat(void);
	Pion getPion(void);
	void setPion(Pion);
	void setVide(void);
	void info(void);
};

