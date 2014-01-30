// Version du 29/01/14

#include "Pion.h"
#include <iostream>
#include <string>

// Variables de classe servant � num�roter les pions
int Pion::compteur=0;
int Pion::nbPionJaune=0;
int Pion::nbPionRouge=0;

// Constructeurs
Pion::Pion()
{
	//cout<<"Constructeur defaut.\n";
}

// Le seul constructeur dont nous aurons besoin affectera obligatoirement une
// couleur � chaque pion en d�but de partie.
Pion::Pion(string cetteCouleur)
{
	compteur++;
	if (cetteCouleur=="rouge") this->nbPionRouge++;
	else this->nbPionJaune++;
	this->num=compteur;
	this->couleur=cetteCouleur;
}

// Destructeur
Pion::~Pion(void)
{
	if (this->couleur!="vide") this->compteur--; 
	if (this->couleur=="rouge") this->nbPionRouge--;
	if (this->couleur=="jaune") this->nbPionJaune--;
}

// Getter et setter
// On n'aura pas � fixer le num�ro ou la couleur du pion
// qui seront d�termin�s au moment de la cr�ation et uniquement
// par le constructeur. Donc, pas de setters correspondants.
// Tous les pions sont cr��s en d�but de partie et aucun n'est
// d�truit en cours de partie.

int Pion::getNum(void)
{
	return this->num;
}

string Pion::getCouleur(void)
{
	return this->couleur;
}

void Pion::info(void)
{
	cout<<"Je suis le pion "<<this->getNum()<<" et je suis de couleur "<<this->getCouleur()<<"."<<endl;
}