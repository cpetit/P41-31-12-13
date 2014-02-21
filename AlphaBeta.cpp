
#include "AlphaBeta.h"

// Constructeur et destructeur
AlphaBeta::AlphaBeta(void)
{
	this->coup=-1;
}

AlphaBeta::~AlphaBeta(void)
{
}

int AlphaBeta::getCoup(void)
{
	return this->coup;
}

// Autres méthodes
int AlphaBeta::parcours(uint64_t etat0,uint64_t etat1,int8_t* firstVide,int prof,int alpha,int beta,int numJoueur)
{
	// Parcours récursif - en profondeur - de l'arbre.
	// Algorithme de parcours Alpha-Beta sous convention Negamax.
	int score;
	vector<int> coupPossible(0);
	// Trouver les coups possibles et les mettre dans une liste d'octets
	for(int i=0;i<LARGEUR;i++)
	{
		if(firstVide[i]<6) coupPossible.push_back(i);
	}
	if((prof==0)||(coupPossible.size()==0))return this->eval(etat0,etat1);
    else
	{
		score=-100000;
		for(int i=0;i<(int)coupPossible.size();i++)
		{
			int numCase=firstVide[i]+LARGEUR*i;
			etat0^=(uint64_t)1<<numCase;
			firstVide[i]++;
			score=-parcours(etat1,etat0,firstVide,prof-1,-beta,-alpha,(numJoueur+1)%2);
			firstVide[i]--;
			etat0^=(uint64_t)1<<numCase;
			if(score>=alpha)
			{
				alpha=score;
				this->coup=coupPossible[i];
				if(alpha>=beta)break;
			}
			//cout<<"Prof "<<prof<<" :"<<this->coup<<"("<<score<<")"<<endl;
        }
		return(alpha);
	}
}

int AlphaBeta::eval(uint64_t etat0,uint64_t etat1)
{
	int score=0;
	int poids[49]={3,4,5,5,4,3,0,4,6,8,8,6,4,0,5,8,11,11,8,5,0,7,10,13,13,10,7,0,5,8,11,11,8,5,0,4,6,8,8,6,4,0,3,4,5,5,4,3,0};
	for(int i=0;i<49;i++)score+=(int)poids[i]*((etat0>>i)%2-(etat1>>i)%2);
	// Est-ce que l'on gagne ?
	if(this->quatre(etat0))score+=100000;
    // Est-ce que l'on perd ?
	if(this->quatre(etat1))score-=100000;
	// Y a-t-il une menace de trois pions ?
	if(trois(etat0,etat1)!=0)score+=10000;
	if(trois(etat1,etat0)!=0)score-=5000;
	return score;
}

// Existe-t-il 4 pions alignés dans l'état
bool AlphaBeta::quatre(uint64_t etat)
{
	bool aligne=false;
	uint64_t c=etat&(etat>>6);if (c & (c >> 2 * 6))aligne=true;
    c = etat & (etat >> 7);if (c & (c >> 2 * 7))aligne=true;
    c = etat & (etat >> 8);if (c & (c >> 2 * 8))aligne=true;
    c = etat & (etat >> 1);if (c & (c >> 2))aligne=true;
	return aligne;
}

uint64_t AlphaBeta::trois(uint64_t etat0,uint64_t etat1)
{
	int H1=HAUTEUR+1;
	uint64_t BAS=((1ull<<(H1*LARGEUR))-1) / ((1ull<<H1)-1);
	uint64_t COL1=(1ull<<HAUTEUR)-1;
	uint64_t GRILLE=BAS*COL1;
	uint64_t vide=(~(etat0|etat1))&GRILLE;
	uint64_t res=0ull;
	// Menace de type horizontale:
	// X pour pion et _ pour vide
	res|=vide&(etat0>>H1)&(etat0>>(2*H1))&(etat0<<H1);		// X_XX
	res|=vide&(etat0>>H1)&(etat0<<H1)&(etat0<<(2*H1));		// XX_X
	res|=vide&(etat0>>H1)&(etat0>>(2*H1))&(etat0>>(3*H1));	// _XXX
	res|=vide&(etat0<<H1)&(etat0<<(2*H1))&(etat0<<(3*H1));	// XXX_
	// Menace de type verticale : (bas)XXX_(haut) seul cas de figure.
	//res|=vide&(etat0<<1)&(etat0<<2)&(etat0<<3);
	// Menaces de type diagonale ou antidiagonale:
	res|=vide&(etat0>>(H1+1)) & (etat0>>(2*(H1+1))) & (etat0>>(3*(H1+1)));
	res|=vide&(etat0>>(H1+1)) & (etat0>>(2*(H1+1))) & (etat0<<(H1+1));
	res|=vide&(etat0>>(H1+1)) & (etat0<<(H1+1)) & (etat0<<(2*(H1+1)));
	res|=vide&(etat0<<(H1+1)) & (etat0<<(2*(H1+1))) & (etat0<<(3*(H1+1)));
	res|=vide&(etat0>>(H1-1)) & (etat0>>(2*(H1-1))) & (etat0>>(3*(H1-1)));
	res|=vide&(etat0>>(H1-1)) & (etat0>>(2*(H1-1))) & (etat0<<(H1-1));
	res|=vide&(etat0>>(H1-1)) & (etat0<<(H1-1)) & (etat0<<(2*(H1-1)));
	res|=vide&(etat0<<(H1-1)) & (etat0<<(2*(H1-1))) & (etat0<<(3*(H1-1)));
	return res;
}