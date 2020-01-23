#include "modules/curseur.h"

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
  //print_matrice(contenu); Enlever le commentaire pour afficher le fichier au début du programme
  
/* initialisation du curseus*/
  stack pile = create();
  curseur curseur = init_curseur();
  curseur.lec = contenu.content[0][0];
  curseur.mode = 0;

  int pont = 0;

  int user = 0; //variable utile pour le scanf, pour le cas '&'
  char user2;   //variable utile pour le scanf, pour le cas '~'

  while (curseur.lec !='@'){
    /* Cette boucle while termine si et seulement si le curseur lit le caractère '@'*/
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
        case '.': printf("%i",pop(&pile));break;
        case '?': curseur.direction=random_direction();break;
        case '\'':curseur.direction=direction_apostrophe(&pile);break;//le test ==''' entraine une erreur de compilation -> '\''
        case ']': tourne_gauche_45(&curseur);break;
        case '[': tourne_droite_45(&curseur);break;
        case '_': conditionnelle_horizontale(&curseur,&pile);break;
        case '|': conditionnelle_verticale(&curseur,&pile);break;
        case '/': conditionnelle_diagonale1(&curseur,&pile);break;
        case '\\': conditionnelle_diagonale2(&curseur,&pile);break;
        case '"' : switch_mode(&curseur);break;
        case ',': printf("%c",pop(&pile));break;
        case '#': pont = pop(&pile)+1;break;
        case 'g': get(contenu,&pile);break;
        case 'p': put(&contenu,&pile);break;
        case '&': scanf("%d",&user);empile(&pile,user);break;
        case '~': scanf("%c",&user2);empile(&pile,user2);break;
        default:break;
    }
	}

  	else if (curseur.mode==1 && pont == 0){//Si le pont ne vaut pas 0 et que le mode du curseur est 1 on empile la valeur ASCII du caractère
	   	if (curseur.lec =='"') switch_mode(&curseur);
		  else empile(&pile,curseur.lec);
	}
    //On déplace le curseur selon sa direction
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
  //Fin du while
  printf("\n");
  free(contenu.content);
  free(pile.t);
  return 0;
}