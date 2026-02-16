#ifndef __TAD_LISTAGEN__
    #define __TAD_LISTAGEN__


    typedef struct listagen{
        void* info;
        struct listagen* prox;
    } ListaGen;

    ListaGen* lstgen_cria();
    int lstgen_vazia(ListaGen* l);
    ListaGen* lstgen_insere(ListaGen* l, void* elemento);
    void lstgen_percorre(ListaGen* l, void (*processa)(void*));
    void* lstgen_busca(ListaGen* l, int (*compara)(void*, void*), void* dado);
    ListaGen* lstgen_retira(ListaGen* l,  int (*compara)(void*, void*), void* dado);
    ListaGen* lstgen_duplica(ListaGen* l, void* (*duplica)(void*));
    void lstgen_libera(ListaGen* l);
    ListaGen* lstgen_filtra(ListaGen* l, int (*criterio)(void*));
    ListaGen* lstgen_ordena(ListaGen* l, int (*compara)(void*, void*));
    int lstgen_grava_csv(ListaGen* l, char* nome_arquivo_csv, char* (*cria_linha_csv)(void*));
    ListaGen* lstgen_carrega_csv(char* nome_arquivo_csv, void* (*cria_elemento)(char* linha_csv));


    #include "TAD_LISTAGEN.c"
#endif