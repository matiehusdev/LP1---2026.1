#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TAD_HASH/TAD_HASH.h"

// ===============================
// Função para ler uma linha CSV
// ===============================
void* ler_linha_csv(char* linha) {
    Aluno* a = (Aluno*) malloc(sizeof(Aluno));
    if (!a) return NULL;

    char* token = strtok(linha, ",");

    if (!token) return NULL;
    a->mat = atoi(token);

    token = strtok(NULL, ",");
    if (!token) return NULL;
    strcpy(a->nome, token);

    token = strtok(NULL, ",");
    if (!token) return NULL;
    strcpy(a->tel, token);

    token = strtok(NULL, ",");
    if (!token) return NULL;
    strcpy(a->email, token);

    token = strtok(NULL, ",");
    if (!token) return NULL;
    a->nota = atof(token);

    a->prox = NULL;

    return a;
}

// ===============================
// Função para escrever CSV
// ===============================
char* escrever_linha_csv(void* dado) {
    Aluno* a = (Aluno*) dado;

    char* linha = (char*) malloc(200);
    sprintf(linha, "%d,%s,%s,%s,%.2f\n",
            a->mat, a->nome, a->tel, a->email, a->nota);

    return linha;
}

// ===============================
// Inicializa tabela
// ===============================
void inicializar_tabela(Aluno** tab) {
    for (int i = 0; i < N; i++) {
        tab[i] = NULL;
    }
}

// ===============================
// MAIN
// ===============================
int main() {
    inicializar_tabela(TABELA);

    printf("==== IMPORTANDO CSV ====\n");
    if (!hsh_importa_arquivo(TABELA, "alunos.csv", ler_linha_csv)) {
        printf("Erro ao importar arquivo\n");
        return 1;
    }

    printf("\n==== LISTA COMPLETA ====\n");
    hsh_lista_todos(TABELA);

    printf("\n==== TOTAL DE ALUNOS ====\n");
    printf("Total: %d\n", hsh_conta_alunos(TABELA));

    printf("\n==== BUSCA POR MATRICULA ====\n");
    Aluno* a = hsh_busca(TABELA, 101);
    if (a) {
        printf("Encontrado: %s (%.2f)\n", a->nome, a->nota);
    } else {
        printf("Aluno não encontrado\n");
    }

    printf("\n==== BUSCA POR NOME (Ana) ====\n");
    a = hsh_busca_por_nome(TABELA, "Ana");
    if (a) {
        printf("Encontrado: %s\n", a->nome);
    }

    printf("\n==== ATUALIZANDO ALUNO ====\n");
    hsh_atualiza(TABELA, 102, "Bruno Atualizado", "85900000000", "novo@email.com");

    printf("\n==== REMOVENDO ALUNO ====\n");
    hsh_remove(TABELA, 103);

    printf("\n==== LISTA APÓS ALTERAÇÕES ====\n");
    hsh_lista_todos(TABELA);

    printf("\n==== FATOR DE CARGA ====\n");
    printf("Fator: %.3f\n", hsh_fator_carga(TABELA));

    printf("\n==== COLISÕES ====\n");
    printf("Total colisões: %d\n", hsh_conta_colisoes(TABELA));

    printf("\n==== MAIOR LISTA ====\n");
    Aluno* maior = hsh_maior_lista(TABELA);
    if (maior) {
        printf("Primeiro da maior lista: %s\n", maior->nome);
    }

    printf("\n==== EXPORTANDO CSV ====\n");
    hsh_exporta_arquivo(TABELA, "saida.csv", escrever_linha_csv);

    printf("\n==== EXPORTANDO ACIMA DA MEDIA ====\n");
    hsh_exporta_acima_media(TABELA, "acima_media.txt");

    printf("\n==== EXPORTANDO PREFIXO (Ana) ====\n");
    hsh_exporta_prefixo(TABELA, "Ana", "prefixo.txt");

    printf("\n==== LIMPEZA ====\n");
    hsh_limpa_tabela(TABELA);

    printf("Tabela limpa.\n");

    return 0;
}