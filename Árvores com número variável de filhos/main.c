#include <stdio.h>
#include "TAD_VARTREE/TAD_VARTREE.h"

int main(){
    /*Cria nós como folhas*/
    Arvvar* a = arvv_cria('a');
    Arvvar* b = arvv_cria('b');
    Arvvar* c = arvv_cria('c');
    Arvvar* d = arvv_cria('d');
    Arvvar* e = arvv_cria('e');
    Arvvar* f = arvv_cria('f');
    Arvvar* g = arvv_cria('g');
    Arvvar* h = arvv_cria('h');
    Arvvar* i = arvv_cria('i');
    Arvvar* j = arvv_cria('j');
    /*Monta a hierarquia*/
    arvv_insere(c,d);
    arvv_insere(b,e);
    arvv_insere(b,c);
    arvv_insere(i,j);
    arvv_insere(g,i);
    arvv_insere(g,h);
    arvv_insere(a,g);
    arvv_insere(a,f);
    arvv_insere(a,b);
    return 0;
}