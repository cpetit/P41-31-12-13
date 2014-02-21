// Version du 01/02/2014

#include "Noeud.h"

Noeud::Noeud(void)
{
}

Noeud::~Noeud(void)
{
}

list<Noeud> Noeud::getFils(int numJoueur)
{ 
	list<Noeud> res;
    return res;
}
 
bool Noeud::isFeuille(int numJoueur)
{
	bool feuille = false;
    return feuille;
 }
 
int Noeud::eval(uint64_t etat0,uint64_t etat1)
{
	int score=0;
	int poids[49]={3,4,5,5,4,3,0,4,6,8,8,6,4,0,5,8,11,11,8,5,0,7,10,13,13,10,7,0,5,8,11,11,8,5,0,4,6,8,8,6,4,0,3,4,5,5,4,3,0};
	for(int i=0;i<49;i++)score+=(int)poids[i]*((etat0>>i)%2-(etat1>>i)%2);
    return score;
}