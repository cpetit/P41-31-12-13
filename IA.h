// Version du 11/02/2014

#pragma once
#include "joueur.h"

class IA : public Joueur
{
	private:

	public:
	IA(void);
	~IA(void);
	int jouer(uint64_t,uint64_t);
};

