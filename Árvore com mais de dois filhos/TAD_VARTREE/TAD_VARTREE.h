#ifndef __TAD_VARTREE_H__
    #define __TAD_VARTREE_H__

    #define N 3

    typedef struct arvvar{
        char info;
        struct arvvar* prim;
        struct arvvar* prox;
    } Arvvar;

    Arvvar* arvv_cria(char c);
    void arvv_insere(Arvvar* a, Arvvar* sa);
    void arvv_imprime(Arvvar* a);
    int arvv_pertence(Arvvar* a, char c);
    void arvv_libera(Arvvar* a);
    int arvv_altura(Arvvar* a);
    
    int arvv_nos(Arvvar* a);
    int arvv_folhas(Arvvar* a);
    int arvv_grau(Arvvar* a);
    
#endif