// Version du 08/02/14

#include "Fenetre.h"

// Variables globales devant être appelées dans les différentes
// fonctions de callback (dont on ne peut pas modifier le prototype).

Partie maPartie;
int valeurMenu;
char couleurCase[HAUTEUR][LARGEUR];
bool* partieEnCours= new bool(true);

// Constructeur et destructeur (par défaut).
Fenetre::Fenetre(void)
{
}

Fenetre::~Fenetre(void)
{
	delete(partieEnCours);
}

// Méthodes

// La méthode ouvrir récupère les paramètres arg et argv indispensables
// au lancement de la bibliothèque opengl.
// Elle initialise la fenêtre graphique et gère les évènements.

void Fenetre::ouvrir(int argc, char** argv)
{

	// Prototypes des fonctions qui seront appelées par les fonctions callback
	// lorsqu'un évènement se déclenche.
	// Ces prototypes sont imposés et non modifiables.
	// Il s'agit (constructeurs exceptés) de la seule méthode de fenêtre:
	// La machine à états OpenGL impose le passage de tous les évènements via
	// cette méthode. Nous allons donc travailler à partir d'ouvrir, à
	// l'intérieur de laquelle sera appelée la boucle openGL.
	// Toutes les actions devront se dérouler dans cette méthode et être appelées
	// via des fonctions callback dont les prototypes suivent.
	// Le code de ces fonctions se trouve à la fin du fichier .ccp

	void affiche(void);
	void handleButtons(int button, int state, int x, int y);
	void handleResize(int w, int h);
	void handleKey(unsigned char key, int x, int y);
	void menu(int);
	void initTab(void);
	//_________________________________________________________________________

	initTab();	// Initialise les couleurs des cases de la grille.

	// Initialisations de la fenêtre graphique
	// et des modes graphiques utilisés.
	glutInit(&argc, argv);							// Initialisation de glut.  
    glutInitWindowSize(800, 800*1080/1920);			// Taille de la fenetre.
    glutInitWindowPosition(50, 50);					// Position de la fenetre.
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);   // Type d'affficahge RGBA. 
    glutCreateWindow("PUISSANCE 4 - clic droit pour accéder au menu - q pour quitter -"); 
	//_________________________________________________________________________


	// Création du menu
	int m = glutCreateMenu(menu) ;
	glutSetMenu(m) ;
	glutAddMenuEntry("Charger partie.",1) ;
	glutAddMenuEntry("Sauvegarder partie.",2) ;
	glutAddMenuEntry("Annuler coup.",3) ;
	glutAddMenuEntry("Nouvelle partie.",4) ;
	glutAttachMenu(GLUT_RIGHT_BUTTON) ;
	//_____________________________________________


	// On écoute les évènements via les fonctions callback
	// et on effctue l'affichage en fonction des appels.
	glutDisplayFunc(affiche);
	glutKeyboardFunc(handleKey);
	glutMouseFunc(handleButtons);
	glutReshapeFunc(handleResize);
	//____________________________________________________

	// Lancement de la boucle principale d'affichage et de
	// la machine à états opengl.
	glutMainLoop();
	delete partieEnCours;
}	// fin de la méthode ouvrir


//_____________________________________________________________
// Liste et code des fonctions appelées lors des évènements.
//_____________________________________________________________

void initTab(void)
{
	// Initialisation de la couleur (noire) des cases en
	// début de jeu.
	for(int i=0;i<HAUTEUR;i++)
	{
		for(int j=0;j<LARGEUR;j++) couleurCase[i][j]='N';
	}
}

void affiche()
{
	// Fonction effectuant l'affichage et sa mise à jour.
	// Cette fonction est automatiquement appelée (via la 
	// fonction callback glutDisplayFunc) dès qu'un affichage
	// est à effectuer.
	int i;
	void annuleCoup(void);		// prototype d'annuleCoup
	void nouvellePartie(void);	// self explanatory
	void sauvegarde(void);		// idem
	void chargerPartie(void);			// idem
  
	glClearColor(0, 0, 1, 0);		// Couleur de fond
	glClear(GL_COLOR_BUFFER_BIT);	// Nettoyage de la fenêtre 
  
	// Ecoute du menu et exécution de la fonction
	// correspondante à chaque choix (via le callback !).
	switch(valeurMenu)
	{
		case 1: chargerPartie();break;
		case 2: sauvegarde();break;
		case 3: annuleCoup();break;
		case 4: nouvellePartie();break;
	}
	valeurMenu=0;
 
	// Tracé de la grille.
	glColor3f(0, 0, 0);
	glLineWidth(1);  
	glBegin(GL_LINES);
	for(i = 0; i <= LARGEUR; i++)
	{
		glVertex2f(0, i);
		glVertex2f(LARGEUR, i);
	}
	for(i = 0; i <= LARGEUR; i++)
	{
		glVertex2f(i, 0);
		glVertex2f(i, HAUTEUR);
	}
	glEnd();
	glFlush();

	// Tracé des cases.
	glEnableClientState(GL_NORMAL_ARRAY);
	for(int k=0;k<LARGEUR;k++)
	{
		for(int l=0;l<HAUTEUR;l++)
		{
			if(couleurCase[l][k]=='N') glColor3f(0, 0, 0);
			else if(couleurCase[l][k]=='R') glColor3f(1, 0, 0);
			else glColor3f(255, 255, 0);
			glBegin(GL_POLYGON);
			for(double i = 0; i < 2 * PI; i += PI / 25)glVertex3f(0.5+k+cos((double)i)*0.4,0.5+l+sin((double)i)*0.4, 0.0);
			glEnd();
			glFlush();
		}

		//Tests pour utiliser des quadriques à la place des polygones.
		//pour une version ultérieure du programme...
		//GLUquadricObj *circle = gluNewQuadric ();
		//if (circle != 0) gluQuadricDrawStyle(circle, GLU_FILL); 
		//gluDisk (nomDuDisque,centre,rayon,rayonTrouCentral,1);
		//gluDisk (circle,0,2,60,4); 
	}
}

void handleButtons(int button, int state, int x, int y)
{
	// Fonction de gestion de la souris dans la fenêtre.
	// Gestion des clics dans la grille.

	int i, j;				// ligne et colonne
	float dx, dy;			// déplacements en x et y
	bool* ok= new bool;		// vrai si coup possible
	int* coup=new int;		// colonne où le coup est joué
	int* ligne=new int;		// ligne (hauteur) du coup
	string* c=new string;	// couleur du pion joué
	*ok=true;

	// Où se trouve la souris sur la grille ?
	if(button != GLUT_LEFT_BUTTON || state != GLUT_UP) return;  
	y = Height - y;
	dy = Height/(float)HAUTEUR;
	dx = Width/(float)LARGEUR;
	i = (int)(y/dy);
	j = (int)(x/dx); 

	// Un clic sur une colonne déclenche un coup dans cette colonne.
	cout<<"Clic sur la case ("<<j<<","<<i<<").\n";
	*coup=j;
	maPartie.joueUnCoup(partieEnCours,coup,ligne,ok,c);
	if(*ok)
	{
		// Si le coup a été effectivement joué, on effectue
		// l'affichage correspondant de la nouvelle case.
		if (*c=="rouge")couleurCase[*ligne][*coup]='R';
		if (*c=="jaune")couleurCase[*ligne][*coup]='J';
		glutPostRedisplay();
	}
	else
	{
		if(*partieEnCours)
		{
			cout<<"Coup non possible."<<endl;
		}
		else
		{
			cout<<"Partie terminee."<<endl;
			cout<<maPartie.getGagnant()<<" gagnant."<<endl;
		}
	}
	// Nettoyage
	delete ok;
	delete coup;
	delete ligne;
	delete c;
}

void handleResize(int w, int h)
{
	// Fonction de changement de taille ou de place
	// de la fenêtre et de mise à jour des éléments à afficher.
	Width = w;
	Height = h;
	glViewport(0, 0, Width, Height); 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, LARGEUR, 0, HAUTEUR);
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}

void handleKey(unsigned char key,int x, int y)
{
	// Gestion des évènements du clavier.
	// Q pour quitter.
	switch(key)
	{
		case 'q':
		case 'Q':
		exit(0);
	}
}

void menu(int choix)
{
	// Ecoute le menu et positionne valeurMenu
	// pour exécution de la fonction callback
	// correspondante via la fonction affiche.
	valeurMenu = choix;
	glutPostRedisplay() ;
}


void annuleCoup(void)
{
	// Tente d'annuler le dernier coup joué.
	bool* isCoupAnnule= new bool;
	int* i=new int;
	int* j=new int;
	maPartie.annuleCoup(isCoupAnnule,i,j);
	if(*isCoupAnnule)
	{
		couleurCase[*i][*j]='N';
		*partieEnCours=true;
		glutPostRedisplay() ;
	}
	else cout<<"Aucun coup a annuler."<<endl;
	delete isCoupAnnule;
	delete i;
	delete j;
}

void nouvellePartie(void)
{
	// Ramène une partie au début.
	int n=maPartie.getNbCoup();
	for(int i=n;i>0;i--)
	{
		annuleCoup();
	}
}

void sauvegarde(void)
{
	// Fonction qui sauvegarde la partie en cours.
	string nomFichier;								// Fichier dans lequel on sauvegarde.
	vector<int> vecteur=maPartie.getHistorique();	// Historique des coups.
	string premier=maPartie.getTrait();				// Joueur qui a débuté la partie.
	int nbCoup=maPartie.getNbCoup();				// Nombre de coups joués.

	if(nbCoup%2==1)
	{
		if(premier=="rouge")premier="jaune";
		else premier="rouge";
	}
	cout<<"Nom de la partie a sauvegarder : ";
	cin>>nomFichier;
	ofstream fichier(nomFichier+".txt");
    if (!fichier)
    {
        cerr <<"Erreur\n";
        return;
    }
	else
	{
		fichier<<nbCoup<<"\n";
		fichier<<premier<<"\n";
		for(int i=0;i<nbCoup;i++)fichier<<vecteur[i]<<"\n";
		fichier.close();
    }
}

void chargerPartie(void)
{
	// Fonction qui charge une partie depuis un fichier
	// texte dans le répertoire local.
	string nomFichier;		// Fichier dans lequel on sauvegarde.
	vector<int> vecteur;	// Historique des coups.
	string premier;			// Joueur qui a débuté la partie.
	int nbCoup;				// Nombre de coups joués.
	int pos;				// Position à mettre dans l'historique.
	bool* ok= new bool;		// vrai si coup possible
	//int* coup=new int;		// colonne où le coup est joué
	int* ligne=new int;		// ligne (hauteur) du coup
	string* c=new string;	// couleur du pion joué
	*ok=true;

	// On recupère dans le fichier le nombre de coups joués,
	// la couleur du joueur qui a débuté la partie et
	// l'historique des coups.
	cout<<"Nom de la partie a charger : ";
	cin>>nomFichier;
	ifstream fichier(nomFichier+".txt",ios::in);
    if(fichier)
    {
		fichier>>nbCoup;
		cout<<nbCoup<<endl;
		fichier>>premier;
		cout<<premier<<endl;
		for(int i=0;i<nbCoup;i++)
		{
			fichier>>pos;
			vecteur.push_back(pos);
			cout<<vecteur[i]<<endl;
		}
		fichier.close();
    }
    else cerr<<"Erreur"<<endl;

	// On rejoue la partie jusqu'au dernier coup !
	nouvellePartie();
	for(int i=0;i<nbCoup;i++)
	{
		// il faut trouver le numero de colonne
		// correspondant à chaque case
		pos=(int)(vecteur[i]-vecteur[i]%LARGEUR)/LARGEUR;
		maPartie.joueUnCoup(partieEnCours,&pos,ligne,ok,c);
		if(*ok)
		{
			if (*c=="rouge")couleurCase[*ligne][pos]='R';
			if (*c=="jaune")couleurCase[*ligne][pos]='J';
		}
	}
	// On réaffiche tout à la fin.
	glutPostRedisplay();	
	// Nettoyage
	delete ok;
	//delete coup;
	delete ligne;
	delete c;
}