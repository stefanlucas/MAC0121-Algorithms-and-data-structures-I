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
// Data: 2015-11-23
// 
// Este arquivo faz parte da tarefa I
// da disciplina MAC0121.
// 
////////////////////////////////////////////////////////////// */

#ifndef BST_H
#define BST_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct cel {
  int linha;
  struct cel *prox;
};
typedef struct cel celula;

struct noh {
  char *palavra;
  celula *l;
  struct noh *esq;
  struct noh *dir;
};
typedef struct noh *arvore;
typedef struct noh noh;

/* Cria uma bst vazia.*/
arvore criaBst ();

/* Retorna a quantidade de nós da arvore r*/
int nosBst (arvore r);

/* Retorna a altura da arvore r*/
int alturaBst (arvore r);

/* Insere na bst uma palavra de uma determinada 
// linha de um arquivo texto.
*/
arvore insereBst (arvore r, char *pal, int linha);

/* Grava no arquivo saida a impressão da
// bst na ordem esquerda-raiz-direita
*/
void erd (arvore r, FILE * saida);

/* Libera a memória alocada pela bst */
void liberaBst (arvore r);

#endif
