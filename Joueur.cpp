// Version du 12/02/2014

#include "Joueur.h"

Joueur::Joueur(void)
{
}

Joueur::Joueur(int num)
{
	this->numJ=num;
}

Joueur::~Joueur(void)
{
}

int Joueur::getNumJ(void)
{
	return this->numJ;
}

string Joueur::getNom(void)
{
	return(this->nom);
}

string Joueur::getCouleur(void)
{
	return(this->couleur);
}

int Joueur::getCoup(void)
{
	return(this->coup);
}

vector<Pion> Joueur::getListePion(void)
{
	return(this->listePion);
}

void Joueur::setJoueur(string nom,string couleur)
{
	this->nom=nom;
	this->couleur=couleur;
	for(int i=0;i<(LARGEUR*HAUTEUR)/2;i++) this->listePion.push_back(Pion(couleur));
}

void Joueur::popPion(void)
{
	this->listePion.pop_back();
}

void Joueur::pushPion(Pion pi)
{
	this->listePion.push_back(pi);
}

// Méthode virtuelle qui sera implémentée
// différemment pour Humain et IA.
int Joueur::jouer(EtatCourant* EtC)
{
	return -1;
}

// Méthode virtuelle qui sera implémentée
// différemment pour Humain et IA.
bool Joueur::isHumain(void)
{
	return true;
}

void Joueur::info(void)
{
	cout<<"Je m'appelle "<<this->getNom()<<"."<<endl;
}
