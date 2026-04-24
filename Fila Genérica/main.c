#include <stdio.h>
#include <string.h>
#include "TAD_FILAGEN/TAD_FILAGEN.h"

typedef struct {
    char nome[30];
    float preco;
} Produto;

// Callback de Impressão
void imprime_produto(void* p) {
    Produto* prod = (Produto*)p;
    printf("Produto: %s | R$ %.2f\n", prod->nome, prod->preco);
}

// Callback de Filtro (Critério: preco < 100)
int eh_barato(void* p) {
    return ((Produto*)p)->preco < 100.0;
}

int main() {
    Fila* estoque = filagen_cria();

    // Criando alguns produtos
    Produto p1 = {"Teclado", 150.0};
    Produto p2 = {"Mouse", 80.0};
    Produto p3 = {"Cabo HDMI", 45.0};

    filagen_insere(estoque, &p1);
    filagen_insere(estoque, &p2);
    filagen_insere(estoque, &p3);

    printf("--- Estoque Completo (%d itens) ---\n", filagen_tamanho(estoque));
    filagen_percorre(estoque, imprime_produto);

    printf("\n--- Filtrando Produtos Baratos ---\n");
    Fila* baratos = filagen_filtra(estoque, eh_barato);
    filagen_percorre(baratos, imprime_produto);

    // Limpeza (Não passamos callback de liberação porque os produtos estão na stack)
    filagen_libera(estoque, NULL);
    filagen_libera(baratos, NULL);

    return 0;
}