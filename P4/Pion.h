#pragma once
#include <string>
using namespace std;

class Pion
{
	// Attributs
	private:
	static int compteur;		// Compteur servant � num�roter tous les points.
	static int nbPionJaune;		// Compteur de pions jaunes.
	static int nbPionRouge;		// Compteur de pions rouges.
	int num;
	string couleur;

	// M�thodes
	public:
	Pion();
	Pion(string);
	~Pion(void);
	int getNum(void);
	string getCouleur(void);
	void info(void);
};
