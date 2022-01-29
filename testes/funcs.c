#include <stdio.h>
#include <string.h>
 
#include "definitions.h"
 
void ordena_agenda(Entry* vet, int tam){
   Entry aux;
 
   for(int i=0; i<tam-1; i++)
       for(int j=i+1; j<tam; j++){
           if(vet[i].hi > vet[j].hi){
               aux = vet[i];
               vet[i] = vet[j];
               vet[j] = aux;
           }
           else if(vet[i].hi == vet[j].hi && vet[i].mi > vet[j].mi){
               aux = vet[i];
               vet[i] = vet[j];
               vet[j] = aux;
           }
       }
}
 
void consulta_compromissos(Entry* agenda, int hi, int mi, int hf, int mf){
 if(agenda->hi > hi && agenda->hi < hf){
   printf("%02d:%02d - %s\n", agenda->hi, agenda->mi, agenda->descricao);
 }
 else if(agenda->hi == hi && agenda->hf == hi){
   if(agenda->mi >= mi && agenda->mi <= mf)
     printf("%02d:%02d - %s\n", agenda->hi, agenda->mi, agenda->descricao);  
 }
 else if(agenda->hi == hi){
   if(agenda->mi >= mi)
     printf("%02d:%02d - %s\n", agenda->hi, agenda->mi, agenda->descricao);
 }
 else if(agenda->hi == hf){
     if(agenda->mi <= mf)
       printf("%02d:%02d - %s\n", agenda->hi, agenda->mi, agenda->descricao);
   }
}
 
void cadastra_compromisso(Entry *novo){
 char descricao[500];
 
 printf("Digite as informacoes:\n");
 scanf("%d:%d %d:%d", &novo->hi, &novo->mi, &novo->hf, &novo->mf);
 scanf(" %[^\n]", descricao);
 strcpy(novo->descricao, descricao);
}