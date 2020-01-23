#ifndef _OUVERTURE_H
#define _OUVERTURE_H
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

struct matrix{
   int x,y;
   char** content;
};

typedef struct matrix matrix;

/*@requires nothing
   assigns nothing
   ensures renvoi une matrice de type matrix de taille x et y*/
matrix create_matrix(int x, int y);

/*@requires nothing
   assigns nothing
   ensures renvoie la copy de la matrice m */
matrix copy_matrix(matrix m);

/*@requires nothing
   assigns nothing
   ensures renvoi une matrice de type matrix de taille x et y*/
void print_matrice(matrix t);

/*@requires nothing
   assigns nothing
   ensures converti prend un caractere en entrée et renvoi l'entier lui correspondant*/
int convert_str_int(char caractere);

/*@requires fichier une adresse valide
   assigns nothing
   ensures renvoi le premier entier présent sur la première ligne du fichier*/
int get_x(FILE* fichier);

/*@requires fichier une adresse valide
   assigns nothing
   ensures renvoi le deuxième entier présent sur la première ligne du ficher */
int get_y(FILE * fichier);

/*@requires f une adresse valide
   assigns nothing
   ensures renvoi une matrice de caractère contenant tous les caractère présent dans le fichier f sauf la première ligne*/
matrix ouverture(FILE *f);

#endif