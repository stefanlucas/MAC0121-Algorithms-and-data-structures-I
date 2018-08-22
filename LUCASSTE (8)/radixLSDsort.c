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
// Data: 2015-11-01
// 
// Este arquivo faz parte da tarefa H
// da disciplina MAC0121.
// 
////////////////////////////////////////////////////////////// */

/* //// O que o programa faz? //////////////////////////////////
//
// Programa que compara experimentalmente o desempenho dos 
// algoritmos de ordenação heapsort e ordenação digital,
// gerando vetores aleatórios com 40 mil, 80 mil, 160 mil
// e 320 mil números inteiros, todos com 9 dígitos decimais.
//
////////////////////////////////////////////////////////////// */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "ordenacao.h"
#define N 40000

/* Gera vetores v1[0..n-1] de strings de números
// e v2[0..n-1] de inteiros, ambos com os mesmos
// números
*/
void geraVetores (char *v1[], int v2[], int n);

/* Recebe um vetor de strings de números v[0..n-1]
// e retorna 1 se está em ordem crescente, ou 0 c.c
*/
int ehCrescente1 (char *v[], int n);

/* Recebe um vetor de inteiros v[0..n-1] e retorna
// 1 se está em ordem crescente, ou 0 c.c
*/
int ehCrescente2 (int v[], int n);

/* A função RandomInteger devolve um inteiro 
// aleatório entre low e high inclusive,
// ou seja, no intervalo fechado low..high.
// Vamos supor que 0 <= low <= high < RAND_MAX.
// (O código foi copiado da biblioteca random de
// Eric Roberts.)
*/
int RandomInteger (int low, int high);

/* A função Randomize inicializa o gerador de números 
// aleatórios de modo que os resultados das
// invocações de RandomInteger seja imprevisível.
*/
void Randomize (void);

int
main ()
{
  int i, pot;
  double tempo[4][2], start, finish;
  char **v1 = malloc ((8 * N) * sizeof (char *));
  int v2[8 * N];
  for (i = 0; i < 8 * N; i++)
    v1[i] = malloc (10 * sizeof (char));
  for (i = 0, pot = 1; i < 4; i++, pot *= 2) {
    geraVetores (v1, v2, N * pot);

    start = (double) clock () / CLOCKS_PER_SEC;
    ordenacaoDigital (v1, N * pot, 9);
    finish = (double) clock () / CLOCKS_PER_SEC;
    if (!ehCrescente1 (v1, N * pot)) {
      printf ("Erro na ordenacaoDigital\n");
      exit (EXIT_FAILURE);
    }
    tempo[i][0] = finish - start;

    start = (double) clock () / CLOCKS_PER_SEC;
    heap_sort (N * pot, v2);
    finish = (double) clock () / CLOCKS_PER_SEC;
    if (!ehCrescente2 (v2, N * pot)) {
      printf ("Erro no heapsort\n");
      exit (EXIT_FAILURE);
    }
    tempo[i][1] = finish - start;
  }
  printf
    ("\n****** Consumo de tempo ordenacaoDigital vs heapsort ******\n");
  printf ("     N      ordenacaoDigital         heapsort\n");
  for (i = 0, pot = 1; i < 4; i++, pot *= 2) {
    printf ("%6d           %9f s      %9f s\n", N * pot,
            tempo[i][0], tempo[i][1]);
  }
  printf ("\n");
  for (i = 0; i < 8 * N; i++)
    free (v1[i]);
  free (v1);
  return 0;
}

void
geraVetores (char *v1[], int v2[], int n)
{
  int i;
  Randomize ();
  for (i = 0; i < n; i++) {
    v2[i] = RandomInteger (100000000, 999999999);
    sprintf (v1[i], "%d", v2[i]);
  }
}

int
ehCrescente1 (char *v[], int n)
{
  int i;
  for (i = 0; i < n - 1; i++)
    if (strcmp (v[i], v[i + 1]) > 0)
      return 0;
  return 1;
}

int
ehCrescente2 (int v[], int n)
{
  int i;
  for (i = 0; i < n - 1; i++)
    if (v[i] > v[i + 1])
      return 0;
  return 1;
}

void
Randomize (void)
{
  srand (time (NULL));
}

int
RandomInteger (int low, int high)
{
  int k;
  double d;
  d = (double) rand () / ((double) RAND_MAX + 1);
  k = d * (high - low + 1);
  return low + k;
}
