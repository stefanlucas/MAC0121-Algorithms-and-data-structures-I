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
#include "simples.h"

struct dado {
  int num;
  int vazio;
};
typedef struct dado dado;

/*Retorna o indice do menor elemento de f[0..k-1]*/
static int menor (dado f[], int k);

int
mergeSimples (char *args[], int k)
{
  int n = 0, i, soma = 0, qtdLidos, indice;
  dado *f = malloc (k * sizeof (dado));
  FILE **entrada = malloc (k * sizeof (FILE *));
  FILE *saida = fopen (args[2 + k], "w");
  for (i = 0; i < k; i++)
    entrada[i] = fopen (args[2 + i], "r");
  for (i = 0; i < k; i++) {
    qtdLidos = fscanf (entrada[i], "%d\n", &(f[i].num));
    if (qtdLidos == EOF) {
      soma++;
      f[i].vazio = 1;
    }
    else {
      f[i].vazio = 0;
      n++;
    }
  }
  while (soma < k) {
    indice = menor (f, k);
    fprintf (saida, "%d\n", f[indice].num);
    qtdLidos = fscanf (entrada[indice], "%d", &(f[indice].num));
    if (qtdLidos == EOF) {
      f[indice].vazio = 1;
      soma++;
    }
    else
      n++;
  }
  for (i = 0; i < k; i++) {
    fclose (entrada[i]);
  }
  free (entrada);
  fclose (saida);
  free (f);
  return n;
}

static int
menor (dado f[], int k)
{
  int i, menor = 0, indice = 0;
  for (i = 0; i < k; i++) {
    if (!(f[i].vazio)) {
      menor = f[i].num;
      indice = i;
      break;
    }
  }
  for (i = i + 1; i < k; i++) {
    if (!(f[i].vazio) && f[i].num < menor) {
      menor = f[i].num;
      indice = i;
    }
  }
  return indice;
}
