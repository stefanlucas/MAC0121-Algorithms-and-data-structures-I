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

/* //// O que o programa faz? ////////////////////////////////////
//
// O objetivo desta tarefa é processar um arquivo de texto e 
// construir um índice remissivo do texto.  
// O índice remissivo é uma tabela de duas colunas:
//
// * na primeira coluna aparece o dicionário do texto, em ordem 
//   lexicográfica.
// * na segunda coluna, para cada palavra do dicionário, aparecem 
//   os números das linhas do arquivo que contêm a palavra. 
//
////////////////////////////////////////////////////////////// */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "bst.h"

/* Função que constroi uma bst com palavras (chave) 
// e uma lista ligada (conteudo) com as linhas onde 
// ela aparece no arquivo entrada.
*/
arvore constroiArvore (FILE * entrada);

/* Função que le uma palavra do arquivo entrada
// e a retorna, ou retorn NULL caso não tenha mais 
// palavras.
*/
char *proximaPalavra (FILE * entrada);

/* Função que expande o tamanho do buffer de leitura
// das palavras
*/
void expandeBuffer (void);

/* Função que calcula o piso de log n*/
int lg (int N);

char *buffer;
int B;
int linha;
int total;

int
main (int numargs, char *args[])
{
  int n, pisoLog, altura;
  FILE *entrada = fopen (args[1], "r");
  FILE *saida = fopen (args[2], "w");
  double start, finish, elapsed;
  arvore r;
  B = 4;
  buffer = malloc (B * sizeof (char));

  start = (double) clock () / CLOCKS_PER_SEC;
  r = constroiArvore (entrada);
  finish = (double) clock () / CLOCKS_PER_SEC;
  elapsed = finish - start;
  erd (r, saida);
  n = nosBst (r);
  pisoLog = lg (n);
  altura = alturaBst (r);
  printf ("Tempo gasto: %f\n", elapsed);
  printf ("n = %d\npiso Log n = %d\naltura = %d\n", n, pisoLog,
          altura);

  free (buffer);
  liberaBst (r);
  fclose (entrada);
  fclose (saida);
  return 0;
}

arvore
constroiArvore (FILE * entrada)
{
  arvore r;
  char *pal;
  r = criaBst ();
  linha = 1;
  total = 0;
  while ((pal = proximaPalavra (entrada)) != NULL) {
    int i;
    total++;
    for (i = 0; pal[i] != '\0'; i++)
      pal[i] = tolower (pal[i]);
    if (i > 2)
      r = insereBst (r, pal, linha);
    else
      free (pal);
  }
  return r;
}

char *
proximaPalavra (FILE * entrada)
{
  int i, c;
  char *pal;
  /* pula caracteres nao alfanumericos */
  do {
    c = getc (entrada);
    if (c == '\n')
      linha++;
    if (c == EOF)
      return NULL;
  } while (!isalnum (c));
  /* le uma palavra */
  i = 0;
  do {
    buffer[i++] = c;
    if (i >= B)
      expandeBuffer ();
    c = getc (entrada);
    if (c == '\n')
      linha++;
  } while (c != EOF && isalnum (c));
  buffer[i] = '\0';
  pal = malloc (strlen (buffer) + 1);
  strcpy (pal, buffer);
  return pal;
}

void
expandeBuffer (void)
{
  char *novobuffer;
  int i;
  novobuffer = malloc (2 * B * sizeof (char));
  for (i = 0; i < B; i++)
    novobuffer[i] = buffer[i];
  B *= 2;
  free (buffer);
  buffer = novobuffer;
}

int
lg (int N)
{
  int i = 0, n = N;
  while (n > 1) {
    n = n / 2;
    i += 1;
  }
  return i;
}
