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
// Data: 2015-08-29
// 
// Este arquivo faz parte da tarefa E
// da disciplina MAC0121.
// 
////////////////////////////////////////////////////////////// */

/* Essa função recebe uma string palavra e um vetor em ordem 
// lexicografica de string dicionario[0..n-1], ela
// devolve um indice i em 0..n, tal que 
// dicionario[i-1] <= palavra < dicionario[i].
*/
int 
buscaBinaria (char **dicionario, char *palavra, int *n);