#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE 20
#define LOOKAHEAD_SIZE 15




typedef struct
{
    int distancia;
    int tamanho;
    char prox;
} Tupla;




int compressao(char *entrada, int tam_entrada, Tupla *saida)
{
    int i = 0, k = 0;
   
    while (i < tam_entrada)
    {
        int tam_max = 0;
        int distancia_max = 0;
       
        // percorre a frase de acordo com a distancia dos caracteres
        for (int distancia = 1; distancia <= i; distancia++) {
           
            int tam = 0;
           
           // verifica se há repetição de caracteres
            while (entrada[i + tam] == entrada[i - distancia + tam])
                tam++;
           
            if (tam > tam_max)
            {
                tam_max = tam;
                distancia_max = distancia;
            }
        }
       
        // inserindo na tupla, informações de elementos repetidos no dic
        if (tam_max > 0)
        {
            saida[k].distancia = distancia_max;
            saida[k].tamanho = tam_max;
            saida[k].prox = entrada[i + tam_max];
            i += tam_max + 1;
        }
       
        // inserindo na tupla, informações de elementos que não estão no dic
        else
        {
            saida[k].distancia = 0;
            saida[k].tamanho = 0;
            saida[k].prox = entrada[i];
            i++;
        }
        k++;
    }
   
    // retorna as tuplas - compressao da frase
    for (int i = 0; i < k; i++)
        printf("(%d, %d, %c) ", saida[i].distancia, saida[i].tamanho, saida[i].prox);
   
    printf("\n");


    return k;
}




int decompressao(Tupla *entrada, int tam_entrada, char *saida)
{
    int i = 0, j = 0;
   
    while (i < tam_entrada)
    {
        // se o caracter ainda nao estava no dicionario
        if (entrada[i].distancia == 0 && entrada[i].tamanho == 0)
        {
            saida[j] = entrada[i].prox;
            i++;
            j++;
        }
       
        // caso o caracter ja esteja no dicionario (repeticao)
        else
        {
            int tam = j - entrada[i].distancia;
           
            for (int l = 0; l < entrada[i].tamanho; l++) {
                saida[j] = saida[tam + l]; // retorna o caracter repetido
                j++;
            }
           
            // retorna o caracter que foi adicionado junto com o caracter repetido
            saida[j] = entrada[i].prox;
            i++;
            j++;
        }
    }
    return j;
}




int main()
{
    char entrada[BUFFER_SIZE];
    Tupla saida[BUFFER_SIZE];
    char decompressado[BUFFER_SIZE];


    printf("Digite uma frase: ");
    fgets(entrada, BUFFER_SIZE, stdin);
   
    int tam_entrada = strlen(entrada);
    entrada[tam_entrada] = '\0';
   
    printf("Compressao: ");
    int tam_tupla = compressao(entrada, tam_entrada, saida);


    decompressao(saida, tam_tupla, decompressado);
    printf("Decompressao: %s", decompressado);


    return 0;
}
