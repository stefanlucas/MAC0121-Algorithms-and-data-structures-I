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
// Este arquivo faz parte da tarefa D
// da disciplina MAC0121.
// 
////////////////////////////////////////////////////////////// */

/* //// O que o programa faz? /////////////////////////////////
// Programa que l� um arquivo texto da entrada padr�o
// (stdin), processa todas as palavras que est�o no texto, e 
// por fim, as imprime na sa�da padr�o (stdout) em ordem 
// lexicogr�fica (como no dicion�rio). 
//
// Obs.1: Se uma palavra aparecer mais de uma vez no texto 
// a imprime apenas uma vez.
// Obs.2: Considere que as palavras possuem apenas os caracteres
// alfanumericos da tabela ASCII.
////////////////////////////////////////////////////////////// */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct cel {
    char *palavra;
    struct cel *prox;
};

typedef struct cel celula;

/* Fun��o que faz a leitura de uma palavra da entrada padr�o, retorna a
   palavra, caso exista, ou retorna o ponteiro NULL c.c. */
char * 
lePalavra () {
   char *palavra, *npalavra, caractere;
   int n, tamanho;
   n = 0;
   tamanho = 60;
   palavra = malloc ((tamanho + 1) * sizeof (char));
   caractere = getchar ();
   while (isalnum (caractere))  {
      if (n == tamanho) {
         tamanho *= 2;
         npalavra = malloc (tamanho + 1 * sizeof (char));
         strncpy (npalavra, palavra, n);
         free (palavra);
         palavra = npalavra;
      }
      palavra[n++] = caractere;
      caractere = getchar ();
   }
   if (n == 0 && caractere == EOF) {
      free (palavra);
      return NULL;
   }
   palavra[n] = '\0';
   npalavra = malloc ((n + 1) * sizeof (char));
   strcpy (npalavra, palavra);
   free (palavra);
   return npalavra;
}

/* Func�o que recebe uma palavra e converte suas letras em mai�scula para
   min�scula */
void 
converteParaMinuscula (char *palavra) {
    int i = 0;
    for (i = 0; palavra[i] != '\0'; i++)
        if(palavra[i] >= 65 && palavra[i] <= 90) palavra[i] += 32;
}

/* Fun��o que recebe um dicionario (lista ligada com cabe�a), uma palavra 
   e a insere no dicion�rio em sua posi��o lexicogr�fica correta */
void
insereNoDicionario (celula *ini, char *palavra) {
    celula *anterior, *nova;
    int comp = -1;
    anterior = ini;
    ini = ini->prox;
    while (ini != NULL && (comp = strcmp (palavra, ini->palavra)) > 0) {
        anterior = ini;
        ini = ini->prox;
    }
    if (comp != 0) {
        nova = malloc (sizeof (celula));
        nova->prox = ini;
        anterior->prox = nova;
        nova->palavra = palavra;
    }
    else free (palavra);
}

/* Fun��o que recebe um dicion�rio (lista ligada com cabe�a) e o imprime. */
void 
imprimeDicionario (celula *ini) {
    ini = ini->prox;
    while (ini != NULL) {
        printf ("%s\n", ini->palavra);
        ini = ini->prox;
    }
}

/* Fun��o que desaloca a mem�ria do dicion�rio (lista ligada com cabe�a)
   recursivamente */
void
desalocaMemoria (celula *ini) {
    if (ini == NULL) return;
    desalocaMemoria (ini->prox);
    free (ini->palavra);
    free (ini);
}

int main () {
    char *palavra;
    celula *ini = malloc (sizeof (celula));
    ini->prox = NULL;
    ini->palavra = NULL;
    while ((palavra = lePalavra ()) != NULL) {
        if (palavra[0] != '\0') {
            converteParaMinuscula (palavra);
            insereNoDicionario (ini, palavra);        
        }
        else free (palavra);
    }
    imprimeDicionario (ini);
    desalocaMemoria (ini);
    return 0;
}
