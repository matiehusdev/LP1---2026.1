#include <stdio.h>
#include <string.h>

int main(){
    // Parte 1 - escrever o poema no arquivo
    FILE* fp = fopen("poema.txt", "w");
    if(!fp) return 1;

    char *poema[] = {"A vida e bela", "O sol brilha forte", "O vento sopra suave", "a chuva cai mansamente", "O mar e infinito", "A terra e nossa casa"};
    for(int i = 0; i < 6; i++){
        fprintf(fp, "%s\n", poema[i]);
    }

    fclose(fp);
    
    // Parte 2 - leitura do poema indicando cada linha
    fp = fopen("poema.txt", "r");
    if(!fp) return 1;

    char linha[101];
    int i = 0;
    int tamLinha = 0;
    int maiorLinha;
    
    while(fgets(linha, sizeof(linha), fp) != NULL){
        linha[strcspn(linha, "\n")] = '\0';        
        printf("%d: %s\n", i+1, linha);

        int aux= strlen(linha);
        if(tamLinha < aux){
            tamLinha = aux;
            maiorLinha = i+1;
        }
        i++;
    }
    
    fclose(fp);

    // Parte 3 - imprimir quantas linhas foram lidas e qual foi a maior linha
    printf("Foram lidas %d linhas\n", i);
    printf("A maior linha foi a %d\n", maiorLinha);

    return 0;
}