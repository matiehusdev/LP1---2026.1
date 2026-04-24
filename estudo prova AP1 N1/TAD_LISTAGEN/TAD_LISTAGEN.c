#include "TAD_LISTAGEN.h"
#include <stdio.h>
#include <stdlib.h>

ListaGen* lstgen_cria(){
    return NULL;
}
int lstgen_vazia(ListaGen* l){
    return (l == NULL);
}
ListaGen* lstgen_insere(ListaGen* l, void* elemento){
    ListaGen* novo = (ListaGen*)malloc(sizeof(ListaGen));
    if(!novo) exit(1);
    novo->info = elemento;
    novo->prox = l;

    l = novo;
    return l;
}
ListaGen* lstgen_inserefinal(ListaGen* l, void* elemento){
    ListaGen* novo = (ListaGen*)malloc(sizeof(ListaGen));
    if(!novo) exit(1);
    novo->info = elemento;
    novo->prox = NULL;

    if(l == NULL)
        return novo;

    ListaGen* p = l;
    while(p->prox != NULL){
        p = p->prox;
    }

    p->prox = novo;
    return l;
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
        if(criterio(p->info, dado)){
            ListaGen* aux = p;
            if(ant == NULL)
                l = p->prox;        
            else
                ant->prox = p->prox;
            free(aux);
            return l;
        }
        else{
            ant = p;
            p = p->prox;
        }
    }
    return l;
}
ListaGen* lstgen_duplica(ListaGen* l, void* (*duplica)(void*)){
    ListaGen* novo = NULL;
    ListaGen* final = NULL;

    for(ListaGen* p = l; p != NULL; p = p->prox){
        ListaGen* aux = (ListaGen*)malloc(sizeof(ListaGen));
        if(!aux) exit(1);
        aux->info = duplica(p->info);
        aux->prox = NULL;

        if(novo = NULL)
            novo = aux;
        else
            final->prox = aux;
        final = aux;
    }
    return novo;
}
void lstgen_libera(ListaGen* l);
ListaGen* lstgen_filtra(ListaGen* l, int (*criterio)(void*));
ListaGen* lstgen_ordena(ListaGen* l, int (*compara)(void*, void*)){
    ListaGen* p = l->prox;
    while(l != NULL){
        if(compara(l->info, p->info)){
            void* aux = p->info;
            p->info = l->info;
            l->info = aux;
        }
        p = p->prox;
    }
    return l;
}
int lstgen_grava_csv(ListaGen* l, char* nome_arquivo_csv, char* (*cria_linha_csv)(void*));
ListaGen* lstgen_carrega_csv(char* nome_arquivo_csv, void* (*cria_elemento)(char* linha_csv));