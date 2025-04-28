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
gcc main.c insertion.c heap.c merge.c quick.c -ansi -o main -lm 

(-lm para compilar a biblioteca math.h no Linux)


Para executar:
- Entre no diretório onde se encontra os arquivos
- No terminal:
./main * quantidade de numeros a ordenar* < * nome_arquivo_com_numeros.txt*


