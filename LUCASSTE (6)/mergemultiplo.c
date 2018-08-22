/* -*- coding: iso-latin-1-unix; -*- */
/* DECLARO QUE SOU O UNICO AUTOR E RESPONSAVEL POR ESTE PROGRAMA.
// TODAS AS PARTES DO PROGRAMA, EXCETO AS QUE FORAM FORNECIDAS
// PELO PROFESSOR OU COPIADAS DO LIVRO OU DAS BIBLIOTECAS DE
// SEDGEWICK OU ROBERTS, FORAM DESENVOLVIDAS POR MIM.  DECLARO
// TAMBEM QUE SOU RESPONSAVEL POR TODAS AS COPIAS DESTE PROGRAMA
// E QUE NAO DISTRIBUI NEM FACILITEI A DISTRIBUICAO DE COPIAS.
// 
// Autor: Lucas Stefan Abe
// Numero USP: 8531612
// Sigla: LUCASSTE
// Data: 2015-10-06
// 
// Este arquivo faz parte da tarefa E
// da disciplina MAC0121.
// 
////////////////////////////////////////////////////////////// */

/* //// O que o programa faz? ////////////////////////////////
// Programa que recebe na linha de comando, nessa ordem: 
// 1) A opcao de fila de prioridade -s ou -h 
// 2) k arquivos com numeros em ordem crescente
// 3) um arquivo de saida, onde sera armazenada a intercalacao
//    dos k arquivos
// A opcao -s usa uma implementacao simploria de fila de 
// prioridades para fazer a intercalacao, enquanto a opcao -h
// usa o conceito de heap.
////////////////////////////////////////////////////////////// */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "simples.h"
#include "sofisticado.h"

/* Verifica se os numeros de um arquivo arq estao em ordem
// crescente, retorna 1 se estao, e 0 c.c */
int ehCrescente (char *arq);

/* Retorna a quantidade total de numeros dos arquivos args[2..2+k-1] */
int qtdNumeros (char *args[], int k);

int
main (int numargs, char *args[])
{
  int n = 0, k = numargs - 3;
  double start, finish, elapsed;
  start = (double) clock () / CLOCKS_PER_SEC;
  if (strcmp ("-s", args[1]) == 0)
    n = mergeSimples (args, k);
  else if (strcmp ("-h", args[1]) == 0)
    n = mergeSofisticado (args, k);
  finish = (double) clock () / CLOCKS_PER_SEC;
  elapsed = finish - start;
  printf ("Tempo gasto na intercalacao: %f segundo(s)\n", (double) elapsed);
  printf ("Numero de arquivos de entrada : %d\n", k);
  printf ("Quantidade de numeros do arquivo de saida: %d\n", n);
  return EXIT_SUCCESS;
}

int
ehCrescente (char *arq)
{
  FILE *arquivo = fopen (arq, "r");
  int anterior, atual;
  if (fscanf (arquivo, "%d", &anterior) == EOF)
  	return 1;
  while (fscanf (arquivo, "%d", &atual) != EOF) {
    if (anterior > atual) {
      fclose (arquivo);
      return 0;
    }
    anterior = atual;
  }
  return 1;
}

int
qtdNumeros (char *args[], int k)
{
  int cont, i, aux;
  FILE *arquivo;

  for (i = 0, cont = 0; i < k; i++) {
    arquivo = fopen (args[2 + i], "r");
    for (; fscanf (arquivo, "%d", &aux) != EOF; cont++);
    fclose (arquivo);
  }

  return cont;
}
