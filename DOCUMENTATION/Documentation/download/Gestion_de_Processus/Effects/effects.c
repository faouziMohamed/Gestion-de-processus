#include "effects.h"

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
void Continuer()
{
	printf("\n\n\t\t\t Appuyez sur la touche %sENTREE%s pour continuer...",jaune,init);
	getchar();
}
void __progressBar(void)
{
	printf(" %s",rouge);
	ligneG(); printf("%s\n",init );
	printf("\n\n\n\n\n\t\t\t\t Chargement...\n");
	printf("\t\t\t\t%s ",bgRg);
	for(int i = 0; i< N; i++ )
	{	/** 
		* Affichage de deux espaces en couleur Jaune #Si (i%2 = 0), 
		* #Sinon on éfface ces deux espaces et on affiche une autre espace
		* Puis la première boucle for() on affiche des espaces en couleur rouge
		* et ensuite on les efface dans la deuxième boucle for()
		**/
		i % 2 == 0 ? printf("%s  %s",bgJne,init) : printf("%s\b \b\b \b %s",bgJne,init);
		for(int j = 0; j < 12; j++ ) { printf("%s %s",bgRg,init);Sleep(0.9);}
		for(int j = 0; j < 12; j++ ) { printf("\b \b");Sleep(0.8); }
		
			Sleep(10);
	}

	printf("%s %s",bgRg,init);
	Sleep(600);printf("\n"); //La fonction ne prend que des valeurs en octal
}

void __progress_Gant(char *string)
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
		for(int j = 0; j < 12; j++ ) { printf("%s %s",bgBC,init);Sleep(0.9);}
		for(int j = 0; j < 12; j++ ) { printf("\b \b");Sleep(0.02); }
		
			Sleep(2);
	}

	printf("%s %s",bgBC,init);
	Sleep(00010);printf("\n"); //La fonction ne prend que des valeurs en octal
}



void __loadOfSimulation(void)
{
	__progress_Gant("Compilation des donnees");clear();
	__progress_Gant("Lancement de la simulation");
	Sleep(600);
}

void __startOfProgram(void)
{

	char str1[] = "\e[34m UNIVERSITE IBN TOFAIL\e[0m";
	char str2[] = "\e[34m FACULTE DES SCIENCES DE KENITRA\e[0m";
	char str3[] = "\e[32mPROGRAMME DE GESTION DE PROCESSUS\e[0m";
	
	Color(7,0);
	clear();
	//UNIVERSITE IBN TOFAIL
	printf(" %s",rouge);	ligneG(); printf("%s\n\n",init );
	margin_left();

	for(int i = 0; i<strlen(str1);i++)  { printf("%c",str1[i]);Sleep(0030);}
		Sleep(1000);
	for (int i = 0; i < strlen(str1)-9; ++i) { printf("\b \b");Sleep(0030);}

	//FACULTE DES SCIENCES DE KENITRA
	  //Balayage avant d'aficher
	clear_margin_left();
	margin_left();

	for(int i = 0; i<strlen(str2);i++)  { printf("%c",str2[i]);Sleep(0030);}
	Sleep(1000);
	for (int i = 0; i < strlen(str2)-9; ++i) { printf("\b \b");Sleep(0030);}


	//PROGRAMME DE GESTION DE PROCESSUS
	clear_margin_left();
	margin_left();
	for(int i = 0; i<strlen(str3);i++)  { printf("%c",str3[i]);Sleep(0030);}
		Sleep(1000);

	printf("\n\n");
	__progressBar();

	for(int i = 0; i<30; i++) { printf("\n");Sleep(0010);}
}



void Color(int couleurDuTexte,int couleurDeFond)
{
	HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}
void couleurFondGris(void)
{
		Color(0,8);
		clear();
}

void couleurFondNoir(void)
{
		Color(7,0);
		clear();
}

void garderCouleurDeFOnd(void){ Color(0,8); }

void EndOfMain(void)
{
	Color(7,0);
	clear();
}


void menuApresGenerique(void)
{
	printf("\n\n\n\n");

	lignetAvant_ApresMenu();	
	/*LIGNE AU DESSUS DU MENU PRINCIPAL*/
	printf("\n\t\t\t\t");
	LigneSurMenu();
  
    printf("%s",bgJne );
	
	/*DEBUT DU MENU PRINCIPAL*/
	printf("\e[4m\n\t\t\t\t###");
	for(int i = 0; i < 19; i++) {	printf("=");Sleep(005);}
	printf(" MODE DE LECTURE ");
	for(int i = 0; i < 19; i++) {	printf("=");Sleep(005);}
	printf("###\t\t\t\t\t\t\n");

	printf("\t\t\t\t\e[0;41m \e[0m\e[40;37m Veuillez choisir votre Mode de lecture :\e[0m\n");
	printf("%s     1) Lire les processus a partir du clavier         %s\n",unslctdWt,endUnseleted);
	printf("%s     2) Lire les processus depuis un fichier           %s\n",unslctdBl,endUnseleted);
	printf("%s     3) Fermer le Gestionnaire de Processus            %s\n",unslctdRs,endUnseleted);
	 Color(0,8);
	printf("\t\t\t\t\e[41m \e[30m"); garderCouleurDeFOnd();
	for (int i = 0; i < 60; ++i) printf("\e[4m ");
	printf("%s",bgJne );  printf("\n\t\t\t\t\e[4m");
    for(int i = 0; i<61;i++) {	printf("#");Sleep(005);}printf("\n");
    /*FIN DU MENU PRINCIPAL*/

    /*LIGNE APRES LE MENU*/
    garderCouleurDeFOnd();
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
  
    printf("%s",bgJne );
	
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
	
	printf("\t\t\t\t\e[41m \e[30m"); garderCouleurDeFOnd();
	for (int i = 0; i < 60; ++i) printf("\e[4m ");
	printf("%s",bgJne );  printf("\n\t\t\t\t\e[4m");
    for(int i = 0; i<61;i++) printf("#");printf("\n");
    /*FIN DU MENU PRINCIPAL*/

    /*LIGNE APRES LE MENU*/
    printf("%s",init);
	lignetAvant_ApresMenu();
    printf("%s",init);
	Sleep(01100);clear();
}


void menuApresGeneriqueChoix2(void)
{
	clear();
	printf("\n\n\n\n");

	lignetAvant_ApresMenu();	
	/*LIGNE AU DESSUS DU MENU PRINCIPAL*/
	printf("\n\t\t\t\t");
	LigneSurMenu();
  
    printf("%s",bgJne );
	
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
	
	printf("\t\t\t\t\e[41m \e[30m"); garderCouleurDeFOnd();
	for (int i = 0; i < 60; ++i) printf("\e[4m ");
	printf("%s",bgJne );  printf("\n\t\t\t\t\e[4m");
    for(int i = 0; i<61;i++) printf("#");printf("\n");
    /*FIN DU MENU PRINCIPAL*/

    /*LIGNE APRES LE MENU*/
    printf("%s",init);
	lignetAvant_ApresMenu();
    printf("%s",init);
	Sleep(01100);clear();
}


void menuApresGeneriqueChoix3(void)
{
	clear();
	printf("\n\n\n\n");

	lignetAvant_ApresMenu();	
	/*LIGNE AU DESSUS DU MENU PRINCIPAL*/
	printf("\n\t\t\t\t");
	LigneSurMenu();
  
    printf("%s",bgJne );
	
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
	
	printf("\t\t\t\t\e[41m \e[30m"); garderCouleurDeFOnd();
	for (int i = 0; i < 60; ++i) printf("\e[4m ");
	printf("%s",bgJne );  printf("\n\t\t\t\t\e[4m");
    for(int i = 0; i<61;i++) printf("#");printf("\n");
    /*FIN DU MENU PRINCIPAL*/

    /*LIGNE APRES LE MENU*/
    printf("%s",init);
	lignetAvant_ApresMenu();
    printf("%s",init);
	Sleep(01100);clear();
}


void premierMENU(void)
{
	printf("\n\n\n\n");

	lignetAvant_ApresMenu();	
	/*LIGNE AU DESSUS DU MENU PRINCIPAL*/
	printf("\n\t\t\t\t");
	LigneSurMenu();
  
    printf("%s",bgJne );
	
	/*DEBUT DU MENU PRINCIPAL*/
	printf("\e[4m\n\t\t\t\t###");
	for(int i = 0; i<19;i++) {	printf("=");Sleep(005);}
	printf(" MENU PRINCIPALE ");
	for(int i = 0; i<19;i++) {	printf("=");Sleep(005);}
	printf("###\t\t\t\t\t\t\n");
	//garderCouleurDeFOnd();
	printf("\t\t\t\t\e[0;41m \e[0m\e[40;37m Taper votre choix :\e[0m\n");
	printf("%s          0) Simulation avec FIFO                      %s\n",unslctdWt,endUnseleted);
	printf("%s          1) Simulation avec Tourniquet                %s\n",unslctdBl,endUnseleted);
	printf("%s          2) Lecture de processus                      %s\n",unslctdWt,endUnseleted);
	printf("%s          3) Affichage des processus                   %s\n",unslctdBl,endUnseleted);
	printf("%s          4) Supprimer un Processus                    %s\n",unslctdWt,endUnseleted);
	printf("%s          5) Ajouter un Processus                      %s\n",unslctdBl,endUnseleted);
	printf("%s          6) Fermer le Gestionnaire de Processus       %s\n",unslctdRs,endUnseleted);
	
	printf("\t\t\t\t\e[41m \e[30m"); garderCouleurDeFOnd();
	for (int i = 0; i < 60; ++i) printf("\e[4m ");
	printf("%s",bgJne );  printf("\n\t\t\t\t\e[4m");
    for(int i = 0; i<61;i++) {	printf("#");Sleep(005);}printf("\n");
    /*FIN DU MENU PRINCIPAL*/

    /*LIGNE APRES LE MENU*/
    /*LIGNE APRES LE MENU*/
    garderCouleurDeFOnd();
	lignetAvant_ApresMenu();
}

void Choix_Lecture(void)
{
	garderCouleurDeFOnd();
	clear();
	printf("\n\n\n\n");

	lignetAvant_ApresMenu();
	/*LIGNE AU DESSUS DU MENU PRINCIPAL*/
	printf("\n\t\t\t\t");
	LigneSurMenu();
  
    printf("%s",bgJne );
	
	/*DEBUT DU MENU PRINCIPAL*/
	BarreEcrisMENU();
	garderCouleurDeFOnd();
	printf("\t\t\t\t\e[41m \e[0m\e[45;37m Taper votre choix :\e[0m\n");
	printf("%s         0) Simulation avec FIFO                       %s\n",unslctdWt,endUnseleted);
	printf("%s         1) Simulation avec Tourniquet                 %s\n",unslctdBl,endUnseleted);
	printf("%s         2) Lecture de processus                       %s\n",selected,endSelected);
	printf("%s         3) Affichage des processus                    %s\n",unslctdWt,endUnseleted);
	printf("%s         4) Supprimer un Processus                     %s\n",unslctdBl,endUnseleted);
	printf("%s         5) Ajouter un Processus                       %s\n",unslctdWt,endUnseleted);
	printf("%s         6) Fermer le Gestionnaire de Processus        %s\n",unslctdBl,endUnseleted);
	
	garderCouleurDeFOnd();	printf("\t\t\t\t\e[4m");
	for (int i = 0; i < 61; ++i) printf(" ");
	printf("%s",bgJne );  printf("\n\t\t\t\t\e[4m");
    LigneSurMenu();
    /*FIN DU MENU PRINCIPAL*/

    /*LIGNE APRES LE MENU*/
    garderCouleurDeFOnd();
	lignetAvant_ApresMenu();
	printf("%s",init);
	Sleep(01100);clear();
}

void Choix_Affichage(void)
{
	garderCouleurDeFOnd();
	clear();
	printf("\n\n\n\n");

	lignetAvant_ApresMenu();
	/*LIGNE AU DESSUS DU MENU PRINCIPAL*/
	printf("\n\t\t\t\t");
	LigneSurMenu();
  
    printf("%s",bgJne );
	
	/*DEBUT DU MENU PRINCIPAL*/
	BarreEcrisMENU();
	garderCouleurDeFOnd();
	printf("\t\t\t\t\e[41m \e[0m\e[45;37m Taper votre choix :\e[0m\n");
	printf("%s         0) Simulation avec FIFO                       %s\n",unslctdWt,endUnseleted);
	printf("%s         1) Simulation avec Tourniquet                 %s\n",unslctdBl,endUnseleted);
	printf("%s         2) Lecture de processus                      %s\n",unslctdBl,endUnseleted);
	printf("%s         3) Affichage des processus                   %s\n",selected,endSelected);
	printf("%s         4) Supprimer un Processus                    %s\n",unslctdBl,endUnseleted);;
	printf("%s         5) Ajouter un Processus                      %s\n",unslctdWt,endUnseleted);;
	printf("%s         6) Fermer le Gestionnaire de Processus       %s\n",unslctdBl,endUnseleted);;
	
	garderCouleurDeFOnd();	printf("\t\t\t\t\e[4m");
	for (int i = 0; i < 61; ++i) printf(" ");
	printf("%s",bgJne );  printf("\n\t\t\t\t\e[4m");
    LigneSurMenu();
    /*FIN DU MENU PRINCIPAL*/

    /*LIGNE APRES LE MENU*/
    garderCouleurDeFOnd();
	lignetAvant_ApresMenu();
	printf("%s",init);
	Sleep(01100);clear();
}

void Choix_Suppression(void)
{
	garderCouleurDeFOnd();
	clear();
	printf("\n\n\n\n");

	lignetAvant_ApresMenu();
	/*LIGNE AU DESSUS DU MENU PRINCIPAL*/
	printf("\n\t\t\t\t");
	LigneSurMenu();
  
    printf("%s",bgJne );
	
	/*DEBUT DU MENU PRINCIPAL*/
	BarreEcrisMENU();
	garderCouleurDeFOnd();
	printf("\t\t\t\t\e[41m \e[0m\e[45;37m Taper votre choix :\e[0m\n");
	printf("%s         0) Simulation avec FIFO                       %s\n",unslctdWt,endUnseleted);
	printf("%s         1) Simulation avec Tourniquet                 %s\n",unslctdBl,endUnseleted);
	printf("%s         2) Lecture de processus                       %s\n",unslctdBl,endUnseleted);
	printf("%s         3) Affichage des processus                    %s\n",unslctdWt,endUnseleted);
	printf("%s         4) Supprimer un Processus                     %s\n",selected,endSelected);
	printf("%s         5) Ajouter un Processus                       %s\n",unslctdWt,endUnseleted);
	printf("%s         6) Fermer le Gestionnaire de Processus        %s\n",unslctdBl,endUnseleted);
	
	garderCouleurDeFOnd();	printf("\t\t\t\t\e[4m");
	for (int i = 0; i < 61; ++i) printf(" ");
	printf("%s",bgJne );  printf("\n\t\t\t\t\e[4m");
    LigneSurMenu();
    /*FIN DU MENU PRINCIPAL*/

    /*LIGNE APRES LE MENU*/
    garderCouleurDeFOnd();
	lignetAvant_ApresMenu();
	printf("%s",init);
	Sleep(01100);clear();
}

void Choix_Ajout(void)
{
	garderCouleurDeFOnd();
	clear();
	printf("\n\n\n\n");
	lignetAvant_ApresMenu();

	/*LIGNE AU DESSUS DU MENU PRINCIPAL*/
	printf("\n\t\t\t\t");
	LigneSurMenu();
    printf("%s",bgJne );
	/*DEBUT DU MENU PRINCIPAL*/
	BarreEcrisMENU();
	garderCouleurDeFOnd();
	printf("\t\t\t\t\e[41m \e[0m\e[45;37m Taper votre choix :\e[0m\n");
	printf("%s         0) Simulation avec FIFO                       %s\n",unslctdWt,endUnseleted);
	printf("%s         1) Simulation avec Tourniquet                 %s\n",unslctdBl,endUnseleted);
	printf("%s         2) Lecture de processus                       %s\n",unslctdBl,endUnseleted);
	printf("%s         3) Affichage des processus                    %s\n",unslctdWt,endUnseleted);
	printf("%s         4) Supprimer un Processus                     %s\n",unslctdBl,endUnseleted);
	printf("%s         5) Ajouter un Processus                       %s\n",selected,endSelected);
	printf("%s         6) Fermer le Gestionnaire de Processus        %s\n",unslctdBl,endUnseleted);
	garderCouleurDeFOnd();	printf("\t\t\t\t\e[4m");
	for (int i = 0; i < 61; ++i) printf(" ");
	printf("%s",bgJne );  printf("\n\t\t\t\t\e[4m");
    LigneSurMenu();
    /*FIN DU MENU PRINCIPAL*/

    /*LIGNE APRES LE MENU*/
    garderCouleurDeFOnd();
	lignetAvant_ApresMenu();
	printf("%s",init);
	Sleep(01100);clear();
}

void Choix_Quitter(void)
{
	garderCouleurDeFOnd();
	clear();
	printf("\n\n\n\n");

	lignetAvant_ApresMenu();
	/*LIGNE AU DESSUS DU MENU PRINCIPAL*/
	printf("\n\t\t\t\t");
	LigneSurMenu();
  
    printf("%s",bgJne );
	
	/*DEBUT DU MENU PRINCIPAL*/
	BarreEcrisMENU();
	garderCouleurDeFOnd();
	printf("\t\t\t\t\e[41m \e[0m\e[45;37m Taper votre choix :\e[0m\n");
	printf("%s         0) Simulation avec FIFO                       %s\n",unslctdWt,endUnseleted);
	printf("%s         1) Simulation avec Tourniquet                 %s\n",unslctdBl,endUnseleted);
	printf("%s         2) Lecture de processus                       %s\n",unslctdBl,endUnseleted);
	printf("%s         3) Affichage des processus                    %s\n",unslctdWt,endUnseleted);
	printf("%s         4) Supprimer un Processus                     %s\n",unslctdBl,endUnseleted);
	printf("%s         5) Ajouter un Processus                       %s\n",unslctdWt,endUnseleted);
	printf("%s         6) Fermer le Gestionnaire de Processus        %s\n",selected,endSelected);
	
	garderCouleurDeFOnd();	printf("\t\t\t\t\e[4m");
	for (int i = 0; i < 61; ++i) printf(" ");
	printf("%s",bgJne );  printf("\n\t\t\t\t\e[4m");
    LigneSurMenu();
    /*FIN DU MENU PRINCIPAL*/

    /*LIGNE APRES LE MENU*/
    garderCouleurDeFOnd();
	lignetAvant_ApresMenu();
	printf("%s",init);
	Sleep(01100);clear();
}

/*
int main(int argc, char const *argv[])
{
	__startOfProgram();
	return 0;
}
*/