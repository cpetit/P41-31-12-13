// Version du 12/02/2014

#pragma once
#include <string>
#include <vector>
#include <stdint.h>
#include <fstream>
#include <iostream>
#include "EtatCourant.h"
#include "Pion.h"
using namespace std;

class Joueur
{
	// Attributs
	protected:
	int numJ;
	string nom;
	string couleur;
	int coup;
	vector<Pion> listePion;

	// Méthodes
	public:
	// Constructeur et destructeur
	Joueur(void);
	Joueur(int);
	~Joueur(void);
	// Getters et setters.
	int getNumJ(void);
	string getNom(void);
	string getCouleur(void);
	void setJoueur(string,string);
	int getCoup(void);
	vector<Pion> getListePion(void);
	// Autres méthodes.
	void popPion(void);
	void pushPion(Pion);
	virtual int jouer(EtatCourant*);
	virtual bool isHumain(void);
	void info(void);
};

