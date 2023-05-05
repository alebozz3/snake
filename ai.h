char AddMove(char direction);
char AddMove(char direction) {
	void* buffer = realloc(moves, sizeof(char) * (movesindex + 1));
	moves = buffer;

	moves[movesindex++] = direction;
	points = points - 1;

	return direction;
}

char Move(char direction);
char Move(char direction) {
	lastmove = direction;
	Maze[cp[0]][cp[1]] = '.';

	switch (direction) {
	case 'N':
		if (Maze[cp[0] - 1][cp[1]] == '$') { points = points + 10; }
		else if (Maze[cp[0] - 1][cp[1]] == '!') { points = points / 2; }
		Maze[cp[0] - 1][cp[1]] = 'o'; cp[0] = cp[0] - 1;
		break;
	case 'E':
		if (Maze[cp[0]][cp[1] + 1] == '$') { points = points + 10; }
		else if (Maze[cp[0]][cp[1] + 1] == '!') { points = points / 2; }
		Maze[cp[0]][cp[1] + 1] = 'o'; cp[1] = cp[1] + 1;
		break;
	case 'S':
		if (Maze[cp[0] + 1][cp[1]] == '$') { points = points + 10; }
		else if (Maze[cp[0] + 1][cp[1]] == '!') { points = points / 2; }
		Maze[cp[0] + 1][cp[1]] = 'o'; cp[0] = cp[0] + 1;
		break;
	case 'O':
		if (Maze[cp[0]][cp[1] - 1] == '$') { points = points + 10; }
		else if (Maze[cp[0]][cp[1] - 1] == '!') { points = points / 2; }
		Maze[cp[0]][cp[1] - 1] = 'o'; cp[1] = cp[1] - 1;
		break;
	}

	return AddMove(direction);
}

void FirstMove();
void FirstMove() {
	Maze[cp[0]][cp[1]] = '.';

	if (cp[0] == R - 1) { Move('N'); }
	else if (cp[1] == 0) { Move('E'); }
	else if (cp[0] == 0) { Move('S'); }
	else if (cp[1] == C - 1) { Move('O'); }
}

char CheckMove();
char CheckMove() {
	bool exit;

	// Controlla monete vicine
	if (Maze[cp[0] - 1][cp[1]] == '$') { return Move('N'); }
	if (Maze[cp[0]][cp[1] + 1] == '$') { return Move('E'); }
	if (Maze[cp[0] + 1][cp[1]] == '$') { return Move('S'); }
	if (Maze[cp[0]][cp[1] - 1] == '$') { return Move('O'); }

	// Controlla uscita vicina
	if (Maze[cp[0] - 1][cp[1]] == '_') { Move('N'); return '\0'; }
	if (Maze[cp[0]][cp[1] + 1] == '_') { Move('E'); return '\0'; }
	if (Maze[cp[0] + 1][cp[1]] == '_') { Move('S'); return '\0'; }
	if (Maze[cp[0]][cp[1] - 1] == '_') { Move('O'); return '\0'; }

	// Controlla allineamento uscita
	if (cp[1] == end[1] && Maze[cp[0] - 1][cp[1]] != '#' && Maze[cp[0] - 1][cp[1]] != '.') { return Move('N'); }
	if (cp[1] == end[1] && Maze[cp[0] + 1][cp[1]] != '#' && Maze[cp[0] + 1][cp[1]] != '.') { return Move('S'); }
	if (cp[0] == end[0] && Maze[cp[0]][cp[1] + 1] != '#' && Maze[cp[0]][cp[1] + 1] != '.') { return Move('E'); }
	if (cp[0] == end[0] && Maze[cp[0]][cp[1] - 1] != '#' && Maze[cp[0]][cp[1] - 1] != '.') { return Move('O'); }

	// Controlla imprevisti vicini
	if (Maze[cp[0] - 1][cp[1]] == '!' || Maze[cp[0] + 1][cp[1]] == '!') { // ! a NORD o SUD
		if (cp[1] < end[1] && Maze[cp[0]][cp[1] + 1] != '!' && Maze[cp[0]][cp[1] + 1] != '#' && Maze[cp[0]][cp[1] + 1] != '.') { return Move('E'); }
		if (cp[1] > end[1] && Maze[cp[0]][cp[1] - 1] != '!' && Maze[cp[0]][cp[1] - 1] != '#' && Maze[cp[0]][cp[1] - 1] != '.') { return Move('O'); }
	}

	if (Maze[cp[0]][cp[1] + 1] == '!' || Maze[cp[0]][cp[1] - 1] == '!') { // ! a EST o OVEST
		if (cp[0] < end[0] && Maze[cp[0] + 1][cp[1]] != '!' && Maze[cp[0] + 1][cp[1]] != '#' && Maze[cp[0] + 1][cp[1]] != '.') { return Move('S'); }
		if (cp[0] > end[0] && Maze[cp[0] - 1][cp[1]] != '!' && Maze[cp[0] - 1][cp[1]] != '#' && Maze[cp[0] + 1][cp[1]] != '.') { return Move('N'); }
	}

	// Controlla muri vicini
	if (Maze[cp[0] - 1][cp[1]] == '#' || Maze[cp[0] + 1][cp[1]] == '#') { // ! a NORD o SUD
		if (cp[1] < end[1] && Maze[cp[0]][cp[1] + 1] != '!' && Maze[cp[0]][cp[1] + 1] != '#' && Maze[cp[0]][cp[1] + 1] != '.') { return Move('E'); }
		if (cp[1] > end[1] && Maze[cp[0]][cp[1] - 1] != '!' && Maze[cp[0]][cp[1] - 1] != '#' && Maze[cp[0]][cp[1] - 1] != '.') { return Move('O'); }
		if (cp[1] == end[1]) {
			if (Maze[cp[0]][cp[1] + 1] != '#' && Maze[cp[0]][cp[1] + 1] != '.' && !(cp[1] < (C - 1) - cp[1])) { return Move('E'); }
			if (Maze[cp[0]][cp[1] - 1] != '#' && Maze[cp[0]][cp[1] - 1] != '.') { return Move('O'); }
		}
	}

	if (Maze[cp[0]][cp[1] + 1] == '#' || Maze[cp[0]][cp[1] - 1] == '#') { // ! a EST o OVEST
		if (cp[0] > end[0] && Maze[cp[0] - 1][cp[1]] != '!' && Maze[cp[0] - 1][cp[1]] != '#' && Maze[cp[0] - 1][cp[1]] != '.') { return Move('N'); }
		if (cp[0] < end[0] && Maze[cp[0] + 1][cp[1]] != '!' && Maze[cp[0] + 1][cp[1]] != '#' && Maze[cp[0] + 1][cp[1]] != '.') { return Move('S'); }
		if (cp[0] == end[0]) {
			if (Maze[cp[0] - 1][cp[1] + 1] != '#' && Maze[cp[0] - 1][cp[1] + 1] != '.' && cp[0] < (R - 1) - cp[0]) { return Move('N'); }
			if (Maze[cp[0] + 1][cp[1] + 1] != '#' && Maze[cp[0] + 1][cp[1] + 1] != '.') { return Move('S'); }
		}
	}

	// Controlla monete prima dell'uscita
	exit = false;
	if (cp[0] < end[0]) {
		int i, j;
		for (i = cp[0]; i < end[0]; i++) {
			for (j = cp[1]; j < end[1]; j++) {
				if (Maze[i][j] == '$') {
					exit = true;
					break;
				}
			}
			if (exit) break;
		}
		if (cp[1] < j && Maze[cp[0]][cp[1] + 1] != '#' && Maze[cp[0]][cp[1] + 1] != '.') { return Move('E'); }
		if (cp[1] > j && Maze[cp[0]][cp[1] - 1] != '#' && Maze[cp[0]][cp[1] - 1] != '.') { return Move('O'); }
	}
	if (cp[0] > end[0]) {
		int i, j;
		for (i = cp[0]; i > end[0]; i--) {
			for (j = cp[1]; j > end[1]; j--) {
				if (Maze[i][j] == '$') {
					exit = true;
					break;
				}
			}
			if (exit) break;
		}
		if (cp[1] < j && Maze[cp[0]][cp[1] + 1] != '#' && Maze[cp[0]][cp[1] + 1] != '.') { return Move('E'); }
		if (cp[1] > j && Maze[cp[0]][cp[1] - 1] != '#' && Maze[cp[0]][cp[1] - 1] != '.') { return Move('O'); }
	}

	// Va verso uscita
	if (cp[0] > end[0] && Maze[cp[0] - 1][cp[1]] != '#' && Maze[cp[0] - 1][cp[1]] != '.') { return Move('N'); }
	else if (cp[0] < end[0] && Maze[cp[0] + 1][cp[1]] != '#' && Maze[cp[0] + 1][cp[1]] != '.') { return Move('S'); }
	else if (cp[1] < end[1] && Maze[cp[0]][cp[1] + 1] != '#' && Maze[cp[0]][cp[1] + 1] != '.') { return Move('E'); }
	else if (cp[1] > end[1] && Maze[cp[0]][cp[1] - 1] != '#' && Maze[cp[0]][cp[1] - 1] != '.') { return Move('O'); }

	// Nulla di vicino, va dritto fino a muro
	if (lastmove == 'N' && Maze[cp[0] - 1][cp[1]] != '#') { return Move('N'); }
	else if (lastmove == 'E' && Maze[cp[0]][cp[1] + 1] != '#') { return Move('E'); }
	else if (lastmove == 'S' && Maze[cp[0] + 1][cp[1]] != '#') { return Move('S'); }
	else if (lastmove == 'O' && Maze[cp[0]][cp[1] - 1] != '#') { return Move('O'); }

	return '\0';
}