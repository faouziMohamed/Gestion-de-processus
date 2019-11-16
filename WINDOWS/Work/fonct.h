#ifndef FONCT_H
#define FONCT_H

#include "../Effects/effects.h"
#include     "../ord/ordonne.h"
#include <sys/types.h>
#include    <dirent.h>
#include      <time.h>


/****************************************************************************/
				/*\   les prototype des fonctions   \*/
/****************************************************************************/


/*Vérification et extra*/
void ERROR_ALLOC();
void Continuer();
int la_liste_est_vide(ListeP L);
int la_liste_est_Pleine(ListeP L);

//OPération mémoire
void initialiser_La_Liste(ListeP *L,int NMAX);
BCP  *reallocation(int old_size,int size_to_add, ListeP *L);
void liberationDeLaMemoire(ListeP *L);
void __endOfProgram(char *string, ListeP *L);

//Tri d'un tableau de BCP
void fusionner(BCP tab[], int debut, int milieu, int fin);
void triFusion_BCP(BCP tab[],int debut,int fin);

/*Opération sur l'afichage*/
void une_ligne_du_Schema_temporel(BCP p);
void afficher_Le_Schema_Temporelle(ListeP l);
void faireFIFO_Ou_Tourniquet(_ListeTrnq *Tr, ListeP lst, char *algo); //Lancement de la simulation
void __horloge_TIMER(int n); //Utilisé sur le digramme de Gant
void diagramme_de_GANT(_ListeTrnq *Tr, ListeP *liste);
/** Travaux sur les fichiers **/
int plusGrandID(ListeP L);
long nbligne(FILE *stream);
FILE *fprintp(BCP tab[], int deb, int fin, FILE *stream);
void fscanp(ListeP *L);
/*Opération du menu Principal */
BCP scanp();
void ajouter_Depuis_clavier(ListeP *L, int add_a_lot);
void Afficher_En_Resume(ListeP L, _ListeTrnq *Tr, char type ); /*Afficher les BCP         */
void Supprimer(ListeP *L);                      /*Supprimer un BCP au début*/



#endif

