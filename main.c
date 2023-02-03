#include "fonction.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define csAVLMode '1'
#define csABRMode '2'
#define csLstChaineMode '3'
#define csMode1 '1'
#define Altitude '5'
#define Humidite '4'
#define Pression '6'
#define Tmode1 '7'
#define Pmode1 '8'
#define csHumidite '4'
#define cSeparateur ';'
#define csSeparateurPv ";"
#define csSeparateurV ","
#define bdebug 0

int main(int argc, char **argv) {
  int i = 0;
  int h, id;
  double val_temp;
  double val_TempPress;
  pChainon pliste = NULL;
  pArbre a = NULL;
  pAVL b = NULL;
  Mode mode1;
  Data2 data;
  pAVLaltitude nouveau2 = NULL, f = NULL;
  ArbreModeAVL *c = NULL;
  ArbreModeAVL *nouveau = NULL;
  pArbreModeABR nouveau3 = NULL, d = NULL;
  pChainonMode chainonMode1 = NULL, chainonMode2 = NULL;
  char reponse = argv[1][0];
  char mode = argv[2][0];
  char *fileName = argv[3];
  char reponse3;
  FILE *fp;
  char Trame[100] = {0};
  int lgMax = 100;
  int n = 0;
  char sAutresElts[100] = {0};
  int ident;
  char *ptChaine;
  char *ptChaine2;
  char sCoordon[50] = {0};
  double Coord1, Coord2, temp;
  int TrouveELt = 0;

  if (mode == Altitude)
    memcpy(fileName, "altitude.csv", sizeof("altitude.csv"));
  else if (mode == Humidite)
    memcpy(fileName, "humidite.csv", sizeof("humidite.csv"));
  else if (mode == Tmode1)
    memcpy(fileName, "Tmode1.csv", sizeof("Tmode1.csv"));
  else if (mode == Pmode1)
    memcpy(fileName, "Pmode1.csv", sizeof("Pmode1.csv"));

  if (reponse == csAVLMode) {
    switch (mode) {
    //**** Cas Altitude ************
    //------------------------------
    case Altitude:
      printf("Altitude \n\n");

      fp = fopen(fileName, "r");

      if (fp == NULL) {
        perror("Error in opening file\nle fichié a été suprimé");
        exit(0);
        return (-1);
      }
      do {
        fgets(Trame, lgMax, fp);
        if (bdebug >= 1)
          printf("Trame[0] = %s\n", Trame);
        if (Trame[0] != '\n') {
          // On récupére la premier partie avant le séparateur
          ptChaine = strtok(Trame, csSeparateurPv);
          if (ptChaine != NULL) {
            // On récupére lepremier element IDENt
            sscanf(ptChaine, "%lf", &Coord1);
            if (bdebug >= 1)
              printf("coord1 %lf\n", Coord1);
          }

          // On se positionne sur le deuxiéme element aprés le séparateur
          ptChaine = strtok(NULL, csSeparateurPv);

          // On récupére le deuxiéme élement
          if (ptChaine != NULL) {
            sscanf(ptChaine, "%lf \n", &Coord2);
            if (bdebug >= 1)
              printf("Coordonnée2 %lf\n", Coord2);
          }

          // On se positionne sur le troisiéme element aprés le séparateur
          ptChaine = strtok(NULL, csSeparateurPv);
          // On récupére le troisième élement
          if (ptChaine != NULL) {
            sscanf(ptChaine, "%d \n", &ident);
            if (bdebug >= 1)
              printf("Coordonnée2 %d\n", ident);
          }

          // Reconsitution de la chaine a transmettre à partir des
          // coordonnées de base
          sprintf(sAutresElts, "%lf %c %lf", Coord1, cSeparateur, Coord2);
          if (bdebug >= 1)
            printf("ident= %d\n", ident);
          b = insertionAVL(b, ident, &h, sAutresElts);
        }
        if (feof(fp)) {
          break;
        }

      } while (1);

      fclose(fp);

      parcourInfixeAVL(b);
      printf("\n\n ----l'AVL a bien marché !!---- \n\n ");

      break;
    //***** Cas Tmode1
    //----------------
    case Tmode1:
      if (bdebug >= 2)
        printf("Tmode1 \n\n");
    //***** Cas Pmode1
    //----------------
    case Pmode1:
      if (bdebug >= 2)
        printf("Pmode1 \n\n");

      fp = fopen(fileName, "r");
      if (fp == NULL) {
        perror("Error in opening file\nle fichié a été suprimé");
        return (-1);
      }
      do {
        fgets(Trame, lgMax, fp);
        if (bdebug > 1)
          printf("Trame[0] = %s\n", Trame);
        if (Trame[0] != '\n') {

          ptChaine = strtok(Trame, ";");
          if (ptChaine != NULL) {
            sscanf(ptChaine, "%d", &ident);
            if (bdebug >= 1)
              printf("ident %d\n", ident);

            ptChaine = strtok(NULL, ";");
            if (ptChaine != NULL) {
              sscanf(ptChaine, "%lf", &val_TempPress);
              if (bdebug >= 1)
                printf("val_TempPress %lf\n", val_TempPress);

              nouveau = creer_ArbreModeAVL(ident, val_TempPress);
              c = insertModeAVL(c, nouveau, &h);
            }
          }
          if (feof(fp)) {
            break;
          }
        }
      } while (1);
      fclose(fp);
      parcourInfixeModeAVL(c);
      printf("\n\n ----l'AVL a bien marché !!---- \n\n ");

      break;
      //***** Cas Humidite
      //----------------
    case Humidite:
      if (bdebug >= 2)
        printf("humidite \n\n");

      fp = fopen(fileName, "r");
      if (fp == NULL) {
        perror("Error in opening file\nle fichié a été suprimé");
        return (-1);
      }
      do {
        fgets(Trame, lgMax, fp);
        if (Trame[0] != '\n') {
          ptChaine = strtok(Trame, ";");
          if (ptChaine != NULL) {

            ptChaine = strtok(NULL, ";");
            if (ptChaine != NULL) {
              sscanf(ptChaine, "%d", &ident);
              sprintf(sCoordon, ptChaine, sizeof(sCoordon));
              ptChaine2 = strtok(sCoordon, ";");
              ptChaine2 = strtok(ptChaine2, ",");
              sscanf(ptChaine2, "%lf ", &Coord1);
              printf("Coordonnée1 %lf \n", Coord1);
              ptChaine2 = strtok(NULL, ",");
              sscanf(ptChaine2, "%lf \n", &Coord2);
              printf("Coordonnée2 %lf", Coord2);
              b = insertionAVLhumidite(b, ident, &h, sAutresElts);
            }
          }
          if (feof(fp)) {
            break;
          }
        }
      } while (1);

      fclose(fp);
      parcourPostAVL(b);
      printf("\n\n ----l'ABR a bien marché !!---- \n\n ");
      break;
    default:
      break;
    }

  }

  //----------------------
  // Traitement mode ABR
  //--------------------
  else if (reponse == csABRMode) {

    // CAS Altitude
    //-------------

    switch (mode) {
    case Altitude:
      printf("Altitude \n\n");

      fp = fopen(fileName, "r");

      if (fp == NULL) {
        perror("Error in opening file\nle fichié a été suprimé");
        return (-1);
      }
      do {

        fgets(Trame, lgMax, fp);
        if (bdebug >= 1)
          printf("Trame[0] = %s\n", Trame);
        if (Trame[0] != '\n') {
          // On récupére la premier partie avant le séparateur
          ptChaine = strtok(Trame, csSeparateurPv);
          if (ptChaine != NULL) {
            // On récupére lepremier element IDENt
            sscanf(ptChaine, "%lf", &Coord1);
            if (bdebug >= 1)
              printf("coord1 %lf\n", Coord1);
          }

          // On se positionne sur le deuxiéme element aprés le séparateur
          ptChaine = strtok(NULL, csSeparateurPv);

          // On récupére le deuxiéme élement
          if (ptChaine != NULL) {
            sscanf(ptChaine, "%lf \n", &Coord2);
            if (bdebug >= 1)
              printf("Coordonnée2 %lf\n", Coord2);
          }

          // On se positionne sur le troisiéme element aprés le séparateur
          ptChaine = strtok(NULL, csSeparateurPv);
          // On récupére le troisième élement
          if (ptChaine != NULL) {
            sscanf(ptChaine, "%d \n", &ident);
            if (bdebug >= 1)
              printf("Coordonnée2 %d\n", ident);
          }

          // Reconsitution de la chaine a transmettre à partir des
          // coordonnées de base
          sprintf(sAutresElts, "%lf %c %lf", Coord1, cSeparateur, Coord2);
          if (bdebug >= 1)
            printf("ident= %d\n\n", ident);
          a = insertABR(a, ident, sAutresElts);
        }
        if (feof(fp)) {
          break;
        }

      } while (1);

      fclose(fp);

      parcourInfixe(a);
      printf("\n\n ----l'ABR a bien marché !!---- \n\n ");

      break;
    //-----------------
    // Humidité
    //---------------------
    case Humidite:
      printf("Humidite \n\n");

      fp = fopen(fileName, "r");

      if (fp == NULL) {
        perror("Error in opening file\nle fichié a été suprimé");
        return (-1);
      }
      do {

        fgets(Trame, lgMax, fp);
        if (bdebug >= 1)
          printf("Trame[0] = %s\n", Trame);
        if (Trame[0] != '\n') {
          // On récupére la premier partie avant le séparateur
          ptChaine = strtok(Trame, csSeparateurPv);
          if (ptChaine != NULL) {
            // On récupére lepremier element IDENt
            sscanf(ptChaine, "%lf", &Coord1);
            if (bdebug >= 1)
              printf("coord1 %lf\n", Coord1);
          }

          // On se positionne sur le deuxiéme element aprés le séparateur
          ptChaine = strtok(NULL, csSeparateurPv);

          // On récupére le deuxiéme élement
          if (ptChaine != NULL) {
            sscanf(ptChaine, "%lf \n", &Coord2);
            if (bdebug >= 1)
              printf("Coordonnée2 %lf\n", Coord2);
          }

          // On se positionne sur le troisiéme element aprés le séparateur
          ptChaine = strtok(NULL, csSeparateurPv);
          // On récupére le troisième élement
          if (ptChaine != NULL) {
            sscanf(ptChaine, "%d \n", &ident);
            if (bdebug >= 1)
              printf("Coordonnée2 %d\n", ident);
          }

          // Reconsitution de la chaine a transmettre à partir des
          // coordonnées de base
          sprintf(sAutresElts, "%lf %c %lf", Coord1, cSeparateur, Coord2);
        
          if (bdebug >= 1)
            printf("ident= %d\n", ident);
           a = insertABRhumidite(a, ident, sAutresElts);
          
        }
        if (feof(fp)) {
          break;
        }

      } while (1);

      fclose(fp);

      parcourPost(a);
      printf("\n\n ----l'ABR a bien marché !!---- \n\n ");

      break;

      //------------------
      //***** Cas Tmode1
    //----------------
    case Tmode1:
      if (bdebug >= 2)
        printf("Tmode1 \n\n");
    //***** Cas Pmode1
    //----------------
    case Pmode1:
      if (bdebug >= 2)
        printf("Pmode1 \n\n");

      fp = fopen(fileName, "r");
      if (fp == NULL) {
        perror("Error in opening file\nle fichié a été suprimé");
        return (-1);
      }
      do {
        fgets(Trame, lgMax, fp);
        if (bdebug > 1)
          printf("Trame[0] = %s\n", Trame);
        if (Trame[0] != '\n') {

          ptChaine = strtok(Trame, ";");
          if (ptChaine != NULL) {
            sscanf(ptChaine, "%d", &ident);
            if (bdebug >= 1)
              printf("ident %d\n", ident);

            ptChaine = strtok(NULL, ";");
            if (ptChaine != NULL) {
              sscanf(ptChaine, "%lf", &val_TempPress);
              if (bdebug >= 1)
                printf("val_TempPress %lf\n", val_TempPress);

              nouveau3 = creer_ArbreModeABR(ident, val_TempPress);
              d = insertModeABR(d, nouveau3);
            }
          }
          if (feof(fp)) {
            break;
          }
        }
      } while (1);
      fclose(fp);
      parcourInfixeModeABR(d);
      printf("\n\n ----l'ABR a bien marché !!---- \n\n ");

      break;

      break;

    default:
      printf("Other \n");
      break;
    }
  }

  //--------tri avec liste chainée---------//

  if (reponse == csLstChaineMode) {
    switch (mode) {
    case Altitude:
      printf("Altitude \n\n");

      fp = fopen(fileName, "r");

      if (fp == NULL) {
        perror("Error in opening file\nle fichié a été suprimé");
        return (-1);
      }
      do {

        fgets(Trame, lgMax, fp);
        if (bdebug >= 1)
          printf("Trame[0] = %s", Trame);
        if (Trame[0] != '\n') {
          // On récupére la premier partie avant le séparateur
          ptChaine = strtok(Trame, csSeparateurPv);
          if (ptChaine != NULL) {
            // On récupére lepremier element IDENt
            sscanf(ptChaine, "%lf", &Coord1);
            if (bdebug >= 1)
              printf("coord1 %lf\n", Coord1);
          }

          // On se positionne sur le deuxiéme element aprés le séparateur
          ptChaine = strtok(NULL, csSeparateurPv);

          // On récupére le deuxiéme élement
          if (ptChaine != NULL) {
            sscanf(ptChaine, "%lf \n", &Coord2);
            if (bdebug >= 1)
              printf("Coordonnée2 %lf\n", Coord2);
          }

          // On se positionne sur le troisiéme element aprés le séparateur
          ptChaine = strtok(NULL, csSeparateurPv);
          // On récupére le troisième élement
          if (ptChaine != NULL) {
            sscanf(ptChaine, "%d \n", &ident);
            if (bdebug >= 1)
              printf("Coordonnée2 %d\n", ident);
          }

          // Reconsitution de la chaine a transmettre à partir des
          // coordonnées de base
          sprintf(sAutresElts, "%lf %c %lf", Coord1, cSeparateur, Coord2);
          if (bdebug >= 1)
            printf("ident= %d\n\n", ident);
          pliste = inserTriCroissant(pliste, ident, sAutresElts);
        }
        if (feof(fp)) {
          break;
        }

      } while (1);

      fclose(fp);

      traiterListe(pliste);
      printf("\n\n ----la liste chainée a bien marché !!---- \n\n ");

      break;

      //------------------
      //***** Cas Tmode1
      //----------------

    case Tmode1:
      if (bdebug >= 2)
        printf("Tmode1 \n\n");

      //------------------
      //***** Cas Pmode1
      //----------------

    case Pmode1:
      if (bdebug >= 2)
        printf("Pmode1 \n\n");

      fp = fopen(fileName, "r");
      if (fp == NULL) {
        perror("Error in opening file\nle fichié a été suprimé");
        return (-1);
      }
      do {
        fgets(Trame, lgMax, fp);
        if (bdebug > 1)
          printf("Trame[0] = %s\n", Trame);
        if (Trame[0] != '\n') {

          ptChaine = strtok(Trame, ";");
          if (ptChaine != NULL) {
            sscanf(ptChaine, "%d", &ident);
            if (bdebug >= 1)
              printf("ident %d\n", ident);

            ptChaine = strtok(NULL, ";");
            if (ptChaine != NULL) {
              sscanf(ptChaine, "%lf", &val_TempPress);
              if (bdebug >= 1)
                printf("val_TempPress %lf\n", val_TempPress);
              chainonMode1 = creationChainonMode(ident, val_TempPress);
              chainonMode2 = inserTriCroissantMode(chainonMode2, chainonMode1);
            }
          }
          if (feof(fp)) {
            break;
          }
        }
      } while (1);
      fclose(fp);
      traiterListeMode(chainonMode2);
      printf("\n\n ----la liste chainée a bien marché !!---- \n\n ");

      break;
      break;

    default:
      printf("Other \n");
      break;
    }
  }

  return 0;
}
