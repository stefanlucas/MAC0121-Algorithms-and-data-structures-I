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

/*//////////////////////////////////////////////////////////
//
// Todas as funcoes abaixo rearranjam um vetor v[0..n-1]  
// de modo que v[0..n-1] fique em ordem crescente.        
//
//////////////////////////////////////////////////////// */

/* Esse algoritmo consome tempo proporcional a n^2*/
void 
insercao (int *v, int n);

/* Esse algoritmo consome tempo proporcional a nlogn */
void 
Mergesort (int *v, int n);

/* Esse algoritmo consome tempo proporcional a nlogn */
void 
Quicksort (int *v, int n);

/* Esse algoritmo consome tempo proporcional a nlogn*/
void 
Heapsort (int *v, int n);
