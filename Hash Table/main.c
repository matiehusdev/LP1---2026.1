#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct aluno{
    int mat;
    char nome[81];
    char email[41];
    char turma;
    struct aluno* prox;
} Aluno;

#define N 37
typedef Aluno* Hash[N];

/* protótipos */
void inicializa(Hash tab);
void insere(Hash tab, int mat, char* n, char* e, char t);
Aluno* busca(Hash tab, int mat);
void remove(Hash tab, int mat);
int hsh_colisoes(Hash tab);
int hsh_posicao_mais_carregada(Hash tab);

/* funções hash */
static int hash(int mat){
    return mat % N;
}

static int hash2(int mat){
    return N - 2 - mat % (N - 2);
}

void inicializa(Hash tab){
    for(int i = 0; i < N; i++)
        tab[i] = NULL;
}

int main(){
    Hash tab;

    inicializa(tab);

    return 0;
}

Aluno* busca(Hash tab, int mat){
    int h = hash(mat);

    Aluno* a = tab[h];
    while(a != NULL){
        if(a->mat == mat)
            return a;
        a = a->prox;
    }

    return NULL;
}

void insere(Hash tab, int mat, char* n, char* e, char t){
    int h = hash(mat);

    Aluno* a = tab[h];
    while(a != NULL){
        if(a->mat == mat)
            break;
        a = a->prox;
    }

    if(a == NULL){
        a = (Aluno*)malloc(sizeof(Aluno));
        a->mat = mat;
        a->prox = tab[h];
        tab[h] = a;
    }

    strcpy(a->nome, n);
    strcpy(a->email, e);
    a->turma = t;

    return a;
}

void remove(Hash tab, int mat){
    int h = hash(mat);

    Aluno* a = tab[h];
    Aluno* ant = NULL;
    while(a != NULL && a->mat != mat){
        ant = a;
        a = a->prox;
    }

    if(a != NULL){
        if(ant == NULL)
            tab[h] = a->prox;
        else
            ant->prox = a->prox;
        free(a);
    }
}

int hsh_colisoes(Hash tab){
    int qtd = 0;
    for(int i = 0; i < N; i++){
        int cont = 0;
        Aluno* a = tab[i];

        while(a != NULL){
            cont++;
            a = a->prox;
        }

        if(cont > 1)
            qtd += cont - 1;
    }
    return qtd;
}

int hsh_posicao_mais_carregada(Hash tab){
    int posicao = -1;
    
    int maior = 0;
    for(int i = 0; i < N; i++){
        Aluno* a = tab[i];

        int cont = 0;
        while(a != NULL){
            cont++;
            a = a->prox;
        }

        if(cont > maior){
            maior = cont;
            posicao = i;
        }
    }

    return posicao;
}