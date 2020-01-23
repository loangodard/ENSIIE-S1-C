#include "pile.h"

/*@ requires nothing
    assigns reserve une zone mémoire pour un tableau d'entier
    ensures initialise une pile vide */
stack create(){
	stack r;
	r.t=(int*) malloc(1*sizeof(int));
	r.top=-1;
	r.size=1;
	return r;
}

/*@ requires p est une adresse valide vers un type stack et new_size positif
    assigns p
    ensures redimensionne la pile p */
void resize(stack *p,int new_size){
	int *tmp;
	int i;
	tmp =(int *) malloc(new_size * sizeof(int));
	for (i = 0; i <= p->top;i++){
		tmp[i] = p->t[i];
	}
	free(p->t);
	p->t=tmp;
	p->size=new_size;
}

/*@ requires p est une adresse valide vers un type stack
    assigns p
    ensures ajoute a en haut de la pile*/
void empile(stack *p, int a){
	if (p->top >= p->size - 1) 
		resize(p,2*p->size);
	p->top += 1;
	p->t[p->top]= a;
}

/*@ requires p est une adresse valide vers un type stack
    assigns p
    ensures retire l'entier au sommet de la pile et le renvoi */
int pop(stack *p){
	if (p->top<0) return 0;
	int r;
	r = p->t[p->top];
	p->top-=1;
	return r;
}

/*@ requires nothing
    assigns nothing
    ensures affiche le contenu de la pile p */
void print_stack(stack p){
	int i;
	printf("|");
	if (p.top<0){printf("\n");return;}
	for (i=0;i<p.top;i++){
		printf("%i|",p.t[i]);
	}
	printf("%i\n",p.t[p.top]);
}
/*@ requires nothing
    assigns nothing
    ensures renvoi 1 si la pile est vide, 0 sinon*/
int empty(stack p){
	if (p.top == -1)
		return 1;
	return 0;
}

/*Affiche la pile comme décrit dans le cahier des charges*/
void print_stack_debogueur(stack p){
	int i;
	if (empty(p)){
		printf("|\n");
		return;
	} 
	for (i=p.top; i>=0;i--){
		printf("(%c) %i|",p.t[i],p.t[i]);
	}
	printf("\n");
}

/*@requires nothing
   assigns nothing
   ensures renvoie la copy de la pile p*/
stack copy_stack(stack p){
	stack r=create();
	while(empty(p) != 1){
		int a = pop(&p);
		empile(&r,a);
	}
	r.top = p.top;
	r.size= p.size;
	return r;
}

/*@requires nothing
   assigns p
   ensures vide p */
void vide_pile(stack *p){
	while (!empty(*p)){
		pop(p);
	}
}
/** Fonction spécifique au projet **/

/*@ requires p est une adresse valide
    assigns p
    ensures depile deux entiers a et b et empile a+b */
void addition(stack *p){
	int a = pop(p);
	int b = pop(p);
	empile(p,a+b);
}

/*@ requires p est une adresse valide
    assigns p
    ensures depile les entiers a puis b et empile b-a */
void soustraction(stack *p){
	int a = pop(p);
	int b = pop(p);
	empile(p,b-a);
}

/*@ requires p est une adresse valide
    assigns p
    ensures depile deux entiers a et b et empile a*b */
void multiplication(stack *p){
	int a = pop(p);
	int b = pop(p);
	empile(p,a*b);
}

/*@ requires p est une adresse valide
    assigns p
    ensures depile deux entier a puis b et empile la division entiere de b par a */
void division_entiere(stack *p){
	int a = pop(p);
	int b = pop(p);
	if (a==0) empile(p,42);
	else empile(p,b/a);
}

/*@ requires p est une adresse valide
    assigns p
    ensures depile deux entier a puis b et empile le reste de la DE de b par a*/
void reste(stack *p){
	int a = pop(p);
	int b = pop(p);
	if (a==0) empile(p,0xbadc0de);
	else empile(p,b%a);	
}

/*@ requires p est une adresse valide
    assigns p
    ensures depile un entier a, si a == 0, empile 1 et empile 0 sinon */
void non_logique(stack *p){
	int a = pop(p);
	empile(p,(a==0));

}

/*@ requires p est une adresse valide
    assigns p
    ensures depile un entier a puis b et empile 1 si b>a, empile 0 sinon */
void plus_grand_que(stack *p){
	int a = pop(p);
	int b = pop(p);
	if (b>a) empile(p,1);
	else empile(p,0);
}

/*@ requires p est une adresse valide
    assigns p
    ensures duplique le sommet de la pile */
void duplique(stack *p){
	int a = pop(p);
	empile(p,a);
	empile(p,a);
}

/*@ requires p est une adresse valide
    assigns p
    ensures echange les deux entiers au sommet de la pile */
void echange_sommet(stack *p){
	int a = pop(p);
	int b = pop(p);
	empile(p,a);
	empile(p,b);
}
