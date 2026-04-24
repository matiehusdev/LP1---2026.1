#ifndef __TAD_PILHAGEN__
    #define __TAD_PILHAGEN__

    typedef struct lista{
        void* info;
        struct lista* prox;
    } Lista;
    
    typedef struct pilha{
        Lista* prim;
    } PilhaGen;

    int PilhaGen_vazia(PilhaGen* p);
    PilhaGen* PilhaGen_cria();
    void PilhaGen_push(PilhaGen* p, void* elemento);
    void* PilhaGen_pop(PilhaGen* p);
    void PilhaGen_libera(PilhaGen* p);
    void PilhaGen_percorre(PilhaGen* p, void (*cb)(void* elemento));

#endif