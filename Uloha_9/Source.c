#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include <math.h>
#pragma warning (disable:4996)
int compare(const void* a, const void* b)
{
	return (*(int*)a - *(int*)b);
}
void prohodit(int* a, int* b) //prohozeni 2 promennych
{
	int O = *a;
	*a = *b;
	*b = O;
}
int quicksort_deleni(int pole[], int min, int max)
{
	int pivot = pole[max]; //urceni pivotu na poslednim indexu
	int mensi = (min - 1); //leva hodnota, hodnota ktera bude na levo od promenny "i"
	for (int i = min; i < max; i++)
	{
		if (pole[i] < pivot) //je-li hodnota mensi nez pivot 
		{
			mensi++;
			prohodit(&pole[mensi], &pole[i]);//prohozeni porovnavane hodnoty na pozici mensi 
		}
	}
	prohodit(&pole[mensi + 1], &pole[max]); //vlozeni pivotu na jeho skutecnou pozici
	return (mensi + 1); //vraci se pozice pivotu
}
void quicksort(int pole[], int min, int max)
{

	int index; //index pivotu
	if (min < max)
	{
		index = quicksort_deleni(pole, min, max); //urceni indexu pivotu a rozdeleni pole do dvou casti: cisla mensi nez pivot a vetsi nez pivot
		quicksort(pole, min, index - 1); //quicksort s levou casti od indexu
		quicksort(pole, index + 1, max); //quicksort s pravou casti od indexu
	}
}
void tiskpole(int pole[], int velikost) //tisk pole dle velikosti zadane uzivatelem
{
	for (int i = 0; i < velikost; i++)
	{
		printf("%i \n", pole[i]);
	}
}
int random_cislo()
{
	int cislo;
	cislo = (rand() % 32766) - 16383;//zvoleni cisla v rozmezi -16838 a 16838
	return cislo;
}

void pole_cisel(int pole[], int velikost)
{

	for (int i = 0; i < velikost; i++)
	{
		pole[i] = random_cislo();//davajici nahodne cislo v rozmemiz -16838 a 16838
	}

}
int main()
{
	srand(time(0));
	int menu = 0;
	int velikost;
	int* pole;
	clock_t cas;
	printf("Jak velke pole bude (5 az 1000)?\n");
	scanf("%d", &velikost);
	while ((velikost < 5 || velikost > 1000))
	{
		printf("Spatna velikost, napsat znovu:\n");
		scanf("%d", &velikost);
	}
	pole = (int*)malloc(velikost * sizeof(int)); //dynamicka alokace pole na mnozstvi promenne "velikost"

	while (1)//menu
	{
		while (!(menu < 6 && menu>0)) //zvoleni pozice menu
		{
			printf("Menu Programu:\n Co si prejete udelat:\n 1 = Vygenerovat novy pole\n 2 = Vypsat pole\n 3 = Vlastni quicksort\n 4 = Qsort\n 5 = Konec Programu\n");
			scanf("%d", &menu);
		}

		if (menu == 1)//vygenerovat pole
		{
			printf("|\n|\n Vygenerovane pole\n|\n|\n");

			pole_cisel(pole, velikost);
			menu = 0;
		}
		if (menu == 2)//vypsani pole
		{
			printf("|\n|\nVypsani pole:\n");
			tiskpole(pole, velikost);
			menu = 0;
		}
		if (menu == 3)//quicksort programatora
		{
			printf("|\n|\nQuicksort:\n");
			cas = clock();//pocatecni cas
			quicksort(pole, 0, velikost - 1);
			cas = clock() - cas;//koncovy cas
			printf("Vypracovani zabralo %f vterin\n|\n|\n", (float)cas / CLOCKS_PER_SEC);//vypsani casu tim ze se konec odecte zacatkem
			menu = 0;
		}
		if (menu == 4)//qsort z knihovny
		{
			printf("|\n|\nQsort():\n");
			cas = clock();
			qsort(pole, velikost, sizeof(int), compare);
			cas = clock() - cas;
			printf("Vypracovani zabralo %f vterin\n|\n|\n", (float)cas / CLOCKS_PER_SEC);
			menu = 0;
		}
		if (menu == 5)
		{
			printf("|\n|\nProgram ukoncen\n|\n|\n");
			exit(0);
		}

	}
}
