#include "quickSortExt.c"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>




void gerarArquivoInt(FILE *arq, int nElem)
{
    int i = 0;
    int *value = (int*)calloc(nElem, sizeof(int));

    srand(time(NULL));
    rewind(arq);

    for(i = 0; i < nElem; i++)
    {
        // value[i] = nElem - i;
        value[i] = rand()%1000;
    }
    fwrite(value, sizeof(int), nElem, arq);
}



int main()
{
    FILE *arq = fopen("test1.bin", "rb+");
    int value = 0;
    int li = 0;
    int i = 0;
    int j = 0;
    short int o = 0;

    gerarArquivoInt(arq, 100);
    printf("Arquivo antes do quickSortExterno\n");
    while(li < 100)
    {
        lerInf(arq, &value, &li, sizeof(int), &o);
        printf("%d - \t%d\n", li, value);
    }
    quickSortExterno(arq, 0, 99, 20);
    li = 0;
    printf("==========================\n");
    printf("Arquivo apos quickSortExterno\n");
    while(li < 100)
    {
        lerInf(arq, &value, &li, sizeof(int), &o);
        printf("%d - \t%d\n", li, value);
    }
    return 0;
}