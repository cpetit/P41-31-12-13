// Version du 11/02/2014

#define PI 3.1415926535897932384626433832795

static int Width;	
static int Height;

#pragma once
#include <windows.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <string>
#include <stdint.h>
#include <vector>
#include <iostream>
#include <fstream>
#include "Partie.h"
#include "Pion.h"
#include "Case.h"
#include "Colonne.h"
#include "EtatCourant.h"
#include "Joueur.h"
#include "Humain.h"
#include "IA.h"
using namespace std;

class Fenetre
{
	// Méthodes
	public:
	Fenetre(void);
	~Fenetre(void);
	void ouvrir(int argc, char** argv);
};