// Version du 08/02/2014

#pragma once
#define HAUTEUR 6
#define LARGEUR 7
#include <string>
#include <vector>
#include <stdint.h>
#include <fstream>
#include <iostream>
#include "Pion.h"
using namespace std;

class Joueur
{
	// Attributs
	private:
	string nom;
	string couleur;
	int coup;
	vector<Pion> listePion;

	// Méthodes
	public:
	// Constructeur et destructeur
	Joueur(void);
	~Joueur(void);
	// Getters et setters.
	string getNom(void);
	string getCouleur(void);
	void setJoueur(string,string);
	int getCoup(void);
	vector<Pion> getListePion(void);
	void popPion(void);
	void pushPion(Pion);
	int choixCoup(void);
	// Autres méthodes.
	void info(void);
};

