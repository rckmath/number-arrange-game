#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>

#ifndef PRJPUZZLE_OUTROS_H
#define PRJPUZZLE_OUTROS_H

// Mudar cor do texto
void cor_Texto(int color){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)color);
}
// Ir para coordenada x e y
void gotoxy(int row, int col){
	COORD coord;
	coord.X = (short)col;
	coord.Y = (short)row;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

#endif //PRJPUZZLE_OUTROS_H
