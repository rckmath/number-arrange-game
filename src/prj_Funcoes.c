#include "prj_Outros.h"

#define SETA_CIMA 72
#define SETA_BAIXO 80
#define SETA_ESQ 75
#define SETA_DIR 77
#define ESC 27
#define KEY_ENTER 13

// Pega casa livre
int get_CasaLivre(const int puzzle_Numbers[]){
    int i;
    for(i = 0; i < 9; i++) if(puzzle_Numbers[i] == 0) return i+1; // Retorna a casa livre (elemento 0 do vetor)
}
// Menu de selecao (puzzle e pause)
int menu_Op(int var_Controle){
    int op = 1;
    // Selecao comeca na primeira opcao
    if(var_Controle == 0){
        gotoxy(13, 35); cor_Texto(15); printf("Puzzle 2");
        gotoxy(12, 35); cor_Texto(10); printf("Puzzle 1");
    } else{
        gotoxy(13, 34); cor_Texto(15); printf("Solucionar");
        gotoxy(12, 33); cor_Texto(10); printf("Nova Partida");
    }
    // Loop enquanto getch() diferente de enter
    while(1){
        switch(getch()){
            case SETA_CIMA:
                if(var_Controle == 0){
                    op = 1;
                    gotoxy(13, 35); cor_Texto(15); printf("Puzzle 2");
                    gotoxy(12, 35); cor_Texto(10); printf("Puzzle 1");
                } else{
                    op = 1;
                    gotoxy(13, 34); cor_Texto(15); printf("Solucionar");
                    gotoxy(12, 33); cor_Texto(10); printf("Nova Partida");
                } break;
            case SETA_BAIXO:
                if(var_Controle == 0){
                    op = 2;
                    gotoxy(12, 35); cor_Texto(15); printf("Puzzle 1");
                    gotoxy(13, 35); cor_Texto(10); printf("Puzzle 2");
                } else{
                    op = 2;
                    gotoxy(12, 33); cor_Texto(15); printf("Nova Partida");
                    gotoxy(13, 34); cor_Texto(10); printf("Solucionar");
                } break;
            case KEY_ENTER:
                cor_Texto(15);
                return op;
            case ESC:
                if(var_Controle != 0) return 0;
                else break;
            default:
                break;
        }
    }
}
// Definicoes de jogo
void def_Game(int *puzzle_Numbers, int *puzzle_Objective, int puzzle_Option){
    int i, puzzle_One[9] = {4, 1, 3, 0, 8, 5, 2, 7, 6}, puzzle_Two[9] = {2, 1, 4, 3, 8, 0, 6, 7, 5}; // Contem os numeros embaralhados dos puzzles
    int puzzle_ObjOne[9] = {1, 2, 3, 4, 5, 6, 7, 8, 0}, puzzle_ObjTwo[9] = {3, 2, 1, 6, 5, 4, 0, 8, 7}; // Objetivo dos puzzles

    for(i = 0; i < 9; i++){
        if(puzzle_Option == 1){
            puzzle_Numbers[i] = puzzle_One[i];
            puzzle_Objective[i] = puzzle_ObjOne[i];
        } else {
            puzzle_Numbers[i] = puzzle_Two[i];
            puzzle_Objective[i] = puzzle_ObjTwo[i];
        }
    }
}
// Mover numeros
int mover_Num(int *puzzle_Numbers, int *casa_Atual, int *casa_Livre, int *cont_Mov, int x, int y){
    int aux = 0;

    *casa_Livre = get_CasaLivre(puzzle_Numbers);
    // Loop enquanto getch diferente de enter
    while(1){
        switch(getch()){
            case SETA_CIMA:
                if(*casa_Atual <= 6){
                    gotoxy(x-=4, y);
                    *casa_Atual += 3;
                } break;
            case SETA_BAIXO:
                if(*casa_Atual >= 4){
                    gotoxy(x+=4, y);
                    *casa_Atual -= 3;
                } break;
            case SETA_ESQ:
                if(*casa_Atual != 1 && *casa_Atual != 4 && *casa_Atual != 7) {
                    gotoxy(x, y-=6);
                    *casa_Atual -= 1;
                } break;
            case SETA_DIR:
                if(*casa_Atual != 9 && *casa_Atual != 6 && *casa_Atual != 3){
                    gotoxy(x, y+=6);
                    *casa_Atual+=1;
                } break;
            case KEY_ENTER:
                if((*casa_Atual != 7 || *casa_Livre != 6) && (*casa_Atual != 6 || *casa_Livre != 7) &&
                   (*casa_Atual != 3 || *casa_Livre != 4) && (*casa_Atual != 4 || *casa_Livre != 3)){
                    aux = *casa_Atual - *casa_Livre;
                    aux = abs(aux);
                    if(aux == 3 || aux == 1){
                        aux = puzzle_Numbers[*casa_Livre - 1];
                        puzzle_Numbers[*casa_Livre - 1] = puzzle_Numbers[*casa_Atual - 1];
                        puzzle_Numbers[*casa_Atual - 1] = aux;
                    } else aux = 1;
                } else aux = 1;
                if(aux == 1){
                    cor_Texto(13); gotoxy(24, 25); printf("N\306o h%c casa livre ao redor!", 160);
                }
                cor_Texto(15); gotoxy(21, 31); printf("Casa escolhida: %d", *casa_Atual);
                Sleep(500); gotoxy(21, 47); printf("*");
                gotoxy(24, 23); printf("                                ");
                *cont_Mov+=1;
                return 0;
            case ESC:
                return 1;
            default:
                break;
        }
    }
}
// Ir para as casas
void ir_paraCasa(int casa_Num, int *x, int *y){
    *x = 21, *y = 13; // Primeira linha e coluna (de baixo para cima) da grade
    int fator[9][2] = {{0, 0}, {0, 6}, {0, 12}, {-4, 0}, {-4, 6}, {-4, 12}, {-8, 0}, {-8, 6}, {-8, 12}};
    gotoxy(*x+=fator[casa_Num-1][0], *y+=fator[casa_Num-1][1]);
}
// Verificar andamento do jogo
int verificar_Andamento(const int puzzle_Numbers[], const int puzzle_Objective[]){
    int casas_Iguais = 0, i;
    for(i = 0; i < 9; i++) if(puzzle_Numbers[i] == puzzle_Objective[i]) casas_Iguais++;
    return casas_Iguais == 9 ? 1 : 0;
}
// Mostrar solucao do jogo
int solucionar_Jogo(int puzzle_Numbers[], const int puzzle_Option, int *x, int *y){
	int i, k = 0, l = 0, aux = 0, puzzle_Solution[9];
	int s_1[] = {2, 7, 8, 2, 4, 1, 2, 5, 6}, s_2[] = {5, 7, 8, 5, 4, 1, 2, 3, 6}; // Solucao dos puzzles

    for(i = 0; i < 9; i++) puzzle_Solution[i] = (puzzle_Option == 1 ? s_1 : s_2)[i];
    while(1){
        ir_paraCasa(l, x, y);
        l = get_CasaLivre(puzzle_Numbers);
        for(i = 0; i < 9; i++) if(puzzle_Numbers[i] == puzzle_Solution[k]) aux = i;
        Sleep(450);
        puzzle_Numbers[l-1] = puzzle_Solution[k];
        puzzle_Numbers[aux] = 0;
        print_Numeros(puzzle_Numbers, 0);
        k++;
        if(k > 8) return 0;
    }
}
// Despausar jogo
void despausar_Jogo(int puzzle_Numbers[], int puzzle_Objective[]){
    print_Inicio(0, 13); print_Grade(11, 10); print_Grade(11, 49);
    gotoxy(1, 1); printf("[||] ESC para pausar o jogo");
    print_Numeros(puzzle_Numbers, 0); print_Numeros(puzzle_Objective, 1);
}
// Resetar variaveis do jogo
void zerar_Var(int *casa_Atual, int *casa_Livre, int *puzzle_Option, int *op_Selec, int *cont_Mov, int *aux){
    *casa_Atual = 0; *casa_Livre = 0; *puzzle_Option = 0; *op_Selec = 0; *cont_Mov = 0; *aux = 0;
}
