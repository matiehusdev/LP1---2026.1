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