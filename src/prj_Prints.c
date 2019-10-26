#include "prj_Outros.h"

// Inicio
void print_Inicio(int x, int y){
    system("cls");

    cor_Texto(10);
	gotoxy(x+3, y);printf("___  _  _ ___  ___  _    ____    ____ ____ _  _ ____  ");
	gotoxy(x+4, y);printf("|__] |  |   /    /  |    |___ __ | __ |__| |\\/| |___ ");
	gotoxy(x+5, y);printf("|    |__|  /__  /__ |___ |___    |__] |  | |  | |___  "); cor_Texto(15);
    gotoxy(9, 14); printf("P U Z Z L E");
    gotoxy(9, 51); printf("O B J E T I V O");
}
// Caixa menu
void print_Menu(int x, int y){
    int i;
	gotoxy(x+1, y); printf("\332\304\304\304\304SELECIONAR\304\304\304\304\277"	);
    for(i = 0; i <= 3; i++){
        gotoxy(x+(i+2), y); printf("\263                  \263");
    }
    gotoxy(x+6, y); printf("\300"); for(i = 0; i < 18; i++) printf("\304"); printf("\331");
}
// Pause
void print_Pause(int x, int y){
    system("cls");
    gotoxy(1, 1); printf("[<-] Pressione ESC para voltar ao jogo"); cor_Texto(10);
    gotoxy(x+3, y); printf("___  ____ _  _ ____ ____ ___  ____  ");
	gotoxy(x+4, y); printf("|__] |__| |  | [__  |__| |  \\ |  | ");
	gotoxy(x+5, y); printf("|    |  | |__| ___] |  | |__/ |__|  "); cor_Texto(15);
}
// Fim
void print_Fim(int x, int y){
    cor_Texto(10);
    gotoxy(x+3, y); printf("____ _ _  _ ____ _    _ ___  ____ ___  ____   ");
	gotoxy(x+4, y); printf("|___ | |\\ | |__| |    |   /  |__| |  \\ |  | ");
	gotoxy(x+5, y);	printf("|    | | \\| |  | |___ |  /__ |  | |__/ |__|  ");
    cor_Texto(15); gotoxy(x+9, y+18); printf("Dev by:"); cor_Texto(10);
    gotoxy(x+11, y+9); printf("+---------+ +-+ +-----+");
    gotoxy(x+12, y+9); printf("|E r i c k| |&| |L e o|");
    gotoxy(x+13, y+9); printf("+---------+ +-+ +-----+");
}
// Grade
void print_Grade(int x, int y){
    int i;

    cor_Texto(10);
    for(i = 0; i <= 10; i++){
       gotoxy(x+(i+1), y); printf("\263     \263     \263     \263");
    }
    gotoxy(x+0, y); printf("\332\304\304\304\304\304\302\304\304\304\304\304\302\304\304\304\304\304\277");
    gotoxy(x+4, y); printf("\303\304\304\304\304\304\305\304\304\304\304\304\305\304\304\304\304\304\264");
    gotoxy(x+8, y); printf("\303\304\304\304\304\304\305\304\304\304\304\304\305\304\304\304\304\304\264");
    gotoxy(x+12, y); printf("\300\304\304\304\304\304\301\304\304\304\304\304\301\304\304\304\304\304\331");
    cor_Texto(15);
}
// Numeros nas grades
void print_Numeros(int *vet_Num, int var_Controle){
    int row = 21, col; // Linha e coluna do centro do primeiro quadrado da grade (de baixo pra cima)
    int k = 0, l = 0, aux = 0, i;

    col = var_Controle == 0 ? 13 : 52; // Se nao for, col recebe 52 p/ printar objetivo a ser atingindo
    do{
        // Printa tres números por linha
        for(i = 0; i < 3; i++){
            if(aux != 9){
                gotoxy(row-k, col+l); // O cursor eh posicionado em linha-k e coluna+l, equidistancia do centro da grade
                vet_Num[aux] != 0 ? printf("%d", vet_Num[aux]) : printf(" ");
                l+=6; // Soma 6 ao que esta em "l", 6 eh a distancia entre as colunas do centro da grade
                aux++; // Soma +1 ao contador
            }
        }
        l = 0; // Zera o que esta em l, visto que a cada tres colunas suas posicoes repetem
        k += 4; // Soma 4 ao que esta em "k", 4 eh a distancia entre as linhas do centro da grade
    } while(aux < 9); // Enqto "aux" nao for 9 (qtd de casas do puzzle), permanecer nesse loop
}
