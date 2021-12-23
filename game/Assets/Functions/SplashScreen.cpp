void SplashScreen::splashScreen(void) {
	SplashScreen::drawZigzag({0, 0}, ' ', 154, 10, 0);
	SplashScreen::drawZigzag({10, 0}, 186, 172, 10, 0);
	SplashScreen::drawZigzag({20, 0}, 205, 182, 10, 0);
	for (int i = 0; i <= 30; ++i) {
		SplashScreen::drawZigzag({0 + i, 0}, 205, 182, 10, 9);
		Sleep(25);
		SplashScreen::drawZigzag({10 + i, 0}, ' ', 154, 10, 9);
		Sleep(25);
		SplashScreen::drawZigzag({20 + i, 0}, 186, 172, 10, 9);
		Sleep(50);
	}
	Sleep(500);
}

void SplashScreen::drawZigzag(position start, char symbol, char color, unsigned char length, unsigned char skip) {
	setColor(color);
	for (int i = 0; i < WIDTH; ++i) {
		setCursor(start);
		for (int j = 0; j < length - skip; ++j) {
			if (start.x + j == WIDTH)
				setCursor(0, start.y);
			printf("%c", symbol);
		}
		++start;
		start %= SCREEN;
	}
}