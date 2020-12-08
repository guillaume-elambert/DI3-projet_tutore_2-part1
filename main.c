/**
 * \file main.c
 * \brief 2ieme etape du TP IL
 * \author NM
 * \version 0.1
 * \date 17/11/2014
 *
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "paramcmd1.h"

/**
 * \fn int main (const int _argc, const char * _argv[])
 * \brief fonction principale
 *
 * \param[in] _argc : nombre d'arguments passes sur la ligne de commande
 * \param[in] _argv : tableau qui contient les chaines de caracteres passes en arguments du programme
 * \return 0 si terminaison normale
*/
int main (const int _argc, const char * _argv[]) {
  /* declaration des paramtres avec leur type+valeurs par defaut */
  TParamDef tab_param[] = {
    {"serveur",PTchaine,'s',.valeur.chaine="??"},
    {"appli",PTchaine,'a',.valeur.chaine=""},
    {"tours",PTentier,'t',.valeur.entier=200}};
  int nb_param = 3;

  /* affichage des formats de parametre */
  printf("Valeurs par defaut :\n");
  PrintParam(tab_param,nb_param);
  /* analyse de la ligne de commande */
  ReadParamFromCommandLine(tab_param,nb_param,_argc,_argv);
  /* affichage des nouveaux parametres */
  printf("Valeurs des parametres :\n");
  PrintParam(tab_param,nb_param);


  return 0;
}
