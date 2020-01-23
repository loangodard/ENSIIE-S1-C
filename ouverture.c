#include "ouverture.h"

//initialisation d'une matrice de caractère de taille (x,y)


/*@requires nothing
   assigns nothing
   ensures renvoi une matrice de type matrix de taille x et y*/
matrix create_matrix(int x, int y){
	matrix r;
	r.x=x;
	r.y=y;
	r.content=(char**) malloc(y*sizeof(char*));
  	for (int k =0; k<y; k++){
  		r.content[k]=calloc(x,sizeof(char));
  	}
  	return r;
}

/*@requires nothing
   assigns nothing
   ensures renvoie la copy de la matrice m */
matrix copy_matrix(matrix m){
	matrix r = create_matrix(m.x,m.y);
	for (int i = 0; i<r.y;i++){
		for (int j = 0; j<r.x;j++){
			r.content[i][j]=m.content[i][j];
		}
	}
	return r;
}

/*@requires nothing
   assigns nothing
   ensures renvoi une matrice de type matrix de taille x et y*/
void print_matrice(matrix t){
	for(int k=0; k<t.y;k++){
		for(int j = 0; j<t.x;j++){
			printf("%c",t.content[k][j]);
		}
		printf("\n");
	}
	printf("\n");
}

/*@requires nothing
   assigns nothing
   ensures converti prend un caractere en entrée et renvoi l'entier lui correspondant*/
int convert_str_int(char caractere){
	return atoi(&caractere);
}

/*@requires fichier une adresse valide
   assigns nothing
   ensures renvoi le premier entier présent sur la première ligne du fichier*/
int get_x(FILE* fichier){
	char fd[7];
	fgets(fd,7,fichier);
	int i = 0;
	int r=0;
	char tmp[7];
	while(fd[i]!=' '){
		tmp[i]=fd[i];
		i+=1;
	}
	/* À ce stade on a x "décomposé" en base 10 dans tmp, on vas le "recomposer" dans r*/
	for(int k = 0; k<i;k++){
		r = r + convert_str_int(tmp[k])*pow(10,i-k-1);
	}
	fseek(fichier, 0, SEEK_SET);
	return r;
}

/*@requires fichier une adresse valide
   assigns nothing
   ensures renvoi le deuxième entier présent sur la première ligne du ficher */
int get_y(FILE * fichier){
	char fd[20];
	fgets(fd,20,fichier);
	int i = 0;
	int r = 0;
	char tmp[5];
	while(fd[i]!=' '){
		i+=1;
	}
	i+=1;
	int l=0;
	while(fd[i]!='\n'){
		tmp[l]=fd[i];
		l+=1;
		i+=1;
	}
	for(int k = 0; k<l;k++){
		r = r + convert_str_int(tmp[k])*pow(10,l-k-1);
	}
	return r;
//on ne replace pas le curseur pour ouvrir la suite	
}

/*@requires f une adresse valide
   assigns nothing
   ensures renvoi une matrice de caractère contenant tous les caractère présent dans le fichier f sauf la première ligne*/
matrix ouverture(FILE *f){
	int x = get_x(f);
    int y = get_y(f);
    //printf("x = %d, y = %d\n",x,y); Enlever le commentaire pour afficher x et y au début du programme
    matrix contenu = create_matrix(x,y);

    for (int i = 0; i<=y;i++){
    	fgets(contenu.content[i],x+2,f);
  }
  return contenu;
}