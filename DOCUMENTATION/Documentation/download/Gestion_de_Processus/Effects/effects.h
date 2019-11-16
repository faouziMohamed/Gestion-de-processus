#ifndef __BIB__EFFECT
#define __BIB__EFFECT

/*Fichier d'entete*/
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*** Les couleurs**/
#define soulign "\e[4m"
#define init    "\e[0m"
#define initSl  "\e[0m\e[4m"
#define bleuC   "\e[1;36m"
#define bleun   "\e[36m"
#define rouge   "\e[31m"
#define rose    "\e[35m"
#define vert    "\e[32m"
#define jaune   "\e[33m"
#define bleu    "\e[34m"
#define blanc   "\e[37m"
#define noir    "\e[30m"
#define bgNoir  "\e[40m"
#define bgVrt   "\e[42m"
#define bgBC    "\e[46m"
#define bgBlanc "\e[47m"
#define bgBcN   "\e[46;30m" //bgBC + Noir
#define bgRgN   "\e[41;30m" //bgRg + Noir
#define bgRg    "\e[41m"
#define bgJne   "\e[43m"
#define bgJneN  "\e[43;30m" //bgJne + Noir
#define etatAP  "\e[0;4;1;36m"
#define etatAV  "\e[0;4;1;36m"
#define selected "\t\t\t\t\e[41m \e[42m   \e[0;40;37m"
#define unslctdWt "\t\t\t\t\e[41m \e[42m   \e[0;30;47m"
#define unslctdRs "\t\t\t\t\e[41m \e[42m   \e[0;30;44m"
#define unslctdBl "\t\t\t\t\e[41m \e[42m   \e[0;30;46m"
#define endUnseleted "\e[42m \e[40m \e[0;30m"
#define endSelected  "\e[42m \e[47m \e[0;30m"
#define menuAff  "\e[42m \e[47m \e[0;37m"


/**********************LES MACROS*****************************/
#define clear() system("cls||clear")
#define activer_Les_Couleurs() system("color")

/****Taille du console*****/
#define taille_Normal_du_terminal() system("mode con lines=30 cols=122")   //MENU
#define taille_agrandi_Gant()       system("mode con lines=9001 cols=161") //DIGRAMME DE GANT
#define taille_Affichage()          system("mode con lines=150 cols=122")  //Affichage des processus

/******************************************************/
//          				MENU
////////////////////////////////////////////////////////
#define lignetAvant_ApresMenu() printf("\n\t\t\e[4m"); for (int i = 0; i < 95; ++i) printf(" ")
/*******************************************************************************************/
#define LigneSurMenu() for (int i = 0; i < 61; ++i) printf("\e[4m ")
/*******************************************************************************************/
#define BarreEcrisMENU() printf("\e[4m\n\t\t\t\t###"); for(int i = 0; i<19;i++) printf("=");	printf(" MENU PRINCIPALE ");\
		for(int i = 0; i<19;i++) printf("=");\
		printf("###\t\t\t\t\t\t\n")

/*******************************************************************************************/
#define ligne()  for(int i = 0; i<117;i++)printf("%s ",soulign); printf("%s\n",init)
/******************************************************/
/****************************************************************************/
//				Utilisé sur la fonction d'affichage en résumé
/////////////////////////////////////////////////////////////////////////////
#define barresup() for( i = 0; i<100; i++) printf(" \e[4m"); printf("\e[0m")
#define entete()printf("\n|\e[4m##  N           ID             ");\
	printf(" Dte_Arv                 TEX");\
	printf("             TES       TempsRot(FIFO)     TempsRot(Q=\e[35mN/A\e[0m)  |\n")
/****************************************************************************/
#define	ligne_gant() for(int i = 0; i<158;i++)printf("%s ",soulign); printf("%s\n",init)
#define TITRE_GANT() printf("\n%sPROC%s ETAT  %s",bgVrt,bgBC,bgJne);\
	for (int i = 0; i < 65; ++i) printf(" ");printf("%sDIAGRAMME DE GANT",noir);\
		for (int i = 0; i < 67; ++i) printf(" ");\
		printf("%s\n",init);
#define finShow() printf("%s%s|%s\n",init,jaune,init)
/********************************************************************************/
/********************************************************************/
#define lignef() for(int i = 0; i<117;i++)printf("%s ",soulign); printf("%s\n",init)
/********************************************************************/


#define N 110
#define ligneG() for(int i = 0; i<117;i++)printf(" %s",soulign); printf("%s\n",init)
#define       margin_left() printf("\t\t\t\t\t     ")
#define clear_margin_left() for(int i = 0;i <40; i++) printf("\b \b")

//Appuyez sur la touche "ENTREE" pour continuer...
void Continuer();

void __loadOfSimulation(void);
void __progress_Gant(char *string);
//void __endOfProgram(char *string);
void __progressBar(void);
void __startOfProgram(void);

/*Menu de l'ouverture*/
void menuApresGenerique(void);
void menuApresGeneriqueChoix1(void);
void menuApresGeneriqueChoix2(void);
void menuApresGeneriqueChoix3(void);


/*Menu dynamique*/
void       premierMENU(void);
void     Choix_Lecture(void);
void   Choix_Affichage(void);
void Choix_Suppression(void);
void       Choix_Ajout(void);
void     Choix_Quitter(void);


/*Prototypes des fonctions*/
void    Color(int couleurDuTexte,int couleurDeFond);
void    couleurFondGris(void);
void    couleurFondNoir(void);
void garderCouleurDeFOnd(void);
void   EndOfMain(void);
#endif