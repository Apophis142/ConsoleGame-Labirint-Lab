void setCursor (int x, int y) {
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(hConsole, c);
}

void setCursor (position pos) {
	COORD c;
	c.X = pos.x;
	c.Y = pos.y;
	SetConsoleCursorPosition(hConsole, c);
}

void setColor (char color) {
	SetConsoleTextAttribute(hConsole, color);
}

void clearScreen (void) {
	COORD c = {0, 0};
	DWORD nKol = 0;
	size_t xy = WIDTH * HEIGHT;
	FillConsoleOutputAttribute(hConsole, 0, xy, c, &nKol);
}

void hideCursor (void) {
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(hConsole, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(hConsole, &structCursorInfo);
}