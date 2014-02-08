// Version du 08/02/2014

#pragma once
#include <windows.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <string>
#include <vector>
#include "Pion.h"
#include "Case.h"
#include "Colonne.h"
#include "EtatCourant.h"
#include "Joueur.h"
#include "IA.h"
#include "Humain.h"
using namespace std;

class Partie
{
	// Attributs
	private:
	Joueur joueur1;
	Joueur joueur2;
	string gagnant;
	vector<int> historique;
	bool gagne;
	int nbCoup;
	string trait;
	EtatCourant situation;

	// Méthodes
	public:
	Partie(void);
	~Partie(void);
	string getGagnant(void);
	int getNbCoup(void);
	Joueur getJoueur(string);
	void joueUnCoup(bool*,int*,int*,bool*,string*);
	void annuleCoup(bool*,int*,int*);
	void info(void);
};

