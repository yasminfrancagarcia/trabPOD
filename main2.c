#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>

void insertSort(int *vetor, int tam);
void heapsort(int a[], int n);
void mergeSortAux(int v[], int n);
void quickSortAux(int *vet, int tam);

/* Definir um tipo para a função de ordenação */
typedef void (*SortFunc)(int*, int);

typedef struct {
    int topo;
    int* balde;
    int capacidade;
} bucket;

void bucket_sort(int v[], int tam, SortFunc algoritmo) {
    int i, j, idx, k, maior;
    int num_bucket;
    bucket* b;
    /* Vetor auxiliar que serve como destino do bucket */
    int *aux;
    aux = (int *) malloc(sizeof(int) * tam);

    if (tam <= 0) return;

    /* Definindo número de buckets como raiz quadrada do número de elementos */
    num_bucket = (int)sqrt(tam);
    b = malloc(num_bucket * sizeof(bucket));

    /* Inicializando buckets */
    for (i = 0; i < num_bucket; i++) {
        b[i].topo = 0;
        b[i].capacidade = (tam / num_bucket) * 2;
        b[i].balde = malloc(b[i].capacidade * sizeof(int));
    }

    /* Encontrar o maior valor */
    maior = v[0];
    for (i = 1; i < tam; i++) {
        if (v[i] > maior)
            maior = v[i];
    }

    /* Distribuir valores nos buckets */
    for (i = 0; i < tam; i++) {
        
        idx = (v[i] * num_bucket) / (maior + 1);
        if (b[idx].topo < b[idx].capacidade) {
            b[idx].balde[b[idx].topo++] = v[i];
        } else {
            /* Realocar bucket se precisar */
            b[idx].capacidade *= 2;
            b[idx].balde = realloc(b[idx].balde, b[idx].capacidade * sizeof(int));
            b[idx].balde[b[idx].topo++] = v[i];
        }
    }

    /* Ordenar cada bucket */
    for (i = 0; i < num_bucket; i++) {
        if (b[i].topo > 0) {
            algoritmo(b[i].balde, b[i].topo);
        }
    }

    /* Juntar os elementos ordenados */
    k = 0;
    for (i = 0; i < num_bucket; i++) {
        for (j = 0; j < b[i].topo; j++) {
            aux[k++] = b[i].balde[j];
        }
        free(b[i].balde);
    }

    free(b);
    free(aux);
}

double difTempo(struct timespec t0, struct timespec t1){
    return (t1.tv_sec - t0.tv_sec) + (double)(t1.tv_nsec - t0.tv_nsec) * 1e-9;
}

int main(int argc, char *argv[]){
    int i;
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

    for(i = 0; i < tamVet; i++){
        fgets(linha, 16, stdin);
        sscanf(linha, "%d", &vet[i]);
    }

    /* Array de ponteiros para funções de ordenação */
    SortFunc algoritmos[] = {insertSort, mergeSortAux, quickSortAux, heapsort};
    const char *nomesAlgoritmos[] = {"Insert Sort", "Merge Sort ", "Quick Sort ", "Heap Sort  "};

    /* Loop para testar cada algoritmo */
    for (i = 0; i < 4; i++) {
        /* Teste de tempo com cada algoritmo */
        clock_gettime(CLOCK_MONOTONIC_RAW, &t0);
        bucket_sort(vet, tamVet, algoritmos[i]);
        clock_gettime(CLOCK_MONOTONIC_RAW, &t1);

        printf("Tempo bucket Sort com %s: %f\n", nomesAlgoritmos[i], difTempo(t0, t1));
    }
    free(vet);
    return 0;
}
