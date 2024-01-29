#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "ecosys.h"
#include<string.h>

/* PARTIE 1*/
/* Fourni: Part 1, exercice 3, question 2 */
Animal *creer_animal(int x, int y, float energie) {
	Animal *na = (Animal *)malloc(sizeof(Animal));
	assert(na);
	na->x = x;
	na->y = y;
	na->energie = energie;
	na->dir[0] = rand() % 3 - 1;
	na->dir[1] = rand() % 3 - 1;
	na->suivant = NULL;
	return na;
}


/* Fourni: Part 1, exercice 3, question 3 */
Animal *ajouter_en_tete_animal(Animal *liste, Animal *animal) {
	assert(animal);
	assert(!animal->suivant);
	animal->suivant = liste;
	return animal;
}

/* A faire. Part 1, exercice 5, question 1 */
void ajouter_animal(int x, int y,  float energie, Animal **liste_animal) {
	assert(x>=0);
	assert(SIZE_X>x);
	assert(y>=0);
	assert(SIZE_Y>y);
	Animal* new=creer_animal(x,y,energie);
	*liste_animal=ajouter_en_tete_animal(*liste_animal,new);
}

/* A Faire. Part 1, exercice 5, question 5 */
void enlever_animal(Animal **liste, Animal *animal) {
	if(*liste==NULL || animal == NULL){
		return;
	}
	if(*liste==animal ){
		Animal* suppr=*liste;
		*liste=(*liste)->suivant;
		free(suppr);
		return;
	}
	Animal* avant=*liste;
	Animal* suppr=(*liste)->suivant;
	while(suppr){
		if(suppr==animal){
			avant->suivant=suppr->suivant;
			free(suppr);
			return;
		}
		else{
		avant=avant->suivant;
		suppr=suppr->suivant;
		}
	}

	return ;
}

/* A Faire. Part 1, exercice 5, question 2 */
Animal* liberer_liste_animaux(Animal *liste) {
	if(liste==NULL) {return NULL;}
	Animal* suppr;
	while(liste->suivant){
		suppr=liste;
		liste=liste->suivant;
		free(suppr);
	}
	free(liste);
	return NULL;
}

/* Fourni: part 1, exercice 3, question 4 */
unsigned int compte_animal_rec(Animal *la) {
	if (!la) return 0;
	return 1 + compte_animal_rec(la->suivant);
}

/* Fourni: part 1, exercice 3, question 4 */
unsigned int compte_animal_it(Animal *la) {
	int cpt=0;
	while (la) {
		++cpt;
		la=la->suivant;
	}
	return cpt;
}



/* Part 1. Exercice 4, question 1, ATTENTION, ce code est susceptible de contenir des erreurs... */
void afficher_ecosys(Animal *liste_proie, Animal *liste_predateur) {
	unsigned int i, j;
	char ecosys[SIZE_X][SIZE_Y];
	Animal *pa=NULL;

	/* on initialise le tableau */
	for (i = 0; i < SIZE_X; ++i) {
		for (j = 0; j < SIZE_Y; ++j) {
			ecosys[i][j]=' ';
		}
	}

	/* on ajoute les proies */
	pa = liste_proie;
	while (pa) {
		ecosys[pa->x][pa->y] = '*';
		pa=pa->suivant;
	}

	/* on ajoute les predateurs */
	pa = liste_predateur;
	while (pa) {
		if ((ecosys[pa->x][pa->y] == '@') || (ecosys[pa->x][pa->y] == '*')) { /* proies aussi present */
			ecosys[pa->x][pa->y] = '@';
		} else {
			ecosys[pa->x][pa->y] = 'O';
		}
		pa = pa->suivant;
	}

	/* on affiche le tableau */
	printf("+");
	for (j = 0; j < SIZE_Y; ++j) {
		printf("-");
	}  
	printf("+\n");
	for (i = 0; i < SIZE_X; ++i) {
		printf("|");
		for (j = 0; j < SIZE_Y; ++j) {
			putchar(ecosys[i][j]);
		}
		printf("|\n");
	}
	printf("+");
	for (j = 0; j<SIZE_Y; ++j) {
		printf("-");
	}
	printf("+\n");
	int nbproie=compte_animal_it(liste_proie);
	int nbpred=compte_animal_it(liste_predateur);

	printf("Nb proies : %5d\tNb predateurs : %5d\n", nbproie, nbpred);

}
void ecrire_ecosys(const char * nomfic , Animal * liste_predateur, Animal * liste_proie){
	FILE * f= fopen(nomfic,"wb");
	fprintf(f,"<proie> \n");
	while(liste_proie){
		fprintf(f,"x=%d y=%d dir=[%d %d] e=%f \n",liste_proie->x,liste_proie->y,liste_proie->dir[0], liste_proie->dir[1], liste_proie->energie );
		liste_proie = liste_proie->suivant;
	}
	fprintf(f,"</proie> \n");
	fprintf(f,"<predateur> \n");
	while(liste_predateur != NULL){
		fprintf(f,"x=%d y=%d dir=[%d %d] e=%f \n",liste_predateur->x,liste_predateur->y,liste_predateur->dir[0], liste_predateur->dir[1], liste_predateur->energie );
		liste_predateur = liste_predateur->suivant;
	}
	fprintf(f,"</predateur> \n");
	fclose(f);
}

void lire_ecosys(const char * nomfic, Animal ** liste_predateur, Animal ** liste_proie){
	FILE * f = fopen(nomfic,"rb");
	char buff[200];
	int x,y,dir0,dir1;
	float e;
	if(fgets(buff,200,f) == NULL || strcmp(buff,"<proie> \n") !=0) exit(1);
	while(fgets(buff,200,f) !=NULL && strcmp (buff,"</proie> \n") !=0){
		sscanf(buff,"x=%d y=%d dir[%d %d] e=%f \n",&x,&y,&dir0,&dir1,&e);
		ajouter_animal(x,y,e,liste_proie);
		(*liste_proie)->dir[0] = dir0;
		(*liste_proie)->dir[1] = dir1;
	}
	if(fgets(buff,200,f) == NULL || strcmp(buff,"<predateur> \n") !=0) exit(1);
	while(fgets(buff,200,f) !=NULL && strcmp (buff,"</predateur> \n") !=0){
		sscanf(buff,"x=%d y=%d dir[%d %d] e=%f \n",&x,&y,&dir0,&dir1,&e);
		ajouter_animal(x,y,e,liste_predateur);
		(*liste_predateur)->dir[0] = dir0;
		(*liste_predateur)->dir[1] = dir1;
	}
	fclose(f);
}
void clear_screen() {
	printf("\x1b[2J\x1b[1;1H");  /* code ANSI X3.4 pour effacer l'ecran */
}

/* PARTIE 2*/

/* Part 2. Exercice 4, question 1 */
void bouger_animaux(Animal *la) {
	while(la){
		if((rand()/(float)RAND_MAX) < p_ch_dir){
			la->dir[0]=(rand()%3)-1;
			la->dir[1]=(rand()%3)-1;
		}
		la->x=(la->x + la->dir[0] + SIZE_X)%SIZE_X;
		la->y=(la->y+ la->dir[1]+ SIZE_Y)%SIZE_Y;
		la = la->suivant;
	}
}

/* Part 2. Exercice 4, question 3 */
void reproduce(Animal **liste_animal, float p_reproduce) {
	Animal *a=*liste_animal;
	printf("<%f>",p_reproduce);
	while(a){
		if(((float)rand()/(float)RAND_MAX) < p_reproduce){
			ajouter_animal(a->x,a->y,a->energie/2,liste_animal);
			a->energie/=2;
		}
		a=a->suivant;
	}
}

/* Part 2. Exercice 6, question 1 */
/*void rafraichir_proies(Animal **liste_proie, int monde[SIZE_X][SIZE_Y]) {
	Animal *lst = *liste_proie;
	bouger_animaux(*liste_proie);
		while(lst){
			lst->energie=lst->energie-1;
			Animal * suiv = lst->suivant;
			if(lst->energie<0){
				enlever_animal(liste_proie,lst);
			}
			else{
				if(monde[lst->x ][lst->y ]>0){
					lst->energie = lst->energie+monde[lst->x][lst->y];
					monde[lst->x][lst->y] = temps_repousse_herbe;
				}
			}			
			lst=suiv; 
		}
	reproduce(liste_proie,p_reproduce_proie);

}*/
void rafraichir_proies(Animal **liste_proie, int monde[SIZE_X][SIZE_Y]) {
	bouger_animaux(*liste_proie);
	Animal*lst=*liste_proie;
	while(lst){
		lst->energie=lst->energie-1;
		if(lst->energie<0){
			Animal*suppr=lst;
			lst=lst->suivant;
			enlever_animal(liste_proie, suppr);
		}else{
			if(monde[lst->x ][lst->y ]>0){
				lst->energie = lst->energie+monde[lst->x][lst->y];
				monde[lst->x][lst->y] = temps_repousse_herbe;
			}
			lst=lst->suivant;
		}
	}
	reproduce(liste_proie,p_reproduce_proie);
}


/* Part 2. Exercice 7, question 1 */
Animal *animal_en_XY(Animal *l, int x, int y) {
	while(l){
		if(l->x == x && l->y == y ){ 
			return l;
		}
		l=l->suivant;
	}
	return NULL;
} 

/* Part 2. Exercice 7, question 2 */
void rafraichir_predateurs(Animal **liste_predateur, Animal **liste_proie) {
	Animal *lst = *liste_predateur;
	bouger_animaux(*liste_predateur);
	Animal * suiv;
		while(lst){
			lst->energie=lst->energie -1;
			suiv = lst->suivant;
			if(lst->energie<0){
				enlever_animal(liste_predateur, lst);
			
			}
			else{
			Animal * nouriture = animal_en_XY(*liste_proie,lst->x,lst->y);
			if(nouriture ){
				lst->energie+=nouriture->energie;
				enlever_animal(liste_proie,nouriture);			
			}
			}
			lst=suiv;
		} 
	reproduce(liste_predateur,p_reproduce_predateur);
	printf("%f",p_reproduce_predateur);
}

void rafraichir_monde(int monde[SIZE_X][SIZE_Y] ){
	int j,k;
	for(j=0;j<SIZE_X;j++){
		for(k=0;k<SIZE_Y;k++){
			monde[j][k] ++;
		}
	}
}

