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
        value[i] = rand()%100;
    }
    fwrite(value, sizeof(int), nElem, arq);
}

int main()
{
    FILE *arq = fopen("test1.bin", "rb+");
    int value = 0;
    int li = 0;
    short int o = 0;

    gerarArquivoInt(arq, 10);
    while(li < 10)
    {
        lerInf(arq, &value, &li, sizeof(int), &o);
        printf("%d - \t%d\n", li, value);
    }
    quickSortExterno(arq, 0, 9, 3);
    li = 0;
    while(li < 10)
    {
        lerInf(arq, &value, &li, sizeof(int), &o);
        printf("%d - \t%d\n", li, value);
    }

    return 0;
}