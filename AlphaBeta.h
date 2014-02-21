// Version du 01/02/2014

#pragma once
#include <vector>
#include <stdint.h>
#include <list>
#include <fstream>
#include <iostream>
#include "Colonne.h"
using namespace std;

class AlphaBeta
{
	private:
	int coup;

	public:
	AlphaBeta(void);
	~AlphaBeta(void);
	int getCoup(void);
	int parcours(uint64_t,uint64_t,int8_t*,int,int,int,int);
	int eval(uint64_t,uint64_t);
	bool quatre(uint64_t);
	uint64_t trois(uint64_t,uint64_t);
};

