#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/my_menu.h" 
#include "../include/myStudent.h"
#include "../include/stos.h"
#include "../include/message.h"

const char *kierunki[] =
{
	" Architektura",
	" Automatyka i Robotyka",
	" Budownictwo",
	"Informatyka",
	"Informatyka Stosowana",
	"Infotronika",
	"Matematyka",
	"Transport"
};

char menu(int integer)
{
	const char* my_menu[] = {
		"\n\t 1 - Dodaj do stosu.",
		" 2 - Usun ze stosu.",
		" 3 - Wydrukuj na monitorze ostatni element ze stosu.",
		" 4 - Wydrukuj na monitorze wszytkie elementy stosu.",
		" 5 - Odnajdz podany element. ",
		" 6 - Zapisz wszystkie elemnty do pliku binarnego.",
		" 7 - Odczytaj wszystkie elementy z dysku.",
		" 8 - Wyczysc stos",
		" 9 - Zamknij program."
	};
	
	for (int i = 0; i < EXIT; ++i)
	{
		printf("\t%s\n", my_menu[i]);
	}

	if (scanf("%d", &integer) != 1)
	{
		while (integer = getchar() != '\n');
			return 0;
	}

	return integer;
}

void push()
{
	size_t i = 0;
	char *nazwisko = (char *)malloc(128 * sizeof(char));
	if (!nazwisko)
		MyMessage(ERR_ALLOC_MEM);
	int kier;
	unsigned int wiek;

	printf("Wprowadz nazwisko studenta\n\n");
	scanf("%s", nazwisko, 64 * sizeof(char));

	
	printf("Wprowadz wiek studenta\n");
	do
	{
		if (i++ > 0)
		{
			while (wiek = getchar() != '\n');
			MyMessage(NOT_INTEGER);
		}	
	}
	while (scanf("%u", &wiek) != 1);

	printf("\nWybierz kierunek studiow studenta %s: \n", nazwisko);
	for (int i = architektura - 1; i < matematyka; ++i)
		printf("%d - %s\n", i + 1, kierunki[i]);

	i = 0;
	do 
	{
		if (i++ > 0)
		{
			while (kier = getchar() != '\n');
			MyMessage(NOT_INTEGER_1);
		}
	}	 
	while ((scanf("\n%d", &kier) != 1) || (kier > matematyka || kier < architektura));

	void *wd = MyStudentPush(nazwisko, (kierunek_studiow)kier, wiek);
	
	stosPush(wd);

	free(nazwisko);
	nazwisko = NULL;
	
}

void pop()
{
	STOS temp = stosPop();
	MyStudentPrint(temp.wDane);
	MyStudentFree(temp.wDane);

}


void find_student()
{
	const char *my_comp[] =
	{
		"\n 1 - Szukaj ze wzgledu na nazwisko.",
		" 2 - Szukaj ze wzgledu na wiek.",
		" 3 - Szukaj ze wzgledu na kierunek."
	};
	short ch, i = 0, elem = 0;
	for (i ; i < 3; ++i)
		printf("%s\n", my_comp[i]);

	i = 0;

	do
	{
		if (i++ > 0)
		{
			while (ch = getchar() != '\n');
			MyMessage(NOT_INTEGER);
		}
	} while ((scanf("%hd", &ch) != 1) || (0 > ch || ch > 3));

	MY_STUDENT searchD;
	memset(&searchD, 0, sizeof(MY_STUDENT));
	void *pD;
	

	if (ch == 1)
	{
		char str[128];

		printf("Wprowadz nazwisko do wyszukania:\t");
		scanf("%s", str, sizeof(str));

		searchD.nazwisko = (char *)malloc(sizeof(char) * 128);
		if (!searchD.nazwisko)
			MyMessage(ERR_ALLOC_MEM);

		strcpy_s(searchD.nazwisko, sizeof(str), str);
		pD = stosSearch(&searchD, MyStudentSearch, 1, ch);

	
	}
	else if (ch == 2)
	{
		unsigned int wiek;

		printf("Podaj wiek do wyszukania:\t");
		scanf("%u", &wiek);

		searchD.wiek = wiek;
		pD = stosSearch(&searchD, MyStudentSearch, 1, ch);

	}
	else 
	{
		int kierunek;

		printf("Podaj kierunek do wyszuaknia:\n");

		for (i = architektura - 1; i < matematyka; ++i)
			printf("%d - %s\n", i + 1, kierunki[i]);
		i = 0;
		do
		{
			if (i++ > 0)
			{
				while (kierunek = getchar() != '\n');
				MyMessage(NOT_INTEGER_1);
			}
		} while ((scanf("\n%d", &kierunek) != 1) || (kierunek > matematyka || kierunek < architektura));

		searchD.kierunek = (kierunek_studiow)kierunek;
		pD = stosSearch(&searchD, MyStudentSearch, 1, ch);
	}
	if (pD)
	{
		puts("\nZnaleziono: ");
		MyStudentPrint(pD);
		++elem;
	}
	while (pD)
	{
		pD = stosSearch(&searchD, MyStudentSearch, 0, ch);
		if (pD)
		{
			puts("\nZnaleziono: ");
			MyStudentPrint(pD);
			++elem;
		}
	}
	if(elem == 0)
		MyMessage(BRAK_DANYCH);
	
	if (searchD.nazwisko)
		free(searchD.nazwisko);
}

void printlast()
{
	MyStudentPrint(currentData());
}

void printAll()
{
	void *wsk = myDataStos(0);
	MyStudentPrint(wsk);
	
	while (wsk)
	{
		wsk = myDataStos(1);
		MyStudentPrint(wsk);
	}
}

void saveStosToFile()
{
	stosSave();
}

void readStosFromFile()
{
	StosRead();
}

void clear()
{
	StosFree();
}

void my_exit()
{
	StosFree();
	exit(0);
}

void my_menu()
{
	MyMessage(START_PROGRAMU);
	stosInit(MyStudentFree, MyStudentRead, MyStudentSave);
	int symb = NULL;

	while (true)
	{
		symb = menu(symb);
		switch (symb)
		{
		case PUSH:	push();
			break;
		case POP:	pop();
			break;
		case TAKE_LAST:	printlast();
			break;
		case TAKE_ALL:	printAll();
			break;
		case FIND:	find_student();
			break;
		case SAVE_ALL_TO_FILE:	saveStosToFile();
			break;
		case READ_ALL_FROM_FILE:	readStosFromFile();;
			break;
		case CLEAR:	clear();
			break;
		case EXIT:	my_exit();
			break;
		default:
			MyMessage(BLEDNA_KOMENDA);
		}
	}
}