#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TAD_PILHAGEN.h"
#include "..\TAD_LISTAGEN\TAD_LISTAGEN.h"

ListaGen* insere_final(ListaGen* l, void* info);

char* volta_pagina(PilhaGen* undo, PilhaGen* redo);
char* avancar_pagina(PilhaGen* undo, PilhaGen* redo);
void* pilha_topo(PilhaGen* p);

ListaGen* lstgen_filtra(ListaGen* l, int (*criterio)(void*));
ListaGen* lstgen_mapeia(ListaGen* l, void* (*transforma)(void*));
int pilhas_iguais(PilhaGen* p1, PilhaGen* p2, int (*compara)(void*, void*));
void lstgen_limpa_selecionados(ListaGen** l, int (*criterio)(void*), void (*libera_info)(void*));

int main(){
    
}

ListaGen* insere_final(ListaGen* l, void* info){
    ListaGen* aux = (ListaGen*)malloc(sizeof(ListaGen));
    if(!aux) exit(1);

    aux->info = info;
    aux->prox = NULL;

    if(lstgen_vazia(l))
        return aux;

    ListaGen* p = l;
    while(p->prox != NULL)
        p = p->prox;

    p->prox = aux;
    return l;
}

char* volta_pagina(PilhaGen* undo, PilhaGen* redo){
    if(PilhaGen_vazia(undo)) return NULL;

    char* atual = pilha_desempilhar(undo);

    if(PilhaGen_vazia(undo)){
        pilha_empilar(undo, atual);
        return NULL;
    }

    pilha_empilhar(redo, atual);

    return pilha_topo(undo);
}

char* avancar_pagina(PilhaGen* undo, PilhaGen* redo){
    if(PilhaGen_vazia(redo)) return NULL;

    char* pagina = pilha_desempilhar(redo);
    pilha_empilhar(undo, pagina);

    return pilha_topo(undo);
}

void* pilha_topo(PilhaGen* p){
    if(p == NULL || p->prim == NULL) return NULL;
    return p->prim->info;
}

ListaGen* lstgen_filtra(ListaGen* l, int (*criterio)(void*)){
    Lista* filtrada = NULL;
    
    for(ListaGen* p = l; p != NULL; p = p->prox)
        if(criterio(p->info))
            filtrada = lstgen_insere(filtrada, p->info);

    return filtrada;
}

ListaGen* lstgen_mapeia(ListaGen* l, void* (*transforma)(void*)){
    ListaGen* nova_lista = NULL;
    for(ListaGen* p = l; p != NULL; p = p->prox){
        void* aux = transforma(p->info);
        nova_lista = insere_final(nova_lista, aux);
    }
    return nova_lista;
}

int pilhas_iguais(PilhaGen* p1, PilhaGen* p2, int (*compara)(void*, void*)){
    if(p1 == NULL || p2 == NULL)
        return 0;
    if(p1->prim == NULL || p2->prim == NULL)
        return 0;

    ListaGen* q1 = p1->prim;
    ListaGen* q2 = p2->prim;
    while(q1 != NULL && q2 != NULL){
        if(!compara(q1->info, q2->info))
            return 0;
        q1 = q1->prox;
        q2 = q2->prox;
    }

    if((q1 == NULL && q2 != NULL) || (q1 != NULL && q2 == NULL))
        return 0;
    
    return 1;
}

void lstgen_limpa_selecionados(ListaGen** l, int (*criterio)(void*), void (*libera_info)(void*));