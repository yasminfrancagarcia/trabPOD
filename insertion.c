#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
void imprimeVet(int *vet, int tam){
  int i;
  for(i=0; i<tam; i++)
    printf("%d\n",vet[i]);
  return;
}

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
  insertSort(vet, tamVet);
  clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
//  imprimeVet(vet, tamVet);
  printf("Tempo Insertion Sort: %f\n", (float)difTempo(t0, t1));
  exit(0);
}
