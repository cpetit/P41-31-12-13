// Version du 11/02/2014

#include "Humain.h"


Humain::Humain(void)
{
}

Humain::Humain(int num)
{
	this->numJ=num;
}

Humain::~Humain(void)
{
}

bool Humain::isHumain(void)
{
	return true;
}

int Humain::jouer(EtatCourant* EtC)
{
	return -1;
}
