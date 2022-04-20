
typedef void (*FreeData)(void *pdat);
typedef int (CompData)(void * pcurData, void * pSearchData, short in);
typedef void  *(*readFromFile)(FILE *dane, long *arr, unsigned int rec, unsigned int elem);
typedef void (*SaveToFile)(void *ptr, FILE *dane, long *arr);


struct STOS
{
	void *wDane;
	STOS *prev;
};


void stosInit(FreeData pFreeData, readFromFile preadFromFile, SaveToFile pSaveToFile);
void StosFree();
STOS *stosPush(void *pD);
STOS stosPop();
void *stosSearch(void *pSd, CompData ptr, int entry, short in);
void *currentData();
void *myDataStos(int i);
int countElement();
void stosSave();
void StosRead();

