#include "TAD_HASH.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static int hash(int mat){
    return mat % N;
}
    
Aluno* hsh_busca(Aluno** tab, int mat){
    int h = hash(mat);
    Aluno* a = tab[h];
    while(a != NULL) {
        if(a->mat == mat)
            return a;
        a = a->prox;
    }
    return NULL;
}

Aluno* hsh_insere(Aluno** tab, int mat, char* nome, char* tel, char* email) {
    int h = hash(mat);
    Aluno* a = tab[h];

    while(a != NULL) {
        if(a->mat == mat)
            break;
        a = a->prox;
    }

    if(a){
        strcpy(a->nome, nome);    
        strcpy(a->tel, tel);    
        strcpy(a->email, email);    
        return a;
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

int hsh_remove(Aluno** tab, int mat) {
    int h = hash(mat);

    Aluno* a = tab[h];
    Aluno* ant = NULL;

    while(a != NULL) {
        if(a->mat == mat)
            break;
        ant = a;
        a = a->prox;
    }

    if(a == NULL) return 0;
    if(ant == NULL)
        tab[h] = a->prox;
    else
        ant->prox = a->prox;
    free(a);
    return 1;
}

int hsh_atualiza(Aluno** tab, int mat, char* nome, char* tel, char* email) {
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

void hsh_lista_todos(Aluno** tab) {
    for(int i = 0; i < N; i++){
        Aluno* atual = tab[i];
        while(atual != NULL){
            printf("Aluno: %s\n", atual->nome);
            printf("Matricula: %d\n", atual->mat);
            printf("Telefone: %s\n", atual->tel);
            printf("Email: %s\n", atual->email);
            atual = atual->prox;
        }
    }
}

int hsh_conta_alunos(Aluno** tab) {
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

Aluno* hsh_busca_por_nome(Aluno** tab, char* nome) {
    for(int i = 0; i < N; i++){
        Aluno* atual = tab[i];
        while(atual != NULL){
            if(!strcmp(atual->nome, nome))
                return atual;
            atual = atual->prox;
        }
    }
    return NULL;
}

void hsh_limpa_tabela(Aluno** tab) {
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

float hsh_fator_carga(Aluno** tab) {
    return (float) hsh_conta_alunos(tab) / N;
}

int hsh_vazia(Aluno** tab) {
    for(int i = 0; i < N; i++)
        if(tab[i] != NULL)
            return 0;
    return 1;
}

int hsh_exporta_arquivo(Aluno** tab, char* filename, char* (*escrever_linha_csv)(void*)) {
    FILE* fp = fopen(filename, "w");
    if(!fp) return 0;

    for(int i = 0; i < N; i++){
        Aluno* atual = tab[i];
        while(atual != NULL){
            char* linha = ler_linha_csv(atual);
            if(!linha){
                fclose(fp);
                return 0;
            }
            fprintf(fp, "%s\n", linha);
            free(linha);
            atual = atual->prox;
        }
    }

    fclose(fp);
    return 1;
}

int hsh_importa_arquivo(Aluno** tab, char* filename, void* (*ler_linha_csv)(char*)) {
    FILE* fp = fopen(filename, "r");
    if(!fp) return 0;

    char linha[512];
    while(fgets(linha, 512, fp)){
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

int hsh_conta_colisoes(Aluno** tab) {
    int colisoes = 0;
    for(int i = 0; i < N; i++){
        if(tab[i] != NULL)
            colisoes += hsh_conta_colisoes(tab[i]->prox);
    }
    return colisoes;
}

Aluno* hsh_maior_lista(Aluno** tab) {
    int maior = 0;
    Aluno* maior_no = NULL;

    for(int i = 0; i < N; i++){
        Aluno* atual = tab[i];
        int aux = 0;
        while(atual != NULL){
            aux++;
            atual = atual->prox;
        }
        if(aux > maior){
            maior = aux;
            maior_no = tab[i];
        }
    }
    return maior_no;    
}

Aluno* hsh_rehash_aux(Aluno** tab, int mat, char* nome, char* tel, char* email, int tam) {
    int h = mat % tam;
    Aluno* a = tab[h];

    while(a != NULL){
        if(a->mat == mat)
            break;
        a = a->prox;
    }

    if(a){
        strcpy(a->nome, nome);
        strcpy(a->tel, tel);
        strcpy(a->email, email);
        return a;
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
int hsh_rehash(Aluno** tab_antiga, Aluno** tab_nova, int novo_tam) {
    int count = 0;
    for(int i = 0; i < N; i++){
        Aluno* atual = tab_antiga[i];
        while(atual != NULL){
            hsh_rehash_aux(tab_nova, atual->mat, atual->nome, atual->tel, atual->email, novo_tam);
            count++;
            atual = atual->prox;
        }
    }
    return count;
}

void hsh_imprime_estatisticas(Aluno** tab) {
    int total_alunos = 0;
    int posicoes_ocupadas = 0;
    int maior_lista = 0;

    for(int i = 0; i < N; i++){
        Aluno* atual = tab[i];
        int aux = 0;
        
        if(atual != NULL)
            posicoes_ocupadas++;
            
        while(atual != NULL){
            aux++;
            total_alunos++;
            atual = atual->prox;
        }
                    Aluno* atual = tab[i];
            while(atual != NULL && atual->prox != NULL){
                if(comparar(atual, atual->prox) > 0){ // se for maior que zero, b -> a | a-> b
                    int mat = atual->mat;
                    char nome[81], tel[13], email[39];
                    strcpy(nome, atual->nome);
                    strcpy(tel, atual->tel);
                    strcpy(email, atual->email);

                    atual->mat = atual->prox->mat;
                    strcpy(atual->nome, atual->prox->nome);
                    strcpy(atual->tel, atual->prox->tel);
                    strcpy(atual->email, atual->prox->email);

                    atual->prox->mat = mat;
                    strcpy(atual->prox->nome, nome);
                    strcpy(atual->prox->tel, tel);
                    strcpy(atual->prox->email, email);
                    trocou = 1;
                }
            }
        } while(trocou != 0);
    }
}

int hsh_exporta_binario(Aluno** tab, char* filename);

Aluno** hsh_importa_binario(char* filename);

        if(aux > maior_lista)
            maior_lista = aux;
    }
    
    float fator_carga = total_alunos / N;
    int colisoes = hsh_conta_colisoes(tab);

    printf("Total de alunos: %d\n", total_alunos);
    printf("Posicoes ocupadas: %d\n", posicoes_ocupadas);
    printf("Posicoes vazias: %d\n", N - posicoes_ocupadas);
    printf("Maior lista: %d nos\n", maior_lista);
    printf("Fator de carga: %.2f\n", fator_carga);
    printf("Colisoes: %d\n", colisoes);
}

Aluno** hsh_filtrar(Aluno** tab, int (*criterio)(Aluno*));

void hsh_ordenar_lista(Aluno** tab, int (*comparar)(Aluno*, Aluno*)) {
    for(int i = 0; i < N; i++){

        int trocou;
        do{
            trocou = 0;
            Aluno* atual = tab[i];
            while(atual != NULL && atual->prox != NULL){
                if(comparar(atual, atual->prox) > 0){ // se for maior que zero, b -> a | a-> b
                    int mat = atual->mat;
                    char nome[81], tel[13], email[39];
                    strcpy(nome, atual->nome);
                    strcpy(tel, atual->tel);
                    strcpy(email, atual->email);

                    atual->mat = atual->prox->mat;
                    strcpy(atual->nome, atual->prox->nome);
                    strcpy(atual->tel, atual->prox->tel);
                    strcpy(atual->email, atual->prox->email);

                    atual->prox->mat = mat;
                    strcpy(atual->prox->nome, nome);
                    strcpy(atual->prox->tel, tel);
                    strcpy(atual->prox->email, email);
                    trocou = 1;
                }
            }
        } while(trocou != 0);
    }
}

int hsh_exporta_binario(Aluno** tab, char* filename);

Aluno** hsh_importa_binario(char* filename);

int hsh_tamanho_bucket(Aluno** tab, int indice) {
    Aluno* atual = tab[indice];

    int count = 0;
    while(atual != NULL){
        count++;
        atual = atual->prox;
    }

    return count;
}

int hsh_maior_colisao(Aluno** tab) {
    int maior = 0;

    for(int i = 0; i < N; i++){
        Aluno* atual = tab[i];
        int aux = 0;
        while(atual != NULL){
            aux++;
            atual = atual->prox;
        }
        if(aux > maior)
            maior = aux;
    }
    
    return maior;
}


Aluno* hsh_insere_final(Aluno** tab, int mat, char* nome, char* tel, char* email) {
    int h = hash(mat);
    Aluno* atual = tab[h];
    Aluno* ultimo = NULL;
    while(atual != NULL){
        if(atual->mat == mat){
            strcpy(atual->nome, nome);
            strcpy(atual->tel, tel);
            strcpy(atual->email, email);            Aluno* atual = tab[i];
            while(atual != NULL && atual->prox != NULL){
                if(comparar(atual, atual->prox) > 0){ // se for maior que zero, b -> a | a-> b
                    int mat = atual->mat;
                    char nome[81], tel[13], email[39];
                    strcpy(nome, atual->nome);
                    strcpy(tel, atual->tel);
                    strcpy(email, atual->email);

                    atual->mat = atual->prox->mat;
                    strcpy(atual->nome, atual->prox->nome);
                    strcpy(atual->tel, atual->prox->tel);
                    strcpy(atual->email, atual->prox->email);

                    atual->prox->mat = mat;
                    strcpy(atual->prox->nome, nome);
                    strcpy(atual->prox->tel, tel);
                    strcpy(atual->prox->email, email);
                    trocou = 1;
                }
            }
        } while(trocou != 0);
    }
}

int hsh_exporta_binario(Aluno** tab, char* filename);

Aluno** hsh_importa_binario(char* filename);

            return atual;
        }
        ultimo = atual;
        atual = atual->prox;
    }
    
    Aluno* novo = (Aluno*)malloc(sizeof(Aluno));
    if(!novo) exit(1);
    
    novo->mat = mat;
    strcpy(novo->nome, nome);
    strcpy(novo->tel, tel);
    strcpy(novo->email, email);
    novo->prox = NULL;
    
    if(ultimo == NULL)
    tab[h] = novo;
    else
    ultimo->prox = novo;
    
    return atual;
}

Aluno* hsh_clone_aux(Aluno** tab, int tam, int mat, char* nome, char* tel, char* email) {
    int h = mat % tam;
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

Aluno* hsh_clone(Aluno** tab, int tam) {
    Aluno** new_tab = calloc(tam, sizeof(Aluno*));

    for(int i = 0; i < N; i++){
        Aluno* atual = tab[i];
        while(atual != NULL){
            hsh_clone_aux(new_tab, tam, atual->mat, atual->nome, atual->tel, atual->email);
            atual = atual->prox;
        }
    }
    return new_tab;
}

int hsh_exporta_prefixo(Aluno** tab, char* prefixo, char* filename) {
    FILE* fp = fopen(filename, "w");
    if(!fp) return 0;

    for(int i = 0; i < N; i++){
        Aluno* atual = tab[i];
        while(atual != NULL){
            if(strncmp(atual->nome, prefixo, strlen(prefixo)) == 0)
                fprintf(fp, "%d,%s,%s,%s\n", atual->mat, atual->nome, atual->tel, atual->email);
            atual = atual->prox;
        }
    }

    fclose(fp);

    return 1;
}

float hsh_calcula_media(Aluno** tab) {
    float sum = 0.0;
    float count = 0;

    for(int i = 0; i < N; i++){
        Aluno* atual = tab[i];
        while(atual != NULL){
            count++;
            sum += atual->nota;
            atual = atual->prox;
        }
    }

    if(count == 0) return 0.0;
    return sum / count;
}

int hsh_exporta_acima_media(Aluno** tab, char* filename) {
    FILE* fp = fopen(filename, "w");
    if(!fp) return 0;

    float media = hsh_calcula_media(tab);

    for(int i = 0; i < N; i++){
        Aluno* atual = tab[i];
        while(atual != NULL){
            if(atual->nota > media)
                fprintf(fp, "%d,%s,%.2f\n", atual->mat, atual->nome, atual->nota);
            atual = atual->prox;
        }
    }
    
    fclose(fp);
    return 1;
}

int hsh_mesclar_arquivos(char* filename1, char* filename2, char* filename_saida) {
    FILE* f_saida = fopen(filename_saida, "w");

    // ler o primeiro arquivo, insere os elementos na tabela e no hash de matriculas
    FILE* f1 = fopen(filename1, "r");
    if(!f1 || !f_saida) return 0;

    int mat;
    char nome[81];
    char tel[13];
    char email[51];
    int mat_vistas[N];

    while(fscanf(f1, "%d,%[^,],%[^,],%s", &mat, nome, tel, email) == 4){
        fprintf(f_saida, "%d,%s,%s,%s\n", mat, nome, tel, email);
        mat_vistas[mat ] = mat;
    }
    fclose(f1);

    // ler o segundo arquivo, verifica se a matricula já está na tabela
    // se não estiver adiciona a tabela e ao hash de matriculas
    FILE* f2 = fopen(filename2, "r");
    if(!f2){
        fclose(f_saida);
        return 0;
    }
    int existe = 0;
    for(int i = 0; fscanf(f2, "%d,%[^,],%[^,],%s", &mat, nome, tel, email) == 4; i++){
        int h = mat % N;
        if(mat_vistas[h] == mat){
            existe = 1;
            break;
        }
    }
    fclose(f2);
    fclose(f_saida);
    return 1;
}