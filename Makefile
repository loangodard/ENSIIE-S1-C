all:interpreteur debogueur

interpreteur: pile.o ouverture.o curseur.o interpreteur.o
	gcc -o interpreteur pile.o ouverture.o curseur.o interpreteur.o

debogueur: pile.o ouverture.o curseur.o debogueur.o
	gcc -o debogueur pile.o ouverture.o curseur.o debogueur.o
	
pile.o: modules/pile.c modules/pile.h
	gcc -o pile.o -c modules/pile.c -Wall

ouverture.o: modules/ouverture.c modules/ouverture.h
	gcc -o ouverture.o -c modules/ouverture.c -Wall

curseur.o: modules/curseur.c modules/curseur.h modules/ouverture.h modules/pile.h
	gcc -o curseur.o -c modules/curseur.c -Wall

interpreteur.o: interpreteur.c modules/curseur.h
	gcc -o interpreteur.o -c interpreteur.c -Wall

debogueur.o: debogueur.c debogueur.h modules/curseur.h
	gcc -o debogueur.o -c debogueur.c -Wall

clean:
	rm -f *.o