/**
 * \file paramcmd1.h
 * \brief 3ieme etape du TP IL
 * \author Loann Duplessis
 * \author Paul Poitrineau
 * \author Guillaume Elambert
 * \version 0.1
 * \date 08/12/2020
 */

#ifndef PARAM_CMD_H
#define PARAM_CMD_H

/**
 * \enum TParamType
 * \brief Constantes pour le type des parametres de la ligne de commande
 */
typedef enum {
    PTentier, /**< un nombre entier */
    PTreel, /**< un nombre reel */
    PTchaine /**< une chaine de caracteres */
  } TParamType;



/** constante chaine de caracteres pour l'affichage des types */
extern const char* ParamTypeChaine[];


/**
 * \union TParamValue
 * \brief union permettant de  manipuler un entier/reel/chaine
 */
typedef union {
    int entier;
    float reel;
    const char * chaine;
  } TParamValue;

/**
 * \struct TParamDef
 * \brief represente un parametre de la ligne de commande (nom,type,valeur...)
 */
typedef struct {
    char * nom; /**< nom du parametre */
    TParamType type; /**< type (entier,reel,chaine) */
    char lettre; /**< lettre a utiliser sur la ligne de commande */
    TParamValue valeur; /**< valeur a affecter au parametre */
  } TParamDef;


char * ValeurParamToString(TParamDef * _tabParam, const int _index);

void PrintParam(TParamDef * _tabParam, const int _nbParam);
int ReadParamFromCommandLine(TParamDef * _tabParam, const int _nbParam, const int _argc, const char * _argv[]);

#endif