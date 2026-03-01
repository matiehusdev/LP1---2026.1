#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TAD_PILHAGEN\TAD_PILHAGEN.h"

typedef struct aluno{
    int id;
    char nome[51];
} Aluno;

void turma_imprime(void* turma);

int main(){
    // CRIANDO UMA PILHA DE ALUNOS
    PilhaGen* turma = PilhaGen_cria();
    for(int i = 0; i < 5; i++){
        Aluno* a = (Aluno*)malloc(sizeof(Aluno));
        if(!a) exit(1);
        
        a->id = i+1;
        
        printf("Nome do aluno: ");
        scanf(" %50[^\n]", a->nome);
    
        PilhaGen_push(turma, a);
    }

    // IMPRIMINDO TURMA
    PilhaGen_percorre(turma, turma_imprime);

    // REMOVENDO ALUNO DO TOPO DA PILHA (TURMA)
    Aluno* saiu = PilhaGen_pop(turma);
    printf("Aluno removido \n");
    printf("ID: %d\n", saiu->id);
    printf("Nome: %s\n",saiu->nome);
    printf("\n");
    free(saiu);

    // IMPRIMINDO TURMA DEPOIS DO POP
    PilhaGen_percorre(turma, turma_imprime);

    // LIBERANDO A PILHA
    PilhaGen_libera(turma);
}

void turma_imprime(void* elemento){
    Aluno* a = (Aluno*)elemento;

    printf("ID: %d\n", a->id);
    printf("Nome: %s\n", a->nome);
    printf("############\n");
}