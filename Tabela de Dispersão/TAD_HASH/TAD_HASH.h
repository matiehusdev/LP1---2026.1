#ifndef __TAD_HASH__
    #define __TAD_HASH__
    
    #define N 127

    typedef struct aluno{
        int mat;
        char nome[81];
        char tel[13];
        char email[51];
        float nota;
        struct aluno* prox; 
    } Aluno;
    
    Aluno* TABELA[N];

    // 1. Calcula o hash de uma chave primária
    // static int hash(int mat);
    
    // 2. Busca um aluno por matrícula e retorna o ponteiro para a estrutura, caso exista.
    Aluno* hsh_busca(Aluno** tab, int mat);

    // 3. Insere um aluno na tabela de dispersão, caso a matrícula já exista, atualizar os dados do aluno.
    Aluno* hsh_insere(Aluno** tab, int mat, char* nome, char* tel, char* email);

    // 4. Remover aluno pela matrícula
    int hsh_remove(Aluno** tab, int mat);

    // 5. Atualizar dados de um aluno
    int hsh_atualiza(Aluno** tab, int mat, char* nome, char* tel, char* email);

    // 6. Listar todos os alunos
    void hsh_lista_todos(Aluno** tab);

    // 7. Contar número de alunos na tabela
    int hsh_conta_alunos(Aluno** tab);

    // 8. Buscar aluno por nome (busca parcial)
    Aluno* hsh_busca_por_nome(Aluno** tab, char* nome);

    // 9. Limpar/liberar toda a tabela
    void hsh_limpa_tabela(Aluno** tab);

    // 10. Calcular fator de carga da tabela
    float hsh_fator_carga(Aluno** tab);

    // 11. Verificar se tabela está vazia
    int hsh_vazia(Aluno** tab);

    // 12. Exportar dados para arquivo
    int hsh_exporta_arquivo(Aluno** tab, char* filename, char* (*escrever_linha_csv)(void*));

    // 13. Importar dados de arquivo
    int hsh_importa_arquivo(Aluno** tab, char* filename, void* (*ler_linha_csv)(char*));

    // Contar colisões — nós além do primeiro em cada lista
    int hsh_conta_colisoes(Aluno** tab);

    // Retornar o primeiro nó da lista mais longa da tabela
    Aluno* hsh_maior_lista(Aluno** tab);

    // Recriar a tabela com novo tamanho, reinserindo todos os elementos
    int hsh_rehash(Aluno** tab_antiga, Aluno** tab_nova, int novo_tam);

    // Imprimir relatório completo de estatísticas da tabela
    void hsh_imprime_estatisticas(Aluno** tab);

    // Retornar nova tabela apenas com alunos que passam no critério
    Aluno** hsh_filtrar(Aluno** tab, int (*criterio)(Aluno*));

    // Ordenar lista encadeada de cada posição usando função de comparação
    void hsh_ordenar_lista(Aluno** tab, int (*comparar)(Aluno*, Aluno*));

    // Exportar tabela para arquivo binário
    int hsh_exporta_binario(Aluno** tab, char* filename);

    // Importar tabela de arquivo binário e retornar nova tabela
    Aluno** hsh_importa_binario(char* filename);

    int hsh_tamanho_bucket(Aluno** tab, int indice);

    int hsh_maior_colisao(Aluno** tab);

    Aluno* hsh_insere_final(Aluno** tab, int mat, char* nome, char* tel, char* email);
    
    Aluno* hsh_clone(Aluno** tab, int tam);
    
    // Buscar alunos cujo nome contém o prefixo e salvar em arquivo texto
    int hsh_exporta_prefixo(Aluno** tab, char* prefixo, char* filename);
    
    // Buscar alunos com nota acima da média e salvar em arquivo texto
    int hsh_exporta_acima_media(Aluno** tab, char* filename);
    
    // Mesclar dois arquivos texto de alunos em um terceiro, sem duplicatas por matrícula
    int hsh_mesclar_arquivos(char* filename1, char* filename2, char* filename_saida);
    
#endif