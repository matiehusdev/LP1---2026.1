#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TAD_HASH/TAD_HASH.h"

// ==========================
// Exercício R1
// ==========================

/* Retorna o aluno com maior matrícula da tabela, ou NULL se vazia */
Aluno* hsh_maior_matricula(Aluno** tab) {
    Aluno* maior_mat = NULL;
    int aux = 0;
    for(int i = 0; i < N; i++){
        Aluno* atual = tab[i];
        while(atual != NULL){
            if(atual->mat > aux){
                aux = atual->mat;
                maior_mat = atual;
            }
            atual = atual->prox;
        }
    }
    return maior_mat;
}

/* Remove todos os alunos cuja nota seja menor que o valor informado
   Retorna quantos alunos foram removidos */
int hsh_remover_abaixo_nota(Aluno** tab, float nota_minima) {
    int removidos = 0;

    for(int i = 0; i < N; i++){
        Aluno* ant = NULL;
        Aluno* atual = tab[i];

        while(atual != NULL){
            Aluno* prox = atual->prox;
            if(atual->nota < nota_minima){
                removidos++;
                if(ant == NULL)
                    tab[i] = atual->prox;
                else
                    ant->prox = atual->prox;
                free(atual);
            }
            else
                ant = atual;            
            atual = prox;
        }
    }
    return removidos;
}

// ==========================
// Exercício R2
// ==========================

/* Transfere todos os alunos de tab_origem para tab_destino
   removendo-os de tab_origem. Retorna quantos foram transferidos. */
int hsh_transferir(Aluno** tab_origem, Aluno** tab_destino) {
    int transferidos = 0;

    for(int i = 0; i < N; i++){
        Aluno* atual = tab_origem[i];
        while(atual != NULL){
            Aluno* prox = atual->prox;
            hsh_insere(tab_destino, atual->mat, atual->nome, atual->tel, atual->email);
            free(atual);
            transferidos++;
            atual = prox;
        }
        tab_origem[i] = NULL;
    }
    return transferidos;
}

/* Retorna 1 se dois alunos com matrículas diferentes têm o mesmo
   hash, 0 caso contrário */
int hsh_colidem(int mat1, int mat2) {
    if(hash(mat1) == hash(mat2)) return 1;
    return 0;
}

// ==========================
// Exercício R3
// ==========================

/* Retorna uma nova tabela contendo apenas os alunos que existem
   nas DUAS tabelas (interseção por matrícula).
   Não modifica nenhuma das duas tabelas originais. */
Aluno** hsh_intersecao(Aluno** tab1, Aluno** tab2) {
    Aluno** new_tab = calloc(N, sizeof(Aluno*));
    if(!new_tab) return NULL;
    
    for(int i = 0; i < N; i++){
        Aluno* atual1 = tab1[i];
        while(atual1 != NULL){
            Aluno* atual2 = tab2[i];
            while(atual2 != NULL){
                if(atual1->mat == atual2->mat){
                    hsh_insere(new_tab, atual1->mat, atual1->nome, atual1->tel, atual1->email);
                    break;
                }
                atual2 = atual2->prox;
            }
            atual1 = atual1->prox;
        }
    }
    return new_tab;
}

/* Imprime todos os alunos ordenados por matrícula crescente
   sem modificar a tabela — usa um array auxiliar */

// Função auxiliar
void lst_ordena_imprime(Aluno* l) {
    Aluno* p = l;
    while(p != NULL && p->prox !+ NULL){
        Aluno* prox = p->prox;
        if(p->mat > p->prox->mat){
            prox->prox = p;
            p = prox;
        }
        p = p->prox;
    }
    while(l != NULL){
        printf("matricula: %d\n", l->mat);
        printf("matricula: %s\n", l->nome);
        printf("matricula: %s\n", l->tel);
        printf("matricula: %s\n", l->email);
        l = l->prox;
    }
}
void hsh_imprimir_ordenado(Aluno** tab) {
    for(int i = 0; i < N; i++){
        Aluno* atual = tab[i];
        lst_ordena_imprime(tab[i]);
    }
}

/* Retorna a matrícula que causou mais colisões na tabela,
   ou -1 se a tabela estiver vazia */
int hsh_matricula_mais_colisoes(Aluno** tab);