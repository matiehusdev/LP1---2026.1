#include "TAD_LISTAGEN.h"
#include <stdio.h>
#include <stdlib.h>

ListaGen* lstgen_cria(){
    return NULL;
}

int lstgen_vazia(ListaGen* l){
    return l == NULL;
}

ListaGen* lstgen_insere(ListaGen* l, void* elemento){
    ListaGen* novo = (ListaGen*)malloc(sizeof(ListaGen));
    novo->info = elemento;
    novo->prox = l;
    return novo;
}

void lstgen_percorre(ListaGen* l, void (*processa)(void*)){
    for(ListaGen* p = l; p != NULL; p = p->prox)
        processa(p->info);
}

void* lstgen_busca(ListaGen* l, int (*compara)(void*, void*), void* dado){
    for(ListaGen* p = l; p != NULL; p = p->prox)
        if(compara(p->info, dado))
            return p->info;
    return NULL;
}

ListaGen* lstgen_retira(ListaGen* l,  int (*compara)(void*, void*), void* dado){
    ListaGen* p = l;
    ListaGen* ant = NULL;
    while(p != NULL){
        ListaGen* aux = p;
        if(compara(p->info, dado)){
            if(ant == NULL)
                l = p->prox;
            else
                ant->prox = p->prox;
            free(aux);
            return l;
        }
        ant = p;
        p = p->prox;
    }
    return l;
}

ListaGen* lstgen_duplica(ListaGen* l, void* (*duplica)(void*)){
    ListaGen* novo = NULL;
    ListaGen* final = NULL;
    for(ListaGen* p = l; p != NULL; p = p->prox){
        ListaGen* aux = (ListaGen*)malloc(sizeof(ListaGen));
            aux->info = duplica(p->info);
            aux->prox = NULL;
        if(novo == NULL)
            novo = aux;
        else
            final->prox = aux;
        final = aux;
    }
    return novo;
}

void lstgen_libera(ListaGen* l);
ListaGen* lstgen_filtra(ListaGen* l, int (*criterio)(void*)){
    ListaGen* filt = NULL;
    for(; l != NULL; l = l->prox)
        if(criterio(l->info))
            filt = lstgen_insere(filt, l->info);
    return filt;
}
ListaGen* lstgen_filtra(ListaGen* l, int (*criterio)(void*)){
    ListaGen* filt = NULL;
    for(ListaGen* p = l; p != NULL; p = p->prox){
        if(criterio(p->info))
            filt = lstgen_insere(filt, p->info);
    }
    return filt;
}
ListaGen* lstgen_conc(ListaGen* l1, ListaGen* l2){
    if(l1 == NULL) return l2;

    ListaGen* p = l1;
    while(p->prox != NULL)
        p = p->prox;

    p->prox = l2;
    return l1;
}
ListaGen* lstgen_ordena(ListaGen* l, int (*compara)(void*, void*));
int lstgen_grava_csv(ListaGen* l, char* nome_arquivo_csv, char* (*cria_linha_csv)(void*));
ListaGen* lstgen_carrega_csv(char* nome_arquivo_csv, void* (*cria_elemento)(char* linha_csv));
