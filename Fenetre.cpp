// Version du 11/02/14

#include "Fenetre.h"

// Variables globales devant �tre appel�es dans les diff�rentes
// fonctions de callback (dont on ne peut pas modifier le prototype).

Partie maPartie;
int valeurMenu;
int clic=-1;
char couleurCase[HAUTEUR][LARGEUR];
bool* partieEnCours= new bool(true);
int* coup=new int(-1);	// colonne o� jouer et/ou marqueur de clic
bool* ok= new bool;		// vrai si coup possible
int* ligne=new int;		// ligne (hauteur) du coup
int* j=new int;			// num�ro du joueur courant

// Constructeur et destructeur (par d�faut).
Fenetre::Fenetre(void)
{
}

Fenetre::~Fenetre(void)
{
	
}

// M�thodes

// La m�thode ouvrir r�cup�re les param�tres arg et argv indispensables
// au lancement de la biblioth�que opengl.
// Elle initialise la fen�tre graphique et g�re les �v�nements.

void Fenetre::ouvrir(int argc, char** argv)
{

	// Prototypes des fonctions qui seront appel�es par les fonctions callback
	// lorsqu'un �v�nement se d�clenche.
	// Ces prototypes sont impos�s et non modifiables.
	// Il s'agit (constructeurs except�s) de la seule m�thode de fen�tre:
	// La machine � �tats OpenGL impose le passage de tous les �v�nements via
	// cette m�thode. Nous allons donc travailler � partir d'ouvrir, �
	// l'int�rieur de laquelle sera appel�e la boucle openGL.
	// Toutes les actions devront se d�rouler dans cette m�thode et �tre appel�es
	// via des fonctions callback dont les prototypes suivent.
	// Le code de ces fonctions se trouve � la fin du fichier .ccp

	void affiche(void);
	void handleButtons(int button, int state, int x, int y);
	void handleResize(int w, int h);
	void handleKey(unsigned char key, int x, int y);
	void menu(int);
	void submenu(int);
	void initTab(void);
	void idle(void);
	//_________________________________________________________________________

	initTab();	// Initialise les couleurs des cases de la grille.

	// Initialisations de la fen�tre graphique
	// et des modes graphiques utilis�s.
	glutInit(&argc, argv);							// Initialisation de glut.  
    glutInitWindowSize(800, 800*1080/1920);			// Taille de la fenetre.
    glutInitWindowPosition(50, 50);					// Position de la fenetre.
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);   // Type d'affficahge RGBA. 
    glutCreateWindow("PUISSANCE 4 - clic droit pour acc�der au menu - a pour annuler coup - q pour quitter -"); 
	//_________________________________________________________________________


	// Cr�ation du menu
	int sm = glutCreateMenu(menu);
    glutAddMenuEntry ("Humain vs humain", 4);
    glutAddMenuEntry ("Humain vs IA", 5);
    glutAddMenuEntry ("IA vs IA", 6);
	int m = glutCreateMenu(menu);
	glutSetMenu(m) ;
	glutAddMenuEntry("Charger partie",1) ;
	glutAddMenuEntry("Sauvegarder partie",2) ;
	glutAddMenuEntry("Annuler coup",3) ;
	glutAddSubMenu("Nouvelle partie",sm) ;
	glutAttachMenu(GLUT_RIGHT_BUTTON) ;

	//_____________________________________________


	// On �coute les �v�nements via les fonctions callback
	// et on effctue l'affichage en fonction des appels.
	glutDisplayFunc(affiche);
	glutKeyboardFunc(handleKey);
	glutMouseFunc(handleButtons);
	glutReshapeFunc(handleResize);
	//____________________________________________________

	// Lancement de la boucle principale d'affichage et de
	// la machine � �tats opengl.
	glutIdleFunc(idle);
	glutMainLoop();
	// Nettoyage
	delete ok;
	delete coup;
	delete ligne;
	delete j;
	delete partieEnCours;
	delete(coup);
}	// fin de la m�thode ouvrir


//_____________________________________________________________
// Liste et code des fonctions appel�es lors des �v�nements.
//_____________________________________________________________

void initTab(void)
{
	// Initialisation de la couleur (noire) des cases en
	// d�but de jeu.
	for(int i=0;i<HAUTEUR;i++)
	{
		for(int k=0;k<LARGEUR;k++) couleurCase[i][k]='N';
	}
}

void affiche()
{
	// Fonction effectuant l'affichage et sa mise � jour.
	// Cette fonction est automatiquement appel�e (via la 
	// fonction callback glutDisplayFunc) d�s qu'un affichage
	// est � effectuer.
	int i;
	void annuleCoup(void);		// prototype d'annuleCoup
	void nouvellePartie(void);	// self explanatory
	void sauvegarde(void);		// idem
	void chargerPartie(void);	// idem
  
	glClearColor(0, 0, 1, 0);		// Couleur de fond
	glClear(GL_COLOR_BUFFER_BIT);	// Nettoyage de la fen�tre 
  
	// Ecoute du menu et ex�cution de la fonction
	// correspondante � chaque choix (via le callback !).
	switch(valeurMenu)
	{
		case 1: chargerPartie();break;
		case 2: sauvegarde();break;
		case 3: annuleCoup();break;
		case 4: nouvellePartie();break;
		case 5: nouvellePartie();break;
		case 6: nouvellePartie();break;
	}
	valeurMenu=0;
 
	// Trac� de la grille.
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

	// Trac� des cases.
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

		// Tests pour utiliser des quadriques � la place des polygones.
		// pour une version ult�rieure du programme...
		// pour la sp�cularit�, le brouillard, etc. on verra aussi apr�s.
		// GLUquadricObj *circle = gluNewQuadric ();
		// if (circle != 0) gluQuadricDrawStyle(circle, GLU_FILL); 
		// gluDisk (nomDuDisque,centre,rayon,rayonTrouCentral,1);
		// gluDisk (circle,0,2,60,4); 
	}
}

void idle(void)
{
	// Fonction qui est ex�cut�e en t�che de fond,
	// tant qu'aucun autre �v�nement ne se d�clenche.
	// Elle permet de g�rer le clic ou l'absence de clic
	// entre joueur humain et IA et permet la temporisation
	// lors de l'annulation d'un coup.
	// *coup est la valeur du coup � jouer pour un joueur humain.
	// la fonction jouer d'un humain renvoie -1 et tant que le clavier
	// n'a pas �t� sollicit�, *coup reste � -1: il ne se passe rien.
	// Lorsque la fonction de callback du clavier est appel�, *coup
	// prend la valeur de la colonne � jouer.
	// La fonction jouer de l'IA renvoie directement la valeur du coup
	// en ce cas, le coup est jou� directement sans avoir � cliquer.

	// VARIABLES GLOBALES UTILISEES DANS CETTE FONCTION
	// *j, *ok, *coup, *ligne, *partieEnCours, maPartie
	
	*j=maPartie.getTrait();
	uint64_t etat0=maPartie.getSituation().getEtat(0);
	uint64_t etat1=maPartie.getSituation().getEtat(1);
	*coup=maPartie.getJoueur(0).jouer();
	if(clic>=0)
	{
		*ok=true;
		if (*coup<0)*coup=clic;
		maPartie.joueUnCoup(partieEnCours,coup,ligne,ok,j);
		if(*ok)
		{
			// Si le coup a �t� effectivement jou�, on effectue
			// l'affichage correspondant de la nouvelle case.
			if (*j==0)couleurCase[*ligne][*coup]='R';
			if (*j==1)couleurCase[*ligne][*coup]='J';
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
		*coup=-1;
		clic=-1;
	}
}

void handleButtons(int button, int state, int x, int y)
{
	// Fonction de gestion de la souris dans la fen�tre.
	// Gestion des clics dans la grille.

	int i, k;				// ligne et colonne
	float dx, dy;			// d�placements en x et y

	// O� se trouve la souris sur la grille ?
	if(button != GLUT_LEFT_BUTTON || state != GLUT_UP) return;  
	y = Height - y;
	dy = Height/(float)HAUTEUR;
	dx = Width/(float)LARGEUR;
	i = (int)(y/dy);
	k = (int)(x/dx); 
	// Capture le num�ro de colonne o� a eu lieu le clic
	// et le met dans *coup pour que le coup puisse �tre
	// effectif dans idle.
	if(*coup<0) clic=k;
}

void handleResize(int w, int h)
{
	// Fonction de changement de taille ou de place
	// de la fen�tre et de mise � jour des �l�ments � afficher.
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
	// Gestion des �v�nements du clavier.
	// Q pour quitter.
	void annuleCoup(void);
	switch(key)
	{
		case 'a': annuleCoup();break;
		case 'A': annuleCoup();break;
		case 'q':
		case 'Q':
		exit(0);
	}
}

void menu(int choix)
{
	// Ecoute le menu et positionne valeurMenu
	// pour ex�cution de la fonction callback
	// correspondante via la fonction affiche.
	valeurMenu = choix;
	glutPostRedisplay() ;
}


void annuleCoup(void)
{
	// Tente d'annuler le dernier coup jou�.
	bool* isCoupAnnule= new bool;
	int* i=new int;
	int* k=new int;
	maPartie.annuleCoup(isCoupAnnule,i,k);
	if(*isCoupAnnule)
	{
		couleurCase[*i][*k]='N';
		*partieEnCours=true;
		glutPostRedisplay() ;
	}
	else cout<<"Aucun coup a annuler."<<endl;
	delete isCoupAnnule;
	delete i;
	delete k;
}

void nouvellePartie(void)
{
	// Cr�e une nouvelle partie.
	// Permet le choix du type de joueur.
	// Ram�ne une partie au d�but.

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
	int premier=maPartie.getTrait();				// Joueur qui a d�but� la partie.
	int nbCoup=maPartie.getNbCoup();				// Nombre de coups jou�s.

	if(nbCoup%2==1)premier=(1+premier)%2;
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
	// texte dans le r�pertoire local.
	string nomFichier;		// Fichier dans lequel on sauvegarde.
	vector<int> vecteur;	// Historique des coups.
	string premier;			// Joueur qui a d�but� la partie.
	int nbCoup;				// Nombre de coups jou�s.
	int pos;				// Position � mettre dans l'historique.
	bool* ok= new bool;		// vrai si coup possible
	int* ligne=new int;		// ligne (hauteur) du coup
	int* j=new int;			// num�ro du joueur courant
	*ok=true;

	// On recup�re dans le fichier le nombre de coups jou�s,
	// la couleur du joueur qui a d�but� la partie et
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
		// correspondant � chaque case
		pos=(int)(vecteur[i]-vecteur[i]%LARGEUR)/LARGEUR;
		maPartie.joueUnCoup(partieEnCours,&pos,ligne,ok,j);
		if(*ok)
		{
			if (*j==0)couleurCase[*ligne][pos]='R';
			if (*j==1)couleurCase[*ligne][pos]='J';
		}
	}
	// On r�affiche tout � la fin.
	glutPostRedisplay();	
	// Nettoyage
	delete ok;
	delete ligne;
	delete j;
}