// Version du 12/02/14

#include "EtatCourant.h"
#include <iostream>

// Constructeur.
EtatCourant::EtatCourant(void)
{
	this->gagne=false;

	// Les colonnes sont num�rot�es � la cr�ation.
	for(int i=0;i<LARGEUR;i++)this->listeCol[i]=Colonne(i);
	
	// Cr�ation du tableau des positions gagnantes,
	// � partir du fichier qui les stocke.
	// ATTENTION !!
	// Le fichier texte doit se trouver dans le r�pertoire courant.
	/*ifstream fichier("posg.txt",ios::in);
    if(fichier)
    {
      for(int indice=0;indice<NBPOSG;indice++) fichier>>this->posG[indice];
      fichier.close();
    }
    else cerr << "Erreur" << endl;*/

	// Initialise l'�tat de la partie � 0, pour chaque joueur.
	this->etat[0]=(uint64_t)0;
	this->etat[1]=(uint64_t)0;
	for(int i=0;i<LARGEUR;i++)firstVide[i]=0;
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

uint64_t EtatCourant::getEtat(int j)
{
	return this->etat[j];
}

int8_t* EtatCourant::getFirstVide(void)
{
	int8_t* adresse=firstVide;
	return adresse;
}

// Teste si la partie est gagn�e par le joueur num�ro j.
bool EtatCourant::isGagne(int j)
{
	/* Premi�re m�thode (personnelle) finalement non utilis�e.

	bool res=false;
	for(int indice=0;(indice<NBPOSG)&&(!res);indice++)
	{
		// Chaque grille est repr�sent�e par un entier dont la d�composition
		// binaire donne les cases o� un joueur a mis ses pions.
		// On effectue un "et" binaire entre une position gagnante et la grille actuelle.
		// Ceci revient � faire un masque en se focalisant uniquement sur les cases
		// qui composent la position gagnante (4 cases � tester).
		// Si ce "et" coincide avec la position gagnante, le jeu est termin�.
		// Au final on parcourt uniquement le tableau de positions gagnantes:
		// au + 69 op�rations pour la taille de jeu standard.
		if((this->posG[indice]&this->etat[j])==this->posG[indice])
		{
			res=true;  
			cout<<"Joueur "<<j<<" a gagne !!\n";
		}
	}
	return res;
	*/

	// Seconde m�thode (de John TROMP) utilisant seulement des shifts
	// et des "et" binaires, sans aucune boucle !!

	uint64_t c=this->etat[j]&(this->etat[j]>>6);
    if (c & (c >> 2 * 6))return true;
    c = this->etat[j] & (this->etat[j] >> 7);
    if (c & (c >> 2 * 7))return true;
    c = this->etat[j] & (this->etat[j] >> 8);
    if (c & (c >> 2 * 8))return true;
    c = this->etat[j] & (this->etat[j] >> 1);
    if (c & (c >> 2))return true;
    return false;
}

// Joue un pion � la colonne l.
// Si la colonne est pleine, rien ne se passe.
bool EtatCourant::jouer(Pion pi,int l,int j)
{
	int h,numCase;
	bool ok=false;
	if (this->listeCol[l].isPleine()) cout<<"Coup impossible, colonne pleine."<<endl;
	else
	{
		this->listeCol[l].ajoutPion(pi);
		// Met � jour l'�tat.
		h=this->listeCol[l].getNbPion()-1;
		this->firstVide[l]++;
		numCase=h+LARGEUR*l;
		this->etat[j]+=(uint64_t)1<<numCase;
		// On pourrait aussi faire un ou exclusif � la place du + car le pion est ajout�
		// sur une case vide.
		cout<<"Pion "<<this->listeCol[l].getContenuH(h).getNum()<<" en case "<<numCase<<" ("<<l<<","<<h<<")."<<endl;
		ok=true;
	}
	return ok;
}

bool EtatCourant::enlever(int l,int j)
{
	// l est la colonne o� enlever le pion
	// j est le nim�ro du joueur
	int h,numCase;
	bool ok=false;
	h=this->listeCol[l].getNbPion()-1;
	if (h+1>0)
	{
		numCase=h+LARGEUR*l;
		cout<<"Pion "<<this->listeCol[l].getContenuH(h).getNum()<<" en case "<<numCase<<" ("<<l<<","<<h<<") enleve..."<<endl;
		this->listeCol[l].enlevePion();
		this->firstVide[l]--;
		// Mise � jour this->etat :
		// Il faut remettre un z�ro dans la case correspondante,
		// c.-�-d. soustraire 2 ^ num�ro de case.
		this->etat[j]-=(uint64_t)1<<numCase;
		// Idem; on pourrait refaire un ou exclusif.
		ok=true;
	}
	else cout<<"Colonne vide."<<endl;
	return ok;
}