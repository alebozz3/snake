#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <wchar.h>
#include <locale.h>

#if defined _WIN32
#define clearcommand "cls"
#else
#define clearcommand "clear"
#endif

unsigned char** Maze;
char* moves;
int* tail;
int length = 0;

int R, C, oldR, cp[2], end[2], movesindex = 0, points = 1000, drill = 0;
char lastmove;

bool Restart = false;
bool FirstStart = true;

#include "functions.h"
#include "ai.h"
#include "playermode.h"

int main() {
	setlocale(LC_ALL, "");
	ResetConsole();
	do {
		if (Restart) AskRestart();
		if (FirstStart) {
			InputData(); // Inserimento labirinto
		}
		printf("\n1 - Modalità AI\n2 - Modalità interattiva\nRETURN - Ricomincia");
#if defined _WIN32
		while (1) {
			if (_kbhit()) {
				char Key = _getch();
				if (Key == 49) { // 1
					if (moves) { free(moves); }
					moves = (char*)malloc(sizeof(char) * movesindex); // Stringa per movimenti
					FirstMove();
					while (CheckMove() != '\0') continue;
					ResetConsole();
					printf("\n");
					Print();
					printf("\n\n");
					printf("Punti accumulati: %d\nNumero mosse effettuate: %d (", points, movesindex);
					for (int i = 0;i < movesindex;i++) {
						printf("%c", moves[i]);
					}
					printf(")\n\n");
					break;
				}
				else if (Key == 50) { // 2
					if (tail) { free(tail); }
					tail = (int*)malloc(sizeof(int*) * (movesindex + 1) * 2);
					ResetConsole();
					printf("\n");
					Print();
					PlayerMode();
					break;
				}
				else if (Key == 8) { // RETURN
					Restart = true;
					break;
				}
			}
			else continue;
		}
#else
		bool Keyloop = true;
		do {
			int Key = _getch();
			if (Key == 49) { // 1
				if (moves) { free(moves); }
				moves = (char*)malloc(sizeof(char) * movesindex); // Stringa per movimenti
				FirstMove();
				while (CheckMove() != '\0') continue;
				ResetConsole();
				printf("\n");
				Print();
				printf("\n\n");
				printf("Punti accumulati: %d\nNumero mosse effettuate: %d (", points, movesindex);
				for (int i = 0;i < movesindex;i++) {
					printf("%c", moves[i]);
				}
				printf(")\n\n");
				Keyloop = false;
			}
			if (Key == 50) { // 2
				if (tail) { free(tail); }
				tail = (int*)malloc(sizeof(int*) * (movesindex + 1) * 2);
				ResetConsole();
				printf("\n");
				Print();
				PlayerMode();
				Keyloop = false;
			}
			if (Key == 127) { // RETURN
				Restart = true;
				Keyloop = false;
			}
		} while (Keyloop == true);
#endif
	} while (Restart);
	return 0;
}