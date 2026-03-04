#include "TAD_PILHAGEN.h"
#include <stdio.h>
#include <stdlib.h>

int PilhaGen_vazia(PilhaGen* p){
    return (p == NULL || p->prim == NULL);
}
PilhaGen* PilhaGen_cria(){
    PilhaGen* novo = (PilhaGen*)malloc(sizeof(PilhaGen));
    if(!novo) exit(1);

    novo->prim = NULL;
    return novo;
}
void PilhaGen_push(PilhaGen* p, void* elemento){
    Lista* aux = (Lista*)malloc(sizeof(Lista));
    if(!aux) exit(1);

    aux->info = elemento;
    aux->prox = p->prim;
    
    p->prim = aux;
}
void* PilhaGen_pop(PilhaGen* p){
    if(PilhaGen_vazia(p))
        return NULL;

    Lista* aux = p->prim;
    void* dado = aux->info;

    p->prim = aux->prox;
    free(aux);

    return dado;
}
void PilhaGen_libera(PilhaGen* p){
    Lista* aux = p->prim;
    while(aux != NULL){
        Lista* temp = aux->prox;
        free(aux->info);
        free(aux);
        aux = temp;
    }
}
void PilhaGen_percorre(PilhaGen* p, void (*cb)(void* elemento)){
    for(Lista* aux = p->prim; aux != NULL; aux = aux->prox)
        cb(aux->info);
}