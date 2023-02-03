#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

#define cSeparateur  ';'


typedef struct arbreAVL{
  double elmt;
  char OtherElts[1024];
  struct arbreAVL *fg;
  struct arbreAVL *fd;
  int equilibre;
  }AVL;

typedef struct arbre{
  char OtherElts[1024];  //bro
	double elmt;
	struct arbre* fd;
	struct arbre* fg;
}Arbre;

// Structure pour la liste chainé
typedef struct chainon{
  char OtherElts[1024];
	double elmt;
	struct chainon * suivant;
}Chainon;

typedef struct Data {
    int id; 
    double temperature_moyenne;
    double temperature_min;
    double temperature_max;
}Mode;

typedef struct Data2 {
    int alt; 
    double coordonnees;
}Data2;

typedef struct ArbreModeAVL{
  int identifiant;
  int nmb_stations;
  double valeur_moyenne;
  double valeur_min;
  double valeur_max;
  struct ArbreModeAVL *fg;
  struct ArbreModeAVL *fd;
  int equilibre;
}ArbreModeAVL;

typedef struct ArbreModeABR{
  int identifiant;
  int nmb_stations;
  double valeur_moyenne;
  double valeur_min;
  double valeur_max;
  struct ArbreModeABR *fg;
  struct ArbreModeABR *fd;
}ArbreModeABR;

typedef struct chainonMode{
  //char OtherElts[1024];
	int identifiant;
  int nmb_stations;
  double valeur_moyenne;
  double valeur_min;
  double valeur_max;
	struct chainonMode * suivant;
}ChainonMode;




typedef struct AVLaltitude{
  float coordonnees;
  int altitude;
  struct AVLaltitude* fg;
  struct AVLaltitude* fd;
  int equilibre;
}Avl_Altitude;


typedef Avl_Altitude* pAVLaltitude;
typedef Arbre* pArbre;
typedef ArbreModeABR* pArbreModeABR;
typedef AVL* pAVL;
typedef Chainon* pChainon;
typedef ChainonMode* pChainonMode;
typedef ArbreModeAVL* pArbreModeAVL; 



pAVL creer_ArbreAVL(double valeur,char* AutreElts);

pAVLaltitude creer_ArbreAVL2(int alt,float coordonnees);

pChainon creationChainon(double a, char* AutreElts);

pChainonMode creationChainonMode(int a, double valeur);

pArbre creer_Arbre(double a,char * AutresElts);

ArbreModeAVL* creer_ArbreModeAVL(int id,double valeur);

pArbreModeABR creer_ArbreModeABR(int id,double valeur);

int maximum(int a, int b, int c);

int minimum(int a, int b, int c);

ArbreModeAVL* mode_maxAVL(ArbreModeAVL* c,double valeur);

pArbreModeABR mode_maxABR(pArbreModeABR c,double valeur);

ArbreModeAVL* mode_minAVL(ArbreModeAVL* c,double valeur);

pArbreModeABR mode_minABR(pArbreModeABR c,double valeur);

ArbreModeAVL* mode_moyAVL(ArbreModeAVL* c,double valeur);

pArbreModeABR mode_moyABR(pArbreModeABR c,double valeur);

pAVL rotationGauche(pAVL a);

pAVLaltitude rotationGauche2(pAVLaltitude a);

ArbreModeAVL* rotationGaucheModeAVL(ArbreModeAVL* a);

pAVL rotationDroite(pAVL a);

pAVLaltitude rotationDroite2(pAVLaltitude a);

ArbreModeAVL* rotationDroiteModeAVL(ArbreModeAVL* a);

pAVL doubleRotationGauche(pAVL a);

pAVLaltitude doubleRotationGauche2(pAVLaltitude a);

ArbreModeAVL* doubleRotationGaucheModeAVL(ArbreModeAVL* a);

pAVL doubleRotationDroite(pAVL a);

pAVLaltitude doubleRotationDroite2(pAVLaltitude a);

ArbreModeAVL* doubleRotationDroiteModeAVL(ArbreModeAVL* a);

pAVL equilibrage(pAVL a);

pAVLaltitude equilibrage2(pAVLaltitude a);

ArbreModeAVL* equilibrageModeAVL(ArbreModeAVL* a);

pArbre insertABR(pArbre a, double elmt,char * AutresElts);

pArbre insertABRhumidite(pArbre a, double elmt, char *  AutresElts );

pArbre insererOuMettreAJourABR(pArbre a, double elmt, char * AutresElts);

ArbreModeAVL* insertModeAVL(ArbreModeAVL* a,ArbreModeAVL* nouveau,int *h);

pArbreModeABR insertModeABR(pArbreModeABR a,pArbreModeABR nouveau);

pAVL insertionAVL(pAVL a, double valeur,int *h,char * AutreElts);

void rechercheABR(pArbre a,double elmt, char*  AutresElts, int *bTrouve);

pAVL insertionAVLhumidite(pAVL b, double ident, int *h, char * sAutresElts);

pAVLaltitude insertionAVL2(pAVLaltitude c,pAVLaltitude nouveau,int* h);

pChainon insertDebut(pChainon pliste, pChainon nouveau);

pChainonMode insertDebutMode(pChainonMode pliste, pChainonMode nouveau);

pChainonMode inserTriCroissantMode(pChainonMode pliste, pChainonMode nouveau);

pChainon inserTriCroissant(pChainon pliste, double a, char *  AutresElts);

pChainon inserTriDecroissant(pChainon pliste, double a, char *  AutresElts);

pChainonMode inserTriDecroissantMode(pChainonMode pliste, pChainonMode nouveau);

pChainon inserTriDecroissanthumidite(pChainon pliste, double a,char *  AutresElts);

void parcourInfixe(pArbre a);

void parcourInfixeModeABR(pArbreModeABR a);

void parcourInfixeAVL(pAVL a);

void parcourInfixeAVL2(pAVLaltitude a);

void parcourPostAVL(pAVL a);

void parcourPost(pArbre a);

void parcourPostModeABR(pArbreModeABR a);

void traiterListe(pChainon pliste);

void traiterListeMode(pChainonMode pliste);

void parcourInfixeModeAVL(ArbreModeAVL* c);


