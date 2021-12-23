void moveHero (short int move) {
	position movement = {0, 0};
	switch (move) {
		case MOVE_UP:
			movement.y -= 1;
			break;
		case MOVE_DOWN:
			movement.y+= 1;
			break;
		case MOVE_LEFT:
			movement.x -= 1;
			break;
		case MOVE_RIGHT:
			movement.x += 1;
			break;
	}
	if (labirintMap[currentHeroPosition.y + movement.y][currentHeroPosition.x + movement.x].isPassable()) {
		labirintMap[currentHeroPosition.y][currentHeroPosition.x].set_cellType(EMPTY);
		currentHeroPosition += movement;
		labirintMap[currentHeroPosition.y][currentHeroPosition.x].set_cellType(HERO);
	}
}

void updateView (unsigned short range) {
	unsigned short int min_x = std::max(1, currentHeroPosition.x - range - 1), max_x = std::min(WIDTH - 1, currentHeroPosition.x + range + 1);
	unsigned short int min_y = std::max(1, currentHeroPosition.y - range - 1), max_y = std::min(HEIGHT - 1, currentHeroPosition.y + range + 1);
	for (int y = min_y; y <= max_y; ++y)
		for (int x = min_x; x <= max_x; ++x) {
			unsigned short int dx = abs(x - currentHeroPosition.x), dy = abs(y - currentHeroPosition.y);
			if (dx + dy <= viewRange and dy != viewRange)
				labirintMap[y][x].viewCell();
			else
				labirintMap[y][x].blindCell();
		}
}