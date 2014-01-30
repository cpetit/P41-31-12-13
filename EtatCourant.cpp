// Version du 29/01/14

#include "EtatCourant.h"
#include <iostream>

// Constructeur.
EtatCourant::EtatCourant(void)
{
	this->gagne=false;

	// Les colonnes sont num�rot�es � la cr�ation.
	for(int i=0;i<LARGEUR;i++) this->listeCol[i]=Colonne(i);
	
	// Cr�ation du tableau des positions gagnantes,
	// � partir du fichier qui les stocke.
	ifstream fichier("posg.txt",ios::in);
    if(fichier)
    {
      for(int indice=0;indice<NBPOSG;indice++) fichier>>this->posG[indice];     
      fichier.close();
    }
    else cerr << "Erreur" << endl;

	// Initialise l'�tat de la partie � 0.
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
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if(i==1) return this->etat1;
	else return this->etat2;
}

// Teste si la partie est gagn�e.
bool EtatCourant::isGagne(void)
{
	bool res=false;
	for(int indice=0;indice<NBPOSG;indice++)
	{
		// Chaque grille est repr�sent�e par un entier dont la d�composition
		// binaire donne les cases o� un joureur a ses pions.
		// On effectue un "et" binaire entre une position gagnante et la grille actuelle.
		// Ceci revient � faire un masque en se focalisant uniquement sur les cases
		// qui compose la position gagnante � tester.
		// Si ce "et" coincide avec la position gagnante, le jeu est termin�.
		if((this->posG[indice]&&this->etat1)==this->posG[indice]) res=true;  
		//cout<<"Gagne!!\n";	// � virer ensuite.
	}
	return res;
}

// Joue un pion � la colonne l.
// Si la colonne est pleine, rien ne se passe.
void EtatCourant::jouer(Pion pi,int l)
{
	int h,numCase;
	if (this->listeCol[l].isPleine()) cout<<"Coup impossible, colonne pleine."<<endl;
	else
	{
		this->listeCol[l].ajoutPion(pi);
		// Met � jour l'�tat.
		h=this->listeCol[l].getNbPion()-1;
		numCase=h+LARGEUR*l;
		(uint64_t)1<<numCase;
		this->etat1+=(uint64_t)1<<numCase;
	}
}

void EtatCourant::enlever(int l)
{
	int h;
	this->listeCol[l].enlevePion();
	h=this->listeCol[l].getNbPion()-1;
	// Mettre � jour this->etat
}