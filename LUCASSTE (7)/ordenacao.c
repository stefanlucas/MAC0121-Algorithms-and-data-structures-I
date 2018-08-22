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
// Data: 2015-10-13
// 
// Este arquivo faz parte da tarefa G
// da disciplina MAC0121.
// 
////////////////////////////////////////////////////////////// */

#include <stdio.h>
#include <stdlib.h>
#include "ordenacao.h"

/* Esta função rearranja o vetor v[0..n-1] em
// ordem crescente. */
static void
insertion (int n, int v[]);

/* A função recebe vetores crescentes v[p..q-1] 
// e v[q..r-1] e rearranja v[p..r-1] em ordem 
// crescente. */
static void 
intercala (int p, int q, int r, int v[]);

/* A função mergesort rearranja o vetor v[p..r-1]
// em ordem crescente. */
static void
mergesort (int p, int r, int v[]);

/* Recebe vetor v[p..r] com p < r. Rearranja os 
// elementos do vetor e devolve j em p..r tal que 
// v[p..j-1] <= v[j] < v[j+1..r]. */
static int
separa (int v[], int p, int r);

/* A função recebe um vetor v[p..r], com p <= r+1,
// e rearranja o vetor em ordem crescente. */
static void 
quicksort (int v[], int p, int r);

/* Recebe p em 1..m e rearranja o vetor v[1..m] de 
// modo que o "subvetor" cuja raiz é p seja um heap.
// Supõe que os "subvetores" cujas raízes são filhos
// de p já são heaps. */
static void
peneira (int p, int m, int v[]);

/* Rearranja os elementos do vetor v[1..n] 
// de modo que fiquem em ordem crescente. */
static void
heapsort (int n, int v[]);

/*////////////////////////////////////
//
// Funcoes publicas                
//
////////////////////////////////// */

void 
insercao (int *v, int n) 
{
   insertion (n, v);
}

void 
Mergesort (int *v, int n) 
{
   mergesort (0, n, v);
}

void 
Quicksort (int *v, int n) 
{
   quicksort (v, 0, n-1);
}

void 
Heapsort (int *v, int n) 
{
   heapsort (n, v-1);
}

/*///////////////////////////////////
//
// Funcoes privadas               
//
///////////////////////////////// */

static void
insertion (int n, int v[])
{
   int i, j, x;
   for (j = 1; j < n; ++j) {
      x = v[j];
      for (i = j-1; i >= 0 && v[i] > x; --i) 
         v[i+1] = v[i];
      v[i+1] = x;
   }
}

static void 
intercala (int p, int q, int r, int v[]) 
{
   int i, j, k, *w;
   w = malloc ((r-p) * sizeof (int));
   i = p; j = q;
   k = 0;

   while (i < q && j < r) {
      if (v[i] <= v[j])  w[k++] = v[i++];
      else  w[k++] = v[j++];
   }
   while (i < q)  w[k++] = v[i++];
   while (j < r)  w[k++] = v[j++];
   for (i = p; i < r; ++i)  v[i] = w[i-p];
   free (w);
}

static void
mergesort (int p, int r, int v[])
{
   if (p < r-1) {
      int q = (p + r)/2;
      mergesort (p, q, v);
      mergesort (q, r, v);
      intercala (p, q, r, v);
   }
}

static int
separa (int v[], int p, int r)
{
   int c = v[p], i = p+1, j = r, t;
   while (/*A*/ i <= j) {
      if (v[i] <= c) ++i;
      else if (c < v[j]) --j; 
      else {
         t = v[i], v[i] = v[j], v[j] = t;
         ++i; --j;
      }
   }
   /* agora i == j+1 */                 
   v[p] = v[j], v[j] = c;
   return j; 
}

static void 
quicksort (int v[], int p, int r)
{
   int j;                         
   if (p < r) {                   
      j = separa (v, p, r);       
      quicksort (v, p, j-1);      
      quicksort (v, j+1, r);      
   }
}

static void
peneira (int p, int m, int v[])
{
   int f = 2*p, x;
   while (f <= m) {
      if (f < m && v[f] < v[f+1])  ++f;
      /* agora f é o filho "mais valioso" de p */
      if (v[p] >= v[f]) break;
      x = v[p], v[p] = v[f], v[f] = x;
      p = f, f *= 2;
   }
}

static void
heapsort (int n, int v[])
{
   int p, m, x;
   for (p = n/2; p >= 1; --p)
      peneira (p, n, v);
   /* agora v[1..n] é um heap */
   for (m = n; m >= 2; --m) {
      x = v[1], v[1] = v[m], v[m] = x;
      peneira (1, m-1, v);
   }
}
