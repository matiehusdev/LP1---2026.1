#include <stdio.h>
#include <stdlib.h>
#include "TAD_FILAGEN.h"

Fila* filagen_cria(){
    Fila* f = (Fila*)malloc(sizeof(Fila));
    if(!f) exit(1);

    f->ini = f->fin = NULL;

    return f;
}
void filagen_insere(Fila* f, void* elemento){
    Lista* novo_elemento = (Lista*)malloc(sizeof(Lista));
    if(!novo_elemento) exit(1);

    novo_elemento->info = elemento;
    novo_elemento->prox = NULL;

    if(f->fin != NULL)
        f->fin->prox = novo_elemento;
    else
        f->ini = novo_elemento;
    f->fin = novo_elemento;
}
void* filagen_retira(Fila* f){
    if(filagen_vazia(f)) return NULL;

    Lista* p = f->ini;
    void* retirado = p->info;

    f->ini = p->prox; 

    if(f->ini == NULL)
        f->fin = NULL;
    
    free(p);
    return retirado;
}
int filagen_vazia(Fila* f){
    return (f == NULL || f->fin == NULL);
}
void filagen_libera(Fila* f, void (*libera_dado)(void*)){
    Lista* p = f->ini;
    while(p != NULL){
        Lista* aux = p->prox;
        if(libera_dado != NULL)
            libera_dado(p->info);
        p = aux;
    }
    free(f);
}
void filagen_percorre(Fila* f, void (*processa)(void*)){
    if(filagen_vazia(f) || processa == NULL) return;
    
    for(Lista* p =f->ini; p != NULL; p = p->prox)
        processa(p->info);
}
int filagen_tamanho(Fila* f){
    if(filagen_vazia(f)) return 0;
    
    Lista* p = f->ini;
    int tamanho = 0;

    while(p != NULL){
        tamanho++;
        p = p->prox;
    }    
    return tamanho;
}
void* filagen_busca(Fila* f, int (*compara)(void*, void*), void* chave){
    if(filagen_vazia(f) || compara == NULL) return NULL;
    
    for(Lista* p = f->ini; p != NULL; p = p->prox)
        if(compara(p->info, chave))
            return p->info;
    return NULL;
}
void filagen_concatena(Fila* f1, Fila* f2){
    if(f2 == NULL || filagen_vazia(f2)) return;

    if(filagen_vazia(f1)){
        f1->ini = f2->ini;
        f1->fin = f2->fin;
    }
    else{
        f1->fin->prox = f2->ini;
        f1->fin = f2->fin;
    }

    f2->ini = f2->fin = NULL;
}
Fila* filagen_filtra(Fila* f, int (*criterio)(void*)){
    if(f == NULL || criterio == NULL) return NULL;
    Fila* filtrada = filagen_cria();

    for(Lista* p = f->ini; p != NULL; p = p->prox)
        if(criterio(p->info))
            filagen_insere(filtrada, p->info);
    return filtrada;
}