#ifndef _CURSEUR_H
#define _CURSEUR_H
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "pile.h"
#include "ouverture.h"

enum direction {g,d,b,h,dhd,dhg,dbd,dbg};
/*
  g : gauche
  d : droite
  b : bas
  h : haut
  dhd : diagonale haut droite
  dhg : diagonale haut gauche
  dbd : diagonale bas droite
  dbg : diagonale bas gauche
  */

/*Création de la structure du curseur*/
struct curseur{
  char lec; //Le caractère que le curseur est en train de lire 
  int i,j; //Coordonnée du curseur dans la matrice 
  enum direction direction; // direction du curseur 
  int mode; /* si 0: mode entier; si 1: mode chaine de caractère (pour le cas " des .2d)*/
};

typedef struct curseur curseur;

/*@requires nothing
   assigns nothing
   ensures intialise un curseur */
curseur init_curseur();

/*@requires c une adresse valide
   assigns modifie c.lec
   ensures fait avancer le curseur vers la droite*/
void droite(matrix contenu,curseur *c);

/*@requires c une adresse valide
   assigns modifie c.lec
   ensures fait avancer le curseur vers la gauche*/
void gauche(matrix contenu,curseur *c);

/*@requires c une adresse valide
   assigns modifie c.lec
   ensures fait avancer le curseur vers le bas*/
void bas(matrix contenu,curseur *c);

/*@requires c une adresse valide
   assigns modifie c.lec
   ensures fait avancer le curseur vers le haut*/
void haut(matrix contenu,curseur *c);

/*@requires a<b
   assigns nothing
   ensures renvoi un entier compris entre a et b*/
int random_a_b(int a,int b);

/*@requires nothing
   assigns nothing
   ensures renvoi une direction aléatoire*/
enum direction random_direction();

/*@requires pile une adresse valide
   assigns dépile un entier de 'pile'
   ensures renvoi une direction en fonction de l'entier dépilé et de sa division euclidienne par 8*/
enum direction direction_apostrophe(stack *pile);

/*@requires c une adresse valide
   assigns modifie c.direction
   ensures change la direction du curseur de 45 degrès vers la gauche*/
void tourne_gauche_45(curseur *c);

/*@requires c une adresse valide
   assigns modifie c.direction
   ensures change la direction du curseur de 45 degrès vers la droite*/
void tourne_droite_45(curseur *c);

/*@requires c et p des adresses valides
   assigns modifie c.direction et depile un entier de p
   ensures change la direction du curseur vers la gauche si l'entier dépilé est non nul et vers la droite sinon*/
void conditionnelle_horizontale(curseur *c,stack *p);

/*@requires c et p des adresses valides
   assigns modifie c.direction et depile un entier de p
   ensures change la direction du curseur vers le haut si l'entier dépilé est non nul et vers le bas sinon*/
void conditionnelle_verticale(curseur *c,stack *p);

/*@requires c et p des adresses valides
   assigns modifie c.direction et depile un entier de p
   ensures change la direction du curseur vers la gauche et le bas si l'entier dépilé est non nul et vers la droite et le haut sinon*/
void conditionnelle_diagonale1(curseur *c,stack *p);

/*@requires c et p des adresses valides
   assigns modifie c.direction et depile un entier de p
   ensures change la direction du curseur vers la gauche et le haut si l'entier dépilé est non nul et vers la droite et le bas sinon*/
void conditionnelle_diagonale2(curseur *c,stack *p);

/*@requires c une adresse valide
   assigns modifie c.mode 
   ensures change le mode du curseur*/
void switch_mode(curseur *c);

/*@requires p une adresse valide
   assigns depile deux entiers j puis i de la pile p puis empile un entier sur p 
   ensures empile la valeur ASCII de la valeur contenu.content[i-1][j-1]*/
void get(matrix contenu,stack *p);

/*@requires contenu et p des adresses valide
   assigns p 
   ensures depile j,i,z de la pile p et modifie la valeur de contenu.content[i-1][j-1] en la remplacant par z*/
void put(matrix *contenu,stack *p);


#endif