#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "paramcmd1.h"


/** constante chaine de caracteres pour l'affichage des types */
const char *ParamTypeChaine[] = {"entier","reel","chaine"};

/**
 * \fn char * ValeurParamToString(TParamDef * _tabParam, const int _index)
 * \brief fonction qui transforme la valeur d'un parametre en chaine de caractere
 *
 * \param[in] _tabParam tableau des parametres de la ligne de commande
 * \param[in] _index indice du parametre a considerer dans le tableau
 * \return une nouvelle chaine (qu'il faudra libérer par la suite)
*/
char * ValeurParamToString(TParamDef * _tabParam, const int _index) {
  char *toReturn = NULL;
  int length=0;
  TParamDef *p = &_tabParam[_index];
  
  //Copie du contenu en fonction du type de données
  switch (p->type)
  {
    case PTchaine :
      length = snprintf(NULL, 0, "%s", p->valeur.chaine);
      toReturn = malloc(sizeof(char) * (++length));
      if(!toReturn) return NULL;
      snprintf(toReturn, length, "%s", p->valeur.chaine);
    break;
    
    case PTentier :
      length = snprintf(NULL,0,"%d",p->valeur.entier);
      toReturn = malloc(sizeof(char) * (++length));
      if(!toReturn) return NULL;
      snprintf(toReturn, length, "%d",p->valeur.entier);
    break;
    

    case PTreel :
      length = snprintf(NULL, 0, "%f", p->valeur.reel);
      toReturn = malloc(sizeof(char) * (++length));
      if(!toReturn) return NULL;
      snprintf(toReturn, length, "%f", p->valeur.reel);
    break;
  }

  return toReturn;
}

/**
 * \fn PrintParam(TParamDef * _tabParam, const int _nbParam)
 * \brief fonction qui affiche a l'ecran les parametre, leur type et leur valeur
 *
 * \param[in] _tabParam tableau des parametres de la ligne de commande
 * \param[in] _nbParam taille du tableau
 * \return neant
*/
void PrintParam(TParamDef * _tabParam, const int _nbParam) {
  TParamDef *p;
  int length;
  char *toPrint;

  for(int i=0;i<_nbParam;++i){
    
    p = &_tabParam[i];
    length = 0;
    toPrint = NULL;

    //Copie de la lettre, du nom et du type de données
    length = snprintf(NULL, 0, "-%c %s (%s) [%s]", p->lettre, p->nom, ParamTypeChaine[p->type], ValeurParamToString(_tabParam, i));
    toPrint=malloc(sizeof(char)*++length);

    if(toPrint){
      snprintf(toPrint, length, "-%c %s (%s) [%s]", p->lettre, p->nom, ParamTypeChaine[p->type], ValeurParamToString(_tabParam, i));
      printf("%s\n", toPrint);
    }
    if(toPrint) free(toPrint);

  }
  printf("\n");
}

/**
 * \fn int ReadParamFromCommandLine(TParamDef * _tabParam, const int _nbParam, const int _argc, const char * _argv[])
 * \brief fonction qui analyse la ligne de commande pour en extraire des valeurs pour les parametres
 *
 * \param[out] _tabParam tableau des parametres de la ligne de commande
 * \param[in] _nbParam taille du tableau
 * \param[in] _argc nombre d'arguments passes sur la ligne de commande
 * \param[in] _argv tableau qui contient les chaines de caracteres passees en arguments du programme
 * \return >=0 : nombre de parametres mis a jour, <0 : erreur
*/
int ReadParamFromCommandLine(TParamDef * _tabParam, const int _nbParam, const int _argc, const char * _argv[]) {
  /***** A ECRIRE *****/
  char next = -1;

  //Parcours des paramètres de la commande
  for(int i=1; i<_argc; ++i){
    
    //Entrée: le paramètre commance pas un tiret
    //  => ce qui suit est un paramètre donc on stock à quoi correspond ce paramètre 
    if(_argv[i][0]=='-'){
      next = _argv[i][1];
    }
    else {

      if(next==-1){
        printf("Aucun parametre passe.\n");
        return 1;
      }

      int finded=0;

      //Parcours des paramètres possibles
      for(int j=0; j<_nbParam && !finded; ++j){

        //Entrée: le paramètre parcouru correspond au paramètre en ligne de commande
        //  => On définit les valeurs
        if(_tabParam[j].lettre==next){
          switch (_tabParam[j].type)
          {
            case PTchaine :
              _tabParam[j].valeur.chaine = _argv[i];
              finded = 1;
            break;
            
            case PTentier :
              _tabParam[j].valeur.entier = atoi(_argv[i]);
              finded = 1;
            break;
            

            case PTreel :
              _tabParam[j].valeur.reel = atof(_argv[i]);
              finded = 1;
            break;
          }
        }
      }
      if(!finded){
        printf("Parametre '-%c' inconnu.\n",next);
        return 1;
      }
      
    }
  }

  return 0;
}