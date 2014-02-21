// Version du 12/02/14

#define NBPOSG 69
// Nombre de positions gagnantes (si H=6 et L=7)

#pragma once
#include <string>
#include <vector>
#include <stdint.h>
#include <fstream>
#include "Pion.h"
#include "Case.h"
#include "Colonne.h"
using namespace std;

class EtatCourant
{
	
	// Attributs
	private:
	Colonne listeCol[LARGEUR];	// Tableau des colonnes qui composent la grille du jeu.
	//uint64_t posG[NBPOSG];		// Tableau des positions gagnantes.
	uint64_t etat[2];			// Etat de la partie pour le joueur 1 ou 2, sous la forme d'un entier.
	int8_t firstVide[LARGEUR];	// Premi�re case libre de chaque colonne (un octet par case).
	bool gagne;					// Vrai lorsque la partie est gagn�e (et s'arr�te).

	// M�thodes
	public:
	// Constructeur et destructeur.
	EtatCourant(void);
	~EtatCourant(void);
	// Getters et setters.
	Colonne getCol(int);
	uint64_t getEtat(int);
	int8_t* getFirstVide(void);
	// Auutres m�thodes.
	bool jouer(Pion,int,int);	// Tente de jouer un pion dans une colonne, pour un des joueurs.
	bool enlever(int,int);		// Enl�ve un pion pour annuler un coup.
	bool isGagne(int);			// Teste si le joueur qui vient de jouer a gagn� la partie.
};

