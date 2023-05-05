void ResizeTail();
void ResizeTail() {
	movesindex++;

	void* buffer = realloc(tail, sizeof(int) * (movesindex + 1) * 2);
	tail = buffer;

	tail[movesindex * 2] = cp[0];
	tail[(movesindex * 2) + 1] = cp[1];

	for (int i = 0; i < movesindex - length; i++) {
		Maze[tail[i * 2]][tail[(i * 2) + 1]] = ' ';
	}
	for (int i = movesindex - length; i < movesindex; i++) {
#if defined _WIN32
		Maze[tail[i * 2]][tail[(i * 2) + 1]] = 176;
#else
		Maze[tail[i * 2]][tail[(i * 2) + 1]] = '.';
#endif
	}
	Maze[tail[movesindex * 2]][tail[(movesindex * 2) + 1]] = 'o';
}

void CutTail(int r, int c);
void CutTail(int r, int c) {
	int newlength = 0;
	for (int i = movesindex; i > 0; i--) {
		newlength++;
		if (tail[i * 2] == r && tail[(i * 2) + 1] == c) {
			break;
		}
	}
	length = newlength - 1;
}

void End();
void End() {
	printf("\n\nPunti accumulati: %d\nNumero mosse effettuate: %d\n\n", points, movesindex);
}

void NewCp(char direction);
void NewCp(char direction) {
	switch (direction) {
	case 'N':
		cp[0] = cp[0] - 1;
		break;
	case 'E':
		cp[1] = cp[1] + 1;
		break;
	case 'S':
		cp[0] = cp[0] + 1;
		break;
	case 'O':
		cp[1] = cp[1] - 1;
		break;
	}
}

int MovePlayer(char d, int r, int c);
int MovePlayer(char d, int r, int c) {
	if (r < 0 || r > R - 1 || c < 0 || c > C - 1) { return 1; }

	if (Maze[r][c] == '#' && drill > 0) { drill--; }
	else if (Maze[r][c] == '#' && drill <= 0) { return 1; }

	if (Maze[r][c] == '$') { points = points + 10; length++; }
	else if (Maze[r][c] == '!') {
		points = points / 2;
		if (length > 1) { length--; };
	}
	else if (Maze[r][c] == 176) { CutTail(r, c); }
	else if (Maze[r][c] == 'T') { drill = drill + 3; }
	else if (Maze[r][c] == '_') { return -1; }

	NewCp(d);

	ResizeTail();
	return 0;
}

int ToCp(char direction);
int ToCp(char direction) {
	switch (direction) {
	case 'N':
		return MovePlayer(direction, cp[0] - 1, cp[1]);
	case 'E':
		return MovePlayer(direction, cp[0], cp[1] + 1);
	case 'S':
		return MovePlayer(direction, cp[0] + 1, cp[1]);
	case 'O':
		return MovePlayer(direction, cp[0], cp[1] - 1);
	}
}

void PlayerMode();
void PlayerMode() {
	tail[0] = cp[0];
	tail[1] = cp[1];
	Maze[cp[0]][cp[1]] = ' ';
	printf("\nPremere ⇦ | ⇧ | ⇩ | ⇨ per eseguire una mossa");
#if defined _WIN32
	while (1) {
		if (_kbhit()) {
			char Key = _getch();
			int moveresult;
			switch (Key) {
			case 72:
				moveresult = ToCp('N');
				break;
			case 77:
				moveresult = ToCp('E');
				break;
			case 80:
				moveresult = ToCp('S');
				break;
			case 75:
				moveresult = ToCp('O');
				break;
			}
			if (moveresult == -1) {
				End();
				break;
			}
			ResetConsole();
			printf("\n");
			Print();
		}
		else continue;
	}
#else
	bool Keyloop = true;
	do {
		int Key = _getch();
		int moveresult;
		switch (Key) {
		case 65:
			moveresult = ToCp('N');
			break;
		case 67:
			moveresult = ToCp('E');
			break;
		case 66:
			moveresult = ToCp('S');
			break;
		case 68:
			moveresult = ToCp('O');
			break;
		}
		if (moveresult == -1) {
			End();
			break;
		}
		ResetConsole();
		printf("\n");
		Print();
	} while (Keyloop == true);
#endif
}
