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
// Data: 2015-08-08
// 
// Este arquivo faz parte da tarefa B
// da disciplina MAC0121.
// 
///////////////////////////////////////////////////////////////*/


/*///////////////////O que o programa faz/////////////////////////////////
//
//    Programa que l� um arquivo da entrada padr�o (stdin), "limpa" o
//    arquivo, e o imprime na sa�da padr�o (stdout).
//    Mais precisamente, o processo de limpeza consiste nos seguintes
//    passos, executados em sequ�ncia: 
//    
//    1) Troque por um s� espa�o toda sequ�ncia de dois ou mais espa�os
//    que n�o esteja no come�o de uma linha.
//    
//    2) Elimine todos os caracteres de controle exceto newline e tab.
//    Mantenha o newline e troque cada tab por 7 espa�os consecutivos.
//    
//    3) Troque cada caractere ilegal que tenha um sinal diacr�tico pelo
//    correspondente caractere legal sem o sinal diacr�tico. Troque por
//    um espa�o todos os demais caracteres ilegais.
//    
//    4) Insira um newline no fim do arquivo (a menos que o �ltimo 
//    caractere j� seja um newline).
////////////////////////////////////////////////////////////////////////*/

#include <stdio.h>
#include <stdlib.h>
int main() {
    int caractere, caractere_anterior = -1, inicio_texto = 1;

    while ((caractere = getchar()) != EOF){
        if (caractere == 32) {
                printf (" ");
                if (caractere_anterior == 10 || inicio_texto == 1) {
                    while ((caractere = getchar()) == 32) printf (" ");
                    inicio_texto = 0;
                }
                else
                    while ((caractere = getchar()) == 32);
        }
        if (caractere == 9)
            printf ("       ");
        else if(caractere == 10)
            printf("\n");
        else if (caractere >= 192 && caractere <= 195)
            printf ("A");
        else if (caractere == 199)
            printf ("C");
        else if (caractere == 201 || caractere == 202)
            printf ("E");
        else if (caractere == 205)
            printf ("I");
        else if (caractere >= 211 && caractere <= 213)
            printf ("O");
        else if (caractere == 218)
            printf ("U");
        else if (caractere >= 224 && caractere <= 227)
            printf ("a");
        else if (caractere == 231)
            printf ("c");
        else if (caractere == 233 || caractere == 234)
            printf ("e");
        else if (caractere == 237)
            printf ("i");
        else if (caractere >= 243 && caractere <= 245)
            printf ("o");
        else if (caractere == 250)
            printf ("u");
        else if (caractere >= 127 && caractere <= 255)
            printf (" ");
        else if (caractere > 31)
            printf ("%c", caractere);
        caractere_anterior = caractere;
    }   
    if (caractere_anterior != 10)
        printf ("\n");
    return 0;
}
