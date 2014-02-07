// Version du 07/02/14

#include "EtatCourant.h"
#include <iostream>

// Constructeur.
EtatCourant::EtatCourant(void)
{
	this->gagne=false;

	// Les colonnes sont numérotées à la création.
	for(int i=0;i<LARGEUR;i++) this->listeCol[i]=Colonne(i);
	
	// Création du tableau des positions gagnantes,
	// à partir du fichier qui les stocke.
	// ATTENTION !!
	// Le fichier texte doit se trouver dans le répertoire courant.
	ifstream fichier("posg.txt",ios::in);
    if(fichier)
    {
      for(int indice=0;indice<NBPOSG;indice++) fichier>>this->posG[indice];
      fichier.close();
    }
    else cerr << "Erreur" << endl;

	// Initialise l'état de la partie à 0, pour chaque joueur.
	this->etat1=(uint64_t)0;
	this->etat2=(uint64_t)0;
}

// Destructeur.
EtatCourant::~EtatCourant(void)
{

}

// Getters et setters.
Colonne EtatCourant::getCol(int l)
{
	return this->listeCol[l];
}

uint64_t EtatCourant::getEtat(int i)
{
	if(i==1) return this->etat1;
	else return this->etat2;
}

// Teste si la partie est gagnée par le joueur numJoueur.
bool EtatCourant::isGagne(int numJoueur)
{
	bool res=false;
	uint64_t etat;
	if (numJoueur==1) etat=this->etat1;
	if (numJoueur==2) etat=this->etat2;
	for(int indice=0;(indice<NBPOSG)&&(!res);indice++)
	{
		// Chaque grille est représentée par un entier dont la décomposition
		// binaire donne les cases où un joueur a mis ses pions.
		// On effectue un "et" binaire entre une position gagnante et la grille actuelle.
		// Ceci revient à faire un masque en se focalisant uniquement sur les cases
		// qui composent la position gagnante (4 cases à tester).
		// Si ce "et" coincide avec la position gagnante, le jeu est terminé.
		// Au final on parcourt uniquement le tableau de positions gagnantes:
		// au + 69 opérations.
		if((this->posG[indice]&etat)==this->posG[indice])
		{
			res=true;  
			cout<<"Joueur "<<numJoueur<<" a gagne !!\n";
		}
	}
	return res;
}

// Joue un pion à la colonne l.
// Si la colonne est pleine, rien ne se passe.
bool EtatCourant::jouer(Pion pi,int l,int numJoueur)
{
	int h,numCase;
	bool ok=false;
	if (this->listeCol[l].isPleine()) cout<<"Coup impossible, colonne pleine."<<endl;
	else
	{
		this->listeCol[l].ajoutPion(pi);
		// Met à jour l'état.
		h=this->listeCol[l].getNbPion()-1;
		numCase=h+LARGEUR*l;
		if (numJoueur==1)this->etat1+=(uint64_t)1<<numCase;
		if (numJoueur==2)this->etat2+=(uint64_t)1<<numCase;
		cout<<"Etat1: "<<this->etat1<<endl;
		cout<<"Etat2: "<<this->etat2<<endl;
		cout<<"Pion "<<this->listeCol[l].getContenuH(h).getNum()<<" en case "<<numCase<<" ("<<l<<","<<h<<")."<<endl;
		ok=true;
	}
	return ok;
}

bool EtatCourant::enlever(int l,int numJoueur)
{
	int h,numCase;
	bool ok=false;
	h=this->listeCol[l].getNbPion()-1;
	if (h+1>0)
	{
		numCase=h+LARGEUR*l;
		cout<<"Pion "<<this->listeCol[l].getContenuH(h).getNum()<<" en case "<<numCase<<" ("<<l<<","<<h<<") enleve..."<<endl;
		this->listeCol[l].enlevePion();
		// Mise à jour this->etat :
		// Il faut remettre un zéro dans la case correspondante,
		// c.-à-d. soustraire 2 ^ numéro de case.
		if (numJoueur==1)this->etat1-=(uint64_t)1<<numCase;
		if (numJoueur==2)this->etat2-=(uint64_t)1<<numCase;
		ok=true;
	}
	else cout<<"Colonne vide."<<endl;
	return ok;
}