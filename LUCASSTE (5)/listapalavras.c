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
// Data: 2015-09-21
// 
// Este arquivo faz parte da tarefa E
// da disciplina MAC0121.
// 
////////////////////////////////////////////////////////////// */

/* //// O que o programa faz? //////////////////////////////////
// O programa consiste em duas fases:
// 
// 1) Le um arquivo texto e constroi um dicionario com as 
// palavras do texto.O dicionario estará em ordem lexicografica
// e sera gravado em um arquivo "de saida".
//
// 2)A segunda fase e interativa: o usuario digita uma palavra boa
// qualquer, digamos p, no terminal e o programa deve devolver os 
// índices das duas palavra do dicionário que estao mais proximas 
// de p: o indice da palavra lexicograficamente menor ou igual a p
// e o indice da palavra lexicograficamente maior que p.  Junto 
// com os dois indices, o programa deve imprimir tambem as palavras
// que correspondem a esses índices.  Essa interacao do usuario com 
// o programa deve terminar quando o usuario digitar a palavra 
// vazia. 
//
// Terminologia:
//
// Palavra:
// uma palavra e um sequência maximal nao vazia de caracteres 
// alfanuméricos. Uma palavra é boa se começa com uma letra.
//
// Dicionario :
// o dicionário do arquivo de texto é o conjunto de todas as 
// palavras boas do texto.Não há palavras repetidas no 
// dicionário.
///////////////////////////////////////////////////////////////// */

/*///////////////////////////////////////////////////////////////
// Constantes e prototipos de funcoes /////////////////////////*/

#define DEBUG 0

#include <stdlib.h> /* malloc, free, EXIT_SUCCESS */
#include <stdio.h>  /* getc, EOF, printf, fprintf */
#include <string.h> /* strcpy, strcmp, strlen */
#include <ctype.h>  /* isalnum, tolower */
#include <time.h> /*clock, clock_t*/
#include "bb.h" /*buscaBinaria*/

void constroiDicionario (FILE *entrada) ;
char *proximaPalavra (FILE *entrada, int fase) ;
void inserePalavra (char *palavra) ;
void imprimeDicionario (FILE *saida) ;
void expandeBuffer (void) ;
void expandeDic (void) ;
void faseInterativa (void);

/*///////////////////////////////////////////////////////////////
// Variaveis globais ////////////////////////////////////////////
*/

/* O vetor dic[0..n-1] armazenara o dicionario. O vetor e alocado  
// dinamicamente e tem capacidade para N palavras. 
*/
char **dic;
int n, N;

/* O vetor de caracteres buffer[0..B-1] sera usado para
// armazenamento temporario de uma palavra lida de um arquivo. 
*/
char *buffer;
int B;

/* Numero total de palavras do arquivo (contando as repeticoes). 
*/
int total;  


/*///////////////////////////////////////////////////////////////
// Funcoes ////////////////////////////////////////////////////*/


int 
main (int numargs, char *arg[]) 
{
   clock_t t = clock ();
   float dif;
   FILE *entrada = fopen (arg[1], "r");
   FILE *saida = fopen (arg[2], "w");
   int i;
   N = 16;
   dic = malloc (N * sizeof (char *));
   B = 4;
   buffer = malloc (B * sizeof (char));
   constroiDicionario (entrada);
   fclose (entrada);
   imprimeDicionario (saida);
   t = clock () - t;
   dif = ((float)t) / CLOCKS_PER_SEC;
   fprintf (saida, "A parte 1 do programa demorou %f segundos", dif);
   fclose (saida);
   faseInterativa ();
   free (buffer);
   for (i = 0; i < n; i++) free (dic[i]);
   free (dic);
   return EXIT_SUCCESS;
}


/* Realiza a fase interativa do programa (fase 2)
*/
void
faseInterativa (void) 
{
   char *pal;
   int i;
   printf ("> ");
   while ((pal = proximaPalavra (stdin, 2)) != NULL && n > 0) {
      i = buscaBinaria (dic, pal, &n);
      if (i == -1)
         printf ("So tem a palavra lexicog. maior: (%d, %s)", i+1, dic[i+1]);
      else if (i == 0) 
         printf ("So tem a palavra lexicog. maior: (%d, %s)", i, dic[i]);
      else if (i == n) 
         printf ("So tem a palavra lexicog. menor ou igual: (%d, %s)", i-1, dic[i-1]);
      else 
         printf ("(%d, %s) (%d, %s)", i-1, dic[i-1], i, dic[i]);
      printf ("\n> ");
   }
}


/* Constroi o dicionario dic[0..n-1] do arquivo. (As variaveis
// dic e n sao globais.)
*/ 
void
constroiDicionario (FILE *entrada) 
{
   char *pal;
   total = 0;
   n = 0; 
   while ((pal = proximaPalavra (entrada, 1)) != NULL) {
      int i;
      total++;
      for (i = 0; pal[i] != '\0'; i++) 
         pal[i] = tolower (pal[i]);
      if (isalpha(pal[0]))
         inserePalavra (pal);
   }
}


/* Le a proxima palavra do arquivo ou stdin, e devolve essa palavra.
// Se o arquivo estiver esgotado ou se a palavra for vazia (stdin)
// devolve NULL. 
*/ 
char *
proximaPalavra (FILE *entrada, int fase) 
{
   int i, c;
   char *pal;
   /* pula caracteres nao alfanumericos */
   do {
      c = getc (entrada);
      if (fase == 2)
         if (!isalnum (c)) return NULL;
      if (c == EOF) return NULL;
   } while (!isalnum (c));
   /* le uma palavra */
   i = 0;
   do {
      buffer[i++] = c;
      if (i >= B) expandeBuffer ();
      c = getc (entrada);
   } while (c != EOF && isalnum (c));
   buffer[i] = '\0';
   pal = malloc (strlen (buffer) + 1);
   strcpy (pal, buffer);
   return pal;
} 


/* Expande o vetor de caracteres buffer[0..B-1] de modo que 
// ele tenha o dobro da capacidade (portanto, o valor de B 
// dobra.)
*/
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


/* Insere a string pal no dicionario dic[0..n-1] (se ela nao
// estiver la) e atualiza o valor de n. O dicionario dic
// permanece em ordem lexicografica se estiver em ordem
// lexicografica antes da insercao. (As variaveis dic e n
// sao globais.)
*/ 
void
inserePalavra (char *pal) 
{
   int i, j;
   i = buscaBinaria (dic, pal, &n);
   if (i >= 1)
      if (strcmp (dic[i-1], pal) == 0)
         i = i - 1;
   /* pal deveria estar em dic[i] */
   if (i >= n || strcmp (dic[i], pal) > 0) {
      if (n == N) 
         expandeDic ();
      for (j = n-1; j >= i; j--) 
         dic[j+1] = dic[j];
      dic[i] = pal;
      n++;
   } else free (pal);
} 


/* Expande o vetor de ponteiros dic[0..N-1] demodo que ele tenha
// o dobro da capacidade (portanto, o valor de N dobra).
*/
void 
expandeDic (void) 
{
   char **novodic;
   int i;
   novodic = malloc (2 * N * sizeof (char *));
   for (i = 0; i < N; i++) 
      novodic[i] = dic[i];
   N *= 2;
   free (dic);
   dic = novodic;
}


/* Imprime a lista de palavras dic[0..n-1] no arquivo.
*/
void 
imprimeDicionario (FILE *saida) 
{
   int i;
   fprintf (saida, "Lista de palavras distintas ");   
   fprintf (saida, "(%d palavras):\n\n", n);   
   for (i = 0; i < n; i++) 
      fprintf (saida, "%s\n", dic[i]);
   fprintf (saida, "\n");   
   fprintf (saida, "numero total de palavras lidas, contando repeticoes: %d\n", total);
   fprintf (saida, "espaco reservado para o dicionario: %d palavras\n", N); 
   fprintf (saida, "espaco reservado para armazenar uma palavra: %d bytes\n", B); 
}