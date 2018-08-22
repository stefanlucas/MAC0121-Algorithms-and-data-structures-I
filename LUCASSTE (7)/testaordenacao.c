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

/* //// O que o programa faz? ////////////////////////////////////
//
// Programa que verifica se os algoritmos de ordenacao da 
// biblioteca ordenacao.c com arquivo-interface ordenacao.h
// funcionam corretamente.
//
////////////////////////////////////////////////////////////// */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "ordenacao.h"
#define MAX 40000

/* Funcao que retorna 1 se o vetor v[0..n-1] esta 
// em ordem crescente e 0 c.c */
int 
ehCrescente (int v[], int n);

int 
main () 
{
   int i;
   int v[MAX];
   srand (time (NULL));
   for (i = 0; i < MAX; i++) v[i] = rand ();
   insercao (v, MAX);
   if (ehCrescente (v, MAX)) printf ("insercao esta Ok\n");
   else printf ("insercao esta incorreto\n");
   for (i = 0; i < MAX; i++) v[i] = rand ();
   Mergesort (v, MAX);
   if (ehCrescente (v, MAX)) printf ("Mergesort esta Ok\n");
   else printf ("Mergesort esta incorreto\n");
   for (i = 0; i < MAX; i++) v[i] = rand ();
   Quicksort (v, MAX);
   if (ehCrescente (v, MAX)) printf ("Quicksort esta Ok\n");
   else printf ("Quicksort esta incorreto\n");
   for (i = 0; i < MAX; i++) v[i] = rand ();
   Heapsort (v, MAX);
   if (ehCrescente (v, MAX)) printf ("Heapsort esta Ok\n");
   else printf ("Heapsort esta incorreto\n");
   return 0;
}

int 
ehCrescente (int v[], int n) 
{
   int i;
   for (i = 0; i < n-1; i++) if (v[i] > v[i+1]) return 0;
   return 1;
}