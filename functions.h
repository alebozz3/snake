#if !defined _WIN32
#include <termios.h>
#include <unistd.h>

int _getch(void) {
	struct termios oldattr, newattr;
	int ch;
	tcgetattr(STDIN_FILENO, &oldattr);
	newattr = oldattr;
	newattr.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
	ch = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
	return ch;
}
#endif

void ResetConsole();
void ResetConsole() {
	system(clearcommand);
	printf("░██████╗███╗░░██╗░█████╗░██╗░░██╗███████╗\n██╔════╝████╗░██║██╔══██╗██║░██╔╝██╔════╝\n╚█████╗░██╔██╗██║███████║█████═╝░█████╗░░\n░╚═══██╗██║╚████║██╔══██║██╔═██╗░██╔══╝░░\n██████╔╝██║░╚███║██║░░██║██║░╚██╗███████╗\n╚═════╝░╚═╝░░╚══╝╚═╝░░╚═╝╚═╝░░╚═╝╚══════╝");
}

void Print();
void Print() { // Stampa
	printf("\n");
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
#if defined _WIN32
			wprintf(L"%lc", Maze[i][j]);
#else
			printf("%c", Maze[i][j]);
#endif
		}
		printf("\n");
	}
}

void AskRestart();
void AskRestart() {
	Restart = false;
	printf("\n\nGenerare un nuovo labirinto? [y/n] ");
#if defined _WIN32
	while (1) {
		if (_kbhit()) {
			char Key = _getch();
			if (Key == 121) { // Y
				FirstStart = true;
				ResetConsole();
				break;
			}
			else if (Key == 110) { // N
				ResetConsole();
				printf("\n");
				Print();
				break;
			}
		}
		else continue;
	}
#else
	bool Keyloop = true;
	do {
		int Key = _getch();
		if (Key == 121) { // Y
			FirstStart = true;
			ResetConsole();
			Keyloop = false;
		}
		if (Key == 110) { // N
			ResetConsole();
			printf("\n");
			Print();
			Keyloop = false;
		}
	} while (Keyloop == true);
#endif
}

void InputData();
void InputData() { // Inserimento dimensioni
	printf("\n\nINSERIMENTO LABIRINTO\n\n");

	scanf("%d", &C);
	scanf("%d", &R);
	oldR = R;

	if (Maze) {
		for (int i = 0; i < oldR; i++) {
			if (Maze[i]) { free(Maze[i]); }
		}
		free(Maze);
	}
	Maze = (unsigned char**)malloc(sizeof(char*) * R);

	for (int i = 0; i < R; i++) {
		Maze[i] = (char*)malloc(sizeof(char) * (C + 1));

		char* row = (char*)malloc(sizeof(char) * (C + 1));

		int ch;
		while ((ch = getchar()) != '\n' && ch != EOF && i != R - 1);

		fgets(row, C + 1, stdin);
		for (int j = 0; j < C + 1; j++) {
			Maze[i][j] = row[j];
			if (row[j] == 'o') { cp[0] = i; cp[1] = j; }
			if (row[j] == '_') { end[0] = i; end[1] = j; }
		}

		free(row);
	}

	FirstStart = false;
}