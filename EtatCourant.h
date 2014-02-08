// Version du 08/02/14

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
	uint64_t posG[NBPOSG];		// Tableau des positions gagnantes.
	uint64_t etat1;				// Etat de la partie pour le joueur 1, sous la forme d'un entier.
	uint64_t etat2;				// Etat de la partie pour le joueur 2, sous la forme d'un entier.
	bool gagne;					// Vrai lorsque la partie est gagnée (et s'arrête).

	// Méthodes
	public:
	// Constructeur et destructeur.
	EtatCourant(void);
	~EtatCourant(void);
	// Getters et setters.
	Colonne getCol(int);
	uint64_t getEtat(string);
	// Auutres méthodes.
	bool jouer(Pion,int,string);		// Tente de jouer un pion dans une colonne, pour un des joueurs.
	bool enlever(int,string);			// Enlève un pion pour annuler un coup.
	bool isGagne(string);				// Teste si le joueur qui vient de jouer a gagné la partie.
};

