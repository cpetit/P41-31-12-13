// Version du 05/02/14

#include "Case.h"
#include <iostream>


// Constructeur et destructeur.
Case::Case(void)
{
	this->etat="vide";
}

Case::~Case(void)
{
}

// Getters et setterrs.
string Case::getEtat(void)
{
	return this->etat;
}

// Pas de setter sur etat car une case est
// toujours cr��e vide par le constructeur

Pion Case::getPion(void)
{
	return this->pion;
}

void Case::setPion(Pion cePion)
{
	this->pion=cePion;
	this->etat=cePion.getCouleur();
}

void Case::setVide(void)
{
	// Si l'on annule un coup, une case peut �tre remise dans l'�tat vide.
	// On pourrait cr�er un pion vide pour le mettre dedans et "vider" ainsi la case,
	// mais cela est sans int�r�t et n'est pas coh�rent avec la classe pion.
	// On se contente donc de mettre l'�tat � vide.
	// L'ancien pion a �t� remis dans le stock du joueur correspondant et on ne
	// doit donc plus acc�der � this->cePion.
	this->etat="vide";
}

void Case::info(void)
{
	cout<<"Je suis dans l'etat : "<<this->getEtat()<<".";
	if (this->getEtat()!="vide") cout<<" Je contiens le pion "<<this->getPion().getNum()<<".";
	cout<<"\n\n";
}