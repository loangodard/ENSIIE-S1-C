#ifndef _PILE_H
#define _PILE_H
#include<stdlib.h>
#include<stdio.h>

/*Définition des piles*/
struct stack{
    int *t;
    int top;
    int size;
};

typedef struct stack stack;

/*@ requires nothing
    assigns reserve une zone mémoire pour un tableau d'entier
    ensures initialise une pile vide */
stack create();

/*@ requires p est une adresse valide vers un type stack et new_size positif
    assigns p
    ensures redimensionne la pile p */
void resize(stack *p,int new_size);

/*@ requires p est une adresse valide vers un type stack
    assigns p
    ensures ajoute a en haut de la pile*/
void empile(stack *p, int a);

/*@ requires p est une adresse valide vers un type stack
    assigns p
    ensures retire l'entier au sommet de la pile et le renvoi */
int pop(stack *p);

/*@ requires nothing
    assigns nothing
    ensures affiche le contenu de la pile p */
void print_stack(stack p);

/*@ requires nothing
    assigns nothing
    ensures renvoi 1 si la pile est vide, 0 sinon*/
int empty(stack p);

void print_stack_debogueur(stack p);

stack copy_stack(stack p);

void vide_pile(stack *p);

/*@ requires p est une adresse valide
    assigns p
    ensures depile deux entiers a et b et empile a+b */
void addition(stack *p);

/*@ requires p est une adresse valide
    assigns p
    ensures depile les entiers a puis b et empile b-a */
void soustraction(stack *p);

/*@ requires p est une adresse valide
    assigns p
    ensures depile deux entiers a et b et empile a*b */
void multiplication(stack *p);

/*@ requires p est une adresse valide
    assigns p
    ensures depile deux entier a puis b et empile la division entiere de b par a */
void division_entiere(stack *p);

/*@ requires p est une adresse valide
    assigns p
    ensures depile deux entier a puis b et empile le reste de la DE de b par a*/
void reste(stack *p);

/*@ requires p est une adresse valide
    assigns p
    ensures depile un entier a, si a == 0, empile 1 et empile 0 sinon */
void non_logique(stack *p);

/*@ requires p est une adresse valide
    assigns p
    ensures depile un entier a puis b et empile 1 si b>a, empile 0 sinon */
void plus_grand_que(stack *p);

/*@ requires p est une adresse valide
    assigns p
    ensures duplique le sommet de la pile */
void duplique(stack *p);

/*@ requires p est une adresse valide
    assigns p
    ensures echange les deux entiers au sommet de la pile */
void echange_sommet(stack *p);

#endif