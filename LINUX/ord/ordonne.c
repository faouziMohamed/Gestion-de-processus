#include "ordonne.h"
/**
* @faouzi_mohamed
* @smi_s4
* @2018_2019
*/

/**
* L'algorithme d'ordonnencement utilisé dans ce programme est juste le tourniquet,
* dont la réquisition dépend du quantum saisie. Pour FIFO, le quantum sera un nombre très grand
* pour le TOURNIQUET, ce sera l'utilisateur qui va le taper
*/


/**
* La complication retrouvée dans l'algorithme d'ordonnancement est de
* pouvoir faire la synchronisation entre des moments où un processus est élu, fait les ES,BLOQUé
* Ou bien le processus est venu mais n'a pas de temps d'utilisation de cpu, il possède uniquement
* un temps d'ES et que ce processus n'est pas le premier qui est chargé dans la ram.
*/

/**
* Le but de cette fonction est de trouver le premier processus qui ne possède pas d'utilisation
* du cpu et que sa date d'arrivée p.DA <= p1.DA (DA du premier processus élu) et p.DA < p1.DA
* @synchronisation_cpu_es
*/
/*
void doesntHaveCPU(_ListeTrnq *Tr,_ListeTrnq *EsB, ListeP liste)
{
	BCP p;


	if(liste.T[0].nbEX == 0) return;

	for(int j = 0; j < liste.nbproc; j++)
	{
		p = liste.T[j];
		if(p.DA >= liste.T[0].DA && p.DA <= liste.T[0].TEX)
	}
}


*/
Booleen estVide_Liste(_ListeTrnq *L)
{
	return L->Tete == NULL;
}

/* Fonction qui vérifie si un processus a terminé son temps de rotation */
Booleen aTermine(BCP p)
{
	return p.fin_es == -1;
}

Info_BCP *recherche(_ListeTrnq *L, int ID, int k, Etat e)
{
	int i = 1;
	Info_BCP *tmp = L->Tete;
	while(tmp != NULL )
	{
		if(tmp->p.ID == ID && tmp->E == e)
		{
			if(i == k) return tmp;
			else i++;
		}
		   tmp = tmp->suivant;
	}

	return NULL;
}


long effectuer_Les_ES(BCP *p, _ListeTrnq *Tr, ListeP liste, long _FIN_DERNIER_ES, long _TIMER)
{
	int m = p->esC;
	if( p->nbES > 0 )
	{
		//Si a ce moment un proc fait les ES, on met bloque puis calcul le moment de faire le ES
		if(_TIMER <= _FIN_DERNIER_ES)
		{
			//Bloqué à partir de [a = DA, b = _FIN_DERNIER_ES]
			if(p->nbEX == 0 && _FIN_DERNIER_ES != 0)
					 listeRepartie(Tr, *p, p->DA, _FIN_DERNIER_ES-1, bloque);
			//Bloqué à partir de [a = _TIMER, b = _FIN_DERNIER_ES]
			else    listeRepartie(Tr, *p, _TIMER, _FIN_DERNIER_ES-1, bloque);

			//ES à partir de [_FIN_DERNIER_ES, _FIN_DERNIER_ES + p->TES[m] ]
			listeRepartie(Tr, *p, _FIN_DERNIER_ES, _FIN_DERNIER_ES + p->TES[m]-1, es);
			//On redéfinie une nouvelle fin d'ES
			_FIN_DERNIER_ES   += p->TES[m] ;

			//On récupère la fin d'entrée sortie récente du processus
			p->fin_es = _FIN_DERNIER_ES;

		}
		else
		{

			//ES à partir de [a = _TIMER, b = a + p->TES[m] ]
			listeRepartie(Tr, *p, _TIMER, _TIMER + p->TES[m]-1, es);
			//On redéfinie une nouvelle fin d'ES
			_FIN_DERNIER_ES = _TIMER + p->TES[m];
			//On redéfinie une nouvelle fin d'ES
			p->fin_es       = _FIN_DERNIER_ES;
		}
		//On passe au temps d'entrée/Sortie suivante
		p->esC++;
	}

	return _FIN_DERNIER_ES;
}

void Ord_Tourniquet(_ListeTrnq *Tr, ListeP liste)
{
	//Hardware peripherique = {libre,libre}; /* CPU libre, interface ES libre (Option avancé pour bien réaliser la synchronisation)*/
	int j               =  0   ;	 /* Compteur du nombre de processus                                     */
	int i               =  0   ;	 /* Compteur dans le tableau des TEX                                    */
	int m               =  0   ;	 /* Compteur dans le tableau des TES                                    */
	int _FINI_EXECUTION_=  0   ;	 /* Compteur desprocessus qui ont terminés leur opérations              */
 	long _FIN_DERNIER_ES=  0   ;	 /* Variable qui va prendre le dernier _TIMER + TES                     */
	long _TIMER         =  liste.T[0].DA ;/* Horloge du processeur pour l'ordonnancement                    */
    BCP *p              = NULL ;	 /* Variable qui va prendre le processus courant afin d'alleger le code */
	int a = 1, prem = -1; int Skip = 0;
	
	do //Cette boucle va se repeter tant que tous les processus n'ont pas consomé tous leurs TEMPS(EX + ES)
	{
		while(j < liste.nbproc) //Boucle contenant l'ordonnancement
		{
			p = &liste.T[j]; /*  Le processus courant  */
			i = p->eluC;     /*  Le temps EX  courant  */
			m = p->esC;      /*  Le temps ES  courant  */


			/*Cas où le temps d'éxecution restant <= Quantum*/
			if( ( (i < p->nbEX  && p->TEX[i] <= Tr->Q) ) || (p->nbEX == 0 && m < p->nbES) )
			{
				//Si cette condition est vérifié, on saute le switch et on directement verfifier les ES
				if((i >= p->nbEX) || p->nbEX == 0 )	goto cond_ES;
				//Vérifiacation si le processus a ce moment ne fait pas dES ou n'est pas bloqué
				switch(etatProc(Tr,*p,_TIMER) == es || etatProc(Tr,*p,_TIMER) == bloque)
				{

					case FAUX : /* Le processus n'est pas entrain de faire les ES ou n'est pas bloqué */
						//Si le processus n'est pas encore chargé ds la RAM, tous ces suivant ne le sont aussi, on recommence la boucle while
						if(p->DA > _TIMER) 
						{ 	
							Skip++;//On compte le nombre de fois ou on afais le skip
							j = liste.nbproc;
							if(Tr->Q == __FIFO)_TIMER++; 
							else if(Skip == liste.nbproc)
							{
								Skip = 0;
								_TIMER++;
							}
							goto fin_while;
						}
						if(liste.nbproc == 1 && etatProc(Tr,*p,p->fin_es-1) == es) //Cas particulier
							listeRepartie(Tr,*p, p->fin_es, p->fin_es + p->TEX[i]-1, elu);
						else
							listeRepartie(Tr,*p, _TIMER, _TIMER + p->TEX[i]-1, elu);  //Cas générale
						//On met à l'etat prêt tous les autres processus qui n'on pas terminé et qui ne font pas ES
						for (int r = 0; r < liste.nbproc; r++)
						{
							BCP processus = liste.T[r];
							//On doit ignorer le processus qui est élu OU/ET un processus qui n'est pas encore chargé dans la RAM ou/ET ceux qui ont terminé
							if(aTermine(processus) == VRAI || processus.ID == p->ID || processus.DA > _TIMER+ p->TEX[i] ) continue;
							else if(processus.eluC<processus.nbEX && (etatProc(Tr,processus,_TIMER) == -1) )
							{
								/*Si c'est la première fois que le processus va être pret, on commence à partir de sa date d'arrivé*/
								if( processus.ID != liste.T[0].ID && recherche(Tr,processus.ID,1,pret) == NULL )
									listeRepartie(Tr,processus, processus.DA, _TIMER+p->TEX[i]-1, pret);
								else /*Ce else signifie que le processus n'a pas encore fait d'E/S, donc rien a synchroniser*/
								listeRepartie(Tr,processus, _TIMER, _TIMER+p->TEX[i]-1, pret);
							}
							else if(etatProc(Tr,processus,_TIMER) == es && processus.fin_es>=_TIMER && processus.fin_es<_TIMER + p->TEX[i]-1)
							{
								/*Test pour synchroniser les temps de l'utilisation du processeur et le per.ES par le processus
								Ce test est fait pour éviter que le processus soit en 2 etat à la fois*/
								listeRepartie(Tr,processus, processus.fin_es, _TIMER+p->TEX[i]-1, pret);
							}
						}						
						if(liste.nbproc == 1 && etatProc(Tr,*p,p->fin_es-1) == es) //Cas particulier
						_TIMER = p->fin_es + p->TEX[i];
						else	
						_TIMER += p->TEX[i];
						p->TEX[i] = 0;
						break;

					case VRAI : /* Le processus est entrain de faire les ES ou est bloqué*/
						a = 1, prem = -1;
						for(int r = 0; r < liste.nbproc; r++)
						{
							if(aTermine(liste.T[r]) == VRAI || etatProc(Tr,liste.T[r],_TIMER) != es) continue;
							if(etatProc(Tr,liste.T[r],_TIMER) == es)
							{
								a *= 1;
								if(prem == -1) prem = r;
							}
							else a *= 0;
						}
						if(a == 1) _TIMER ++;
						goto fin_while;
				}/* Fin du switch() */

				/*Cas où le processus possède des entrées sorties*/
	cond_ES :	_FIN_DERNIER_ES = effectuer_Les_ES(p, Tr, liste, _FIN_DERNIER_ES, _TIMER);
				i = p->eluC;
				m = p->esC;
				//On passe au temps d'execution suivante
				p->eluC++;
				//On vérifie si le processus a terminé sa rotation
				if(p->eluC >= p->nbEX && p->esC >= p->nbES )
			    {
			    	if(m>p->nbES) m = p->nbES-1;
			    	listeRepartie(Tr, *p, _TIMER, _TIMER + p->TES[m]-1, termine);
			    	p->fin_es = -1;
			    	//On compte le nombre de processus qui ont terminé pour pouvoir quitter la fonction
					_FINI_EXECUTION_++;
			 	}
			}
			//Si le temps d'execution > quantum
			else if( (i<p->nbEX) && p->TEX[i] > Tr->Q)
			{
				switch(etatProc(Tr,*p,_TIMER) == es || etatProc(Tr,*p,_TIMER) == bloque)
				{
					case FAUX : /* Le processus n'est pas entrain de faire les ES ou n'est pas bloqué */
						//Si le processus n'est pas encore chargé ds la RAM, tous ces suivant ne le sont aussi, on recommence la boucle while
						if(p->DA > _TIMER) 
						{ 	
							Skip++; //On compte le nombre de fois ou on afais le skip
							j = liste.nbproc;
							if(Tr->Q == __FIFO)_TIMER++; 
							else if(Skip == liste.nbproc)
							{
								Skip = 0;
								_TIMER++;
							}
							goto fin_while;
						}
						if(liste.nbproc == 1 && etatProc(Tr,*p,p->fin_es-1) == es) //Cas particulier
							listeRepartie(Tr,*p, p->fin_es, p->fin_es + p->TEX[i]-1, elu);
						else
							listeRepartie(Tr,*p, _TIMER, _TIMER + Tr->Q-1, elu);  //Cas générale
						p->fin_es = 0;
						//On met à l'etat prêt tous les autres processus qui n'on pas terminé et qui ne font pas ES
						BCP processus;
						for (int r = 0; r < liste.nbproc; r++)
						{
							processus = liste.T[r];
							//On doit ignorer le processus qui est élu OU/ET un processus qui n'est pas encore chargé dans la RAM ou/ET ceux qui ont terminé
							if(aTermine(processus) == VRAI || processus.ID == p->ID || processus.DA > _TIMER+Tr->Q ) continue;
							else if(processus.eluC<processus.nbEX && (etatProc(Tr,processus,_TIMER) == -1) )
							{
								/*Si c'est la première fois que le processus va être pret, on commence à partir de sa date d'arrivé*/
								if( processus.ID != liste.T[0].ID && recherche(Tr,processus.ID,1,pret) == NULL )
								listeRepartie(Tr,processus, processus.DA, _TIMER+Tr->Q-1, pret);
								else /*Ce else signifie que le processus n'a pas encore fait d'E/S, donc rien a synchroniser*/
									listeRepartie(Tr,processus, _TIMER, _TIMER+Tr->Q-1, pret);
							}
							else if(etatProc(Tr,processus,_TIMER) == es && processus.fin_es>=_TIMER && processus.fin_es<_TIMER+Tr->Q-1 )
							{
								/*Test pour synchroniser les temps de l'utilisation du processeur et le per.ES par le processus
								Ce test est fait pour éviterque le processus soit en 2 etat  à la fois*/
								listeRepartie(Tr,processus, processus.fin_es, _TIMER+Tr->Q-1, pret);
								liste.T[r].fin_es = 0;
							}
						}
						if(liste.nbproc == 1 && etatProc(Tr,*p,p->fin_es-1) == es) //Cas particulier
						{
							_TIMER    = p->fin_es + p->TEX[i];
							p->TEX[i] = 0;
						}
						else 
						{
							_TIMER    += Tr->Q;
							p->TEX[i] -= Tr->Q;
						}
						break;
					case VRAI : /* Le processus est entrain de faire les ES */
						//if(j == liste.nbproc-1) _TIMER++;
						a = 1, prem = -1;
						for(int r = 0; r < liste.nbproc; r++)
						{
							if(aTermine(liste.T[r]) == VRAI || etatProc(Tr,liste.T[r],_TIMER) != es) continue;
							if(etatProc(Tr,liste.T[r],_TIMER) == es)
							{
								a *= 1;
								if(prem == -1) prem = r;
							}
							else a *= 0;
						}
						if(a == 1) _TIMER++;
						goto fin_while;
				}/* Fin du switch() */
			}
		fin_while:
			/** On passe au processus suivant j++ **/
			j++;
		}/** Fin du boucle while() **/
		j = 0;
	}while( _FINI_EXECUTION_ < liste.nbproc  );
}

//Création du liste d'ordonnancement du liste d'ordonnancement
void listeRepartie(_ListeTrnq *Tr, BCP p, long disp, long fin, Etat e)
{
	//Création d'un nouveau élément
	Info_BCP *nouveau = (Info_BCP*)malloc(sizeof(Info_BCP));

	nouveau->E       = e;
	nouveau->deb     = disp;
	nouveau->fin     = fin ;
	nouveau->p       = p  ;
	nouveau->suivant = NULL;



	if(estVide_Liste(Tr) == VRAI) //estVide_Liste(Tr) return VRAI(Tr est vide), sinon FAUX
	{
		Tr->nbElmnt = 1;
		Tr->Tete  = nouveau;
		Tr->Queue = nouveau;
	}
	else
	{
		Tr->nbElmnt += 1;
		Tr->Queue->suivant = nouveau; //On sauvegarde dans la Tr chainé le nouveau élément
		Tr->Queue          = nouveau; //On garde l'adresse du dernier élément qui est nouveau
	}
}

//Libération du liste d'ordonnancement
void libererListeRepartie(_ListeTrnq *Tr)
{
	Info_BCP *detruire = NULL;
	while(Tr->nbElmnt > 0 && Tr->Tete != NULL)
	{
		detruire = Tr->Tete;
		Tr->Tete = Tr->Tete->suivant;
		Tr->nbElmnt--;
		free(detruire);
	}
	Tr->Queue = NULL;
}


Etat etatProc(_ListeTrnq *L,BCP p, long time)
{
	if(estVide_Liste(L) == FAUX)
	{
		Info_BCP *tmp = L->Tete;
		while(tmp != NULL )
		{
			if(tmp->p.ID == p.ID  && (tmp->deb<= time && tmp->fin >=time))
			return tmp->E;

			tmp = tmp->suivant;
		}

		return -1;
	}
	else  return -1;
}



void sortieEtatSur_Ecran(long time,long finTime, Etat e, BCP *p)
{
	switch(e)
	{
		case elu       :
			printf("\n A T = [%ld -- %ld] \n",time,finTime );

			(p->ID < 10) ? printf("\t P%d  est %sELU%s\n",p->ID,jaune,init)
			:              printf("\t P%d est %sELU%s\n",p->ID,jaune,init );   break;

		case pret      :
			(p->ID < 10) ? printf(" \t P%d  est %sPRET%s\n",p->ID,vert,init)
			:			   printf(" \t P%d est %sPRET%s\n",p->ID,vert,init );  break;

		case es        :
			(p->ID < 10) ? printf(" \t P%d  fait %sES%s\n",p->ID,bleu,init)
			:              printf(" \t P%d fait %sES%s\n",p->ID,bleu,init );   break;
		case bloque    :
			(p->ID < 10) ? printf(" \t P%d  est %sBLOQUE%s\n",p->ID,rose,init)
			:              printf(" \t P%d est %sBLOQUE%s\n",p->ID,rose,init );break;

		case bloque + 5:
			printf(" A T = %ld\n",time);
			(p->ID < 10) ? printf("\t P%d  est %sBloque%s\n",p->ID,rose,init )
			:              printf("\t P%d est %sBloque%s\n",p->ID,rose,init );
														printf("\t|\n\t|_____");break;
		case es+5      :
			printf("  %sA T = %ld%s : ",rose,time,init);
			printf("P%d Commencera les %sES%s\n",p->ID,bleu,init);               break;
		case termine   :
			printf("\n A T = %ld\n",time);
			printf("\t P%d %sTerminera%s son execution\n",p->ID,rouge,init);     break;
	}

}
















/*
			if(p->nbEX == 0 && p->DA >= liste.T[0].DA && p->DA <= liste.T[0].TEX[0] && etatProc(Tr,liste.T[0],p->DA) != es)
			{
				printf(" GRAND\n");
				_FIN_DERNIER_ES = 0;
				while(m<p->nbES)
				{
					_FIN_DERNIER_ES += p->TES[m];
					m++;
				}

				listeRepartie(Tr,EsB, *p, p->DA, _FIN_DERNIER_ES, es);
				p->esC = m;
			}
*/



