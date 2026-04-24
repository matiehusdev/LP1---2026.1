#include <stdio.h>
#include <string.h>

int main(){
    FILE* fp = fopen("arquivo.txt", "rt");
    if(!fp) return 404;
    
    char c;
    int nlinhas = 0;


    while(fscanf("%c", &c) == 1){
        if(c != '\n')
            nlinhas++;
    }

    fclose(fp);

    // número de linhas usando fscanf
    printf("Numero de linhas do arquivo: %d\n", nlinhas);
    
    return 0;
}