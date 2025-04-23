void insertSort(int *vetor, int tam) {
    int cont, cont2, aux;

    for (cont = 1; cont < tam; cont++) {
        if (vetor[cont] < vetor[cont - 1]) {
            aux = vetor[cont];
            cont2 = cont;
            while (aux < vetor[cont2 - 1] && cont2 > 0) {
                vetor[cont2] = vetor[cont2 - 1];
                cont2--;
            }
            vetor[cont2] = aux;
        }
    }
}

