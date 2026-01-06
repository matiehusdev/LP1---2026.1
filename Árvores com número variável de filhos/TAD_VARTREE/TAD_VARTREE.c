#include "TAD_VARTREE.h"
#include <stdio.h>
#include <stdlib.h>

static max2(int a, int b){
    return (a > b) ? a : b;
}

Arvvar* arvv_cria(char c){
    Arvvar* a = (Arvvar*)malloc(sizeof(Arvvar));
    a->info = c;
    a->prim = NULL;
    a->prox = NULL;
    return a;
}
void arvv_insere(Arvvar* a, Arvvar* sa){
    sa->prox = a->prim;
    a->prim = sa;
}
void arvv_imprime(Arvvar* a){
    Arvvar* p;
    printf("<%c\n", a->info);

    for(p = a->prim; p != NULL; p = p->prox)
        arvv_imprime(p);
    printf(">");
}
int arvv_pertence(Arvvar* a, char c){
    Arvvar* p;
    if(a->info == c)
        return 1;
    else{
        for(p = a->prim; p != NULL; p = p->prox){
            if(arvv_pertence(p, c))
                return 1;
        }
    }
    return 0;
}
void arvv_libera(Arvvar* a){
    Arvvar* p = a->prim;
    while(p != NULL){
        Arvvar* t = p->prox;
        arvv_libera(p);
        p = t;
    }
    free(a);
}
int arvv_altura(Arvvar* a){
    if(a == NULL)
        return -1;
    else
        return max2(1 + arvv_altura(a->prim), arvv_altura(a->prox));
}

int arvv_nos(Arvvar* a){
    if(a == NULL)
        return 0;
    
    int cont = 1;
    for(Arvvar* p = a->prim; p != NULL; p = p->prox)
        cont += arvv_nos(p);
    return cont;
}
int arvv_folhas(Arvvar* a){
    if(a == NULL)
        return 0;

    int cont = 0;
    if(a->prim == NULL)
        cont = 1;
    else
        for(Arvvar* p = a->prim; p != NULL; p = p->prox)
            cont += arvv_folhas(p);
    return cont;
}
int arvv_grau(Arvvar* a){
    if(a == NULL)
        return 0;

    int max = 0;
    for(Arvvar* p = a; p != NULL; p = p->prox){
        int grau = 0;
        for(Arvvar* f = p->prim; f != NULL; f = f->prox)
            grau++;

        if(grau > max)
            max = grau;

        int gfilhos = arvv_grau(p->prim);
        if(gfilhos > max)
            max = gfilhos;
    }
    return max;
}