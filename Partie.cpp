// Version du 11/02/2014

#include <iostream>
#include "Partie.h"

Partie::Partie(void)
{
	this->joueur[0].setJoueur("moa","rouge");
	this->joueur[1].setJoueur("pc","jaune");
	this->gagnant=-1;
	this->gagne=false;
	this->nbCoup=0;
	this->trait=0;
	this->historique.clear();
}

Partie::~Partie(void)
{
	// Nettoyage
}

int Partie::getGagnant(void)
{
	return this->gagnant;
}

Joueur Partie::getJoueur(int i)
{
	return this->joueur[i];
}

vector<int> Partie::getHistorique(void)
{
	return (this->historique);
}

 int Partie::getTrait(void)
{
	return (this->trait);
}

int Partie::getNbCoup(void)
{
	return(this->nbCoup);
}

EtatCourant Partie::getSituation(void)
{
	return this->situation;
}

void Partie::joueUnCoup(bool*encore,int*coup,int*ligne,bool*ok,int*j)
{	
	// *encore reste vrai tant que la partie n'est pas finie
	// (c.-à-d. pas de gagnant et encore des pions à jouer)
	// *encore correspond à la variable partieEnCours de Fenetre.
	// *coup est la colonne où l'on doit jouer.
	// *ligne est le numero de ligne où jouer.
	// *ok indique si le coup est possible ou non
	// *j donne le numéro du joueur qui a le trait (si coup ok)

	int numCase;
	if ((*encore)&&(!situation.getCol(*coup).isPleine())&&(!this->gagne))
	{
		*j=this->trait;
		*ok=situation.jouer(this->joueur[*j].getListePion().back(),*coup,*j);
		nbCoup++;
		cout<<"Nombre de coups : "<<nbCoup<<"\n";
		// Teste si le coup rend gagnant le joueur qui a le trait.
		gagne=situation.isGagne(*j);
		if (this->gagne) this->gagnant=*j;
		// Si un gagnant existe, la partie va s'arrêter.
		*encore=!this->gagne;
		// Le numéro de ligne où a été ajouté le pion est renvoyé
		// à partie pour l'affichage graphique (partie ne connaît pas
		// le nombre de pions présents dans la colonne).
		*ligne=this->situation.getCol(*coup).getNbPion()-1;
		// On ajoute le numéro de case dans l'historique des coups.
		numCase=*ligne+7*(*coup);
		historique.push_back(numCase);
		// On permute le trait.
		this->trait=(1+this->trait)%2;
	}
	else
	{
		// Soit la colonne est pleine, soit la partie est finie.
		// dans les deux cas, le joueur n'est pas autorisé à jouer.
		*ok=false;
	}
}

void Partie::annuleCoup(bool*effectue,int* i,int*j)
{
	// *effectue devient vrai quand le coup est annulable.
	// *j colonne où annuler.
	// *i ligne où annuler.

	int derniereCase,ligne,colonne;
	int numJoueur=(1+this->trait)%2;	// Celui qui jouait au coup précédent
	Joueur joueur;
	if(this->nbCoup>0)
	{
		// On supprime le coup annulé de l'historique des coups.
		derniereCase=this->historique.back();
		this->historique.pop_back();
		// On rajoute le pion correspondant au stock du joueur.
		ligne=derniereCase%7;
		colonne=(int)(derniereCase-ligne)/7;
		joueur.pushPion(this->situation.getCol(colonne).getContenuH(ligne));
		// On enlève le pion de la colonne et on met à jour
		// le nombre de coups et le trait.
		*effectue=this->situation.enlever(colonne,numJoueur);
		if(*effectue)
		{
			nbCoup--;
			this->trait=(1+this->trait)%2;
			*i=ligne;
			*j=colonne;
			this->gagne=false;
		}
	}
	else *effectue=false;
}

void Partie::info(void)
{
	char symbole;
	cout<<endl;
	for(int j=HAUTEUR-1;j>=0;j--)
	{
		for(int i=0;i<LARGEUR;i++)
		{
			if(this->situation.getCol(i).getContenuH(j).getCouleur()=="rouge") symbole='.';
			else
			{
				if(this->situation.getCol(i).getContenuH(j).getCouleur()=="jaune") symbole='O';
				else symbole=' ';
			}
			cout<<symbole;
		}
		cout<<endl;
	}
	cout<<endl;
}

