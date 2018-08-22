/* DECLARO QUE SOU O UNICO AUTOR E RESPONSAVEL POR ESTE PROGRAMA.
// TODAS AS PARTES DO PROGRAMA, EXCETO AS QUE FORAM FORNECIDAS   
// PELO PROFESSOR OU COPIADAS DO LIVRO OU DAS BIBLIOTECAS DE     
// SEDGEWICK OU ROBERTS, FORAM DESENVOLVIDAS POR MIM.  DECLARO   
// TAMBEM QUE SOU RESPONSAVEL POR TODAS AS COPIAS DESTE PROGRAMA 
// E QUE NAO DISTRIBUI NEM FACILITEI A DISTRIBUICAO DE COPIAS.   
//                                                               
// Autor: Lucas Stefan Abe                                               
// Numero USP: 8531612                                              
// Sigla: MAC0121                                      
// Data: 2015-08-06                                              
//                                                               
// Este arquivo faz parte da tarefa A (segunda parte parte)                      
// da disciplina MAC0121.
//                                                               
///////////////////////////////////////////////////////////////*/

char *readLine (FILE *infile) {
   char *line, nline;
   int n, ch, size;
   n = 0;
   size = 120;
   line = malloc (size + 1);
   while ((ch = getc (infile)) != '\n' && ch != EOF) {
      if (n == size) {
         size *= 2;
         nline = malloc (size + 1);
         strncpy (nline, line, n);
         free (line);
         line = nline;
      }
      line[n++] = ch;
   }
   if (n == 0 && ch == EOF) {
      free (line);
      return NULL;
   }
   line[n] = '\0';
   nline = malloc (n + 1);
   strcpy (nline, line);
   free (line);
   return nline;
}
