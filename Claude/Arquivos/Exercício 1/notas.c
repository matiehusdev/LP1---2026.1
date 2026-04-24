#include <stdio.h>
#include <string.h>

int main(){
    
    // Parte 1 - escrita no arquivo
    FILE* fp = fopen("notas.txt", "w");
    if(!fp) return 1;

    char *nomes[] = {"Ana", "Bruno", "Carla", "Diego", "Elena"};
    float notas[] = {8.50, 6.75, 9.20, 7.00, 8.90};
    
    for(int i = 0; i < 5; i ++)
        fprintf(fp, "%s %.1f\n", nomes[i], notas[i]);
    
    fclose(fp);

    // Parte 2 - ler o arquivo
    fp = fopen("notas.txt", "r");
    if(!fp) return 1;

    char nome[51];
    float nota;
    float soma = 0;
    float maiorNota = 0;
    char maiorAluno[51];
    
    while(fscanf(fp, "%s %f", nome, &nota) == 2){
        printf("Aluno: %s | Nota: %.1f\n", nome, nota);
        soma += nota;
        if(maiorNota < nota){
            maiorNota = nota;
            strcpy(maiorAluno, nome);
        }
    }

    fclose(fp);

    // Parte 3 - mostrar média das notas e o aluno com maior nota
    printf("Media das notas: %.1f\n", soma / 5);
    printf("Aluno com maior nota: %s, Nota: %.1f\n", maiorAluno, maiorNota);

    return 0;
}