#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE* fp = fopen("../arquivo.txt", "rt");
    if(!fp){
        printf("erro\n");
        exit(2);
    }

    char c;
    float v1, v2;
    char linha[121];

    while(fgets(linha, 121, fp)){
        int n = sscanf(linha, " %c %f %f", &c, &v1, &v2);
        if(n > 0){
            switch(c){
                case '#':
                break;
                case 'r':
                    if(n != 3){
                        printf("informações insuficientes\n");
                        return 1;
                    }
                    else{
                        printf("Retangulo\n");
                        printf("Base: %.1f\nAltura: %.1f\n", v1, v2);
                    }
                break;
                case 't':
                    if(n != 3){
                        printf("informações insuficientes\n");
                        return 1;
                    }
                    else{
                        printf("Triangulo\n");
                        printf("Base: %.1f\nAltura: %.1f\n", v1, v2);
                    }
                break;
                case 'c':
                    if(n != 2){
                        printf("informações insuficientes\n");
                        return 1;
                    }
                    else{
                        printf("Circulo\n");
                        printf("Raio: %.1f\n", v1);
                    }
                break;
                default:
                    printf("Forma invalida!\n");
                break;
            }
        }
    }

    fclose(fp);
    
    return 0;
}