#include "effectsLinux.h"

/**
* Le caractère '\b' veut dire backslash, qui veut dire (en grod) 
* effacer un caractère (Le dernier caractère affiché)
* Mais il ne fera effet que lorsqu'on écris 2  '\b' mais pas une
* Seule comme '\n'...
* Je vous invite à regarder ce code 
* @Faouzi
* @Chargement
* @Effet 
*/
void __progressBar(void)
{
	printf(" %s",rouge);
	ligneG(); printf("%s\n",init );
	printf("\n\n\n\n\n\t\t\t\t CHARGEMENT...\n");
	printf("\t\t\t\t%s ",bgRg);
	for(int i = 0; i< N; i++ )
	{	/** 
		* Affichage de deux espaces en couleur Jaune #Si (i%2 = 0), 
		* #Sinon on éfface ces deux espaces et on affiche une autre espace
		* Puis la première boucle for() on affiche des espaces en couleur rouge
		* et ensuite on les efface dans la deuxième boucle for()
		**/
		i % 2 == 0 ? printf("%s  %s",bgJne,init) : printf("%s\b \b\b \b %s",bgJne,init);
		for(int j = 0; j < 12; j++ ) { printf("%s %s",bgRg,init);usleep(1200);}
		for(int j = 0; j < 12; j++ ) { printf("\b \b");usleep(1400); }
		
			usleep(1500);
	}

	printf("%s %s",bgRg,init);
	usleep(6000);printf("\n"); //La fonction ne prend que des valeurs en octal
}

void little_Load(char *string)
{
	printf("\n\n\n\n\n\t\t\t\t%s...\n",string);
	printf("\t\t\t\t%s ",bgBC);
	for(int i = 0; i< N; i++ )
	{	/** 
		* Affichage de deux espaces en couleur Jaune #Si (i%2 = 0), 
		* #Sinon on éfface ces deux espaces et on affiche une autre espace
		* Puis la première boucle for() on affiche des espaces en couleur rouge
		* et ensuite on les efface dans la deuxième boucle for()
		**/
		i % 2 == 0 ? printf("%s  %s",bgVrt,init) : printf("%s\b \b\b \b %s",bgVrt,init);
		for(int j = 0; j < 12; j++ ) { printf("%s %s",bgBC,init);usleep(0.09);}
		for(int j = 0; j < 12; j++ ) { printf("\b \b");usleep(0.002); }
		
			usleep(2);
	}

	printf("%s %s",bgBC,init);
	usleep(000010);printf("\n"); //La fonction ne prend que des valeurs en octal
}


void __loadOfSimulation(void)
{
	little_Load("COMPILATION DES DONNEES");clear();
	little_Load("LANCEMENT DE LA SIMULATION");
	usleep(600000);
}

void __startOfProgram(void)
{

	char str1[] = "\e[34m UNIVERSITE IBN TOFAIL\e[0m";
	char str2[] = "\e[34m FACULTE DES SCIENCES DE KENITRA\e[0m";
	char str3[] = "\e[32mPROGRAMME DE GESTION DE PROCESSUS\e[0m";
	
	clear();
	printf(" %s",rouge);  ligneG();
	printf("\n\n");
	margin_left();	printf("     %s\n",str1);
	margin_left();  printf("%s\n",str2);
	margin_left();  printf("%s",str3);

	printf("\n\n");
	__progressBar();
}




	
void menuApresGenerique(void)
{
	clear();
	printf("\n\n\n\n");
	lignetAvant_ApresMenu();	
	/*LIGNE AU DESSUS DU MENU PRINCIPAL*/
	printf("\n\t\t\t\t");
	LigneSurMenu();
  
  	printf("%s",bgBcN);
	
	/*DEBUT DU MENU PRINCIPAL*/
	printf("\e[4m\n\t\t\t\t###");
	for(int i = 0; i < 19; i++)printf("=");
	printf(" MODE DE LECTURE ");
	for(int i = 0; i < 19; i++)printf("=");
	printf("###\t\t\t\t\t\t\n");

	printf("\t\t\t\t\e[0;41m \e[0m\e[40;37m Veuillez choisir votre Mode de lecture :\e[0m\n");
	printf("%s     1) Lire les processus a partir du clavier         %s\n",unslctdWt,endUnseleted);
	printf("%s     2) Lire les processus depuis un fichier           %s\n",unslctdBl,endUnseleted);
	printf("%s     3) Fermer le Gestionnaire de Processus            %s\n",unslctdRs,endUnseleted);
	 
	printf("\t\t\t\t\e[41m \e[30m");
	for (int i = 0; i < 60; ++i) printf("\e[4m ");
	printf("%s",bgBcN);printf("\n\t\t\t\t\e[4m");
    for(int i = 0; i<61;i++) printf("#"); printf("%s\n",init);
    /*FIN DU MENU PRINCIPAL*/

    /*LIGNE APRES LE MENU*/
    
	lignetAvant_ApresMenu();
}


void menuApresGeneriqueChoix1(void)
{
	clear();
	printf("\n\n\n\n");

	lignetAvant_ApresMenu();	
	/*LIGNE AU DESSUS DU MENU PRINCIPAL*/
	printf("\n\t\t\t\t");
	LigneSurMenu();
  
    printf("%s",bgBcN);
	
	/*DEBUT DU MENU PRINCIPAL*/
	printf("\e[4m\n\t\t\t\t###");
	for(int i = 0; i < 19; i++) printf("=");
	printf(" MODE DE LECTURE ");
	for(int i = 0; i < 19; i++) printf("=");
	printf("###\t\t\t\t\t\t\n");

	printf("\t\t\t\t\e[0;41m \e[0m\e[40;37m Veuillez choisir votre Mode de lecture :\e[0m\n");
	printf("%s     1) Lire les processus a partir du clavier         %s\n",selected,endSelected);
	printf("%s     2) Lire les processus depuis un fichier           %s\n",unslctdBl,endUnseleted);
	printf("%s     3) Fermer le Gestionnaire de Processus            %s\n",unslctdRs,endUnseleted);
	
	printf("\t\t\t\t\e[41m \e[30m"); 
	for (int i = 0; i < 60; ++i) printf("\e[4m ");
	printf("%s",bgBcN);  printf("\n\t\t\t\t\e[4m");
    for(int i = 0; i<61;i++) printf("#");printf("\n");
    /*FIN DU MENU PRINCIPAL*/

    /*LIGNE APRES LE MENU*/
    printf("%s",init);
	lignetAvant_ApresMenu();
    printf("%s",init);
	usleep(400100);clear();
}


void menuApresGeneriqueChoix2(void)
{
	clear();
	printf("\n\n\n\n");

	lignetAvant_ApresMenu();	
	/*LIGNE AU DESSUS DU MENU PRINCIPAL*/
	printf("\n\t\t\t\t");
	LigneSurMenu();
  
    printf("%s",bgBcN);
	
	/*DEBUT DU MENU PRINCIPAL*/
	printf("\e[4m\n\t\t\t\t###");
	for(int i = 0; i < 19; i++) printf("=");
	printf(" MODE DE LECTURE ");
	for(int i = 0; i < 19; i++) printf("=");
	printf("###\t\t\t\t\t\t\n");

	printf("\t\t\t\t\e[0;41m \e[0m\e[40;37m Veuillez choisir votre Mode de lecture :\e[0m\n");
	printf("%s     1) Lire les processus a partir du clavier         %s\n",unslctdWt,endUnseleted);
	printf("%s     2) Lire les processus depuis un fichier           %s\n",selected,endSelected);
	printf("%s     3) Fermer le Gestionnaire de Processus            %s\n",unslctdRs,endUnseleted);
	
	printf("\t\t\t\t\e[41m \e[30m"); 
	for (int i = 0; i < 60; ++i) printf("\e[4m ");
	printf("%s",bgBcN);  printf("\n\t\t\t\t\e[4m");
    for(int i = 0; i<61;i++) printf("#");printf("\n");
    /*FIN DU MENU PRINCIPAL*/

    /*LIGNE APRES LE MENU*/
    printf("%s",init);
	lignetAvant_ApresMenu();
    printf("%s",init);
	usleep(400100);clear();
}


void menuApresGeneriqueChoix3(void)
{
	clear();
	printf("\n\n\n\n");

	lignetAvant_ApresMenu();	
	/*LIGNE AU DESSUS DU MENU PRINCIPAL*/
	printf("\n\t\t\t\t");
	LigneSurMenu();
  
    printf("%s",bgBcN);
	
	/*DEBUT DU MENU PRINCIPAL*/
	printf("\e[4m\n\t\t\t\t###");
	for(int i = 0; i < 19; i++) printf("=");
	printf(" MODE DE LECTURE ");
	for(int i = 0; i < 19; i++) printf("=");
	printf("###\t\t\t\t\t\t\n");

	printf("\t\t\t\t\e[0;41m \e[0m\e[40;37m Veuillez choisir votre Mode de lecture :\e[0m\n");
	printf("%s     1) Lire les processus a partir du clavier         %s\n",unslctdWt,endUnseleted);
	printf("%s     2) Lire les processus depuis un fichier           %s\n",unslctdBl,endUnseleted);
	printf("%s     3) Fermer le Gestionnaire de Processus            %s\n",selected,endSelected);
	
	printf("\t\t\t\t\e[41m \e[30m"); 
	for (int i = 0; i < 60; ++i) printf("\e[4m ");
	printf("%s",bgBcN);  printf("\n\t\t\t\t\e[4m");
    for(int i = 0; i<61;i++) printf("#");printf("\n");
    /*FIN DU MENU PRINCIPAL*/

    /*LIGNE APRES LE MENU*/
    printf("%s",init);
	lignetAvant_ApresMenu();
    printf("%s",init);
	usleep(400100);clear();
}


void premierMENU(void)
{
	printf("\n\n\n\n");

	lignetAvant_ApresMenu();	
	/*LIGNE AU DESSUS DU MENU PRINCIPAL*/
	printf("\n\t\t\t\t");
	LigneSurMenu();
  
    printf("%s",bgBcN);
	
	/*DEBUT DU MENU PRINCIPAL*/
	printf("\e[4m\n\t\t\t\t###");
	for(int i = 0; i<19;i++)printf("=");
	printf(" MENU PRINCIPALE ");
	for(int i = 0; i<19;i++)printf("=");
	printf("###\t\t\t\t\t\t\n");
	//
	printf("\t\t\t\t\e[0;41m \e[0m\e[40;37m Taper votre choix :\e[0m\n");
	printf("%s          0) Simulation avec FIFO                      %s\n",unslctdWt,endUnseleted);
	printf("%s          1) Simulation avec Tourniquet                %s\n",unslctdBl,endUnseleted);
	printf("%s          2) Lecture de processus                      %s\n",unslctdWt,endUnseleted);
	printf("%s          3) Affichage des processus                   %s\n",unslctdBl,endUnseleted);
	printf("%s          4) Supprimer un Processus                    %s\n",unslctdWt,endUnseleted);
	printf("%s          5) Ajouter un Processus                      %s\n",unslctdBl,endUnseleted);
	printf("%s          6) Fermer le Gestionnaire de Processus       %s\n",unslctdRs,endUnseleted);
	
	printf("\t\t\t\t\e[41m \e[30m"); 
	for (int i = 0; i < 60; ++i) printf("\e[4m ");
	printf("%s",bgBcN);  printf("\n\t\t\t\t\e[4m");
    for(int i = 0; i<61;i++) printf("#"); printf("%s\n",init);
    /*FIN DU MENU PRINCIPAL*/

    /*LIGNE APRES LE MENU*/
    /*LIGNE APRES LE MENU*/
    
	lignetAvant_ApresMenu();
}

void Choix_Lecture(void)
{
	
	clear();
	printf("\n\n\n\n");

	lignetAvant_ApresMenu();
	/*LIGNE AU DESSUS DU MENU PRINCIPAL*/
	printf("\n\t\t\t\t");
	LigneSurMenu();
  
    printf("%s",bgBcN);
	
	/*DEBUT DU MENU PRINCIPAL*/
	BarreEcrisMENU();
	
	printf("\t\t\t\t\e[41m \e[0m\e[45;37m Taper votre choix :\e[0m\n");
	printf("%s         0) Simulation avec FIFO                       %s\n",unslctdWt,endUnseleted);
	printf("%s         1) Simulation avec Tourniquet                 %s\n",unslctdBl,endUnseleted);
	printf("%s         2) Lecture de processus                       %s\n",selected,endSelected);
	printf("%s         3) Affichage des processus                    %s\n",unslctdWt,endUnseleted);
	printf("%s         4) Supprimer un Processus                     %s\n",unslctdBl,endUnseleted);
	printf("%s         5) Ajouter un Processus                       %s\n",unslctdWt,endUnseleted);
	printf("%s         6) Fermer le Gestionnaire de Processus        %s\n",unslctdBl,endUnseleted);
	
		printf("\t\t\t\t\e[4m");
	for (int i = 0; i < 61; ++i) printf(" ");
	printf("%s",bgBcN);  printf("\n\t\t\t\t\e[4m");
    LigneSurMenu();
    /*FIN DU MENU PRINCIPAL*/

    /*LIGNE APRES LE MENU*/
    
	lignetAvant_ApresMenu();
	printf("%s",init);
	usleep(510100);clear();
}

void Choix_Affichage(void)
{
	
	clear();
	printf("\n\n\n\n");

	lignetAvant_ApresMenu();
	/*LIGNE AU DESSUS DU MENU PRINCIPAL*/
	printf("\n\t\t\t\t");
	LigneSurMenu();
  
    printf("%s",bgBcN);
	
	/*DEBUT DU MENU PRINCIPAL*/
	BarreEcrisMENU();
	
	printf("\t\t\t\t\e[41m \e[0m\e[45;37m Taper votre choix :\e[0m\n");
	printf("%s         0) Simulation avec FIFO                       %s\n",unslctdWt,endUnseleted);
	printf("%s         1) Simulation avec Tourniquet                 %s\n",unslctdBl,endUnseleted);
	printf("%s         2) Lecture de processus                      %s\n",unslctdBl,endUnseleted);
	printf("%s         3) Affichage des processus                   %s\n",selected,endSelected);
	printf("%s         4) Supprimer un Processus                    %s\n",unslctdBl,endUnseleted);;
	printf("%s         5) Ajouter un Processus                      %s\n",unslctdWt,endUnseleted);;
	printf("%s         6) Fermer le Gestionnaire de Processus       %s\n",unslctdBl,endUnseleted);;
	
		printf("\t\t\t\t\e[4m");
	for (int i = 0; i < 61; ++i) printf(" ");
	printf("%s",bgBcN);  printf("\n\t\t\t\t\e[4m");
    LigneSurMenu();
    /*FIN DU MENU PRINCIPAL*/

    /*LIGNE APRES LE MENU*/
    
	lignetAvant_ApresMenu();
	printf("%s",init);
	usleep(510100);clear();
}

void Choix_Suppression(void)
{
	
	clear();
	printf("\n\n\n\n");

	lignetAvant_ApresMenu();
	/*LIGNE AU DESSUS DU MENU PRINCIPAL*/
	printf("\n\t\t\t\t");
	LigneSurMenu();
  
    printf("%s",bgBcN);
	
	/*DEBUT DU MENU PRINCIPAL*/
	BarreEcrisMENU();
	
	printf("\t\t\t\t\e[41m \e[0m\e[45;37m Taper votre choix :\e[0m\n");
	printf("%s         0) Simulation avec FIFO                       %s\n",unslctdWt,endUnseleted);
	printf("%s         1) Simulation avec Tourniquet                 %s\n",unslctdBl,endUnseleted);
	printf("%s         2) Lecture de processus                       %s\n",unslctdBl,endUnseleted);
	printf("%s         3) Affichage des processus                    %s\n",unslctdWt,endUnseleted);
	printf("%s         4) Supprimer un Processus                     %s\n",selected,endSelected);
	printf("%s         5) Ajouter un Processus                       %s\n",unslctdWt,endUnseleted);
	printf("%s         6) Fermer le Gestionnaire de Processus        %s\n",unslctdBl,endUnseleted);
	
		printf("\t\t\t\t\e[4m");
	for (int i = 0; i < 61; ++i) printf(" ");
	printf("%s",bgBcN);  printf("\n\t\t\t\t\e[4m");
    LigneSurMenu();
    /*FIN DU MENU PRINCIPAL*/

    /*LIGNE APRES LE MENU*/
    
	lignetAvant_ApresMenu();
	printf("%s",init);
	usleep(510100);clear();
}

void Choix_Ajout(void)
{
	
	clear();
	printf("\n\n\n\n");
	lignetAvant_ApresMenu();

	/*LIGNE AU DESSUS DU MENU PRINCIPAL*/
	printf("\n\t\t\t\t");
	LigneSurMenu();
    printf("%s",bgBcN);
	/*DEBUT DU MENU PRINCIPAL*/
	BarreEcrisMENU();
	
	printf("\t\t\t\t\e[41m \e[0m\e[45;37m Taper votre choix :\e[0m\n");
	printf("%s         0) Simulation avec FIFO                       %s\n",unslctdWt,endUnseleted);
	printf("%s         1) Simulation avec Tourniquet                 %s\n",unslctdBl,endUnseleted);
	printf("%s         2) Lecture de processus                       %s\n",unslctdBl,endUnseleted);
	printf("%s         3) Affichage des processus                    %s\n",unslctdWt,endUnseleted);
	printf("%s         4) Supprimer un Processus                     %s\n",unslctdBl,endUnseleted);
	printf("%s         5) Ajouter un Processus                       %s\n",selected,endSelected);
	printf("%s         6) Fermer le Gestionnaire de Processus        %s\n",unslctdBl,endUnseleted);
		printf("\t\t\t\t\e[4m");
	for (int i = 0; i < 61; ++i) printf(" ");
	printf("%s",bgBcN);  printf("\n\t\t\t\t\e[4m");
    LigneSurMenu();
    /*FIN DU MENU PRINCIPAL*/

    /*LIGNE APRES LE MENU*/
    
	lignetAvant_ApresMenu();
	printf("%s",init);
	usleep(510100);clear();
}

void Choix_Quitter(void)
{
	
	clear();
	printf("\n\n\n\n");

	lignetAvant_ApresMenu();
	/*LIGNE AU DESSUS DU MENU PRINCIPAL*/
	printf("\n\t\t\t\t");
	LigneSurMenu();
  
    printf("%s",bgBcN);
	
	/*DEBUT DU MENU PRINCIPAL*/
	BarreEcrisMENU();
	
	printf("\t\t\t\t\e[41m \e[0m\e[45;37m Taper votre choix :\e[0m\n");
	printf("%s         0) Simulation avec FIFO                       %s\n",unslctdWt,endUnseleted);
	printf("%s         1) Simulation avec Tourniquet                 %s\n",unslctdBl,endUnseleted);
	printf("%s         2) Lecture de processus                       %s\n",unslctdBl,endUnseleted);
	printf("%s         3) Affichage des processus                    %s\n",unslctdWt,endUnseleted);
	printf("%s         4) Supprimer un Processus                     %s\n",unslctdBl,endUnseleted);
	printf("%s         5) Ajouter un Processus                       %s\n",unslctdWt,endUnseleted);
	printf("%s         6) Fermer le Gestionnaire de Processus        %s\n",selected,endSelected);
	
		printf("\t\t\t\t\e[4m");
	for (int i = 0; i < 61; ++i) printf(" ");
	printf("%s",bgBcN);  printf("\n\t\t\t\t\e[4m");
    LigneSurMenu();
    /*FIN DU MENU PRINCIPAL*/

    /*LIGNE APRES LE MENU*/
    
	lignetAvant_ApresMenu();
	printf("%s",init);
	usleep(510100);clear();
}

/*
int main(int argc, char const *argv[])
{
	__startOfProgram();
	return 0;
}
*/