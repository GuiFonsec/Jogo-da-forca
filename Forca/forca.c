#include <stdio.h>
#include <string.h> 
#include <time.h>
#include <stdlib.h>
#include "forca.h"

//VARIÁVEIS GLOBAIS
char chutes[26];
int chutesdados = 0;
char palavrasecreta[TAMANHO_PALAVRA];


void abertura(){
    printf("*************************\n");
    printf("*     Jogo da Forca     *\n");
    printf("*************************\n\n");    
}

void chuta(){
    char chute;
    scanf(" %c", &chute);
     
    chutes[chutesdados] = chute;
    chutesdados++;
}

int jachutou(char letra){

    int achou = 0;

    for (int j = 0; j < chutesdados; j++)
    {
        if (chutes[j] == letra)
        {
            achou = 1;
            break;
        }
    }

    return achou;
}

void desenhaforca(){

    int erros = chuteserrados();

    printf("  _______       \n");
    printf(" |/      |      \n");
    printf(" |      %c%c%c  \n", (erros >= 1 ? '(' : ' '), (erros >= 1 ? '_' : ' '), (erros >= 1 ? ')' : ' '));
    printf(" |      %c%c%c  \n", (erros >= 3 ? '\\' : ' '), (erros >= 2 ? '|' : ' '), (erros >= 4 ? '/' : ' '));
    printf(" |       %c     \n", (erros >= 2 ? '|' : ' '));
    printf(" |      %c %c   \n", (erros >= 5 ? '/' : ' '), (erros >= 6 ? '\\' : ' '));
    printf(" |              \n");
    printf("_|___           \n");

    printf("\n\n");
 
    for (int i = 0; i < strlen(palavrasecreta); i++)
    {   

        int achou = jachutou(palavrasecreta[i]);

        if (achou)
        {
            printf("%c ", palavrasecreta[i]);
        }
        else
        {
            printf("_ ");     
        }

    }
    printf("\n");
}

void adicionapalavra(){

    char quer;

    printf("Voce deseja adicionar uma nova palavra no jogo? (S/N)\n");
    scanf(" %c", &quer);

    if (quer == 'S')
    {
        char novapalavra[TAMANHO_PALAVRA];
        printf("Qual a nova palavra? ");
        scanf("%s", novapalavra);
        
        FILE* f;
        f = fopen("palavras.txt", "r+");
        if(f == 0){
        printf("Desculpe, banco de dados nao disponivel\n");
        exit(1);
        }
        
        int qtd;
        fscanf(f, "%d", &qtd);
        qtd++;

        fseek(f, 0, SEEK_SET);
        fprintf(f, "%d", qtd);

        fseek(f, 0, SEEK_END);
        fprintf(f, "\n%s", novapalavra);

        fclose(f);
    
    }
    
}

void escolhepalavra(){
    FILE* f;

    f = fopen("palavras.txt", "r");

    if(f == 0){
        printf("Desculpe, banco de dados nao disponivel\n");
        exit(1);
    }

    int qtddepalavras;
    fscanf(f,"%d", &qtddepalavras);

    srand(time(0));
    int randomico = rand() % qtddepalavras;

    for (int i = 0; i <= randomico; i++)
    {
        fscanf(f, "%s", palavrasecreta);
    }

    fclose(f);
}

int acertou(){
    for (int i = 0; i < strlen(palavrasecreta); i++)
    {
        if (!jachutou(palavrasecreta[i]))
        {
            return 0;
        }
    }
    return 1;
}

int chuteserrados(){

    int erros  = 0;

    for (int i = 0; i < chutesdados; i++)
    {
        int existe = 0;

        for (int j = 0; j < strlen(palavrasecreta); j++)
        {
           if (chutes[i] == palavrasecreta[j])
           {
                existe = 1;
                break;
           }
           
        }
        if (!existe){erros++;}
    }
    //Retorne erros se o valor dele for maior ou igual a 5.
    return erros;    

}
int enforcou(){
    return chuteserrados() >= 6;
}

int main(){

    escolhepalavra();
    abertura();

    do
    {
        desenhaforca();
        
        chuta();

    }
    while (!acertou() && !enforcou());
    //While só roda quando a condição for igual a 1 (1 = true, 0 = false)

    if (acertou())
    {
        printf("\n");
        printf("       ___________      \n");
        printf("      '._==_==_=_.'     \n");
        printf("      .-\\:      /-.    \n");
        printf("     | (|:.     |) |    \n");
        printf("      '-|:.     |-'     \n");
        printf("        \\::.    /      \n");
        printf("         '::. .'        \n");
        printf("           ) (          \n");
        printf("         _.' '._        \n");
        printf("        '-------'       \n");

        printf("\nParabens, voce ganhou! A palavra secreta era %s\n", palavrasecreta);
    }
    else
    {
        printf("  _______      \n");
        printf(" |/      |     \n");
        printf(" |      (_)    \n");
        printf(" |      \\|/   \n");
        printf(" |       |     \n");
        printf(" |      / \\   \n");
        printf(" |             \n");
        printf("_|___          \n");
        printf("\n\n");

        printf("\nPuxa, voce foi enforcado. A palavra secreta era %s\n", palavrasecreta);
    }
    

    adicionapalavra();
}
