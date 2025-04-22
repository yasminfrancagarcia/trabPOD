#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

typedef struct {
    int topo;
    int* balde;
    int capacidade;
} bucket;


int *insertSort(int *vetor, int tam){
    int cont, cont2, cont3, aux;
  
    for(cont=1; cont < tam; cont++){
      if(vetor[cont] < vetor[cont-1]){
          aux = vetor[cont];
          cont2 = cont;
          while(aux < vetor[cont2-1] && ((cont2) > 0)){
              vetor[cont2] = vetor[cont2-1];
              cont2--;
          }
          vetor[cont2]=aux;
      }
    }
    return vetor;
  }
void bucket_sort(int v[], int tam) {
    if (tam <= 0) return;

    // Definindo número de buckets e tamanho do bucket dinamicamente
    int num_bucket = tam / 10 + 1;
    bucket* b = malloc(num_bucket * sizeof(bucket));

    // Inicializando buckets
    for (int i = 0; i < num_bucket; i++) {
        b[i].topo = 0;
        b[i].capacidade = tam / num_bucket + 2; // espaço extra
        b[i].balde = malloc(b[i].capacidade * sizeof(int));
    }

    // Encontrar o maior valor para normalização
    int maior = v[0];
    for (int i = 1; i < tam; i++) {
        if (v[i] > maior)
            maior = v[i];
    }

    // Distribuir valores nos buckets
    for (int i = 0; i < tam; i++) {
        int idx = (v[i] * num_bucket) / (maior + 1);  // mapeamento proporcional
        if (b[idx].topo < b[idx].capacidade) {
            b[idx].balde[b[idx].topo++] = v[i];
        } else {
            // Realocar bucket se precisar
            b[idx].capacidade *= 2;
            b[idx].balde = realloc(b[idx].balde, b[idx].capacidade * sizeof(int));
            b[idx].balde[b[idx].topo++] = v[i];
        }
    }

    // Ordenar cada bucket individualmente
    for (int i = 0; i < num_bucket; i++) {
        if (b[i].topo > 0) {
            insertSort(b[i].balde, b[i].topo);
        }
    }

    // Juntar todos os elementos de volta no vetor
    int k = 0;
    for (int i = 0; i < num_bucket; i++) {
        for (int j = 0; j < b[i].topo; j++) {
            v[k++] = b[i].balde[j];
        }
        free(b[i].balde);
    }

    free(b);
}
double difTempo(struct timespec t0, struct timespec t1){
    return (t1.tv_sec - t0.tv_sec) + (double)(t1.tv_nsec - t0.tv_nsec) * 1e-9;
}

void main(int argc, char *argv[]){
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
  
    for(i=0; i<tamVet; i++){
      fgets(linha, 16, stdin);
      sscanf(linha, "%d", &vet[i]);
    }
  
    clock_gettime(CLOCK_MONOTONIC_RAW, &t0);
    bucket_sort(vet, tamVet);
    clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
    free(vet);
  //  imprimeVet(vet, tamVet);
    printf("Tempo bucket Sort com bubble: %f\n", (float)difTempo(t0, t1));
    exit(0);
  }
  
