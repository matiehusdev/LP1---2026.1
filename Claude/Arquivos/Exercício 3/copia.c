#include <stdio.h>

int copiarArquivo(char *origem, char *destino);

int main(){
    FILE* fp = fopen("original.txt", "w");
    if(!fp) return 0;

    char *texto[] = {"Estrutura de Dados em C",
    "Waldemar Celes",
    "Capitulo 9 - Arquivos",
    "fgetc e fputc sao funcoes de leitura e escrita por caractere"};

    for(int i = 0; i < 4; i++){
        fprintf(fp, "%s\n", texto[i]);
    }

    fclose(fp);
    
    copiarArquivo("original.txt", "copia.txt");

    FILE* co = fopen("copia.txt", "r");
    if(!co) return 0;
    
    char linha[101];

    while(fgets(linha, 101, co)){
        printf("%s\n", linha);
    }

    fclose(co);

    return 0;
}

int copiarArquivo(char *origem, char *destino){
    FILE* fo = fopen(origem, "r");
    if(!fo) return 0;
    
    FILE* fd = fopen(destino, "w");
    if(!fd){
        fclose(fo); // se apenas o segundo falhar o primeiro deve ser fechado para retornar
        return 0;
    }

    int c;
    while((c = fgetc(fo)) != EOF){
        fputc(c, fd);
    }

    fclose(fo);
    fclose(fd);

    return 1;
}