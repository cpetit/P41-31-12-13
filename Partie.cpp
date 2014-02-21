// Version du 12/02/2014

#include <iostream>
#include "Partie.h"

// Constructeur par défaut
Partie::Partie()
{
	this->joueur[0]=new Humain(0);
	this->joueur[1]=new Humain(1);
}

// Constructeurs qui permettent en début de partie de décider si l'on
// joue entre deux humains, deux IA, ou un humain et une IA.
// Le tableau "joueur" est un (petit) tableau polymorphe qui va
// contenir des pointeurs vers des humains ou des IA (classes qui
// héritent de Joueur).

Partie::Partie(char typeJ0,string nomJ0,char typeJ1,string nomJ1)
{
	if (typeJ0=='H') this->joueur[0]=new Humain(0);
	else this->joueur[0]=new IA(0,AB);
	if (typeJ1=='H') this->joueur[1]=new Humain(1);
	else this->joueur[1]=new IA(1,AB);
	this->joueur[0]->setJoueur(nomJ0,"rouge");
	this->joueur[1]->setJoueur(nomJ1,"jaune");
	this->gagnant=-1;
	this->gagne=false;
	this->nbCoup=0;
	this->trait=0;
	this->historique.clear();
}

// Trois constructeurs avec type d'algorithmes en cas de joueur non-humain

Partie::Partie(char typeJ0,string nomJ0,ALGO algo0,char typeJ1,string nomJ1,ALGO algo1)
{
	if (typeJ0=='H') this->joueur[0]=new Humain(0);
	else this->joueur[0]=new IA(0,algo0);
	if (typeJ1=='H') this->joueur[1]=new Humain(1);
	else this->joueur[1]=new IA(1,algo1);
	this->joueur[0]->setJoueur(nomJ0,"rouge");
	this->joueur[1]->setJoueur(nomJ1,"jaune");
	this->gagnant=-1;
	this->gagne=false;
	this->nbCoup=0;
	this->trait=0;
	this->historique.clear();
}

Partie::Partie(char typeJ0,string nomJ0,ALGO algo0,char typeJ1,string nomJ1)
{
	if (typeJ0=='H') this->joueur[0]=new Humain(0);
	else this->joueur[0]=new IA(0,algo0);
	if (typeJ1=='H') this->joueur[1]=new Humain(1);
	else this->joueur[1]=new IA(1,AB);
	this->joueur[0]->setJoueur(nomJ0,"rouge");
	this->joueur[1]->setJoueur(nomJ1,"jaune");
	this->gagnant=-1;
	this->gagne=false;
	this->nbCoup=0;
	this->trait=0;
	this->historique.clear();
}

Partie::Partie(char typeJ0,string nomJ0,char typeJ1,string nomJ1,ALGO algo1)
{
	if (typeJ0=='H') this->joueur[0]=new Humain(0);
	else this->joueur[0]=new IA(0,AB);
	if (typeJ1=='H') this->joueur[1]=new Humain(1);
	else this->joueur[1]=new IA(1,algo1);
	this->joueur[0]->setJoueur(nomJ0,"rouge");
	this->joueur[1]->setJoueur(nomJ1,"jaune");
	this->gagnant=-1;
	this->gagne=false;
	this->nbCoup=0;
	this->trait=0;
	this->historique.clear();
}

Partie::~Partie(void)
{
	delete(this->joueur[0]);
	delete(this->joueur[1]);
}

int Partie::getGagnant(void)
{
	return this->gagnant;
}

Joueur* Partie::getJoueur(int i)
{
	return joueur[i];
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

void Partie::SetPartie(string nomJ0,string nomJ1)
{
	delete(this->joueur[0]);
	delete(this->joueur[1]);
	this->joueur[0]=new Humain(0);
	this->joueur[1]=new Humain(1);
	this->joueur[0]->setJoueur(nomJ0,"rouge");
	this->joueur[1]->setJoueur(nomJ1,"jaune");
	this->gagnant=-1;
	this->gagne=false;
	this->nbCoup=0;
	this->trait=0;
	this->historique.clear();
}

void Partie::SetPartie(string nomJ0,string nomJ1,ALGO alg)
{
	delete(this->joueur[0]);
	delete(this->joueur[1]);
	this->joueur[0]=new Humain(0);
	this->joueur[1]=new IA(1,alg);
	this->joueur[0]->setJoueur(nomJ0,"rouge");
	this->joueur[1]->setJoueur(nomJ1,"jaune");
	this->gagnant=-1;
	this->gagne=false;
	this->nbCoup=0;
	this->trait=0;
	this->historique.clear();
}

void Partie::SetPartie(string nomJ0,ALGO algo0,string nomJ1,ALGO algo1)
{
	delete(this->joueur[0]);
	delete(this->joueur[1]);
	this->joueur[0]=new IA(0,algo0);
	this->joueur[1]=new IA(1,algo1);
	this->joueur[0]->setJoueur(nomJ0,"rouge");
	this->joueur[1]->setJoueur(nomJ1,"jaune");
	this->gagnant=-1;
	this->gagne=false;
	this->nbCoup=0;
	this->trait=0;
	this->historique.clear();
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
	// Toutes ces valeurs sont remontées à la méthode qui appelle joueUnCoup
	// via les pointeurs.

	int numCase;
	if ((*encore)&&(!situation.getCol(*coup).isPleine())&&(!this->gagne))
	{
		*j=this->trait;
		*ok=situation.jouer(joueur[*j]->getListePion().back(),*coup,*j);
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
	// Toutes ces valeurs sont remontées à la méthode qui appelle joueUnCoup
	// via les pointeurs.

	int derniereCase,ligne,colonne;
	int numJoueur=(1+this->trait)%2;	// Celui qui jouait au coup précédent
	if(this->nbCoup>0)
	{
		// On supprime le coup annulé de l'historique des coups.
		derniereCase=this->historique.back();
		this->historique.pop_back();
		// On rajoute le pion correspondant au stock du joueur.
		ligne=derniereCase%7;
		colonne=(int)(derniereCase-ligne)/7;
		joueur[numJoueur]->pushPion(this->situation.getCol(colonne).getContenuH(ligne));
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

