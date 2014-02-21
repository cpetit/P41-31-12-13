// Version du 01/02/2014

#pragma once
#include <vector>
#include <stdint.h>
#include <fstream>
#include <iostream>
#include <list>
using namespace std;

class Noeud
{
	private:
	list<Noeud> fils(int);
	
	public:	
	Noeud(void);
	~Noeud(void);
	list<Noeud> getFils(int);
	bool isFeuille(int);
	int eval(uint64_t,uint64_t);
};

