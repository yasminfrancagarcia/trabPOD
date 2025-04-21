//algoritimo para ordenar valores aleatorios com heap e mostrar o tempo no final
//para executar ele recebe um arquivo txt com os valores 
//gcc heap.c -o heapexe 
//./heapexe NumDeValores < RandCem.txt

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

void heapsort(int a[], int n) {
    int i = n / 2, pai, filho, t;

    for (;;) {
        if (i > 0) {
            i--;
            t = a[i];
        } else {
            n--;
            if (n == 0) return;
            t = a[n];
            a[n] = a[0];
        }

        pai = i;
        filho = i * 2 + 1;

        while (filho < n) {
            if ((filho + 1 < n) && (a[filho + 1] > a[filho]))
                filho++;
            if (a[filho] > t) {
                a[pai] = a[filho];
                pai = filho;
                filho = pai * 2 + 1;
            } else {
                break;
            }
        }
        a[pai] = t;
    }
}

void mostra(int *vetor, int tam){
    for(int i = 0; i < tam; i++)
        printf("%d ", vetor[i]);
    printf("\n");
}

double difTempo(struct timespec t0, struct timespec t1){
    return (t1.tv_sec - t0.tv_sec) + (double)(t1.tv_nsec - t0.tv_nsec) * 1e-9;
}

int main(int argc, char *argv[]) {
    int  i;
    int *vet;
    char linha[16];
    int tamVet;
    struct timespec t0, t1;

    if (argc != 2) {
        printf("Uso: %s arquivo.txt\n", argv[0]);
        return 1;
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
    heapsort(vet, tamVet-1);
    clock_gettime(CLOCK_MONOTONIC_RAW, &t1);

    printf("\nTempo médio heap sort: %f segundos\n", difTempo(t0, t1));
   // mostra(vet, count);  //mostra os valores ordenados 

    return 0;
}
