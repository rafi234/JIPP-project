#pragma once

enum BLEDY_I_KOMUNIKATY
{
	START_PROGRAMU,
	INICJOWANIE_STOSU ,
	BLEDNA_KOMENDA,
	POP_LAST,
	NOT_INTEGER,
	NOT_INTEGER_1,
	SAVE_FILE,
	OPEN_FILE,
	ALLOKUJEMY_PAMIEC,
	ZWALNIAMY_PAMIEC,
	BRAK_DANYCH,
	KONIEC,
	ERR_ALLOC_MEM,
	ERR_NO_FILE,
	ERR

};

void MyMessage(enum BLEDY_I_KOMUNIKATY numb);
void exitError_1(FILE *dane, long *arr);
void exitError_2(FILE *dane, void * temp, long *arr);