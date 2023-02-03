#include "fonction.h"

#define bdebug 2

//---------------------------------------------------------------------------------
// Fonction :creer_ArbreAVL 
// Description : Création d'un arbre avec affetcation de la première valeur.
// Entrée : valeur de type float (Valeur a inserer )
// Sortie : Pointeur sur la structure pArbreAVL qui vient d'etre créée
//--------------------------------------------------------------------------------
pAVL creer_ArbreAVL(double valeur,char* autreElts){
  pAVL nouveau = malloc(sizeof(AVL));
  if(nouveau==NULL) exit(2);
	nouveau->fg = NULL;
	nouveau->fd = NULL;
	nouveau->elmt = valeur;
  nouveau->equilibre=0;
  memcpy(nouveau->OtherElts,  autreElts,sizeof(nouveau->OtherElts));
	return nouveau;
  } 




pAVLaltitude creer_ArbreAVL2(int alt, float coordonnees){
  pAVLaltitude a = malloc(sizeof(Avl_Altitude));
  if(a==NULL) exit(2);
	a->fg = NULL;
	a->fd = NULL;
	a->altitude=alt;
  a->coordonnees=coordonnees;
  a->equilibre=0;
	return a;
  }




ArbreModeAVL* creer_ArbreModeAVL( int id,double valeur){
  ArbreModeAVL* c=malloc(sizeof(ArbreModeAVL));
  if(c==NULL) exit(3);
  c->fg = NULL;
	c->fd = NULL;
  c->valeur_min=valeur;
  c->valeur_max=valeur;
  c->valeur_moyenne=valeur;
  c->nmb_stations=1;
  c->identifiant=id;
  return c;
}





// creer un chainon 
pChainon creationChainon(double a, char* autreElts){
	pChainon nouveau =malloc(sizeof(Chainon));
  if(nouveau==NULL) exit(1);
	nouveau -> elmt = a;
	nouveau -> suivant = NULL; 
  memcpy(nouveau->OtherElts,  autreElts,sizeof(nouveau->OtherElts));
  return nouveau;
}

pChainonMode creationChainonMode(int id, double a){
	pChainonMode nouveau =malloc(sizeof(ChainonMode));
  if(nouveau==NULL) exit(1);
	nouveau->identifiant=id;
  int nmb_stations;
  nouveau->valeur_moyenne=a;
  nouveau->valeur_min=a;
  nouveau->valeur_max=a;
	nouveau->suivant=NULL;
  return nouveau;
}


// fonction qui permet de créer un arbre pour un ABR

pArbre creer_Arbre(double a, char * autreElts){ 
	pArbre nouveau = malloc(sizeof(Arbre));
  if(nouveau==NULL) exit(3);
	nouveau->fg = NULL;
	nouveau->fd = NULL;
	nouveau->elmt = a;
  memcpy(nouveau->OtherElts,  autreElts,sizeof(nouveau->OtherElts)); 
	return nouveau;
}



pArbreModeABR creer_ArbreModeABR(int id, double a){ 
	pArbreModeABR nouveau = malloc(sizeof(ArbreModeABR));
  if(nouveau==NULL) exit(3);
	nouveau->fg = NULL;
	nouveau->fd = NULL;
	nouveau->valeur_max=a;
  nouveau->valeur_min=a;
  nouveau->valeur_moyenne=a;
  nouveau->nmb_stations=1;
  nouveau->identifiant=id;
	return nouveau;
}


int maximun(int a,int b,int c){
  if (a>=b){
    if(a>=c) return a;
    else return c;
  }
  else{
    if (b>=c) return b;
    else return c;
  }
}




int minimun(int a,int b,int c){
  if (a<=b){
    if(a<=c) return a;
    else return c;
  }
  else{
    if (b<=c) return b;
    else return c;
  }
}

// fonction qui permet de trouver la temperature maximale d'une station

ArbreModeAVL* mode_maxAVL(ArbreModeAVL* c,double valeur){
  if(c->valeur_max>valeur) return c;
    else {
      c->valeur_max=valeur;
      return c;
    }
}



ArbreModeABR* mode_maxABR(ArbreModeABR* c,double valeur){
  if(c->valeur_max>valeur) return c;
  else{
    c->valeur_max=valeur;
    return c;
  }
}

pChainonMode mode_max_ChainonMode(pChainonMode c,double valeur){
  if(c->valeur_max>valeur) return c;
  else{
    c->valeur_max=valeur;
    return c;
  }
}



// fonction qui permet de trouver la temperature minimale d'une station

pArbreModeAVL mode_minAVL(ArbreModeAVL* c,double valeur){
  if(c->valeur_min<valeur) return c;
    else{
      c->valeur_min=valeur;
      return c;
   }
}

pArbreModeABR mode_minABR(ArbreModeABR* c,double valeur){
  if(c->valeur_min<valeur) return c;
  else{
    c->valeur_min=valeur;
    return c;
   }
}


// fonction qui permet de calculer la moyenne des températures d'une station 

ArbreModeAVL* mode_moyAVL(ArbreModeAVL* c,double valeur){
  c->valeur_moyenne=((c->valeur_moyenne*c->nmb_stations)+valeur)/(c->nmb_stations+1);
  c->nmb_stations++;
  return c;
}


pChainonMode mode_min_ChainonMode(pChainonMode c,double valeur){
  if(c->valeur_min<valeur) return c;
  else{
    c->valeur_min=valeur;
    return c;
   }
}


// fonction qui permet de calculer la moyenne des températures d'une station 

pChainonMode mode_moy_ChainonMode(pChainonMode c,double valeur){
  c->valeur_moyenne=((c->valeur_moyenne*c->nmb_stations)+valeur)/(c->nmb_stations+1);
  c->nmb_stations++;
  return c;
}

pArbreModeABR mode_moyABR(ArbreModeABR* c,double valeur){
  c->valeur_moyenne=((c->valeur_moyenne*c->nmb_stations)+valeur)/(c->   nmb_stations+1);
  c->nmb_stations++;
  return c;
}


//********   rotationGauche pour AVL *******************//
pAVL rotationGauche(pAVL a){
  pAVL pivot;
  int eq_a, eq_p;
  
    pivot=a->fd;
    a->fd=pivot->fg;
    pivot->fg=a;
    eq_a=a->equilibre;
    eq_p=pivot->equilibre;
    a->equilibre=eq_a-maximun(eq_p,0,0)-1;
    pivot->equilibre=minimun( eq_a-2, eq_a+eq_p-2,eq_p-1);
    a=pivot;
  
  return a;
  }

//********   rotationGauche2 pour AVL *******************//
pAVLaltitude rotationGauche2(pAVLaltitude a){
  pAVLaltitude pivot;
  int eq_a, eq_p;
  
    pivot=a->fd;
    a->fd=pivot->fg;
    pivot->fg=a;
    eq_a=a->equilibre;
    eq_p=pivot->equilibre;
    a->equilibre=eq_a-maximun(eq_p,0,0)-1;
    pivot->equilibre=minimun( eq_a-2, eq_a+eq_p-2,eq_p-1);
    a=pivot;
  
  return a;
  }

//********   rotationDroite pour AVL *******************//
pAVL rotationDroite(pAVL a){
  pAVL pivot;
  int eq_a, eq_p;
  
    pivot=a->fg;
    a->fg=pivot->fd;
    pivot->fd=a;
    eq_a=a->equilibre;
    eq_p=pivot->equilibre;
    a->equilibre=eq_a-minimun(eq_p,0,0)+1;
    pivot->equilibre=maximun( eq_a+2, eq_a+eq_p+2,eq_p+1);
    a=pivot;
  
  return a;
  }



//********   rotationDroite2 pour AVL *******************//
pAVLaltitude rotationDroite2(pAVLaltitude a){
  pAVLaltitude pivot;
  int eq_a, eq_p;
  
    pivot=a->fg;
    a->fg=pivot->fd;
    pivot->fd=a;
    eq_a=a->equilibre;
    eq_p=pivot->equilibre;
    a->equilibre=eq_a-minimun(eq_p,0,0)+1;
    pivot->equilibre=maximun( eq_a+2, eq_a+eq_p+2,eq_p+1);
    a=pivot;
  
  return a;
  }

//********   doubleRotationGauche pour AVL *******************//
pAVL doubleRotationGauche(pAVL a)
{
  a->fd=rotationDroite(a->fd);
  return rotationGauche(a);
}


//********   doubleRotationDroite pour AVL *******************//
pAVL doubleRotationDroite(pAVL a)
{
  a->fg=rotationGauche(a->fg);
  return rotationDroite(a);
}

//********   doubleRotationGauche2 pour AVL *******************//
pAVLaltitude doubleRotationGauche2(pAVLaltitude a)
{
  a->fd=rotationDroite2(a->fd);
  return rotationGauche2(a);
}


//********   doubleRotationDroite2 pour AVL *******************//
pAVLaltitude doubleRotationDroite2(pAVLaltitude a)
{
  a->fg=rotationGauche2(a->fg);
  return rotationDroite2(a);
}


//********   rotationGaucheMode pour AVL *******************//
ArbreModeAVL* rotationGaucheModeAVL(ArbreModeAVL* a){
  ArbreModeAVL* pivot;
  int eq_a, eq_p;
  
    pivot=a->fd;
    a->fd=pivot->fg;
    pivot->fg=a;
    eq_a=a->equilibre;
    eq_p=pivot->equilibre;
    a->equilibre=eq_a-maximun(eq_p,0,0)-1;
    pivot->equilibre=minimun( eq_a-2, eq_a+eq_p-2,eq_p-1);
    a=pivot;
  
  return a;
  }


//********   rotationDroiteMode pour AVL *******************//
ArbreModeAVL* rotationDroiteModeAVL(ArbreModeAVL* a){
  ArbreModeAVL* pivot;
  int eq_a, eq_p;
  
    pivot=a->fg;
    a->fg=pivot->fd;
    pivot->fd=a;
    eq_a=a->equilibre;
    eq_p=pivot->equilibre;
    a->equilibre=eq_a-minimun(eq_p,0,0)+1;
    pivot->equilibre=maximun( eq_a+2, eq_a+eq_p+2,eq_p+1);
    a=pivot;
  
  return a;
  }


//********   doubleRotationGaucheMode pour AVL *******************//

ArbreModeAVL* doubleRotationGaucheModeAVL(ArbreModeAVL* a){
  a->fd=rotationDroiteModeAVL(a->fd);
  return rotationGaucheModeAVL(a);
  }


//********   doubleRotationDroiteMode pour AVL *******************//

ArbreModeAVL* doubleRotationDroiteModeAVL(ArbreModeAVL* a){
  a->fg=rotationGaucheModeAVL(a->fg);
  return rotationDroiteModeAVL(a);
  }



//********   equilibrage pour AVL *******************//
pAVL equilibrage(pAVL a){
  if(a->equilibre >= 2){
    if(a->fd->equilibre >=0) return rotationGauche(a);
    else return doubleRotationGauche(a);
  }
  else if (a->equilibre <= -2){
    if(a->fg->equilibre<=0) return rotationDroite(a);
    else return doubleRotationDroite(a);
  }
  return a;
}


//********   equilibrage2 pour AVL *******************//
pAVLaltitude equilibrage2(pAVLaltitude a){
  if(a->equilibre >= 2){
    if(a->fd->equilibre >=0) return rotationGauche2(a);
    else return doubleRotationGauche2(a);
  }
  else if (a->equilibre <= -2){
    if(a->fg->equilibre<=0) return rotationDroite2(a);
    else return doubleRotationDroite2(a);
  }
  return a;
}

//********   equilibrageMode pour AVL *******************//
ArbreModeAVL* equilibrageModeAVL(ArbreModeAVL* a){
  if(a->equilibre >= 2){
    if(a->fd->equilibre >=0) return rotationGaucheModeAVL(a);
    else return doubleRotationGaucheModeAVL(a);
  }
  else if (a->equilibre <= -2){
    if(a->fg->equilibre<=0) return rotationDroiteModeAVL(a);
    else return doubleRotationDroiteModeAVL(a);
  }
  return a;
}




//********   insertionAVL pour AVL *******************//
pAVL insertionAVLhumidite(pAVL a, double valeur,int *h,char* AutreElts)
{
  int result ;
  if(a==NULL)
  {
  *h=1;
    return creer_ArbreAVL(valeur,AutreElts);
  }
  
  if(a->elmt >= valeur)
  {   
    a->fg=insertionAVLhumidite(a->fg,valeur,h,AutreElts);
    *h=-*h;
  }
  else if(a->elmt < valeur)
  {
    a->fd=insertionAVLhumidite(a->fd,valeur,h,AutreElts);
  }
  else
  {
   *h=0;
    return a;
  }
  if(*h !=0)
  {
    a->equilibre=a->equilibre+*h;
    a=equilibrage(a);
    if(a->equilibre==0)*h=0;
    else *h=1;
  }
return a;
}


pAVL insertionAVL(pAVL a, double valeur,int *h,char* AutreElts)
{
  int result ;
  if(a==NULL)
  {
  *h=1;
    return creer_ArbreAVL(valeur,AutreElts);
  }
  
  if(a->elmt >= valeur)
  {   
    a->fg=insertionAVL(a->fg,valeur,h,AutreElts);
    *h=-*h;
  }
  else if(a->elmt < valeur)
  {
    a->fd=insertionAVL(a->fd,valeur,h,AutreElts);
  }
  else
  {
   *h=0;
    return a;
  }
  if(*h !=0)
  {
    a->equilibre=a->equilibre+*h;
    a=equilibrage(a);
    if(a->equilibre==0)*h=0;
    else *h=1;
  }
return a;
}



//********   insertionAVL2 pour AVL *******************//
pAVLaltitude insertionAVL2(pAVLaltitude a,pAVLaltitude nouveau ,int *h)
{
  if(a==NULL){
  *h=1;
    return nouveau;
  }
  else if(a->altitude >= nouveau->altitude){
    a->fg=insertionAVL2(a->fg,nouveau,h);
  *h=-*h;
  }
  else if(a->altitude <= nouveau->altitude){
    a->fd=insertionAVL2(a->fd,nouveau,h);
  }
  else{
   *h=0;
    return a;
 }
  if(*h !=0){
    
    a->equilibre=a->equilibre+*h;
    a=equilibrage2(a);
    if(a->equilibre==0)*h=0;
    else *h=1;
  }
return a;
}


//********   insertMode pour AVL *******************//
ArbreModeAVL* insertModeAVL(ArbreModeAVL* a,ArbreModeAVL* nouveau,int *h){
  if(a==NULL){
      *h=1;
    return nouveau;
  }
  if(a->identifiant==nouveau->identifiant){
      a=mode_maxAVL(a,nouveau->valeur_max);
      a=mode_minAVL(a,nouveau->valeur_min);
      a=mode_moyAVL(a,nouveau->valeur_moyenne);
      return a;
   }
  else if(a->identifiant >nouveau->identifiant){
    a->fg=insertModeAVL(a->fg,nouveau,h);
      *h=-*h;
  }
  else if(a->identifiant < nouveau->identifiant){
    a->fd=insertModeAVL(a->fd,nouveau,h);
  }
    else{
      *h=0;
      return a;
    }
   if(*h !=0){
    
      a->equilibre=a->equilibre+*h;
      a=equilibrageModeAVL(a);
    if(a->equilibre==0)*h=0;
      else *h=1;
    }
return a;
}



pArbreModeABR insertModeABR(pArbreModeABR a,pArbreModeABR nouveau){
  if(a==NULL){
    return nouveau;
  }
  else if(a->identifiant==nouveau->identifiant){
      a=mode_maxABR(a,nouveau->valeur_max);
      a=mode_minABR(a,nouveau->valeur_min);
      a=mode_moyABR(a,nouveau->valeur_moyenne);
      return a;
  }
  else if(a->identifiant >nouveau->identifiant){
    a->fg=insertModeABR(a->fg,nouveau);
  }
  else if(a->identifiant < nouveau->identifiant){
    a->fd=insertModeABR(a->fd,nouveau);
  }
  return a;
}





// fonction qui permet de d'écrire dans un fichier le contenu d'un AVL de manière croissante
//********   parcourInfixeAVL pour AVL *******************//
void parcourInfixeAVL(pAVL a)
{
  FILE *fp;
  char str[80];
    
    if(a!=NULL){
      fp = fopen("fichierTrie.txt", "a");
      parcourInfixeAVL(a->fg);
      sprintf(str, "%lf %c %s\n", a->elmt,cSeparateur,a->OtherElts);
      fputs(str, fp);
      fclose(fp);
      parcourInfixeAVL(a->fd);
     
    }
  }
//********   parcourInfixeAVL2 pour AVL *******************//
  void parcourInfixeAVL2(pAVLaltitude a){
  FILE *fp;
  char str[80];
    
    if(a!=NULL){
      fp = fopen("fichierTrié.txt", "a");
      parcourInfixeAVL2(a->fg);
      sprintf(str, "%d;%f \n", a->altitude,a->coordonnees);
      fputs(str, fp);
      fclose(fp);
      parcourInfixeAVL2(a->fd);
     
    }
}

// fonction qui permet d'écrire dans un fichier le contenu d'un AVL de manière décroissante

void parcourPostAVL(pAVL a){
  FILE *fp;
  char str[80];
    
    if(a!=NULL){
      fp = fopen("fichierTrie.txt", "a");
      parcourPostAVL(a->fd);
      sprintf(str, "%lf %c %s\n", a->elmt,cSeparateur,a->OtherElts);
      
      fputs(str, fp);
      fclose(fp);
      parcourPostAVL(a->fg);
    }
}
//********   parcourInfixeMode pour AVL *******************//
void parcourInfixeModeAVL(ArbreModeAVL* c)
{
  
  FILE *fp;
  char str[80];
    
    if(c!=NULL){
      fp = fopen("fichierTrie.txt", "a");
      parcourInfixeModeAVL(c->fg);
      sprintf(str, "%d;   %f   ;%f   ;%f \n", c->identifiant,c->valeur_moyenne,c->valeur_min,c->valeur_max);
      fputs(str, fp);
      fclose(fp);
      parcourInfixeModeAVL(c->fd);
     
    }
}


//****************************************************//
//                  ABR fonctions                     //
//****************************************************//

//********   insertABR pour ABR *******************//
pArbre insertABR(pArbre a, double elmt, char *  AutresElts ){ 
	
	if(a == NULL){
    return creer_Arbre(elmt,AutresElts);
	}
	else if(elmt <= a -> elmt){
		a->fg= insertABR(a->fg , elmt,AutresElts); 
   // memcpy(a->otherElts,OthersElts,sizeof(a->otherElts));
   
	}	
	else if(elmt >= a -> elmt){
		a->fd = insertABR(a->fd, elmt,AutresElts);

	}
  return a;
  }




void rechercheABR(pArbre a,double elmt, char* Autre_Elts, int *trouve)
{
    if(a!=NULL)
    {

      if(strcmp(a->OtherElts,  Autre_Elts)==0)
      {
        if(a->elmt<elmt)
        { // On inverse l'élémént
          a->elmt=elmt;
        }
        //élémént trouvé a retourner
        //return 1;
        *trouve =1;                   
      } 
      else
      { // Parcours de l'arbre gauche
        rechercheABR(a->fg,elmt,Autre_Elts,trouve);
        // Parcours de l'arbre droit
        rechercheABR(a->fd,elmt,Autre_Elts,trouve);
      }
   }
 //printf("trouve2 %d\n",trouve);*/
  
}


pArbre insertABRhumidite(pArbre a, double elmt, char *  AutresElts )
{ 
  int TrouveELt = 0;
	if(a == NULL)
  {
    return creer_Arbre(elmt,AutresElts);
  }
  rechercheABR(a,elmt,AutresElts,&TrouveELt); 
  //printf("TrouveELt %d\n",TrouveELt);
   //test si Elmt trouvé ?
  if(TrouveELt==1)
  {
   // printf("arbre_temp différent de null !");
  }
  else 
  {
    if(elmt <= a->elmt)
    {
  		  a->fg= insertABRhumidite(a->fg ,elmt,AutresElts); 
    }	
  	else if(elmt > a->elmt)
    {
  	   a->fd = insertABRhumidite(a->fd,elmt,AutresElts);
    }
    //return a;
  }
  //else return a;
  return a;
}



//********   parcourInfixe pour ABR *******************//
void parcourInfixe(pArbre a)
{
  FILE *fp;
  char str[80];
    if(a!=NULL){
      fp = fopen("fichierTrie.txt","a");
      parcourInfixe(a->fg);
      sprintf(str, "%lf %c %s\n", a->elmt,cSeparateur,a->OtherElts);
      fputs(str, fp);
      fclose(fp);
      parcourInfixe(a->fd);
     
    }
}



void parcourInfixeModeABR(pArbreModeABR c)
{
  
  FILE *fp;
  char str[80];
    
    if(c!=NULL){
      fp = fopen("fichierTrie.txt", "a");
      parcourInfixeModeABR(c->fg);
      sprintf(str, "%d;   %f   ;%f   ;%f \n", c->identifiant,c->valeur_moyenne,c->valeur_min,c->valeur_max);
      fputs(str, fp);
      fclose(fp);
      parcourInfixeModeABR(c->fd);
     
    }
}


// fonction qui permet de d'écrire dans un fichier le contenu d'un arbre binaire de manière décroissante
//********   parcourPost pour ABR *******************//
void parcourPost(pArbre a){
  FILE *fp;
  char str[80];
  
  
    
    if(a!=NULL){
      fp = fopen("fichierTrie.txt","a");
      parcourPost(a->fd);
      sprintf(str, "%lf %c %s\n", a->elmt,cSeparateur,a->OtherElts);
      fputs(str, fp);
      fclose(fp);
      parcourPost(a->fg);
     
    }
}



//****************************************************//
//               LstChainée fonctions                 //
//****************************************************//

//********   insertDebut pour LstChainée *******************//
pChainon insertDebut(pChainon pliste, pChainon nouveau){
  nouveau->suivant=pliste;
  return nouveau;
  }

pChainonMode insertDebutMode(pChainonMode pliste, pChainonMode nouveau){
  nouveau->suivant=pliste;
  return nouveau;
  }


//********   inserTriCroissant pour LstChainée *******************//

pChainon inserTriCroissant(pChainon pliste, double a, char *AutresElts) {
  pChainon nouveau = creationChainon(a, AutresElts);
  pChainon P1 = pliste;
  if (pliste == NULL || P1->elmt > a) {
    pliste = insertDebut(P1, nouveau);
    return pliste;
  }
  while (P1->suivant != NULL && P1->suivant->elmt < a) {
    P1 = P1->suivant;
  }
  nouveau->suivant = P1->suivant;
  P1->suivant = nouveau;
  return pliste;
}




pChainonMode inserTriCroissantMode(pChainonMode pliste, pChainonMode nouveau) {
    pChainonMode P1 = pliste;
    pChainonMode previous = NULL;
    
    while (P1 != NULL && P1->identifiant < nouveau->identifiant) {
        previous = P1;
        P1 = P1->suivant;
    }
    
    if (P1 != NULL && P1->identifiant == nouveau->identifiant) {
        P1=mode_max_ChainonMode(P1,nouveau->valeur_max);
        P1=mode_moy_ChainonMode(P1,nouveau->valeur_moyenne);
        P1=mode_min_ChainonMode(P1,nouveau->valeur_min);
        free(nouveau);
        return pliste;
    }
    
    if (previous == NULL) {
        nouveau->suivant = pliste;
        pliste = nouveau;
    } else {
        previous->suivant = nouveau;
        nouveau->suivant = P1;
    }
    
    return pliste;
}


//********   inserTriCroissant pour LstChainée *******************//
// fonction qui permet de crér une liste chainé de manière décroissante
pChainon inserTriDecroissant(pChainon pliste, double a,char *  AutresElts)
{
  pChainon nouveau=creationChainon(a,AutresElts);
  pChainon P1=pliste;
  if(pliste==NULL || P1->elmt<a){
    pliste=insertDebut(P1,nouveau);
    return pliste;
  }
  while(nouveau->elmt < P1->suivant->elmt && P1->suivant != NULL){
    P1=P1->suivant;
  }
  
  nouveau->suivant=P1->suivant;
  P1->suivant=nouveau;
  return pliste;
}





pChainonMode inserTriDecroissantMode(pChainonMode pliste, pChainonMode nouveau)
{
  pChainonMode P1=pliste;
  if(pliste==NULL || P1->identifiant<nouveau->identifiant){
    pliste=insertDebutMode(P1,nouveau);
    return pliste;
  }
  while(nouveau->identifiant < P1->suivant->identifiant && P1->suivant != NULL){
    P1=P1->suivant;
  }
  
  nouveau->suivant=P1->suivant;
  P1->suivant=nouveau;
  return pliste;
}



// fonction qui permet de d'écrire dans un fichier le contenu de la liste chainée
//********   traiterListe pour Liste chainée *******************//
void traiterListe(pChainon pliste)
{
  FILE *fp;
  char str[80];
  while(pliste!=NULL){
     fp = fopen("fichierTrie.txt", "a");
      sprintf(str, "%lf %c %s\n", pliste->elmt,cSeparateur,pliste->OtherElts);
      fputs(str, fp);
      fclose(fp);
    pliste=pliste->suivant;

  }
}

void traiterListeMode(pChainonMode pliste)
{
  FILE *fp;
  char str[80];
  while(pliste!=NULL){
     fp = fopen("fichierTrie.txt", "a");
      sprintf(str, "%d ; %lf ; %lf ; %lf\n",pliste->identifiant,pliste->valeur_moyenne,pliste->valeur_min,pliste->valeur_max);
      fputs(str, fp);
      fclose(fp);
    pliste=pliste->suivant;

  }
}
