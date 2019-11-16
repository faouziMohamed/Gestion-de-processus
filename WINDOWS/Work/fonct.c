#include "fonct.h"

extern int First_ID;
/**
*Définition des Fonctions qui sont utlisé dans le Programme*/




int   la_liste_est_vide(ListeP L) { return L.nbproc  ==       0; }
int la_liste_est_Pleine(ListeP L) { return L.nbproc  >= L.nbMAX; }


void ERROR_ALLOC()
{
	printf(" ERREUR : VOTRE MEMOIRE RAM EST PLEINE <<%sOPERATION D'AJOUT IMPOSSIBLE%s>> \n",rouge,init);
	exit(EXIT_FAILURE);
}
/********Initialisation d'une liste de Processus*************/
void initialiser_La_Liste(ListeP *L,int NMAX)
{
	L->nbMAX  = NMAX;
	L->nbproc =    0;
	L->f = NULL;
	L->T = (BCP*)calloc(NMAX,sizeof(BCP));
	if(L->T == 0) ERROR_ALLOC();
}

/**********Réallocation d'une nouvelle zone mémoire**********/
BCP *reallocation(int old_size,int size_to_add, ListeP *L)
{
	BCP *T = L->T;
	BCP * tab = (BCP*)calloc(old_size,sizeof(BCP));

	//Copie des élements du du tableau vers tab

	for(int i = 0; i< old_size; i++) tab[i] = T[i];

	//Libération de l'ancien tableau
	free(T);

	//Création d'un nouveau tableau de taile = old_size + size_to_add
	T = (BCP*)calloc(old_size + size_to_add, sizeof(BCP));

	//Copie des éléments de tab vers le nouveau tableau
	for(int i = 0; i< old_size; i++) T[i] = tab[i];

	//Libération de tab
	free(tab);
	return T;
}

/***libération d'une zone mémoire alloué dynamiquement***/
void liberationDeLaMemoire(ListeP *L)
{
	free(L->T);
	L->T      = NULL;
	L->nbproc =    0;
}

void  __endOfProgram(char *string, ListeP *L)
{

	Color(7,0);
	clear();
	printf("\n\n\n\n\n\t\t\t\t%s%s...%s\n",jaune,string,init);
	

	//printf("\t\t\t\t");
	printf("\t\t\t\t%s ",bgBC);

	//Vertical
	for(int i = 0; i<20;i++)
	{
		//printf("__");
		printf("%s  %s",bgVrt,init);
	}
	printf("%s \e[0m",bgBC);

	Sleep(0200);
	for(int i = 0; i< 21; i++) 
	{
		printf("\b \b\b \b");
		Sleep(0200);
	}
	printf("\n");

	printf("\t\t\t\t\t\t\tA BIENTO %s!%s\n",vert,init);
	if(L->T != NULL)liberationDeLaMemoire(L);
	if(L->f != NULL)fclose(L->f);
	printf("\n");
}

/*******Saisie des informations d'un Processus***********/
BCP scanp()
{
	/**
	* Certains des champs de ce BCP, sont uniquement requis
	* par l'algorithme d'ordonnancement, D'où l'Initialisationcomplète du Processus
	**/
	BCP new = {0,0,{0,0},{0,0},0,0,0,0,-2};
	int i   = 0;

	//Assignation de l'ID automatiquement
	new.ID = First_ID++;

	printf("\n\t\t\t### Saisie des Iformations Du Processus d'ID %d\n",new.ID);

	printf("\t\t\t\t Date d'arrivee (%sDA%s) : ",bleu,init);
	scanf("%d",&new.DA);

  /********************LES ENTREES/SORTIES********************/


	do{
		printf("\t\t\t\t   Saisir Le nombre de %stemps d'Entree/Sortie (E/S)%s (%smax 2%s) : ",vert,init,jaune,init);
		scanf("%d",&new.nbES);
	}while(new.nbES < 0 || new.nbES>2);

	while(i < new.nbES)
	{
		printf("\t\t\t\t   Donnez le %stemps d'E/S%s numero %d : ",vert,init,i+1);
		scanf("%d",&new.TES[i]);

		if(new.TES[i] <= 0) printf("\t\t\t Vous devez saisir un nombre Positif\n");
		else i++;
	}

  /********************UTILISATION DU CPU********************/
	if(new.nbES != 0)
	{


		do{
			printf("\t\t\t\t   Saisir Le nombre de %stemps d'execution%s (%smax 2%s) : ",jaune,init,jaune,init);
			scanf("%d",&new.nbEX);
		}while(new.nbEX < 0 || new.nbEX > 2);

		i = 0;
		while(i < new.nbEX)
		{
			printf("\t\t\t\t  Donnez le %sTemps d'execution%s numero %d : ",jaune,init, i+1);
			scanf("%d",&new.TEX[i]);

			if(new.TEX[i] <= 0) printf("\t\t\t Vous devez saisir un nombre Positif\n");
			else i++;
		}
	}
	else
	{
		while(new.TEX[0] <= 0)
		{
			printf("\t\t\t\t Donnez le %sTemps d'execution%s du processus : ",jaune,init);
			scanf("%d",&new.TEX[0]);
		}
		new.nbEX = 1;
	}


	if(new.nbEX < 2)
	{
		new.TES[0] += new.TES[1];
		new.nbES = 1;
	}
	printf("\n");
	return new;
}

/****Nombre de ligne sur un fichier contenant des BCP****/
long nbligne(FILE *stream)
{
	long nbligne = 0;
	char c;
	while( (c = fgetc(stream)) != EOF) if(c == '\n') nbligne++;
	//On repositionne le curseur du fichier a 0
	fseek(stream,0,0);
	return nbligne;
}

/***Lecture des processus à partir d'un fichier***/
void fscanp(ListeP *L)
{
	long n = -1;
	char file[200];
	FILE *stream;
	Color(7,0);
	clear();
	printf("\n\n\t\t\t\t  %s  Pour retourner Dans le menu Principal tapez %s-1  %s\n\n",bgRgN, blanc, init);
	printf("\n\n\t\t\t   %s Si le fichier n'est pas dans le meme repertoire que le programme\n",bleu);
	printf("\t\t\t\t\tVous donnerez un chemin absolu du fichier\n\n%s",init);

	do{
		printf(" Veuillez saisir le nom du fichier : ");
		scanf("%s",file);

		if(strcmp(file,"-1") == 0) return;
		//Vérification si le fichier existe
		stream = fopen(file, "r");

		if(stream == NULL)
			printf("%s%s Le fichier saisie n'existe pas %s!\
  Verifiez le chemin du fichier puis reessayez%s\n\n",bgBlanc,noir,rouge,init);
		else
		{
			if( (n = nbligne(stream)) == 0)
			printf("%s%s Le fichier saisie est vide !%s\n\n",bgBlanc,noir,init);
		}
	}while(stream == NULL || n == 0);

	if(la_liste_est_vide(*L))
	{
		//Allocation Dynamique de la mémoire
		initialiser_La_Liste(L,n);
	}
	else if(la_liste_est_Pleine(*L))
	{
		//Reallocation Dynamique de la mémoire
		L->T = reallocation(L->nbproc, n, L);
		//Augmentation de la taille Maximale du tableau
		L->nbMAX += n;
	}
	else if(n + L->nbproc>= L->nbMAX)
	{
		L->T = reallocation(L->nbproc, n, L);
		L->nbMAX = n + L->nbproc;
	}

	BCP p;
	int new_ID;
	int i =L->nbproc; 
	if(L->nbproc)
	{
	 	new_ID = plusGrandID(*L) + 1;

		//Récupération et ajout sur le tableau
		while(fscanf(stream,"%d %d %d %d %d %d %d %d %d %d %ld",&p.ID,&p.DA,&p.TEX[0],\
			&p.TEX[1],&p.TES[0],&p.TES[1],&p.nbEX,&p.nbES,&p.eluC,&p.esC,&p.fin_es) != EOF)
		{
			p.ID = new_ID++;
			L->T[L->nbproc++] = p;
		}
	}
	else
	{
		//Récupération et ajout sur le tableau
		while(fscanf(stream,"%d %d %d %d %d %d %d %d %d %d %ld",&p.ID,&p.DA,&p.TEX[0],\
			&p.TEX[1],&p.TES[0],&p.TES[1],&p.nbEX,&p.nbES,&p.eluC,&p.esC,&p.fin_es) != EOF)
		{
			L->T[L->nbproc++] = p;
		}
	}
	L->f = fprintp(L->T,i,L->nbproc,L->f);
	//Fermeture du fichier
	fclose(stream);
}

int plusGrandID(ListeP L)
{
	int MAX_ID = 0;
	for(int i = 0; i < L.nbproc; i++)
		if(L.T[i].ID > MAX_ID){ MAX_ID = L.T[i].ID; }
	return MAX_ID;
}


/*******Sauvegarde automatique des processus sur un fichier********/
FILE *fprintp(BCP tab[], int deb, int fin, FILE *stream)
{
	FILE *save = NULL;
	char str[20] = "save.txt";
	int i = 1;


	if(stream == NULL)//Il n'ya pas encore un fichier pour ce programme
	{
		//Création du répertoire "_Sauvegarde"
		if(opendir("_Sauvegarde") == NULL) mkdir("_Sauvegarde");

		//Vérification si le fichier n'existe pas
		save = fopen("_Sauvegarde\\save.txt","r");
		if(save == NULL)
		{
			save = fopen("_Sauvegarde\\save.txt", "a+");
		}
		else
		{
			while(1)
			{
				//save1.txt, save2.txt, save3.txt,...
				sprintf(str,"_Sauvegarde\\save%d.txt",i++);
				//Vérification si le fichier n'existe pas
				save = fopen(str,"r");
				if(save == NULL)
				{
					save = fopen(str,"a+");
					break;
				}
				else fclose(save);
			}
		}
	}
	else save = stream;
	BCP p;
	while(deb<fin)
	{
		p = tab[deb++];
		/*** Affichage du processus dans le fichier save.txt ***/
			fprintf(save, "%d %d %d %d %d %d %d %d %d %d %ld\n",p.ID,p.DA,p.TEX[0],\
				p.TEX[1],p.TES[0],p.TES[1],p.nbEX,p.nbES,p.eluC,p.esC,p.fin_es);
	}
	return save;
}


/*******************Ajout de plusieurs Processus dans le tbaleau**********************/
void ajouter_Depuis_clavier(ListeP *L, int add_a_lot)
{
	couleurFondNoir();
	int n = 0;

	//Dans le cas si on va jouter plusieurs Processus
	if(add_a_lot)
	{
		printf("\n\n\t\t\t\t%s Pour retourner Dans le menu Principal tapez %s0 %s\n\n",bgRgN, blanc, init);
		do
		{
			printf("%s Saisissez le nombre de Processus (%sMinimum 1%s%s) :%s ",bgJne,rose,init,bgJne,init);
			scanf("%d",&n);
		}while(n<0);
		if(n == 0) return;
	} //Dans le cas si on va ajouter uniquement une seule processus
	else n = 1;

	if(la_liste_est_vide(*L))
	{
		//Allocation Dynamique de la mémoire
		initialiser_La_Liste(L,n);
	}
	else if(la_liste_est_Pleine(*L))
	{
		//Reallocation Dynamique de la mémoire
		L->T = reallocation(L->nbproc, n, L);
		//Augmentation de la taille Maximale du tableau
		L->nbMAX += n;
	}
	else if(n + L->nbproc >= L->nbMAX)
	{
		L->T = reallocation(L->nbproc, n, L);
		L->nbMAX = n + L->nbproc;
	}


	int k = L->nbproc;
	for (int i = k; i < k + n; ++i)
	{
		printf("\n%s__________ Processus Numero %d __________%s\n",bleu ,L->nbproc + 1,init);
		/*Ajout dans la liste des processus*/
		L->T[L->nbproc++] = scanp();
	}
	L->f = fprintp(L->T,k,L->nbproc,L->f);
}


/*******************Suppression en tête d'un processus***************************/
void Supprimer(ListeP *L)
{
	if(la_liste_est_vide(*L))
	{
		clear();
		printf("\n\n\n\t\t\t\t DESOLE LE TABLEAU EST VIDE POUR LE MOMENT\n\n");
		printf("\t\t\t\t           Il n'y a rien a Supprimer\n");
		return;
	}

	int n = 0;
	_ListeTrnq Tr  = {__FIFO,0,NULL,NULL};
	Afficher_En_Resume(*L,&Tr, 'b');


	printf("\n\n\t\t\t\t\t%s Supression au debut de la liste %s\n\n",bgBcN, init);
	do
	{
		printf(" Saisissez le nombre de Processus a supprimer (%sMaximum %d%s) : ",rose,L->nbproc,init);
		scanf("%d",&n );
	}while(n<0 || n>L->nbproc);
	if(n==0) return;
	else
	{
		if(n == L->nbproc) L->nbproc = 0;
		else
		{

			for(int i = 0; i< L->nbproc-n; i++)
			{
				L->T[i] = L->T[i+n];
			}
			L->nbproc -= n;
		}
	} 
}



/*******************Fonction de tri d'un tableau de processus *******************/
void triFusion_BCP(BCP tab[],int debut,int fin)
{
	int milieu = 0;

	if(debut==fin) return;

	milieu=(debut+fin)/2;

	//On divise le tableau en deux sous tableaux
	triFusion_BCP(tab,debut,milieu);
	triFusion_BCP(tab,milieu+1,fin);
	//On va les fusionner et les trier en même temps
	fusionner(tab,debut,milieu,fin);
}
//Tri récursive par fusion d'un tablea Dans cette liste le champ du quantum ne nous intéresse pas, on va juste le mettre à 0*u
void fusionner(BCP tab[], int debut, int milieu, int fin)
{
	BCP temp[fin+1];
	int compt,cmpt1,cmpt2; //compt pour tab, cmpt1 pour la première moitié et cmpt2 pour la seconde


	//Copie des deux moitié dans temp[]
	for(compt=debut; compt<=fin;compt++) temp[compt]=tab[compt];

	//On fusionne les deux moitiés dans tab[]
	for(cmpt1=compt=debut,cmpt2=milieu+1; (cmpt1<=milieu) && (cmpt2<=fin); compt++)
	{
		if(temp[cmpt1].DA<temp[cmpt2].DA)
		{
			tab[compt]=temp[cmpt1];cmpt1++;
		}
		else if(temp[cmpt1].DA == temp[cmpt2].DA && temp[cmpt1].TEX[0]<temp[cmpt2].TEX[0])
		{
			tab[compt]=temp[cmpt1];cmpt1++;
		}
		else
		{
			tab[compt]=temp[cmpt2];cmpt2++;
		}
	}

	//On recopie le reste dans tab
	if(cmpt1<=milieu)
	{
		while(cmpt1<=milieu)
		{
			tab[compt]=temp[cmpt1];
			cmpt1++;compt++;
		}
	}
	else if (cmpt2<=fin)
	{
		while(cmpt2<=fin)
		{
			tab[compt]=temp[cmpt2];cmpt2++;compt++;
		}
	}
}

/************************Affichage d'une liste de Processus**********************/
void Afficher_En_Resume(ListeP L, _ListeTrnq *Tr, char type )
{
	couleurFondNoir();
	activer_Les_Couleurs();
	if(la_liste_est_vide(L))
	{
		clear();
		printf("\n\n\n\t\t\t\t DESOLE LE TABLEAU EST VIDE POUR LE MOMENT\n\n");
		printf("\t\t\t\t           Il n'y a rien a Afficher\n");
		return;
	}

	printf("%s\n",init);clear();

	taille_Affichage();
	printf("\n\n\t\t\t\t%s Pour retourner Dans le menu Principal tapez %s0 %s\n\n",bgRgN, blanc, init);
	int ex  = 0, es = 0, i, nbchar = 0;
	BCP p;

	barresup(); //Affiche une ligne
	entete();   //Entete du tableau Affiché

	ListeP list = {L.nbproc,L.nbMAX};
	
	list.T = calloc(L.nbMAX,sizeof(BCP));
	for(int i = 0; i<L.nbproc; i++) list.T[i] = L.T[i];
	triFusion_BCP(list.T,0,L.nbproc-1);
	
	long *_TempsRotF = Ord_Tourniquet(Tr,list,"FIFO");


	for ( i = 0; i < L.nbproc; i++)
	{
		p = L.T[i];

		i == L.nbproc-1 ?printf("\e[4m"):printf("");

		ex  = p.TEX[0]+p.TEX[1];
		es  = p.TES[0]+p.TES[1];
		/************************************Numéro************************************/
		if(i+1>= 10) nbchar += printf("|   %d      ",i+1);
		else         nbchar += printf("|    %d      ",i+1);
		/**************************************ID**************************************/
	         if(p.ID >= 100)           nbchar += printf("    %d            ",p.ID);
		else if(p.ID>=10 && p.ID <100) nbchar += printf("     %d            ",p.ID);
		else if(p.ID <10)	           nbchar += printf("      %d            ",p.ID);
		/*******************************Date d'arrivée*********************************/
		     if(p.DA >= 100)           nbchar += printf("   %d",p.DA);
		else if(p.DA>=10 && p.DA <100) nbchar += printf("    %d",p.DA);
		else if(p.DA <10)              nbchar += printf("     %d",p.DA);
		/*******************************Temps d'execution*******************************/
			if(ex >= 100)              nbchar += printf("                   %d",ex);
		else if(ex>=10 && ex <100)     nbchar += printf("                    %d",ex);
		else if(ex <10)   		       nbchar += printf("                     %d",ex);
		/****************************Temps d'Entrée/sortie*******************************/
			if(es >= 100)              nbchar += printf("             %d",es);
		else if(es>=10 && es <100)     nbchar += printf("              %d",es);
		else if(es <10)                nbchar += printf("               %d",es);
		/*******************************Somme des 2 Temps********************************/
			 if(_TempsRotF[i] >= 100)                    nbchar += printf("               %ld",_TempsRotF[i] );
		else if(_TempsRotF[i]>=10 && _TempsRotF[i] <100) nbchar += printf("                %ld",_TempsRotF[i] );
		else if(_TempsRotF[i] <10)                       nbchar += printf("                 %ld",_TempsRotF[i] );



		if(i == L.nbproc-1)
		{
			for(int j = 0;j < 120 - nbchar;j++ ) printf("_");
			printf("\e[0m|\n");
		}
		else
		{
			for(int j = 0;j < 120 - nbchar;j++ ) printf(" ");
			printf("|\n");
		}

		nbchar = 0;
	}

	/***REGLER LE PROBLEME DE TOURNIQUET SUR L'AFFICHAGE***/
	free(_TempsRotF);
	libererListeRepartie(Tr);

	if(type == 'b') return;
	long *_TempsRotT = NULL;

	char ch[2] = "0";
	while(1)
	{
		if(ch[0] < '0' && ch[0] > '2') printf("\n\n\t\t\t\t\t\e[40;31m Ce choix n'existe pas [_INCORRECT_CHOICE_ ] \e[0;30m");
		printf("\n\n\t\t%s Pour retourner Dans le menu Principal tapez %s0 %s",menuAff, jaune, init);
		printf("\n\t\t%s Pour Afficher le schema temporel tapez %s1 %s",menuAff, jaune, init);
		printf("\n\t\t%s Pour Afficher le schema temporel trie par date d'arrivee tapez %s2 %s\n\n",menuAff, jaune, init);
		printf("\t\t Votre choix : ");
		scanf("%s",ch);

		switch(ch[0])
		{
			case '0' : free(list.T);return;
			case '1' : clear(); afficher_Le_Schema_Temporelle(L);   break;
			case '2' : clear(); afficher_Le_Schema_Temporelle(list);break;
			case '3' : clear(); _TempsRotT = Ord_Tourniquet(Tr,list,"TOURNIQUET");
								Afficher_En_Resume(list,Tr,'b');    break;
			case '4' : clear(); Afficher_En_Resume(list,Tr,'b');    break;
			default  : clear(); printf("\n\n\t\t\t\t\e[47;31m Ce choix n'existe pas [_INCORRECT_CHOICE_] \e[30m");
						Afficher_En_Resume(L,Tr,'b');
		}
	}
}



void une_ligne_du_Schema_temporel(BCP p)
{
	int _nbCharPrinted = 0; // Variable qui va contenir le nombre total de caractère affiché sur l'écran par printf
	int i = 0; // Variable utilisé pour faire le bascule entre TEX et TES sur l'affichage dans le tableau
	int j = 0; // Compteur de nombre de TEX du processus courant
	int k = 0; // Compteur de nombre de TES du processus courant
	static int _foo_bar = 0; //La fonction va être appelé pour afficher une ligne
	/**
	* Notez que l'utilisation du variable _nbCharPrinted permet de
	* récuperer le nombre de caractères affichés par la fonction
	* printf()
	*/

	/** Si le processus n'a pas rien à faire il ne sera pas affiché **/
	if(p.nbEX == 0 && p.nbES <=0) return;

	/*** Début du ligne d'affichage du processus pour tableau ***/
	printf("%s",soulign);
	switch(_foo_bar++%2)
	{
		//ID
		case 0 :
		if(p.ID < 10)					   _nbCharPrinted =  printf("%s  p%d   |%s",bgBcN, p.ID,initSl);
		else if(p.ID >= 10 && p.ID < 100 ) _nbCharPrinted =  printf("%s  p%d  |%s",bgBcN, p.ID,initSl    );
		else  		   					   _nbCharPrinted =  printf("%s  p%d |%s",bgBcN, p.ID,initSl    );
		break; 

		case 1 :
		if(p.ID < 10)   				   _nbCharPrinted =  printf("%s  p%d   |%s",bgJneN, p.ID,initSl);
		else if(p.ID >= 10 && p.ID < 100 ) _nbCharPrinted =  printf("%s  p%d  |%s",bgJneN, p.ID,initSl);
		else  		    				   _nbCharPrinted =  printf("%s  p%d |%s",bgJneN, p.ID,initSl);
	}

	//DATE D'ARRIVEE
	if(p.DA < 10) 						_nbCharPrinted += printf("     %d     |",p.DA);
	else if(p.DA >= 10 && p.DA < 100 )	_nbCharPrinted += printf("    %d     |" ,p.DA);
	else		  						_nbCharPrinted += printf("    %d    |" ,p.DA);


	//SCHEMA TEMPORELLE
	/**
	* Le schéma temporelle peut avoir plusieurs cas
	* c'est pourquoi j'ai choisit de le structurer ainsi
	* Pour avoir une sortie d'affichage qui ne casse pas
	* les limites du tableau et ceux suivant tous les cas possibles
	* qu'on peut rencotrer.
	* @Schéma_temporelle
	* @faouzi
	**/
	while(j<2 || k<2)
	{
		switch(i%2)
		{			// 1er cas : TEMPS D'EXECUTION
			case 0 : if(p.nbEX == 1 && p.nbES == 1 && k == 0 && j ==0 ) //S'il n'ya qu'une seule TEX et TES
					 {
					 	/** Structuration de l'affichage suivant les deux cas **/
				 	         if( p.TEX[j] < 10)  _nbCharPrinted += printf("  %d  unites  UCT et ",p.TEX[j]);
						else if( p.TEX[j] >= 10) _nbCharPrinted += printf("%d  unites  UCT et ",p.TEX[j]);
					 }
					 else if(p.nbEX == 1 && p.nbES <=0 && k == 0 && j ==0) //S'il n'ya qu'une seule TEX et aucun TES
					 {
					 	/** Structuration de l'affichage suivant les deux cas **/
					 	     if( p.TEX[j] < 10)  _nbCharPrinted += printf("  %d  unites  UCT.",p.TEX[j]);
						else if( p.TEX[j] >= 10) _nbCharPrinted += printf("%d  unites  UCT.",p.TEX[j]);
					 }
					 else if(p.nbEX == 2  && p.nbES <=0 && k == 0 && j ==0) //S'il n'ya qu'une aucun TES
					 {
					 	j = 3; //On va afficher des chaine vides pour ES
					 	/** Structuration de l'affichage suivant les deux cas **/
					 		 if( p.TEX[0] + p.TEX[1] < 10)  _nbCharPrinted += printf("  %d  unites  UCT.",p.TEX[j]);
						else if( p.TEX[0] + p.TEX[1]>= 10)  _nbCharPrinted += printf(" %d  unites  UCT.",p.TEX[j]);
					 }
					 /**
					 * Si le temps d'éxecution n'est ni ( == 0) ni ( >= à 3)
					 **/
					 else if(j < p.nbEX )
					 {
						if(j==p.nbEX-1 && p.nbEX != 1) // j == denier TEX et != 1
						{
							if(k>=p.nbES)  _nbCharPrinted += printf("%d  unites  UCT.",p.TEX[j]); // Si on a affiché tous les ES
							else // Si on a pas terminé d'affiché tous les ES
							{		 // k = dernier ES et structuration suivant les deux cas <10 || >=10
								     if(k == p.nbES-1 && p.TEX[j] < 10)  _nbCharPrinted += printf(" %d  unites  UCT et ",p.TEX[j]);
								else if(k == p.nbES-1 && p.TEX[j] >= 10) _nbCharPrinted += printf("%d  unites  UCT et ",p.TEX[j]);

								 // k != dernier ES et structuration suivant les deux cas <10 || >=10
								else if(k < p.nbES-1 && p.TEX[j] < 10)   _nbCharPrinted += printf("  %d unites  UCT, ",p.TEX[j]);
								else if(k < p.nbES-1 && p.TEX[j] >= 10)  _nbCharPrinted += printf(" %d  unites  UCT, ",p.TEX[j]);
							}
						}
						// else du j == denier TEX et != 1
						else if(p.TEX[j] < 10) _nbCharPrinted += printf("  %d  unites  UCT, ",p.TEX[j]);
							else			   _nbCharPrinted += printf(" %d  unites  UCT, ",p.TEX[j]);

					 }  else printf(""); //Ce else c'est lorsqu'on a terminé les TEX, on affiche une chaine vide
					j++;break;


			// 2ème cas : TEMPS D'ENTREES/SORTIES
			case 1 : k == 0 && p.nbEX == 0? printf(" "), _nbCharPrinted++ : printf(""); //S'il n'ya aucun TES
					 if(k < p.nbES)
					 {
					 	if(k==p.nbES-1 ) // k == denier TES
					 	{    /** Si on a terminé les TEX et Structuration de l'affichage suivant les deux cas **/
					 		     if(j>=p.nbEX && p.TES[k] < 10)  _nbCharPrinted += printf(" %d  unites  E/S.",p.TES[k]);
					 		else if(j>=p.nbEX && p.TES[k] >= 10) _nbCharPrinted += printf("%d  unites  E/S.",p.TES[k]);
							else // j < denier nombre de temps d'execution
							{		 // j = dernier TEX, NOMBRE DE TEX = 1 et structuration suivant les deux cas <10 || >=10
								     if( j == p.nbEX-1 && p.nbES == 1 && p.TES[k] < 10  ) _nbCharPrinted += printf(" %d  unites  E/S et ",p.TES[k]);
								else if( j == p.nbEX-1 && p.nbES == 1 && p.TES[k] >= 10 ) _nbCharPrinted += printf("%d  unites  E/S et ",p.TES[k]);

								// j = dernier TEX et structuration suivant les deux cas <10 || >=10
								else if( j == p.nbEX-1 && p.TES[k] < 10 )  _nbCharPrinted += printf("  %d  unites  E/S et ",p.TES[k]);
								else if( j == p.nbEX-1 && p.TES[k] >= 10 ) _nbCharPrinted += printf("%d  unites  E/S et ",p.TES[k]);

								// j != dernier TEX et structuration suivant les deux cas <10 || >=10
								else if( j<p.nbEX-1 && p.TES[k] < 10 )     _nbCharPrinted += printf("  %d unites  E/S, ",p.TES[k]);
								else if( j<p.nbEX-1 && p.TES[k] >= 10 )    _nbCharPrinted += printf("%d  unites  E/S, ",p.TES[k]);

								//Si on est au dernier temps d'execution et structuration suivant les deux cas
								else if( p.nbEX-1 == 1 && p.TES[k] < 10 )  _nbCharPrinted += printf("  %d  unites  E/S et ",p.TES[k]);
								else if( p.nbEX-1 == 1 && p.TES[k] >= 10 ) _nbCharPrinted += printf("%d  unites  E/S et ",p.TES[k]);
							}
						}
						/** S'il n'y a pas de TEX et structuration suivant les deux cas **/
					 	else if( p.nbEX == 0 && p.TES[k] < 10 )  _nbCharPrinted += printf(" %d  unites  E/S et ",p.TES[k]);
						else if( p.nbEX == 0 && p.TES[k] >= 10 ) _nbCharPrinted += printf("%d  unites  E/S et ",p.TES[k]);

						/** S'il y'a un TEX et structuration suivant les deux cas **/
					 	else if (p.TES[k] < 10) _nbCharPrinted += printf(" %d  unites  E/S, " ,p.TES[k]);
					 	else                    _nbCharPrinted += printf("%d  unites  E/S, " ,p.TES[k]);
					 }  else printf(""); //Ce else c'est lorsqu'on a terminé les TES, on affiche une chaine vide

					 k++;
		}//FIN DU SWITCH

		i++;
	}
		/**
		* On calcul le nombre de caractère
		* restant pour bien compléter le tableau 
		* par des espaces .
		*/
		int rest = 134 - _nbCharPrinted;
		for (int i = 0; i < rest; ++i) printf(" ");
	printf("%s|\n",init); // On ferme la ligne
	/*** Fin du ligne d'affichage du processus pour tableau ***/
}

/**
* Affichage d'une plusieurs processus
* Avec une structure de tableau dans l'affichage
* @Affichage_Proc_Tab
* @faouzi
*/
void afficher_Le_Schema_Temporelle(ListeP l)
{
	//system("cls");
	printf("%s ",soulign);
	ligne();
	printf("%s%s  PROC  %s Dte Arv    %s                  ",soulign,bgRg,bgVrt,bgBC);
	printf("              Schema temporel");
	for (int i = 0; i < 51; ++i) printf(" ");
	printf("%s|\n",init );

	for(int i = 0; i< l.nbproc ; i++)
	{
		une_ligne_du_Schema_temporel(l.T[i]);
	}
}



void diagramme_de_GANT(_ListeTrnq *Tr, ListeP *liste)
{
	int j = 0;
	int deb = 0;
	int fin = 0;
	int k = 0;
	BCP p;
	Info_BCP *q = NULL;

	TITRE_GANT();
	while(j < liste->nbproc /*5*/ )
	{
		p = liste->T[j];

		/********************************** ELU ***********************************/
		k = 1;
		if( (q = recherche(Tr,p.ID,k,elu)) != NULL ) { deb = q->deb;fin = q->fin; }
		else deb = -1; fin = -1;

		printf("%s%s ",soulign,jaune);	ligne_gant();
		printf("    %s%s|%selu%s   ", soulign,bleuC,blanc,etatAP);//ELU
		for (int i = 0; i < 74; ++i)
		{
			if(i == fin+1 && (q = recherche(Tr,p.ID,k,elu)) != NULL )
			{
				k++;deb = q->deb;fin = q->fin;
			}
			( i>=deb && i<=fin)? printf("|%sX%s",jaune,bleuC) : printf("| ");
		} finShow();
		deb = fin;


		/********************************** PRÊT **********************************/
		k = 1; fin = 0;
		if(p.ID <10) printf(" P%d %s%s|%sPret%s  ",p.ID, soulign,bleuC,blanc,etatAP);
		else if (p.ID >=10 && p.ID < 100)
					printf("P%d %s%s|%sPret%s  ",p.ID, soulign,bleuC,blanc,etatAP);
		else
					printf("P%d%s%s|%sPret%s  ",p.ID, soulign,bleuC,blanc,etatAP);//Pret
		for (int i = 0; i < 74; ++i)
		{
			if(i == fin+1 && (q = recherche(Tr,p.ID,k,pret)) != NULL )
			{
				k++;deb = q->deb;fin = q->fin;
			}
			( i>=deb && i<=fin)? printf("|%sX%s",vert,bleuC) : printf("| ");
		} finShow();
		deb = fin;

		/***************************** ENTRÉES - SORTIES *****************************/
		k = 1; fin = 0;
		printf("    %s|%sE/S%s   ",etatAV,blanc,etatAP);//E/S
		for (int i = 0; i < 74; ++i)
		{
			if(i == fin+1 && (q = recherche(Tr,p.ID,k,es)) != NULL )
			{
				k++;deb = q->deb;fin = q->fin;
			}
			( i>=deb && i<=fin)? printf("|%sX%s",bleu,bleuC) : printf("| ");
		} finShow();
		deb = fin;

		/********************************** BLOQUÉ **********************************/
		k = 1; fin = 0;
		printf("%s    |%sbloque%s",etatAV,blanc,etatAP);//BLOQUE
		for (int i = 0; i < 74; ++i)
		{
			if(i == fin+1 && (q = recherche(Tr,p.ID,k,bloque)) != NULL )
			{
				k++;deb = q->deb;fin = q->fin;
			}
			( i>=deb && i<=fin)? printf("|%sX%s",rose,bleuC) : printf("| ");
		} finShow();


		j++;
	}
	__horloge_TIMER(74);
}


void __horloge_TIMER(int n)
{

	char __timerColor[] = "\e[47;30m";
	printf("\t   %s",soulign);
	for (int i = 0; i < n; ++i)
	{
		(i<10) ? printf("%s %d",__timerColor,i)
				 :
			     printf("%s%d",__timerColor,i);

	     if(i%2 == 0) strcpy(__timerColor,"\e[40;37m");
	     else 		  strcpy(__timerColor,"\e[47;30m");
	};
	printf("%s|\n",init);
}

void faireFIFO_Ou_Tourniquet(_ListeTrnq *Tr, ListeP lst, char *algo)
{
	couleurFondNoir();
	if(la_liste_est_vide(lst))
	{
		clear();
		printf("\n\n\n\t\t\t\t DESOLE LA LISTE DES PROCESSUS EST VIDE POUR LE MOMENT\n\n");
		printf("\t\t\t\t           Il n'y a rien a simule\n\n\n");
		Continuer();
		getchar();
		return;
	}

	ListeP L  = {lst.nbMAX,lst.nbproc};
	L.T   = (BCP*)calloc(lst.nbMAX,sizeof(BCP));
	//On Copie les processus sur un nouveau tableau
	for(int i = 0; i<lst.nbproc; i++) L.T[i] = lst.T[i];

	//Tri du tableau des processus
	triFusion_BCP(L.T,0,lst.nbproc-1);
	

	long *_rotate = NULL; //On doit libérer la mémoir allouée dynamiquement sur la fonction d'ordonnancement,cette variable nous sert de corps de libération
	if(!strcmp(algo,"TOURNIQUET"))
		 _rotate = Ord_Tourniquet(Tr,L,"TOURNIQUET");
	else _rotate = Ord_Tourniquet(Tr,L,"FIFO");

	taille_agrandi_Gant();
	//Affichage d'une petite annimation
	printf("%s\n",init );
	clear();

	__loadOfSimulation();

	clear();
	/*Affichage du schéma temporelle*/
	printf("\n\n\t\t\t\t %s Voici la liste des processus qui sont simules%s\n",bgRgN,init);
	afficher_Le_Schema_Temporelle(L);//return 0;
	//Ordonnancement

	//Affichage du resultat de l'ordonnancement
	diagramme_de_GANT(Tr,&L);
	Continuer();getchar();
	taille_Normal_du_terminal();
	free(L.T);
	free(_rotate);
	libererListeRepartie(Tr);

}

