#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "../include/myStudent.h"
#include <string.h>
#include "../include/message.h"

void *myStudentInit(char *nnazwisko, enum kierunek_studiow kkier, unsigned int wwiek)
{
	MY_STUDENT *temp = (MY_STUDENT *)malloc(sizeof(MY_STUDENT));

	if (!temp)
	{
		MyStudentFree(temp);
		MyMessage(ERR_ALLOC_MEM);
	}

	temp->nazwisko = (char *)malloc((strlen(nnazwisko)  * sizeof(char)) + 1);
	if (!temp->nazwisko)
	{
		free(temp->nazwisko);
		MyMessage(ERR_ALLOC_MEM);
	}
	
	strcpy_s(temp->nazwisko, (strlen(nnazwisko) * sizeof(char)) + 1, nnazwisko);
	temp->kierunek = kkier;
	temp->wiek = wwiek;		
	

	return (void *)(temp);														 
}
  

void MyStudentFree(void *wsk)
{
	MY_STUDENT *dane = (MY_STUDENT *)wsk; 

	if (!dane) return;

	if (dane->nazwisko) 
		free(dane->nazwisko);
	dane->nazwisko = NULL;
	
	free(dane);
}


void *MyStudentPush(char *nnazwisko, enum kierunek_studiow kkier, unsigned int wwiek)
{
	return myStudentInit(nnazwisko, kkier, wwiek);
}


void MyStudentPrint(void *wsk)
{
	MY_STUDENT *p = (MY_STUDENT *)wsk;
	if (p)
	{
		printf("Nazwisko: %s\n", p->nazwisko);
		printf("Wiek    : %d\n", p->wiek);
		printf("Kierunek: ");
		switch (p->kierunek)
		{
		case architektura: puts("Architektura\n"); break;
		case automatyka_i_robotyka: puts("Automatyka i Robotyka\n"); break;
		case budownictwo: puts("Budownictwo\n"); break;
		case informatyka: puts("Informatyka\n"); break;
		case informatyka_stosowana: puts("Informatyka Stosowana\n"); break;
		case infotronika: puts("Informatyka\n"); break;
		case matematyka: puts("Matematyka\n"); break;
		}
	}
}


int MyStudentSearch(void *pC, void *pS, short in)
{
	MY_STUDENT *pcur = (MY_STUDENT *)pC;
	MY_STUDENT *pSearch = (MY_STUDENT *)pS;
	if (in == 1)
	{
		if (strcmp(pcur->nazwisko, pSearch->nazwisko) == 0)
			return 1;
	}
	else if (in == 2)
	{
		if (pcur->wiek == pSearch->wiek)
			return 1;
	}
	else
	{
		if (pcur->kierunek == pSearch->kierunek)
			return 1;
	}
	return 0;
}


/*
void MyStudentSave(void *ptr, FILE *dane, long *arr)
{
	MyMessage(SAVE_FILE);
	MY_STUDENT *temp = (MY_STUDENT*)ptr;
	size_t len = 0;


	if (temp) {
		//SF prosze zapisac obiekt do pliku jako calosc, a nie skladowa-po-skladowej
		len = strlen(temp->nazwisko);
		if (fwrite((const void *)&len, sizeof(size_t), 1, dane) != 1)
		{
			exitError_1(dane, arr);
		}
		if (fwrite((const void *)temp->nazwisko, sizeof(char), len + 1, dane) != len + 1)
		{
			exitError_1(dane, arr);
		}
		if (fwrite((const void *)&temp->kierunek, sizeof(int), 1, dane) != 1)
		{
			exitError_1(dane, arr);
		}
		if (fwrite((const void *)&temp->wiek, sizeof(unsigned int), 1, dane) != 1)
		{
			exitError_1(dane, arr);
		}
	}
}

void *MyStudentRead(FILE* dane, long *arr, unsigned int rec, unsigned int elem)
{

	MY_STUDENT *temp = NULL;

	temp = (MY_STUDENT *)malloc(elem * sizeof(MY_STUDENT));

	memset(temp, 0, elem * sizeof(MY_STUDENT));
	//SF prosze odczytac obiekt do pliku jako calosc, a nie skladowa-po-skladowej

	size_t len = 0;
	if (fread((void *)&len, sizeof(size_t), 1, dane) != 1)
	{
		exitError_2(dane, temp, arr);
	}
	temp[rec].nazwisko = (char *)malloc((len + 1) * sizeof(char));

	if (fread((void *)temp[rec].nazwisko, sizeof(char), len + 1, dane) != len + 1)
	{
		exitError_2(dane, temp, arr);
	}
	if (fread((void *)&temp[rec].kierunek, sizeof(int), 1, dane) != 1)
	{
		exitError_2(dane, temp, arr);
	}
	if (fread((void *)&temp[rec].wiek, sizeof(unsigned int), 1, dane) != 1)
	{
		exitError_2(dane, temp, arr);
	}

	void *pDat = MyStudentPush(temp[rec].nazwisko, temp[rec].kierunek, temp[rec].wiek);

	MyStudentFree(temp);

	return pDat;
}*/

void MyStudentSave(void *ptr, FILE *dane, long *arr)
{
	MY_STUDENT *temp = (MY_STUDENT*)ptr;
	size_t len = 0;

	
	if (temp) {
		//SF prosze zapisac obiekt do pliku jako calosc, a nie skladowa-po-skladowej
		size_t len = strlen(temp->nazwisko);

		if (fwrite((const void *)temp, sizeof(MY_STUDENT), 1, dane) != 1)
		{
			exitError_1(dane, arr);
		}

		if (fwrite((const void *)&len, sizeof(size_t), 1, dane) != 1)
		{
			exitError_1(dane, arr);
		}

		if (fwrite((const void *)temp->nazwisko, sizeof(char), len + 1 , dane) != len + 1)
		{
			exitError_1(dane, arr);
		}

		
	}
}

void *MyStudentRead(FILE* dane, long *arr, unsigned int rec, unsigned int elem)
{
	
	MY_STUDENT *temp = NULL;

	temp = (MY_STUDENT *)malloc(elem * sizeof(MY_STUDENT));

	memset(temp, 0, elem * sizeof(MY_STUDENT));
	//SF prosze odczytac obiekt do pliku jako calosc, a nie skladowa-po-skladowej
	size_t len = 0;


	if (fread((void *)&temp[rec], sizeof(MY_STUDENT), 1, dane) != 1)
	{
		exitError_2(dane, temp, arr);
	}

	if (fread((void *)&len, sizeof(size_t), 1, dane) != 1)
	{
		exitError_2(dane, temp, arr);
	}

	temp[rec].nazwisko = (char *)malloc((len + 1) * sizeof(char));

	if (fread((void *)temp[rec].nazwisko, sizeof(char), len + 1, dane) != len + 1)
	{
		exitError_2(dane, temp, arr);
	}

	void *pDat = MyStudentPush(temp[rec].nazwisko, temp[rec].kierunek, temp[rec].wiek);

	MyStudentFree(temp);

	return pDat;
}