// Version du 11/02/2014

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
	Joueur joueur[2];
	int gagnant;
	vector<int> historique;
	bool gagne;
	int nbCoup;
	int trait;
	EtatCourant situation;

	// Méthodes
	public:
	Partie(void);
	~Partie(void);
	int getGagnant(void);
	int getNbCoup(void);
	int getTrait(void);
	EtatCourant getSituation(void);
	vector<int> getHistorique(void);
	Joueur getJoueur(int);
	void joueUnCoup(bool*,int*,int*,bool*,int*);
	void annuleCoup(bool*,int*,int*);
	void info(void);
};

