#include "prj_Outros.h"
#include "prj_Prints.c"

#include "prj_Funcoes.c"

int main() {
    system("TITLE Puzzle Game");
    system("MODE con cols=78 lines=25\nCOLOR 0F");

    int puzzle_Option = 0;    // Puzzle selecionado pelo usuario
    int puzzle_Numbers[9];    // Vetor que recebera puzzle selecionado
    int puzzle_Objective[9];  // Vetor que recebera solucao selecionada

    int casa_Atual, casa_Livre, op_Selec, aux, cont_Mov = 0;
    int x, y;  // Coordenadas para gotoxy da grade do puzzle

    do {
        zerar_Var(&casa_Atual, &casa_Livre, &puzzle_Option, &op_Selec, &cont_Mov, &aux);
        // Printa toda a tela inicial
        print_Inicio(0, 13);
        print_Grade(11, 10);
        print_Grade(11, 49);
        print_Menu(9, 29);                                          // Prints
        puzzle_Option = menu_Op(0);                                 // Chama funcao p/ menu
        def_Game(puzzle_Numbers, puzzle_Objective, puzzle_Option);  // Define as opcoes
        gotoxy(1, 1);
        printf("[||] ESC para pausar o jogo");
        print_Numeros(puzzle_Numbers, 0);
        print_Numeros(puzzle_Objective, 1);
        MessageBox(NULL,
                   "Use as setas para selecionar a casa desejar e pressione "
                   ""
                   "enter"
                   " para realizar a troca.",
                   "Bem-vindo", MB_OK | MB_ICONINFORMATION | MB_SYSTEMMODAL);

        while (cont_Mov != 30) {
            print_Numeros(puzzle_Numbers, 0);
            // Selecao comeca no espaco livre
            casa_Livre = get_CasaLivre(puzzle_Numbers);
            casa_Atual = casa_Livre;

            gotoxy(20, 33);
            printf("Casa livre: %d", casa_Livre);
            gotoxy(21, 31);
            printf("Casa escolhida: *");
            gotoxy(22, 32);
            printf("Jogadas: %2d/30", cont_Mov);

            ir_paraCasa(casa_Livre, &x, &y);
            Sleep(250);
            // Se verdadeiro, pausa o jogo
            if (mover_Num(puzzle_Numbers, &casa_Atual, &casa_Livre, &cont_Mov, x, y)) {
                int op = 0;
                do {
                    print_Pause(0, 22);
                    print_Menu(9, 29);
                    op_Selec = menu_Op(1);

                    if (op_Selec == 1)
                        op = MessageBox(NULL, "Deseja mesmo iniciar uma nova partida?",
                                        "Confirmar",
                                        MB_YESNO | MB_ICONQUESTION | MB_SYSTEMMODAL);
                    else if (op_Selec == 2) {
                        op = MessageBox(NULL, "Deseja mesmo ver a solucao para o jogo?",
                                        "Confirmar",
                                        MB_YESNO | MB_ICONQUESTION | MB_SYSTEMMODAL);
                        if (op == 6) {
                            def_Game(puzzle_Numbers, puzzle_Objective, puzzle_Option);
                            despausar_Jogo(puzzle_Numbers, puzzle_Objective);
                        }
                    } else
                        despausar_Jogo(puzzle_Numbers, puzzle_Objective);
                } while (op == 7);
            }

            // Se for 1 em selecao, reinicia o jogo
            if (op_Selec == 1) {
                aux = 6;
                break;
            }
            // Se for 2 em selecao, soluciona o jogo
            if (op_Selec == 2) {
                solucionar_Jogo(puzzle_Numbers, puzzle_Option, &x, &y);
                break;
            }
            // Verifica se o jogo foi concluido
            if (verificar_Andamento(puzzle_Numbers, puzzle_Objective)) {
                print_Numeros(puzzle_Numbers, 0);
                break;
            }
        }
        Sleep(400);
        system("cls");
        if (op_Selec != 1) {
            print_Fim(0, 13);
            aux = MessageBox(NULL, "Deseja jogar novamente?", "Confirmar",
                             MB_YESNO | MB_ICONQUESTION | MB_SYSTEMMODAL);
        }
    } while (aux == 6);
    cor_Texto(15);
    gotoxy(15, 13);
    system("pause");
    return 0;
}
