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
// et ne change d'�tat que lorsqu'un pion lui
// est affect�.

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
	this->etat="vide";
}

void Case::info(void)
{
	cout<<"Je suis dans l'etat : "<<this->getEtat()<<".";
	if (this->getEtat()!="vide") cout<<" Je contiens le pion "<<this->getPion().getNum()<<".";
	cout<<"\n\n";
}