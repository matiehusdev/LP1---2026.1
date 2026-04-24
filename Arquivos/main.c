#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    FILE* fp = fopen("arquivo.txt", "rt");
    if(fp == NULL) return 1;

    int c;
    int nlinhas = 0;

    while((c = fgetc(fp)) != EOF){
        printf("%c", c);
        if(c == '\n')
            nlinhas++;
    }

    fclose(fp);

    // número de linhas usando a forma padrão
    printf("Numero de linhas do arquivo: %d\n", nlinhas);

    return 0;
}