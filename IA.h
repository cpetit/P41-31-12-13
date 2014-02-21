// Version du 11/02/2014

#pragma once
#include "joueur.h"
#include "EtatCourant.h"
#include "Partie.h"
#include "Colonne.h"
#include "AlphaBeta.h"
using namespace std;

class IA : public Joueur
{
	private:
	ALGO algo;
	public:
	IA(void);
	IA(int,ALGO);
	~IA(void);
	ALGO getAlgo(void);
	void setAlgo(ALGO);
	bool isHumain(void);
	int jouer(EtatCourant*);
	int auPif(int);
};

