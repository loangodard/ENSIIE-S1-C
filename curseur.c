#include "curseur.h"

/*@requires nothing
   assigns nothing
   ensures intialise un curseur */
curseur init_curseur(){
	curseur c;
	c.i=0;
	c.j=0;
	c.direction=d;
	c.mode = 0;
	return c;
}

/*@requires c une adresse valide
   assigns modifie c.lec
   ensures fait avancer le curseur vers la droite*/
void droite(matrix contenu,curseur *c){
    if (c->j==contenu.x-1) c->j=0;
    else c->j += 1;
    c->lec = contenu.content[c->i][c->j];
}

/*@requires c une adresse valide
   assigns modifie c.lec
   ensures fait avancer le curseur vers la gauche*/
void gauche(matrix contenu,curseur *c){
    if (c->j==0) c->j=contenu.x-1;
    else c->j -= 1;
    c->lec = contenu.content[c->i][c->j];
}

/*@requires c une adresse valide
   assigns modifie c.lec
   ensures fait avancer le curseur vers le bas*/
void bas(matrix contenu,curseur *c){
    if (c->i==contenu.y-1) c->i=0;
    else c->i += 1;
    c->lec = contenu.content[c->i][c->j];
}

/*@requires c une adresse valide
   assigns modifie c.lec
   ensures fait avancer le curseur vers le haut*/
void haut(matrix contenu,curseur *c){
    if (c->i==0) c->i=contenu.y-1;
    else c->i -= 1;
    c->lec = contenu.content[c->i][c->j];
}

/*@requires a<b
   assigns nothing
   ensures renvoi un entier compris entre a et b*/
int random_a_b(int a,int b){
	srand(time(NULL));
	return rand()%(b+1-a)+1;
}

/*@requires nothing
   assigns nothing
   ensures renvoi une direction aléatoire*/
enum direction random_direction(){
	enum direction r;
	switch (random_a_b(1,8)){
		case 1:r=g;break;
		case 2:r=d;break;
		case 3:r=h;break;
		case 4:r=b;break;
		case 5:r=dhd;break;
		case 6:r=dhg;break;
		case 7:r=dbd;break;
		case 8:r=dbg;break;
	}
	return r;
}

/*@requires pile une adresse valide
   assigns dépile un entier de 'pile'
   ensures renvoi une direction en fonction de l'entier dépilé et de sa division euclidienne par 8*/
enum direction direction_apostrophe(stack *pile){
	int a = pop(pile);
	switch(a%8){
		case 0:return h;
		case 1:return dhd;
		case 2:return d;
		case 3:return dbd;
		case 4:return b;
		case 5:return dbg;
		case 6:return g;
		case 7:return dhg;
	}
	return d;
}

/*@requires c une adresse valide
   assigns modifie c.direction
   ensures change la direction du curseur de 45 degrès vers la gauche*/
void tourne_gauche_45(curseur *c){
	switch(c->direction){
		case d: c->direction=dhd;break;
		case dhd: c->direction=h;break;
		case h: c->direction=dhg;break;
		case dhg: c->direction=g;break;
		case g: c->direction=dbg;break;
		case dbg: c->direction=b;break;
		case b: c->direction=dbd;break;
		case dbd: c->direction=d;break;
	}
}

/*@requires c une adresse valide
   assigns modifie c.direction
   ensures change la direction du curseur de 45 degrès vers la droite*/
void tourne_droite_45(curseur *c){
	switch(c->direction){
		case d: c->direction=dbd;break;
		case dbd: c->direction=b;break;
		case b: c->direction=dbg;break;
		case dbg: c->direction=g;break;
		case g: c->direction=dhg;break;
		case dhg: c->direction=h;break;
		case h: c->direction=dhd;break;
		case dhd: c->direction=d;break;
	}
}

/*@requires c et p des adresses valides
   assigns modifie c.direction et depile un entier de p
   ensures change la direction du curseur vers la gauche si l'entier dépilé est non nul et vers la droite sinon*/
void conditionnelle_horizontale(curseur *c,stack *p){
	int a = pop(p);
	if (a==0) c->direction=d;
	else c->direction=g;
}

/*@requires c et p des adresses valides
   assigns modifie c.direction et depile un entier de p
   ensures change la direction du curseur vers le haut si l'entier dépilé est non nul et vers le bas sinon*/
void conditionnelle_verticale(curseur *c,stack *p){
	int a = pop(p);
	if(a==0) c->direction=b;
	else c->direction=h;
}

/*@requires c et p des adresses valides
   assigns modifie c.direction et depile un entier de p
   ensures change la direction du curseur vers la gauche et le bas si l'entier dépilé est non nul et vers la droite et le haut sinon*/
void conditionnelle_diagonale1(curseur *c,stack *p){
	int a =pop(p);
	if(a==0) c->direction=dhd;
	else c->direction=dbg;
}

/*@requires c et p des adresses valides
   assigns modifie c.direction et depile un entier de p
   ensures change la direction du curseur vers la gauche et le haut si l'entier dépilé est non nul et vers la droite et le bas sinon*/
void conditionnelle_diagonale2(curseur *c,stack *p){
	int a=pop(p);
	if (a==0) c->direction=dbd;
	else c->direction=dhg;
}

/*@requires c une adresse valide
   assigns modifie c.mode 
   ensures change le mode du curseur*/
void switch_mode(curseur *c){
	if (c->mode == 0) c->mode = 1;
	else c->mode =0;
}

/*@requires p une adresse valide
   assigns depile deux entiers j puis i de la pile p puis empile un entier sur p 
   ensures empile la valeur ASCII de la valeur contenu.content[i-1][j-1]*/
void get(matrix contenu,stack *p){
	int i=pop(p);
	int j=pop(p);

	if (!(j>=contenu.x || i>=contenu.y || i<0 || j<0)){ 
		empile(p,contenu.content[i][j]); 
	}
	else empile(p,0);
}

/*@requires contenu et p des adresses valide
   assigns p 
   ensures depile j,i,z de la pile p et modifie la valeur de contenu.content[i-1][j-1] en la remplacant par z*/
void put(matrix *contenu,stack *p){
	int i=pop(p);
	int j=pop(p);
	int z=pop(p);
	if (!(j>=contenu->x || i>=contenu->y || i<0 || j<0)){
		contenu->content[i][j]=z;
	}
}
