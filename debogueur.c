#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "debogueur.h"

/*@requires nothing
   assigns nothing
   ensures Affiche l'ordonnee du debogueur*/
void print_ordonnee(int x,int posx){
	int i;
	printf("  0");
	for (i = 1; i<=x; i++)
		if (i%5==0) printf("%5i",i);
	printf("\n");
	for (i = 0; i<2;i++)
		printf(" ");
	for (i = 0 ; i<=x; i++)
		if (i==posx) printf("%c",'v');
		else if (!(i%5==0)) printf("%c",' ');
		else if (i%5==0) printf("%c",'|');
	printf("\n");
}

/*@requires nothing
   assigns nothing
   ensures affiche le fichier avec la postion du curseur comme décrit dans le cachier des charges*/
void affichage(int x, int y, int posx, int posy,matrix contenu,stack p){
	print_ordonnee(x,posx);
	int i,j;
	for(i = 0; i<y;i++){
		if (i==posy){
			if (i%5==0)
				printf("%i>",i);
			else printf(" >");
		} 
		else if (i%5==0) printf("%i-",i);
		else{
			printf("  ");
		}
		for(j=0;j<x;j++) printf("%c",contenu.content[i][j]);
		printf("\n");
}
	print_stack_debogueur(p);
	printf("x : %i ",posx);
	printf("y : %i\n",posy);
}

/*@requires nothing
   assigns nothing
   ensures renvoi 0 si la chaine t est différente de "step", renvoi 1 si t == "step" ou t=="\n" et renvoi n si t="step n"*/
int test_step(char t[]){
	if (t[0]=='\n') return 1;
	char step[4]={'s','t','e','p'};
	for (int l=0;l<4;l++){
		if (!(t[l]==step[l])) return 0;
	}
	if (t[4] == '\n' || t[5] == '\n') // cas où l'utilisateur a entrée step ou step suivi de ' '
		return 1;
	else{
		int r = 0;
		int i = 5;
		int l = 0;
		char tmp[5];
		while (t[i] !='\n'){
			tmp[l]=t[i];
			i++;
			l++;
		}
		for(int k = 0; k<l;k++){
			r = r + convert_str_int(tmp[k])*pow(10,l-k-1);
		}
	return r;
	}
}

/*@requires nothing
   assigns nothing
   ensures renvoie 1 si t=="run" et 0 sinon*/
int test_run(char t[]){
	char run[3]={'r','u','n'};
	for (int l=0; l<3;l++){
		if (!(t[l]==run[l])) return 0;
	}
	return 1;
}

/*@requires nothing
   assigns nothing
   ensures renvoie 1 si t=="quit" et 0 sinon*/
int test_quit(char t[]){
	char quit[4]={'q','u','i','t'};
	for (int l=0; l<4;l++){
		if (!(t[l]==quit[l])) return 0;
	}
	return 1;
}

/*@requires nothing
   assigns nothing
   ensures renvoie 1 si t=="restart" et 0 sinon*/
int test_restart(char t[]){
	char restart[7]={'r','e','s','t','a','r','t'};
	for (int l=0; l<7;l++){
		if (!(t[l]==restart[l])) return 0;
	}
	return 1;
}

int main(int argc, char *argv[]){
/*ouverture du fichier*/
	FILE *f;
    f = fopen(argv[1],"r");
  
    if (f == NULL){
      printf("Impossible d'ouvrir le fichier : %s\n",argv[1]);
      return 1;
    }

/* importation du fichier dans la matrice contenu */
    matrix contenu = ouverture(f);
    fclose(f);
    matrix contenu_ini = copy_matrix(contenu);
    stack pile = create();
    curseur curseur = init_curseur();
    curseur.lec = contenu.content[0][0];
    int pont = 0;
    int user = 0; //variable utile pour le scanf, pour le cas '&'
    char user2;   //variable utile pour le scanf, pour le cas '~'

    int play = 1;
    char buf[256];

    int indicateur =0; // si indicateur == 1 alors l'utilisateur a entré la commande "run" et dans ce cas on continuera jusqu'à la fin sans redemander d'entrée
    affichage(contenu.x, contenu.y, curseur.j, curseur.i, contenu,pile);
    while(play){
    	/*cette boucle while termine si l'utilisateur entre quit ou si le curseur lit le caractère '@' Elle ne termine pas si non*/
    	if (!indicateur){ //On demande un entrée à l'utilisateur s'il n'a pas entrée "run"
    		printf("Entrez une commande :");
    		fgets(buf, 256, stdin);
    		printf("\n");
    	}


		else{//Si l'utilisateur a entré run, on entre toujours '\n' dans le buf pour avancer jusqu'à la fin.
			buf[0]='\n';
		}

		if (test_quit(buf)) play=0; //Dans ce cas on quitte la boucle while pour sortir du programme

		else if (test_restart(buf)){ //Dans ce cas on replace le curseur en (0,0) de direction droite, on copie la matrice initiale et on vide la pile
	 		contenu = copy_matrix(contenu_ini);
	 		vide_pile(&pile);
	 		curseur = init_curseur();
	 		curseur.lec =contenu.content[0][0];
	 		affichage(contenu.x, contenu.y, curseur.j, curseur.i, contenu,pile);
		}
	 
		else if (test_run(buf)) indicateur = 1;

		else if (test_step(buf) > 0){ //Dans ce cas on avance de n pas.
			int n = test_step(buf);

			for (int m =0; m<n; m++){
				if (curseur.lec=='@'){ play =0;break;}
				if (pont>0){
	    		//Si le pont vaut 0, alors c'est qu'on n'a pas recontré '#' dans les n derniers tours.
	    		//Si le pont vaut n, alors on doit sauter les n prochains tours.
					pont -=1;
				}

		   	 if (curseur.mode == 0 && pont == 0){ //Si le pont vaut 0, on n'ignore pas les prochaines instructions
		   	 	switch (curseur.lec){
		   	 		case 'v':curseur.direction = b;break;
		   	 		case '^':curseur.direction = h;break;
		   	 		case '>':curseur.direction = d;break;
		   	 		case '<':curseur.direction = g;break;
		   	 		case '0': empile(&pile,0);break;
		   	 		case '1': empile(&pile,1);break;
		   	 		case '2': empile(&pile,2);break;
		   	 		case '3': empile(&pile,3);break;
		   	 		case '4': empile(&pile,4);break;
		   	 		case '5': empile(&pile,5);break;
		   	 		case '6': empile(&pile,6);break;
		   	 		case '7': empile(&pile,7);break;
		   	 		case '8': empile(&pile,8);break;
		   	 		case '9': empile(&pile,9);break;
		   	 		case '+': addition(&pile);break;
		   	 		case '-': soustraction(&pile);break;
		   	 		case '*': multiplication(&pile);break;
		   	 		case ':': division_entiere(&pile);break;
		   	 		case '%': reste(&pile);break;
		   	 		case '!': non_logique(&pile);break;
		   	 		case '`': plus_grand_que(&pile);break;
		   	 		case '=': duplique(&pile);break;
		   	 		case '$': echange_sommet(&pile);break;
		   	 		case ';': if (!empty(pile)) pop(&pile);break;
		   	 		case '.': printf("%i\n",pop(&pile));break;
		   	 		case '?': curseur.direction=random_direction();break;
		     	 	case '\'':curseur.direction=direction_apostrophe(&pile);break;//le test ==''' entraine une erreur de compilation.
		      		case ']': tourne_gauche_45(&curseur);break;
		      		case '[': tourne_droite_45(&curseur);break;
		      		case '_': conditionnelle_horizontale(&curseur,&pile);break;
		      		case '|': conditionnelle_verticale(&curseur,&pile);break;
		      		case '/': conditionnelle_diagonale1(&curseur,&pile);break;
		      		case '\\': conditionnelle_diagonale2(&curseur,&pile);break;
		      		case '"' : switch_mode(&curseur);break;
		      		case ',': printf("%c\n",pop(&pile));break;
		      		case '#': pont = pop(&pile)+1;break;
		      		case 'g': get(contenu,&pile);break;
		      		case 'p': put(&contenu,&pile);break;
		      		case '&': scanf("%d",&user);empile(&pile,user);break;
		      		case '~': scanf("%c",&user2);empile(&pile,user2);break;
		      		default:break;
		      	}
		  		}	

				else if (curseur.mode==1 && pont == 0){
		  	  		if (curseur.lec =='"') switch_mode(&curseur);
		  			else empile(&pile,curseur.lec);
		  		}

				affichage(contenu.x, contenu.y, curseur.j, curseur.i, contenu,pile);
		  		printf("curseur : %c\n",curseur.lec );
		  		switch(curseur.direction){
					case b:bas(contenu,&curseur);break;
		  			case h:haut(contenu,&curseur);break;
		  			case d:droite(contenu,&curseur);break;
		  			case g:gauche(contenu,&curseur);break;
		  			case dhd:haut(contenu,&curseur);droite(contenu,&curseur);break;
		  			case dhg:haut(contenu,&curseur);gauche(contenu,&curseur);break;
		  			case dbd:bas(contenu,&curseur);droite(contenu,&curseur);break;
		  			case dbg:bas(contenu,&curseur);gauche(contenu,&curseur);break;
		  			default: break;
		 		}
			}
		}
	}
	affichage(contenu.x, contenu.y, curseur.j, curseur.i, contenu,pile);
	free(contenu.content);
	free(pile.t);
	return 0;
}


