#include "TAD_HASH.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static int hash(int mat){
    return mat % N;
}

Aluno* hsh_busca(Aluno** tab, int mat){
    int h = hash(mat);
    Aluno* atual = tab[h];
    while(atual != NULL){
        if(atual->mat == mat)
            return atual;
        atual = atual->prox;
    }
    return NULL;
}

Aluno* hsh_insere(Aluno** tab, int mat, char* nome, char* tel, char* email){
    int h = hash(mat);
    Aluno* atual = tab[h];
    while(atual != NULL){
        if(atual->mat == mat){
            strcpy(atual->nome, nome);
            strcpy(atual->tel, tel);
            strcpy(atual->email, email);
            return atual;
        }
        atual = atual->prox;
    }

    Aluno* novo = (Aluno*)malloc(sizeof(Aluno));
    if(!novo) exit(1);
    novo->mat = mat;
    strcpy(novo->nome, nome);
    strcpy(novo->tel, tel);
    strcpy(novo->email, email);
    novo->prox = tab[h];
    tab[h] = novo;

    return novo;
}

int hsh_remove(Aluno** tab, int mat){
    int h = hash(mat);
    Aluno* atual = tab[h];
    Aluno* ant = NULL;
    
    while(atual != NULL){
        if(atual->mat == mat){
            if(ant == NULL)
                tab[h] = atual->prox;
            else
                ant->prox = atual->prox;
            free(atual);
            return 1;
        }
        else
            ant = atual;
        atual = atual->prox;
    }
    return 0;
}

int hsh_atualiza(Aluno** tab, int mat, char* nome, char* tel, char* email){
    int h = hash(mat);
    Aluno* atual = tab[h];

    while(atual != NULL){
        if(atual->mat == mat){
            strcpy(atual->nome, nome);
            strcpy(atual->tel, tel);
            strcpy(atual->email, email);
            return 1;
        }
        atual = atual->prox;
    }
    return 0;
}

void hsh_lista_todos(Aluno** tab){
    for(int i = 0; i < N; i++){
        Aluno* atual = tab[h];
        while(atual != NULL){
            printf("Aluno: %s | matricula: %d\n", atual->nome, atual->mat);
            atual = atual->prox;
        }
    }
}

int hsh_conta_alunos(Aluno** tab){
    int count = 0;
    for(int i = 0; i < N; i++){
        Aluno* atual = tab[i];
        while(atual != NULL){
            count++;
            atual = atual->prox;
        }
    }
    return count;
}

Aluno* hsh_busca_por_nome(Aluno** tab, char* nome);

void hsh_limpa_tabela(Aluno** tab){
    for(int i = 0; i < N; i++){
        Aluno* atual = tab[i];
        while(atual != NULL){
            Aluno* temp = atual->prox;
            free(atual);
            atual = temp;
        }
        tab[i] = NULL;
    }
}

float hsh_fator_carga(Aluno** tab){
    int count = 0;
    for(int i = 0; i < N; i++){
        Aluno* atual = tab[i];
        while(atual != NULL){
            count++;
            atual = atual->prox;
        }
    }
    return (float)count / N;
}

int hsh_vazia(Aluno** tab);

int hsh_exporta_arquivo(Aluno** tab, char* filename, char* (*escrever_linha_csv)(void*)){
    FILE* fp = fopen(filename, "w");
    if(!fp) return 0;

    for(int i = 0; i < N; i++){
        Aluno* atual = tab[i];
        while(atual != NULL){
            char* linha = escrever_linha_csv(atual);
            fprintf(fp, "%s\n", linha);
            free(linha);
            atual = atual->prox;
        }
    }

    fclose(fp);
    return 1;
}

int hsh_importa_arquivo(Aluno** tab, char* filename, void* (*ler_linha_csv)(char*)){
    FILE*  fp = fopen(filename, "r");
    if(!fp) return 0;

    char linha[155];
    while(fgets(linha, 155, fp)){
        linha[strcspn(linha, "\n")] = '\0';

        Aluno* a = (Aluno*) ler_linha_csv(linha);
        if(!a){
            fclose(fp);
            return 0;
        }

        hsh_insere(tab, a->mat, a->nome, a->tel, a->email);
        free(a);
    }

    fclose(fp);
    return 1;
}

int hsh_conta_colisoes(Aluno** tab);

Aluno* hsh_maior_lista(Aluno** tab);

int hsh_rehash(Aluno** tab_antiga, Aluno** tab_nova, int novo_tam);

void hsh_imprime_estatisticas(Aluno** tab);

Aluno** hsh_filtrar(Aluno** tab, int (*criterio)(Aluno*)){
    Aluno** new_tab = (Aluno**)malloc(N * sizeof(Aluno*));
    if(!new_tab) return NULL;

    for(int i = 0; i < N; i++){
        new_tab[i] = NULL;
    }

    for(int i = 0; i < N; i++){
        Aluno* atual = tab[i];
        while(atual != NULL){
            if(criterio(atual))
                hsh_insere(new_tab, atual->mat, atual->nome, atual->tel, atual->email);
            atual = atual->prox;
        }
    }
    return new_tab;
}

void hsh_ordenar_lista(Aluno** tab, int (*comparar)(Aluno*, Aluno*));

int hsh_exporta_binario(Aluno** tab, char* filename);

Aluno** hsh_importa_binario(char* filename);

int hsh_tamanho_bucket(Aluno** tab, int indice);

int hsh_maior_colisao(Aluno** tab); 

Aluno* hsh_insere_final(Aluno** tab, int mat, char* nome, char* tel, char* email);
    
Aluno* hsh_clone(Aluno** tab, int tam);
    
int hsh_exporta_prefixo(Aluno** tab, char* prefixo, char* filename);
    
int hsh_exporta_acima_media(Aluno** tab, char* filename);
    
int hsh_mesclar_arquivos(char* filename1, char* filename2, char* filename_saida);