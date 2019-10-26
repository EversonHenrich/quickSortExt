#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

/*  void lerSup: 
        Lê nBytes do arquivo apontado por arqLS na posição lS*nBytes distante do início do arquivo, armazena os dados lidos em reg, decrementa lS e
altera ordem para 0.
            - FILE *arqLS - ponteiro para o arquivo onde será realizada a leitura.
            - int *reg - ponteiro para inteiro da variável que armazenará os dados lidos.
            - int *lS - ponteiro para inteiro que indica a posição a ser lida.
            - short int *ordem - ponteiro para inteiro (short) que indica qual será a próxima leitura(1 para lerSup e 0 para lerInf).
        Sem retorno.
*/
void lerSup(FILE *arqLS, int *reg, int *lS, int nBytes, short int *ordem);

/*  void lerInf: 
        Lê nBytes do arquivo apontado por arqLI na posição lI*nBytes distante do início do arquivo, armazena os dados lidos em reg, incrementa lI e
altera ordem para 1.
            - FILE *arqLI - ponteiro para o arquivo onde será realizada a leitura.
            - int *reg - ponteiro para inteiro da variável que armazenará os dados lidos.
            - int *lI - ponteiro para inteiro que indica a posição a ser lida.
            - short int *ordem - ponteiro para inteiro (short) que indica qual será a próxima leitura(1 para lerSup e 0 para lerInf).
        Sem retorno.
*/
void lerInf(FILE *arqLI, int *reg, int *lI, int nBytes, short int *ordem);

/*  void escSup: 
        Escreve nBytes da variável reg no arquivo apontado por arqES na posição eS*nBytes distante do início do arquivo e decrementa eS.
            - FILE *arqES - ponteiro para o arquivo onde será realizada a escrita.
            - int *reg - ponteiro para inteiro da variável que terá seus dados escritos no arquivo.
            - int *eS - ponteiro para inteiro que indica a posição a ser escrita
        Sem retorno.
*/
void escSup(FILE *arqES, int *reg, int *eS, int nBytes);

/*  void escInf: 
        Escreve nBytes da variável reg no arquivo apontado por arqEI na posição eI*nBytes distante do início do arquivo e incrementa eI.
            - FILE *arqEI - ponteiro para o arquivo onde será realizada a escrita.
            - int *reg - ponteiro para inteiro da variável que terá seus dados escritos no arquivo.
            - int *eI - ponteiro para inteiro que indica a posição a ser escrita.
        Sem retorno.
*/
void escInf(FILE *arqEI, int *reg, int *eI, int nBytes);

/*  void inserirArea:
        Insere a variável reg de forma ordenada na área da memória primária apontada por area e incrementa areaOcupada.
            - int *reg - ponteiro para inteiro da variável que será armazenada na área.
            - int *area - ponteiro para inteiro da área da memória primária.
            - int *areaOcupada - ponteiro para inteiro da variável que armazena a area ocupada da memória primária.
        Sem retorno.
*/
void inserirArea(int *reg, int *area, int *areaOcupada);

/*  void rmvPrimeiroArea:
        Remove o primeiro elemento armazenado na área da memória primária apontada por area e decrementa areaOcupada.
            - int *area - ponteiro para inteiro da área da memória primária.
            - int *areaOcupada - ponteiro para inteiro da variável que armazena a area ocupada da memória primária.
        Sem retorno.
*/
void rmvPrimeiroArea(int *area, int *areaOcupada);

/*  void particao:
        Particiona o arquivo apontado por arq em três áreas:
        área 1 - Elementos menores que o menor elemento da área 2.
        área 2 - Elementos ordenados.
        área 3 - Elementos maiores que o maior elemento da área 2.
            - FILE *arq - ponteiro para o arquivo à ser particionado.
            - int inicio - inteiro que indica o primeiro elemento do vetor à ser particionado.
            - int fim - inteiro que indica o último elemento do vetor à ser particionado.
            - int *i - ponteiro para inteiro que indica o início da área 2.
            - int *j - ponteiro para inteiro que indica o fim da área 2.
            - int tamArea - inteiro que indica o tamanho da área na memória principal.
        Sem retorno.
*/
void particao(FILE *arq, int inicio, int fim, int *i, int*j, int tamArea);

/*  void quickSortExterno:
        Ordena os dados do arquivo apontado por arq.
            - FILE *arq - ponteiro para o arquivo à ser ordenado.
            - int inicio - inteiro que indica o primeiro elemento do vetor à ser ordenado.
            - int fim - inteiro que indica o último elemento do vetor à ser ordenado.
            - int tamArea - inteiro que indica o tamanho da área na memória principal.
        Sem retorno.
*/
void quickSortExterno(FILE *arq, int inicio, int fim, int tamArea);
