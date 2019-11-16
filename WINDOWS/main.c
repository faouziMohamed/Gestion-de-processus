#include "Work/fonct.h"

int First_ID;

int main()
{

	int choix = 1;
	ListeP lst = {0,0};
	_ListeTrnq Tr  = {__FIFO,0,NULL,NULL};
	
	taille_Normal_du_terminal();
	activer_Les_Couleurs();

	/*Initialisation de l'ID a un nombre aléatoire compris sur [0-30]*/
	srand(time(NULL));
	First_ID = rand()%(3+1);

	//__startOfProgram();
			  
			   clear();
	 couleurFondGris();
	
	/*** Menu après l'affichage du générique ***/
	while(1)
	{
		garderCouleurDeFOnd();
		if( choix < 1 || choix > 3)
		printf("\n\n\t\t\t\t\t%s%s Ce choix n'existe pas [_INCORRECT_CHOICE_ ] %s",bgNoir,rouge,noir);
	lecture: // Etiquette de l'Instruction goto
		garderCouleurDeFOnd();
		menuApresGenerique();
		printf("\n\t\t%s%s Votre choix : %s",init,bgRgN,init); 
		garderCouleurDeFOnd();
		scanf("%d",&choix);

		switch (choix)
		{
			case 1:menuApresGeneriqueChoix1(); ajouter_Depuis_clavier(&lst,1);Continuer();getchar();
					clear();if(lst.nbproc == 0){ clear(); couleurFondGris(); continue;} else break;
			case 2:menuApresGeneriqueChoix2(); fscanp(&lst);Continuer();getchar();
					clear();if(lst.nbproc == 0) { clear(); couleurFondGris(); continue;} else break;
	   		case 3:menuApresGeneriqueChoix3(); EndOfMain();
	   				__endOfProgram("\t\tFermeture du programme",&lst);
	          		exit(EXIT_SUCCESS);
			default : clear();					 
		}// Fin du boucle while() 
		couleurFondGris();
		if( choix >= 1 && choix <= 3) break; //On passe au menu Principal du programme
	}	

	/*** Menu après lecture des processus ***/
	while(1)
	{
		garderCouleurDeFOnd();
		if( choix < 0 || choix > 6)
		printf("\n\n\t\t\t\t\t%s%s Ce choix n'existe pas [_INCORRECT_CHOICE_ ] %s",bgNoir,rouge,noir);
		garderCouleurDeFOnd();
		
		premierMENU();   
		printf("\n\t\t%s%s Votre choix : %s",init,bgRgN,init); 
		garderCouleurDeFOnd();
		scanf("%d",&choix);

		
		
		

		switch (choix)
		{
			case 0: faireFIFO_Ou_Tourniquet(&Tr,lst,"FIFO");break;
			case 1: faireFIFO_Ou_Tourniquet(&Tr,lst,"TOURNIQUET");break;
			case 2: Choix_Lecture(); 
					if(lst.nbproc) First_ID = plusGrandID(lst) + 1; 
					goto lecture;
					break;

			case 3: Choix_Affichage();Afficher_En_Resume(lst,&Tr,'a');
					taille_Normal_du_terminal();
					break;

			case 4: Choix_Suppression();Supprimer(&lst);
					Continuer();getchar();
					break;

			case 5: Choix_Ajout();ajouter_Depuis_clavier(&lst,0);
					Continuer();getchar();
					break;
	   		case 6: Choix_Quitter(); EndOfMain();
	   				__endOfProgram("\t\tFermeture du programme",&lst);
	          		exit(EXIT_SUCCESS);
			default : clear();
					  
					 
		}/** Fin du boucle while() **/
		couleurFondGris();
	}		
	return 0;
}























































/*

	taille_Normal_du_terminal();

	ListeP lst = {12,12};
	BCP p0  = { 8, 7,{ 4, 6}, { 7, 5}, 2,2,0,0,0};
	BCP p1  = {25, 0,{ 4, 2}, { 7, 5}, 2,2,0,0,0};
	BCP p2  = { 5,12,{ 3, 2}, {10, 0}, 1,1,0,0,0};
	BCP p3  = { 4, 7,{ 3, 5}, { 9, 5}, 2,2,0,0,0};
	BCP p4  = { 9, 8,{ 7, 2}, { 5, 3}, 2,2,0,0,0};
	BCP p5  = { 3, 7,{ 8, 5}, { 7, 0}, 2,1,0,0,0};
	BCP p6  = {27, 9,{ 5, 1}, { 4, 7}, 2,2,0,0,0};
	BCP p7  = {13, 6,{ 2, 1}, { 2, 4}, 2,2,0,0,0};
	BCP p8  = { 2, 9,{ 9, 4}, { 6, 4}, 2,0,0,0,0};
	BCP p9  = { 1, 7,{ 5, 3}, { 4, 5}, 2,2,0,0,0};
	BCP p10 = { 6,10,{ 6, 1}, { 3, 6}, 2,2,0,0,0};
	BCP p11 = { 7, 9,{ 6, 2}, { 3, 4}, 2,2,0,0,0};

	lst.T = (BCP*)calloc(12,sizeof(BCP));
	int i = 0;
	lst.T[i++] =  p0;
	lst.T[i++] =  p1;
	lst.T[i++] =  p2;
	lst.T[i++] =  p3;
	lst.T[i++] =  p4;
	lst.T[i++] =  p5;
	lst.T[i++] =  p6;
	lst.T[i++] =  p7;
	lst.T[i++] =  p8;
	lst.T[i++] =  p9;
	lst.T[i++] = p10;
	lst.T[i++] = p11;

free(lst.T);

*/
