#include "quickSortExt.c"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>




int gerarArquivoInt(FILE *arq, int nElem)
{
    int i = 0;
    int *value;
    value = (int*)calloc(nElem, sizeof(int));

    srand(time(NULL));
    rewind(arq);

    for(i = 0; i < nElem; i++)
    {
        value[i] = nElem - i;
    }
    fwrite(value, sizeof(int), nElem, arq);
    return 0;
}

int main()
{
    FILE *arq = fopen("test1.bin", "rb+");
    int value = 0;
    int i = 0;
    int li = 0;
    short int o = 0;

    gerarArquivoInt(arq, 10);
    while(li < 10)
    {
        lerInf(arq, &value, &li, sizeof(int), &o);
        printf("%d  %d\n", value, li);
    }
    printf("==============\n");
    particao(arq, 0, 10, 10);
    li = 0;
    while(li < 10)
    { 
        lerInf(arq, &value, &li, sizeof(int), &o);
        printf("%d  %d\n", value, li);
    }

    return 0;
}