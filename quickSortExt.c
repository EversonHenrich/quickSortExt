#include "quickSortExt.h"   
//TESTADO
void lerSup(FILE *arqLS, int *reg, int *lS, int nBytes, short int *ordem)
{
    fseek(arqLS, *(lS)*nBytes, SEEK_SET);
    fread(reg, nBytes, 1, arqLS);
    (*lS)--;
    *ordem = 0;
}
//TESTADO
void lerInf(FILE *arqLI, int *reg, int *lI, int nBytes, short int *ordem)
{
    fseek(arqLI, *(lI)*nBytes, SEEK_SET);
    fread(reg, nBytes, 1, arqLI);
    (*lI)++;
    *ordem = 1;
}
//TESTADO
void escSup(FILE *arqES, int *reg, int *eS, int nBytes)
{
    fseek(arqES, *(eS)*nBytes, SEEK_SET);
    fwrite(reg, 1, nBytes, arqES);
    (*eS)--;
}
//TESTADO
void escInf(FILE *arqEI, int *reg, int *eI, int nBytes)
{
    fseek(arqEI, *(eI)*nBytes, SEEK_SET);
    fwrite(reg, nBytes, 1, arqEI);
    (*eI)++;
}
//TESTADO
void inserirArea(int *area, int *reg, int *areaOcupada)
{
    int aux;
    int i = *areaOcupada; 

    while(i > 0)
    {
        if(area[i-1] > *reg)
            area[i] = area[i-1];
        else    
            break;
        i--;
    }
    area[i] = *reg;
    (*areaOcupada)++;
}

void removerPrimArea(int *area, int *areaOcupada)
{
    int i = 0;
    for(i = 0;i < *areaOcupada; i++)
        area[i] = area[i+1];
    (*areaOcupada)--;
}

int particao(FILE *arq,int inicio, int fim, int tamArea)
{

    int *area = (int*)calloc(tamArea, sizeof(int));
    int areaOcupada = 0;

    int i = inicio - 1;
    int j = fim + 1;
    int k = 0;

    int lI = inicio;
    int lS = fim;
    int eI = inicio;
    int eS = fim;
    unsigned short int ordem = 1;

    int limInf = INT32_MIN;
    int limSup = INT32_MAX;
    
    int valor = 0;

    while(lS > lI)
    {
        if(areaOcupada + 1 < tamArea)
        {
            if(ordem == 1)
                lerSup(arq, &valor, &lS, sizeof(int), &ordem);
            else
                lerInf(arq, &valor, &lI, sizeof(int), &ordem);
            
            inserirArea(area, &valor, &areaOcupada);
        }
        else
        {
            if(lI == eI)
                lerInf(arq, &valor, &lI, sizeof(int), &ordem);
            else if(lS == eS)
                lerSup(arq, &valor, &lS, sizeof(int), &ordem);
            else
            {
                if(ordem == 1)
                    lerSup(arq, &valor, &lS, sizeof(int), &ordem);
                else
                    lerInf(arq, &valor, &lI, sizeof(int), &ordem);
            }
            
            if(valor > limSup)
            {
                j = eS;
                escSup(arq, &valor, &eS, sizeof(int));
                
            }

            else if(valor < limInf)
            {
                i = eI;
                escInf(arq, &valor, &eI, sizeof(int));
            }
            else
                inserirArea(area, &valor, &areaOcupada);

            if((i - inicio) < (fim - j))
            {
                escInf(arq, &(area[0]), &eI, sizeof(int));
                limInf = area[0];
                removerPrimArea(area, &areaOcupada);
            }
            else
            {
                escSup(arq, &(area[areaOcupada]), &eS, sizeof(int));
                limSup = area[areaOcupada];
                areaOcupada--;
            }
        }
    }
    for(k = 0; k < tamArea; k++)
        escInf(arq, &(area[k]), &eI, sizeof(int));
    return 0;
}