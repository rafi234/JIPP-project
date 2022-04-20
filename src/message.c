#include <stdio.h>
#include <stdlib.h>
#include "../include/message.h"
#include "../include/my_menu.h"
#include "../include/myStudent.h"


void MyMessage(enum BLEDY_I_KOMUNIKATY numb)
{
	const char *my_message[] =
	{
		"W Start programu.",	
		"W Inicjujemy stos.",
		"W Bledna komenda.",
		"W Usunieto z wierzcholka stosu element:",
		"W Podany znak nie jest liczba naturalna.",
		"W Podany znak nie jest liczba z poprawnego przedzialu.",
		"W Zapisujemy do pliku.",
		"W Czytamy plik",									
		"W Alokujemy pamiec.",								
		"W Zwalniamy wszystko.",
		"W Brak danych na stosie.",
		"W Koniec programu.",																	
		"E blad alokacji pamieci",	
		"E blad otwarcia pliku",
		"E blad fatalny"
	};

	printf("%s\n", my_message[numb] + 1);

	switch (my_message[numb][0])
	{
	case 'W':
		break;
	case 'E':
		my_exit();
		break;
	}
}

void exitError_1(FILE *dane, long *arr)
{
	if (dane)
		fclose(dane);
	if (arr)
		free(arr);
	MyMessage(ERR);
}

void exitError_2(FILE *dane, void *temp, long *arr) {
	if (dane)
		fclose(dane);
	if (arr)
		free(arr);
	MyStudentFree(temp);
	MyMessage(ERR);
}