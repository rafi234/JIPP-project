#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/stos.h"
#include "../include/message.h"

static STOS *wsk = NULL;
static FreeData ptr_free_data;
static readFromFile ptr_fun_read;
static SaveToFile ptr_fun_save;

void stosInit(FreeData pFreeData, readFromFile preadFromFile, SaveToFile pSaveToFile)
{
	MyMessage(INICJOWANIE_STOSU);
	wsk = NULL;
	ptr_free_data = pFreeData;
	ptr_fun_read = preadFromFile;
	ptr_fun_save = pSaveToFile ;
}

void StosFree()
{
	MyMessage(ZWALNIAMY_PAMIEC);
	STOS *p = wsk, *wtemp = NULL;
	if (!p)
	{
		MyMessage(BRAK_DANYCH);
	}
	else
	{
	while (p)
		{
			(*ptr_free_data)(p->wDane);
			wtemp = p;
			p = p->prev;
			free(wtemp);
		}
	}
	wsk = NULL;
}

STOS * stosPush(void *pD)
{
	STOS *current = (STOS *)malloc(sizeof(STOS));

	if (!current)
	{
		MyMessage(ERR_ALLOC_MEM);
	}
	current->wDane = pD;
	current->prev = wsk;
	wsk = current;

	return current;

}


STOS stosPop()
{
	STOS p;
	if (!wsk)
	{
		MyMessage(BRAK_DANYCH);
		p.wDane = NULL;
		p.prev = NULL;
	}
	else
	{
		STOS *nastepny = wsk;
		p.wDane = wsk->wDane;
		wsk = wsk->prev;
		free(nastepny);
		
	}
	
	return p;
}


void *stosSearch(void *pSd, CompData ptr, int entry, short in)
{
	static STOS *p;
	STOS *ptemp = NULL;

	if (entry)
		p = wsk;

	while (p)
	{
		if (!(*ptr)(p->wDane, pSd, in))
		{
			p = p->prev;
		}
		else
		{
			ptemp = p;
			p = p->prev;
			return ptemp->wDane;
		}
	}
	
	return NULL;
}

void *currentData()
{
	if (!wsk)
	{
		MyMessage(BRAK_DANYCH);
		return NULL;
	}
	return wsk->wDane;
}

void *myDataStos(int i)
{
	if (!wsk)
	{
		MyMessage(BRAK_DANYCH);
		return NULL;
	}
	static STOS * ptemp;
	if (i == 0)
	{
		ptemp = wsk;
		return wsk->wDane;
	}
	else 
	{
		ptemp = ptemp->prev;
		if (ptemp)
		{
			return ptemp->wDane;
		}
		else
		{
			MyMessage(BRAK_DANYCH);
			free(ptemp);

		}
	}
	return NULL;
}

int countElement() 
{
	STOS *temp = wsk;
	int element = 0;
	if (temp)
	{
		while (temp )
		{
			element++;
			temp = temp->prev;
		}
	}
	return element;
}



void stosSave()
{
	MyMessage(SAVE_FILE);

	FILE *dane;
	fopen_s(&dane, "MY_STOS.bin", "wb");
	if (!dane) {
		fclose(dane);
		MyMessage(ERR);
	}
	STOS *temp = wsk;

	int elem = countElement();

	long  *arr = (long *)malloc((elem + 1) * sizeof(long));

	if (!arr)
	{
		exitError_2(dane, temp->wDane, arr);
	}

	if (fwrite(&elem, sizeof(int), 1, dane) != 1)
	{
		exitError_2(dane, temp->wDane, arr);
	}

	fseek(dane, (elem + 1) * sizeof(long), 1);

	size_t i = 0;
	
	while (temp)
		{
			arr[i] = ftell(dane);
			ptr_fun_save(temp->wDane, dane, &arr[i++]);
			temp = temp->prev;
		} 
	
	arr[i] = ftell(dane);
	fseek(dane, sizeof(int), 0);

	if (fwrite(arr, sizeof(long), elem + 1, dane) != elem + 1)
	{
		exitError_2(dane, temp->wDane, arr);
	}

	if (dane)
		fclose(dane);
	dane = NULL;

	if (arr)
		free(arr);
	arr = NULL;
}

void StosRead() {

	StosFree();

	MyMessage(OPEN_FILE);
	FILE *dane;
	fopen_s(&dane, "MY_STOS.bin", "rb");

	if (!dane) 
		MyMessage(ERR_NO_FILE);

	unsigned int elem = 0, i, rec;
	long *arr = NULL;
	

	if (fread(&elem, sizeof(int), 1, dane) != 1)
	{
		exitError_1(dane, arr);
	}
	arr = (long *)malloc((elem + 1) *sizeof(long));

	if (!arr)
	{
		exitError_1(dane, arr);
	}

	if (fread(arr, sizeof(long), elem + 1, dane) != elem + 1)
	{
		exitError_1(dane, arr);
	}

	for (i = 0; i < elem; ++i)
	{
		rec = elem - i - 1;
		fseek(dane, arr[rec], 0);

		void* pDat = ptr_fun_read(dane, arr, rec, elem);

 		stosPush(pDat);	
	}

	if (arr) 	
		free(arr);
	arr = NULL;

	if (dane)
		fclose(dane);
	dane = NULL;
}
