#include "quickSortExt.h"   

void lerSup(FILE *arqlS, int *reg, int *lS, int nBytes, short int *ordem)
{
    //posiciona o cursor em lS*nBytes distante do início do arquivo
    //E armazena em reg o valor contido nessa posição
    fseek(arqlS, *(lS)*nBytes, SEEK_SET);
    fread(reg, nBytes, 1, arqlS);
    //decrementa o indicador
    (*lS)--;
    //indica que a próxima leitura é lerInf
    *ordem = 0;
}

void lerInf(FILE *arqlI, int *reg, int *lI, int nBytes, short int *ordem)
{
    //posiciona o cursor em lI*nBytes distante do início do arquivo
    //E armazena em reg o valor contido nessa posição
    fseek(arqlI, *(lI)*nBytes, SEEK_SET);
    fread(reg, nBytes, 1, arqlI);
    //incrementa o indicador
    (*lI)++;
    //indica que a próxima leitura é lerSup
    *ordem = 1;
}

void escSup(FILE *arqES, int *reg, int *eS, int nBytes)
{
    //posiciona o cursor em eS*nBytes distante do início do arquivo
    //E escreve nessa posição o conteúdo de reg
    fseek(arqES, *(eS)*nBytes, SEEK_SET);
    fwrite(reg, 1, nBytes, arqES);
    //decrementa o indicador
    (*eS)--;
}

void escInf(FILE *arqEI, int *reg, int *eI, int nBytes)
{
    //posiciona o cursor em eI*nBytes distante do início do arquivo
    //E escreve nessa posição o conteúdo de reg
    fseek(arqEI, *(eI)*nBytes, SEEK_SET);
    fwrite(reg, nBytes, 1, arqEI);
    //incrementa o indicador
    (*eI)++;
}

void inserirArea(int *area, int *reg, int *areaOcupada)
{
    int i = *areaOcupada; 
    //Armazena na memória primária de forma ordenada
    //Enquanto não encontrar um elemento menor que reg ou chegar ao inicio do vetor
    //Desloca o elemento verificado em uma posição para direita
    while(i > 0)
    {
        if(area[i-1] > *reg)
            area[i] = area[i-1];
        else    
            break;
        i--;
    }
    //Armazena reg na posição 
    //incrementa areaOcupada
    area[i] = *reg;
    (*areaOcupada)++;
}

void rmvPrimeiroArea(int *area, int *areaOcupada)
{
    int i = 0;
    //Remove o primeiro elemento da memória primária
    //Desloca o vetor em uma posição para esquerda
    for(i = 0;i < *areaOcupada; i++)
        area[i] = area[i+1];
    //Decrementa areaOcupada
    (*areaOcupada)--;
}

void particao(FILE *arq,int inicio, int fim, int *i, int *j, int tamArea)
{
    //aloca espaço na memória primária
    int *area = (int*)calloc(tamArea, sizeof(int));
    int areaOcupada = 0;

    //variável de índice
    int k = 0;
    //variáveis que indicam posição:
    //lI - leitura inferior
    //lS - leitura superior
    //eI - escrita inferior
    //eS - escrita Superior
    int lI = inicio;
    int lS = fim;
    int eI = inicio;
    int eS = fim;
    //variável que indica a ordem de leitura
    unsigned short int ordem = 1;
    
    //Armazenam os limites superiores e inferiores da memória primária
    int limInf = INT32_MIN;
    int limSup = INT32_MAX;
    
    //Armazena o valor lido/escrito
    int valor = 0;

    //Indicam a posição da área ordenada
    (*i) = inicio - 1;
    (*j) = fim + 1;

    while(lS >= lI)
    {
        if(areaOcupada + 1 < tamArea)
        {
            //Preenche a área na memória principal até areaOcupada = tamArea - 1
            //Lendo de forma alternada entre Leitura Superior e Leitura Inferior
            if(ordem == 1)
                lerSup(arq, &valor, &lS, sizeof(int), &ordem);
            else
                lerInf(arq, &valor, &lI, sizeof(int), &ordem);
            
            inserirArea(area, &valor, &areaOcupada);
        }
        //areaOcupada = tamArea - 1
        else
        {
            //Interrompe, se necessário, a ordem alternada de leitura para evitar que dados sejam sobrescritos
            if(lI == eI)
                lerInf(arq, &valor, &lI, sizeof(int), &ordem);
            else if(lS == eS)
                lerSup(arq, &valor, &lS, sizeof(int), &ordem);
            else
            {
                //Ordem alternada de leitura
                if(ordem == 1)
                    lerSup(arq, &valor, &lS, sizeof(int), &ordem);
                else
                    lerInf(arq, &valor, &lI, sizeof(int), &ordem);
            }
            //Verifica se o valor lido está dentro dos limites de valor da memória primária
            //Se não tiver será escrito na memória secundária sem ser armazenado na memória primária
            if(valor > limSup)
            {
                (*j) = eS;
                escSup(arq, &valor, &eS, sizeof(int));
            }
            else if(valor < limInf)
            {
                (*i) = eI;
                escInf(arq, &valor, &eI, sizeof(int));
            }
            else
            {
                //Valor dentro dos limites superior e inferior
                //armazena na memória primária
                inserirArea(area, &valor, &areaOcupada);
                //memória primária cheia
                if(eI - inicio < fim - eS) 
                {
                    //Se a area inferior for menor remove o menor elemento da memória primária
                    //Escreve esse elemento na memória secundária
                    //atribui a limInf o valor desse elemento
                    escInf(arq, &(area[0]), &eI, sizeof(int));
                    limInf = area[0];
                    rmvPrimeiroArea(area, &areaOcupada);
                }
                else
                {
                    //senão remove o maior elemento da memória primária 
                    //Escreve esse elemento na memória secundária
                    //atribui a limSup o valor desse elemento
                    escSup(arq, &(area[areaOcupada-1]), &eS, sizeof(int));
                    limSup = area[areaOcupada-1];
                    areaOcupada--;
                }
            }
        }
    }
    //Fim da partição
    //Escreve no arquivo enquanto houver elementos na memória primária
    //Escrita realizada na posição de escrita inferior
    for(k = 0; k < areaOcupada; k++)
        escInf(arq, &(area[k]), &eI, sizeof(int));
}

void quickSortExterno(FILE *arq, int inicio, int fim, int tamArea)
 {
    int i = inicio;
    int j = fim;
    //Se a área tiver mais que 1 elemento
    if(fim - inicio > 1)
    {
        //chama partição para a área do arquivo
        particao(arq, inicio, fim, &i, &j, tamArea);
        //Verifica qual das áreas desordenadas é menor
        //Chama recursivamente quickSortExterno para essa área
        //Chama recursivamente quickSortExterno para a outra área
        if((i - inicio) > (fim - j))
        { 
            quickSortExterno(arq, j, fim, tamArea);
            quickSortExterno(arq, inicio, i, tamArea);
        }
        else
        {
            quickSortExterno(arq, inicio, i, tamArea);
            quickSortExterno(arq, j, fim, tamArea);
        }
    
    }
 }