#include <stdio.h>
#include <stdlib.h>

typedef struct arvvar{
    int info;
    struct arvvar* prim;
    struct arvvar* prox;
} Arvvar;

Arvvar* arvv_cria(int x);
void arvv_insere(Arvvar* a, Arvvar* sa);
int pares(Arvvar* a);
int folhas(Arvvar* a);
int um_filho(Arvvar* a);
int igual(Arvvar* a, Arvvar* b);
Arvvar* copia(Arvvar* a);

int main(){
    
    return 0;
}

Arvvar* arvv_cria(int x){
    Arvvar* a = (Arvvar*)malloc(sizeof(Arvvar));
    a->info = x;
    a->prim = NULL;
    a->prox = NULL;
    return a;
}
void arvv_insere(Arvvar* a, Arvvar* sa){
    sa->prox = a->prim;
    a->prim = sa;
}
int pares(Arvvar* a){
    if(a == NULL)
        return 0;

    int cont = 0;
    if(a->info % 2 == 0)
        cont = 1;
    for(Arvvar* p = a->prim; p != NULL; p = p->prox)
        cont += pares(p);
    return cont;
}
int folhas(Arvvar* a){
    if(a == NULL)
        return 0;
        
    int cont = 0;
    if(a->prim == NULL)
        cont = 1;
    for(Arvvar* p = a->prim; p != NULL; p = p->prox)
        cont += folhas(p);
    return cont;
}
int um_filho(Arvvar* a){
    if(a == NULL)
        return 0;

    int cont = 0;

    int filhos = 0;
    for(Arvvar* p = a->prim; p != NULL; p = p->prox)
        filhos++;

    if(filhos == 1)
        cont = 1;
    
    for(Arvvar* p = a->prim; p != NULL; p = p->prox)
        cont += um_filho(p);
    return cont;
}
int igual(Arvvar* a, Arvvar* b){
    if(a == NULL && b == NULL)
        return 1;
    if(a == NULL || b == NULL)
        return 0;
    if(a->info != b->info)
        return 0;

    Arvvar* p = a->prim;
    Arvvar* q = b->prim;
    while(p != NULL && q != NULL){
        if(!igual(p, q))
            return 0;
        p = p->prox;
        q = q->prox;
    }

    if(p != NULL || q != NULL)
        return 0;

    return 1;
}
Arvvar* copia(Arvvar* a){
    if(a == NULL)
        return NULL;

    Arvvar* copy = (Arvvar*)malloc(sizeof(Arvvar));
    copy->info = a->info;
    copy->prim = NULL;
    copy->prox = NULL;

    Arvvar* ult = NULL;

    for(Arvvar* p = a->prim; p != NULL; p = p->prox){
        Arvvar* filhos = copia(p);

        if(copy->prim == NULL)
            copy->prim = filhos;
        else
            ult->prox = filhos;
        ult = filhos;
    }

    return copy;
}