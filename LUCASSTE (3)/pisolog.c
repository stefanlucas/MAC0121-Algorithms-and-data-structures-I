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
// Data: 2015-08-17
// 
// Este arquivo faz parte da tarefa C
// da disciplina MAC0121.
// 
////////////////////////////////////////////////////////////// */

/* //// Descrição do programa //////////////////////////////////
//
// Programa que recebe dois inteiros B e K pela linha de comando,
// calcula e imprime o piso de logN (base 2), para N igual a    
// B^1, B^2, ..., B^K.
//
// Obs: Para que o programa funcione corretamente, é necessário
// que B seja um inteiro tal que 1 <= B <= INT_MAX, onde 
// INT_MAX é o valor máximo que pode ser armazenado por uma
// variável do tipo int. 
////////////////////////////////////////////////////////////// */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
int main (int numargs, char *arg[]) {
    int n, i, j, b, k, anterior, potencia_atual;
    b = atoi (arg[1]);
    k = atoi (arg[2]);
    printf ("INT MAX = %d\n", INT_MAX);
    printf ("N              Piso de logN (base 2)\n");
    n = b;
    for (i = 1; i <= k; i++) {
        anterior = 0;
        potencia_atual = 1;
        for (j = 0; potencia_atual <= n; j++) {
        /*A cada passo do laço a variável anterior
        sempre vai dobrar de valor*/
            if (anterior > INT_MAX/2) {
                printf ("Overflow aritmetico!\n");
                exit (EXIT_FAILURE);
            }
            anterior = potencia_atual;
            potencia_atual *= 2;
        }
        printf ("%.2d^%.2d          log%d = %d\n", b, i, n, j-1);
        if (n > INT_MAX/b && i < k) {
            printf ("Overflow aritmetico!\n");
            exit (EXIT_FAILURE);
        }
        n *= b;
    }
    return 0;
}
