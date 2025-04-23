#include <stdlib.h>

void merge(int vet[], int inicio, int meio, int fim) {
    int com1 = inicio, com2 = meio+1, comAux = 0, tam = fim-inicio+1;
    int *vetAux;
    vetAux = (int*)malloc(tam * sizeof(int));

    while(com1 <= meio && com2 <= fim){
        if(vet[com1] < vet[com2]) {
            vetAux[comAux] = vet[com1];
            com1++;
        } else {
            vetAux[comAux] = vet[com2];
            com2++;
        }
        comAux++;
    }

    while(com1 <= meio){  /*Caso ainda haja elementos na primeira metade*/
        vetAux[comAux] = vet[com1];
        comAux++;
        com1++;
    }

    while(com2 <= fim) {   /*Caso ainda haja elementos na segunda metade*/
        vetAux[comAux] = vet[com2];
        comAux++;
        com2++;
    }

    for(comAux = inicio; comAux <= fim; comAux++){    /*Move os elementos de volta para o vet original*/
        vet[comAux] = vetAux[comAux-inicio];
    }
    
    free(vetAux);
}

void mergeSort(int vet[], int comeco, int fim){
    if (comeco < fim) {
        int meio = (fim+comeco)/2;

        mergeSort(vet, comeco, meio);
        mergeSort(vet, meio+1, fim);
        merge(vet, comeco, meio, fim);
    }
}

void mergeSortAux(int v[], int n) {
    mergeSort(v, 0, n - 1);
}
