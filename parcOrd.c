/*
  Programa que utiliza versão modificada de gaps no Shell sort para ordenar
  parcialmente dados da entrada.
*/

#include <stdio.h>
#include <stdlib.h>

void imprime(int *vetor, int tam){
  int cont;
  for(cont=0; cont<tam; cont++)
	printf("%d\n", vetor[cont]);
  return;
}

int *parcOrd(int *vet, int tam){
  int i, j, k = 0, temp;
  int gaps[8] = {701, 301, 132, 57, 23, 10, 4, 2};

  while (k < 8 && gaps[k] > ((tam / 2) - 1)) 
    k++;
  if (k == 8) k = 7; // fallback seguro para evitar acesso fora dos limites

  while (k < 8 && gaps[k] >= 1) {
    for (i = gaps[k]; i < tam; i++) {
      temp = vet[i];
      j = i - gaps[k];
      while (j >= 0 && temp < vet[j]) {
        vet[j + gaps[k]] = vet[j];
        j -= gaps[k];
      }
      vet[j + gaps[k]] = temp;
    }
    k++;
  }
  return vet;
}

int main(int argc, char *argv[]){
  int  i;
  int *vet;
  char linha[16];
  int tamVet;
  int maior = -1;

  if(argc < 2){
    printf("Uso: %s <numero de elementos a ordenar parcialmente>\n", argv[0]);
    exit(0);
  }
  tamVet = atoi(argv[1]);
  vet = (int *) malloc(sizeof(int) * tamVet);

  for(i=0; i<tamVet; i++){
	fgets(linha, 16, stdin);
	sscanf(linha, "%d", &vet[i]);
	if(vet[i] > maior)
		maior = vet[i];
  }

  parcOrd(vet, tamVet);
  imprime(vet, tamVet);

  exit(0);
}
