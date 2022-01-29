#include <stdio.h>
#include <string.h>
 
#include "definitions.h"
#include "io.h"
#include "funcs.h"
 
typedef struct compromisso{
   char descricao[105];
   int hi, mi, hf, mf;
} Entry;
 
int main(){
   int entradas, i, j;
   int hi, mi, hf, mf;
   char linha[20];
   Entry agenda[105] = {0};
 
   entradas = carrega_agenda(agenda);
 
   ordena_agenda(agenda, entradas);
 
   int sair = 0;
 
   while(!sair){
     printf("Digite o comando\n");
     scanf(" %s", linha);
     if(strcmp(linha, "Consultar") == 0){
       scanf("%d:%d %d:%d", &hi, &mi, &hf, &mf);
       for(j=0; j<entradas; j++){
         consulta_compromissos(&agenda[j], hi, mi, hf, mf);
       }
       printf("\n");
     }
     else if(strcmp(linha, "Cadastrar") == 0){
       cadastra_compromisso(&agenda[entradas++]);
       ordena_agenda(agenda, entradas);
       printf("\n");
     }
     else if(strcmp(linha, "Sair") == 0){
       sair = 1;
     }
     else{
       printf("Comando Inválido\n");
     }
   }
 
   //Salva estado atual da agenda
   salvar_agenda(agenda, entradas);
  
   return 0;
}