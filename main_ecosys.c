#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <strings.h>
#include "ecosys.h"



#define NB_PROIES 20
#define NB_PREDATEURS 20
#define T_WAIT 40000


/* Parametres globaux de l'ecosysteme (externes dans le ecosys.h)*/


int main(void) {
int herbe[SIZE_X][SIZE_Y];
int j,k;
	for( j =0 ;j<SIZE_X;j++){
		for(k = 0;k<SIZE_Y;k++){
			herbe[j][k] = 0;
		}
	}	

	Animal *liste_proie = NULL;
	Animal *liste_predateur = NULL;
	int energie=10;
	int i;

	srand(time(NULL));

	Animal *a1 = creer_animal(19,49, energie);

	liste_proie=a1;
	afficher_ecosys(liste_proie,liste_predateur); 
	reproduce(&liste_proie,p_reproduce_proie); 

	bouger_animaux(liste_proie);
	afficher_ecosys(liste_proie,liste_predateur); 
	reproduce(&liste_proie,p_reproduce_proie);

	bouger_animaux(liste_proie);
	afficher_ecosys(liste_proie,liste_predateur); 
	reproduce(&liste_proie,p_reproduce_proie); 
	
	bouger_animaux(liste_proie);
	afficher_ecosys(liste_proie,liste_predateur);   
	assert(liberer_liste_animaux(liste_predateur)==NULL);
	assert(liberer_liste_animaux(liste_proie)==NULL);

	Animal *lst_proie = NULL;
	Animal *lst_predateur = NULL;
	FILE*f=fopen("Evol_Pop.txt","w");
	for(i=0;i<20;i++){
		ajouter_animal((int)(rand()%SIZE_X), (int)(rand()%SIZE_Y),  (int)(rand()%51), &lst_proie);
	}
	for(i=0;i<100;i++){
		ajouter_animal((int)(rand()%SIZE_X), (int)(rand()%SIZE_Y),  (int)(rand()%51), &lst_predateur);
	}
	for(i=0;i<500;i++){
		if(lst_proie == NULL && lst_predateur == NULL) break;
		fprintf(f,"%d %d %d\n",i,compte_animal_it(lst_proie),compte_animal_it(lst_predateur));
		rafraichir_predateurs(&lst_predateur,&lst_proie);
		rafraichir_proies(&lst_proie,herbe);
		rafraichir_monde(herbe);
		afficher_ecosys(lst_proie,lst_predateur);
		usleep(5);
	}
	fprintf(f,"%d %d %d\n",i,compte_animal_it(lst_proie),compte_animal_it(lst_predateur));
	
	assert(liberer_liste_animaux(lst_predateur)==NULL);
	assert(liberer_liste_animaux(lst_proie)==NULL);

	fclose(f);
	return 0;
}

