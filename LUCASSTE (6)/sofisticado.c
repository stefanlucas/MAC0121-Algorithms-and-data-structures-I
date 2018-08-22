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

#include <stdio.h>
#include <stdlib.h>
#include "sofisticado.h"

struct heap {
  int index;
  int num;
};

typedef struct heap heap;

/* Recebe p em 1..k e rearranja o vetor h[1..k] de 
// modo que o "subvetor" cuja raiz eh p seja um heap.
// Supoe que os "subvetores" cujas raizes sao filhos
// de p ja sao heaps. */
static void peneira (int p, int k, heap h[]);

int
mergeSofisticado (char *args[], int k)
{
  int n = 0, i, aux, tam = k, qtdLidos;
  heap *h = malloc ((k + 1) * sizeof (heap));
  FILE **entrada = malloc (k * sizeof (FILE *));
  FILE *saida = fopen (args[k + 2], "w");
  for (i = 0; i < k; i++)
    entrada[i] = fopen (args[2 + i], "r");
  for (i = 0; i < k; i++) {
    qtdLidos = fscanf (entrada[i], "%d", &aux);
    if (qtdLidos != EOF) {
      h[i + 1].num = aux;
      h[i + 1].index = i;
      n++;
    }
  }
  for (i = k / 2; i >= 1; i--)
    peneira (i, k, h);
  while (k >= 1) {
    fprintf (saida, "%d\n", h[1].num);
    qtdLidos = fscanf (entrada[h[1].index], "%d", &aux);
    if (qtdLidos != EOF) {
      h[1].num = aux;
      n++;
    }
    else {
      h[1] = h[k];
      k--;
    }
    peneira (1, k, h);
  }
  for (i = 0; i < tam; i++) {
    fclose (entrada[i]);
  }
  free (entrada);
  fclose (saida);
  free (h);
  return n;
}

static void
peneira (int p, int k, heap h[])
{
  int f = 2 * p;
  heap x;
  while (f <= k) {
    if (f < k && h[f].num > h[f + 1].num)
      ++f;
    if (h[p].num <= h[f].num)
      break;
    x = h[p];
    h[p] = h[f];
    h[f] = x;
    p = f, f *= 2;
  }
}