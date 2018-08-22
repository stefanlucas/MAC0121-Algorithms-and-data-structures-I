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

#include "bst.h"

/* Libera a memória alocada pela lista com cabeça p*/
static void
liberaLista (celula * p)
{
  if (p != NULL) {
    liberaLista (p->prox);
    free (p);
  }
}

/* Insere um elemento na lista com cabeça p*/
static void
insereLista (celula * p, int linha)
{
  celula *anterior = p, *novo;
  p = p->prox;
  while (p != NULL) {
    if (p->linha == linha)
      return;
    anterior = p;
    p = p->prox;
  }
  novo = malloc (sizeof (celula));
  novo->linha = linha;
  novo->prox = NULL;
  anterior->prox = novo;
}

arvore
criaBst ()
{
  return NULL;
}

int
nosBst (arvore r)
{
  if (r == NULL)
    return 0;
  return 1 + nosBst (r->esq) + nosBst (r->dir);
}

int
alturaBst (arvore r)
{
  int he, hd;
  if (r == NULL)
    return -1;
  he = alturaBst (r->esq);
  hd = alturaBst (r->dir);
  if (he > hd)
    return he + 1;
  return hd + 1;
}

arvore
insereBst (arvore r, char *pal, int linha)
{
  noh *filho, *pai, *novo;
  novo = malloc (sizeof (noh));
  novo->palavra = pal;
  novo->l = malloc (sizeof (celula));
  novo->l->prox = NULL;
  insereLista (novo->l, linha);
  novo->esq = novo->dir = NULL;

  if (r == NULL)
    return novo;
  filho = r;
  while (filho != NULL) {
    pai = filho;
    if (strcmp (filho->palavra, pal) > 0)
      filho = filho->esq;
    else if (strcmp (filho->palavra, pal) == 0) {
      insereLista (filho->l, linha);
      liberaLista (novo->l);
      free (pal);
      free (novo);
      return r;
    }
    else
      filho = filho->dir;
  }
  if (strcmp (pai->palavra, pal) > 0)
    pai->esq = novo;
  else
    pai->dir = novo;
  return r;
}

void
erd (arvore r, FILE * saida)
{
  if (r != NULL) {
    celula *p;
    erd (r->esq, saida);
    fprintf (saida, "%s ", r->palavra);
    p = r->l->prox;
    while (p != NULL) {
      fprintf (saida, "%d ", p->linha);
      p = p->prox;
    }
    fprintf (saida, "\n");
    erd (r->dir, saida);
  }
}

void
liberaBst (arvore r)
{
  if (r != NULL) {
    liberaBst (r->esq);
    liberaBst (r->dir);
    liberaLista (r->l);
    free (r->palavra);
    free (r);
  }
}
