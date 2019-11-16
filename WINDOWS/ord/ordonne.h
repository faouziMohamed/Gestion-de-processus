/**
* 
* Ce Fichier contient uniquement l'algorithme de touriquet et ses dépendances
* (des fonctions utilisés sur cet algorithme) 
* @author faouzi
* Fichier écris par : MOHAMED FAOUZI FAOUZOUDINE
* Email 			: faouzoudine.mohamedfaouzi@uit.ac.ma 
*****************************************************************/

#ifndef _MACRO_ORD
#define _MACRO_ORD
#include "../Effects/effects.h"

/**************** Déclaration des de structures de données utilisés dans le projet ********************/
/************************************************************************************************************/

/* Les structures (Et listes chainés) */
typedef struct Info_BCP Info_BCP;
typedef struct BCP BCP;

/* Les Listes */
typedef struct ListeP ListeP;
typedef struct _ListeTrnq _ListeTrnq;

/* Type énumeré */
typedef enum Booleen{ FAUX, VRAI } Booleen;
typedef enum Etat{termine, bloque, es, pret, elu }Etat;

/*** Structure première (comme matière première ) de ce projet ****/
struct BCP
{
	int       ID;
	int       DA;
	int   TEX[2];
	int   TES[2];
	int     nbEX;
	int     nbES;
	int     eluC; 
	int      esC; 
	long  fin_es;
};

	/* Liste contenant tous les processus*/
struct ListeP
{
	int nbMAX; 
	int nbproc;
	BCP *T;
	FILE *f; //Fichier utilisé pour le sauvegarde des processus sur le pc
};

/***** Etat d'un BCP a un instant x compris entre [deb,fin], (stocké sous forme de liste chainé) *****/
struct Info_BCP
{
	Etat  E;
	int deb;
	int fin;
	BCP p;
	Info_BCP *suivant;
};


/*** Structure consistant à garder la tête et la queue d'une liste d'Info_BCP *****/
	struct _ListeTrnq
	{
		long Q;   //Le Quantum
		unsigned nbElmnt; //Nombre d'élément de cette Liste
		Info_BCP *Tete;
		Info_BCP *Queue;
	};


#define __FIFO 999999999

/*** PROTOTYPES DES FONCTIONS ***/

	Info_BCP *recherche(_ListeTrnq *L, int ID, int k, Etat e); //Retourne l'adresse d'un processus selon l'etat voulu et son ordre
	Booleen estVide_Liste(_ListeTrnq *L);
	Booleen aTermine(BCP p);
	Etat etatProc(_ListeTrnq *L, BCP p, long time);               //retourne l'etat d'un processus

	void sortieEtatSur_Ecran(long time,long finTime, Etat e, BCP *p);
	long* _RotateTime(BCP p, long rotate[], int indice, long addTime);
	long effectuer_Les_ES(BCP *p, _ListeTrnq *Tr, ListeP liste, long _FIN_DERNIER_ES, long _TIMER, int indice,long rotate[]); //éguillage de l'entrée sortie
	void listeRepartie(_ListeTrnq *Tr, BCP p, long disp, long fin, Etat e); //Ajoute un processus dans la liste d'ordonnancement
	void libererListeRepartie(_ListeTrnq *Tr);
	long* Ord_Tourniquet(_ListeTrnq *Tr, ListeP liste, char *typeAlgo);   //Algorithme d'ordonnancement

#endif
