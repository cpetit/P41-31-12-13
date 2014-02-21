// Version du 12/02/2014

enum ALGO {NAIF,AB};

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
#include "IA.h"
using namespace std;

class Partie
{
	// Attributs
	private:
	Joueur *joueur[2];		// Tableau de pointeurs sur deux joueurs
	int gagnant;			// Numéro du joueur gagnant
	vector<int> historique;	// Historique des numéros de cases jouées
	bool gagne;				// Vrai si la partie est gagnée
	int nbCoup;				// Nombre de coups joués depuis le début
	int trait;				// Qui a la main pour jouer
	EtatCourant situation;	// Etat courant de la partie à un tour donné

	// Méthodes
	public:
	Partie();
	Partie(char,string,char,string);
	Partie(char,string,ALGO,char,string);
	Partie(char,string,char,string,ALGO);
	Partie(char,string,ALGO,char,string,ALGO);
	~Partie(void);
	int getGagnant(void);
	int getNbCoup(void);
	int getTrait(void);
	EtatCourant getSituation(void);
	vector<int> getHistorique(void);
	Joueur* getJoueur(int);
	void joueUnCoup(bool*,int*,int*,bool*,int*);
	void annuleCoup(bool*,int*,int*);
	void info(void);
};

