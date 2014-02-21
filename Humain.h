// Version du 11/02/2014

#pragma once
#include "joueur.h"
#include "EtatCourant.h"

class Humain : public Joueur
{
	public:
	Humain(void);
	Humain(int);
	~Humain(void);
	int Humain::jouer(EtatCourant*);
	bool Humain::isHumain(void);
};
