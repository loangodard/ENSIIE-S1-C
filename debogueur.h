#ifndef _DEBOGUEUR_H
#define _DEBOGUEUR_H
#include "modules/curseur.h"

/*@requires nothing
   assigns nothing
   ensures Affiche l'ordonnee du debogueur*/
void print_ordonnee(int x,int posx);

/*@requires nothing
   assigns nothing
   ensures affiche le fichier avec la postion du curseur comme décrit dans le cachier des charges*/
void affichage(int x, int y, int posx, int posy,matrix contenu,stack p);

/*@requires nothing
   assigns nothing
   ensures renvoi 0 si la chaine t est différente de "step", renvoi 1 si t == "step" ou t=="\n" et renvoi n si t="step n"*/
int test_step(char t[]);

/*@requires nothing
   assigns nothing
   ensures renvoie 1 si t=="run" et 0 sinon*/
int test_run(char t[]);

/*@requires nothing
   assigns nothing
   ensures renvoie 1 si t=="quit" et 0 sinon*/
int test_quit(char t[]);

/*@requires nothing
   assigns nothing
   ensures renvoie 1 si t=="restart" et 0 sinon*/
int test_restart(char t[]);


#endif