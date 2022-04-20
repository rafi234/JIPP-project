#pragma once

enum  kierunek_studiow
{
	architektura = 1,
	automatyka_i_robotyka,
	budownictwo,
	informatyka,
	informatyka_stosowana,
	infotronika,
	matematyka,

};

struct MY_STUDENT
{

	char *nazwisko;
	enum kierunek_studiow kierunek;
	unsigned int wiek;

};



void *myStudentInit(char *nnazwisko, enum kierunek_studiow kkier, unsigned int wwiek);
void MyStudentFree(void *wsk);
void *MyStudentPush(char *nnazwisko, enum kierunek_studiow kkier, unsigned int wwiek);
void MyStudentPrint(void *wsk);
int MyStudentSearch(void *pC, void *pS, short in);
void MyStudentSave(void *ptr, FILE *dane, long *arr);
void *MyStudentRead(FILE *dane, long *arr, unsigned int rec, unsigned int elem);
