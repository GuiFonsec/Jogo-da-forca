#define TAMANHO_PALAVRA 20

void abertura();
void chuta();
void desenhaforca();
void escolhepalavra();
int acertou();
int enforcou();
int jachutou(char letra);
void adicionapalavra();
int chuteserrados();

//Declarar quais funções serão usadas no arquivo para que possam ser escritas em qualquer ordem sem que o compilador dê erro
//O Jachutou pode vir antes ou depois do desenha forca, pois já foi declarada anteriormente