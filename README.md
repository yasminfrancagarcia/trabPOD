tarefa 1 - ordenação de dados

Algoritmo híbrido de ordenação de dados.
Base o Bucket Sort.
Variações:
insert (original);
heap;
merge;
quick.

Grupos de dados de 3 tamanhos: 100000, 1000000, 100000000 de elementos (números inteiros positivos).

Para usar compile utilizando linux com o seguinte comando
gcc main.c insertion.c heap.c merge.c quick.c -ansi -o main

Para executar:
- Entre no diretório onde se encontra os arquivos
cem mil: ./main 100000 < arqRandCem.txt

um milhão: ./main 1000000 < arqRandMilhaotxt

cem milhões: ./main 100000000 < arqRandCemMilhoes.txt
