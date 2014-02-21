
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "IA.h"

IA::IA(void)
{
	this->algo=NAIF;
}

IA::IA(int num,ALGO algo)
{
	this->numJ=num;
	this->algo=algo;
}

IA::~IA(void)
{
}

ALGO IA::getAlgo(void)
{
	return(this->algo);
}

void IA::setAlgo(ALGO algo)
{
	this->algo=algo;
}

bool IA::isHumain(void)
{
	return false;
}

int IA::jouer(EtatCourant* EtC)
{
	// Fonction qui décide quel coup jouer
	// au vu de l'état courant de la partie
	// et de l'algorihme utilisé par l'IA.
	vector<int> coupPossible(0);
	unsigned int choixCoup;
	int score;
	for(int i=0;i<LARGEUR;i++)
	{
		if(!EtC->getCol(i).isPleine())coupPossible.push_back(i);
	}
	switch(this->algo)
	{
		case NAIF:
		{
			choixCoup=this->auPif(coupPossible.size());
			break;
		}
		case AB:
		{
			AlphaBeta iaAB;
			score=iaAB.parcours(EtC->getEtat(this->numJ),EtC->getEtat((1+this->numJ)%2),EtC->getFirstVide(),1,-10000,10000,this->numJ);
			choixCoup=iaAB.getCoup();
			//cout<<"Racine: "<<choixCoup<<"("<<score<<")"<<endl;
			break;
		}
		default: break;
	}
	return choixCoup;
}

// Génère un entier au hasard entre 0 et n-1
int IA::auPif(int n)
{
	srand ((unsigned int)time(NULL));
	return (rand()%n);
}
