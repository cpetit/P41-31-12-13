// Version du 06/02/2014

#define PI 3.1415926535897932384626433832795

static int Width;	
static int Height;

#pragma once
#include <windows.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <string>
#include <vector>
#include "Pion.h"
#include "Case.h"
#include "Colonne.h"
#include "EtatCourant.h"
using namespace std;

class Fenetre
{
	// Attributs
	private:

	// M�thodes
	public:
	Fenetre(void);
	~Fenetre(void);
	void ouvrir(int argc, char** argv);
};

