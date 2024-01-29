#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ecosys.h"



int main(void) {
  int i;
  Animal *liste_proie = NULL;
  Animal *liste_predateur = NULL;
  Animal *lst_proie = NULL;
  Animal *lst_predateur = NULL;
  int energie=10;

  srand(time(NULL));
	for(int i=0;i<20;i++){
		ajouter_animal((int)(rand()%SIZE_X), (int)(rand()%SIZE_Y),  (int)(rand()%51), &liste_proie);
	}
	for(int i=0;i<20;i++){
		ajouter_animal((int)(rand()%SIZE_X), (int)(rand()%SIZE_Y),  (int)(rand()%51), &liste_predateur);
	}
  printf("%d\n",(int)compte_animal_it(liste_predateur));
  printf("%d\n",(int)compte_animal_it(liste_proie));

  afficher_ecosys(liste_proie,liste_predateur); 
  ecrire_ecosys("fic",liste_predateur,liste_proie);
  assert(liberer_liste_animaux(liste_predateur)==NULL);
  assert(liberer_liste_animaux(liste_proie)==NULL);
  lire_ecosys("fic",&lst_predateur,&lst_proie);
  afficher_ecosys(lst_proie,lst_predateur); 
  assert(liberer_liste_animaux(lst_predateur)==NULL);
  assert(liberer_liste_animaux(lst_proie)==NULL);
  return 0;
}
