/*Escreva um programa completo em C chamado hash_arquivo.c que implemente
a mesma TAD de alunos, mas persistida em arquivo binário — a tabela não
existe em memória, cada operação lê e escreve diretamente no disco.*/

#include <stdio.h>
#include <stdlib.h>

#define N 127
#define VAZIO    0
#define OCUPADO  1
#define REMOVIDO 2

typedef struct {
    int  mat;
    char nome[81];
    char tel[13];
    char email[51];
    int  estado;       /* VAZIO, OCUPADO ou REMOVIDO */
} Aluno;              /* sem ponteiro prox — arquivo não tem listas */

// inicializa todos em estado vazio
void hsh_inicializar(char *filename);

// Lê o arquivo de indice i para *a
void hsh_ler(FILE *fp, int i, Aluno *a);

// Escreve *a na posição i do arquivo
void hsh_escrever(FILE *fp, int i, Aluno *a);

// Insere com sondagem linear. Retorna 1 em sucesso e 0 em tabela cheia 
int hsh_inserir(FILE *fp, int mat, char *nome, char *tel, char *email);

// Retorna indice onde o aluno está, ou -1 se não encontrar
int hsh_buscar(FILE *fp, int mat);

// Marca o estado como REMOVIDO. Retorna 1 em sucesso e 0 caso contrário
int hsh_remover(FILE *fp, int mat);

int main() {
    return 0;
}

void hsh_inicializar(char *filename) {
    FILE* fp = fopen(filename, "wb");
    if(!fp) return;

    Aluno a;
    a.estado = VAZIO;

    for(int i = 0; i < N; i++)
        fwrite(&a, sizeof(Aluno), 1, fp);
    
    fclose(fp);
}

void hsh_ler(FILE *fp, int i, Aluno *a) {
    fseek(fp, i * sizeof(Aluno), SEEK_SET);
    fread(a, sizeof(Aluno), 1, fp);
}

void hsh_escrever(FILE *fp, int i, Aluno *a) {
    fseek(fp, i * sizeof(Aluno), SEEK_SET);
    fwrite(a, sizeof(Aluno), 1, fp);
}

int hsh_inserir(FILE *fp, int mat, char *nome, char *tel, char *email) {
    int h = mat % N;
    int i = h;

    Aluno novo, lido;
    novo.mat = mat;
    strcpy(novo.nome, nome);
    strcpy(novo.tel, tel);
    strcpy(novo.email, email);
    
    do{
        hsh_ler(fp, i, &lido);

        if(lido.estado == VAZIO || lido.estado == REMOVIDO){
            hsh_escrever(fp, i, &novo);
            return 1;
        }
        if(lido.estado == OCUPADO){

        }
        i = (i+1) % N;
    }
    while(i != h);
    return 0;
}

int hsh_buscar(FILE *fp, int mat) {
    fseek
}

int hsh_remover(FILE *fp, int mat);