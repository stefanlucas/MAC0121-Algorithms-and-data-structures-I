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

#include <stdio.h>
#include <stdlib.h>
#include "ordenacao.h"

/* Recebe p em 1..m e rearranja o vetor v[1..m] de 
// modo que o "subvetor" cuja raiz é p seja um heap.
// Supõe que os "subvetores" cujas raízes são filhos
// de p já são heaps.
*/
static void
peneira (int p, int m, int v[])
{
  int f = 2 * p, x;
  while (f <= m) {
    if (f < m && v[f] < v[f + 1])
      ++f;
    if (v[p] >= v[f])
      break;
    x = v[p], v[p] = v[f], v[f] = x;
    p = f, f *= 2;
  }
}

/* Rearranja os elementos do vetor v[1..n] 
// de modo que fiquem em ordem crescente.
*/
static void
heapsort (int n, int v[])
{
  int p, m, x;
  for (p = n / 2; p >= 1; --p)
    peneira (p, n, v);
  for (m = n; m >= 2; --m) {
    x = v[1], v[1] = v[m], v[m] = x;
    peneira (1, m - 1, v);
  }
}

void
heap_sort (int n, int v[])
{
  heapsort (n, v - 1);
}

void
ordenacaoDigital (char *v[], int n, int W)
{
  int d, i, r;
  int R = 128;
  int *fp;
  char **aux;
  fp = malloc ((R + 1) * sizeof (int));
  aux = malloc (n * sizeof (char *));

  for (d = W - 1; d >= 0; d--) {
    for (r = 0; r <= R; r++)
      fp[r] = 0;
    for (i = 0; i < n; i++)
      fp[(int) v[i][d] + 1] += 1;
    for (r = 1; r <= R; r++)
      fp[r] += fp[r - 1];
    for (i = 0; i < n; i++) {
      aux[fp[(int) v[i][d]]] = v[i];
      fp[(int) v[i][d]]++;
    }
    for (i = 0; i < n; i++)
      v[i] = aux[i];
  }

  free (fp);
  free (aux);
}
