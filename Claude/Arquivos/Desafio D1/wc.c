#include <stdio.h>
#include <string.h>
#include <ctype.h>

void contarArquivo(char *nome, int *linhas, int *palavras, int *chars);

int main(){
    FILE* fp = fopen("texto.txt", "w");
    if(!fp) return 1;
    
    char* texto[] = {"o rato roeu a roupa do rei de roma",
    "a arara ara",
    "o lobo comeu o cordeiro",
    "pack my box with five dozen liquor jugs"};

    
    return 0;
}

void contarArquivo(char *nome, int *linhas, int *palavras, int *chars){

}