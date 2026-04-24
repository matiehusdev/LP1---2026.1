#ifndef __TAD_FILAGEN__
    #define __TAD_FILAGEN__

    typedef struct lista{
        void* info;
        struct lista* prox;
    } Lista;

    typedef struct fila{
        Lista* ini;
        Lista* fin;
    } Fila;

    Fila* filagen_cria();
    void filagen_insere(Fila* f, void* elemento);
    void* filagen_retira(Fila* f);
    int filagen_vazia(Fila* f);
    void filagen_libera(Fila* f, void (*libera_dado)(void*));
    void filagen_percorre(Fila* f, void (*processa)(void*));
    
    int filagen_tamanho(Fila* f);
    void* filagen_busca(Fila* f, int (*compara)(void*, void*), void* chave);
    void filagen_concatena(Fila* f1, Fila* f2);
    Fila* filagen_filtra(Fila* f, int (*criterio)(void*));
#endif