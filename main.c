#include "quickSortExt.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct {
    int a;
}teste;


int compara(teste *a, teste *b)
{
    if(a->a == b->a)
        return 0;
    else if(a->a > b->a)
        return 1;
    else
        return -1;
}


int gerarArquivoInt(FILE *arq, int nElem)
{
    int i = 0;
    teste *value = (teste*)calloc(nElem, sizeof(teste));

    srand(time(NULL));
    rewind(arq);

    for(i = 0; i < nElem; i++)
    {
        value[i].a = rand()%1000;
    }
    return fwrite(value, sizeof(teste), nElem, arq);
}



int main()
{
    FILE *arq = fopen("test1.bin", "wb+");
    teste value;
    int li = 0;
    int i = 0;
    int j = 0;
    short int o = 0;

    printf("%d valores gerados.\n", gerarArquivoInt(arq, 50));
    printf("Arquivo antes do quickSortExterno\n");

    while(li < 50)
    {
        lerInf(arq, (void*)(&value), &li, sizeof(teste), &o);
        printf("%d - \t%d\n", li, value.a);
    }

    quickSortExterno(arq, 0, 49, 15, sizeof(teste), compara);

    li = 0;
    printf("==========================\n");
    printf("Arquivo apos quickSortExterno\n");

    while(li < 50)
    {
        lerInf(arq, (void*)(&value), &li, sizeof(teste), &o);
        printf("%d - \t%d\n", li, value.a);
    }
    
    return 0;
}