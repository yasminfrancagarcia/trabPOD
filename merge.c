#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

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

    while(com1 <= meio){  //Caso ainda haja elementos na primeira metade
        vetAux[comAux] = vet[com1];
        comAux++;
        com1++;
    }

    while(com2 <= fim) {   //Caso ainda haja elementos na segunda metade
        vetAux[comAux] = vet[com2];
        comAux++;
        com2++;
    }

    for(comAux = inicio; comAux <= fim; comAux++){    //Move os elementos de volta para o vet original
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

double difTempo(struct timespec t0, struct timespec t1){
    return (t1.tv_sec - t0.tv_sec) + (double)(t1.tv_nsec - t0.tv_nsec) * 1e-9;
  }
  
int main(int argc, char *argv[]){
    int  i;
    int *vet;
    char linha[16];
    int tamVet;
    struct timespec t0, t1;
  
    if(argc < 2){
      printf("Uso: %s <numero de elementos a ordenar>\n", argv[0]);
      exit(0);
    }
    tamVet = atoi(argv[1]);
    vet = (int *) malloc(sizeof(int) * tamVet);
  
    clock_gettime(CLOCK_MONOTONIC_RAW, &t0);
    for(i=0; i<tamVet; i++){
      fgets(linha, 16, stdin);
      sscanf(linha, "%d", &vet[i]);
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
    printf("Tempo leitura de dados: %f\n", (float)difTempo(t0, t1));
   // mostra(vet,tamVet);
  
    clock_gettime(CLOCK_MONOTONIC_RAW, &t0);
    mergeSort(vet, 0, tamVet-1);
    clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
    printf("Tempo merge Sort: %f\n", (float)difTempo(t0, t1));
  // mostra(vet,tamVet);
  
    exit(0);
  }
  
