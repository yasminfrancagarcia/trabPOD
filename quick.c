int partition(int *vet, int lo, int hi){
  int pivo, i, j, aux;
  pivo = vet[lo];
  i=lo-1;
  j=hi+1;

  while(1){
	do{
	  j--;
	} while(vet[j] > pivo);

	do{
		i++;
	} while(vet[i] < pivo);

	if(i<j){
		aux = vet[i];
		vet[i] = vet[j];
		vet[j] = aux;
	} else {
		return j;
	}
  }
}

void quickSort(int *vet, int lo, int hi) {
    int p;
    if (lo < hi) {
        p = partition(vet, lo, hi);  /* partição do vetor*/
        quickSort(vet, lo, p);        /* Ordena a parte esquerda*/
        quickSort(vet, p + 1, hi);    /* Ordena a parte direita*/
    }
}

void quickSortAux(int *vet, int tam) {
    quickSort(vet, 0, tam - 1);
}