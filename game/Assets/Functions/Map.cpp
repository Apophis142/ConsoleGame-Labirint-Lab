void displayMap (void) {
	clearScreen();
	setCursor(0, 0);
	printf("\n");
	for (int y = 1; y < HEIGHT - 1; ++y, printf("\n"))
	{
		printf(" ");
		for (int x = 1; x < WIDTH - 1; ++x)
		{
			position pos = {x, y};
			drawCell(pos);
		}
	}
}

void displayMap (unsigned short int range) {
	range += 1;
	unsigned short start_x = std::max(1, currentHeroPosition.x - range), 
					end_x = std::min(WIDTH - 2, currentHeroPosition.x + range);
	unsigned short start_y = std::max(1, currentHeroPosition.y - range), 
					end_y = std::min(HEIGHT - 2, currentHeroPosition.y + range);
	
	for (int y = start_y; y <= end_y; ++y)
	{
		setCursor(start_x, y);
		for (int x = start_x; x <= end_x; ++x)
		{
			position pos = {x, y};
			drawCell(pos);
		}
	}
}

void getMap (const char path[]) {
	std::ifstream file_map(path, std::ios_base::in);
	char row[WIDTH];
	for (int y = 0; y < HEIGHT; ++y) {
		file_map >> row;
		for (int x = 0; x < WIDTH; ++x) {
			labirintMap[y][x].set_cellType(row[x] - 0);
			if (row[x] - 0 == ENEMY) {
				Enemy newEn({x, y});
				enemies.push_back(newEn);
			}
		}
	}
	file_map.close();
}

void chooseColor(position pos) {
	if (labirintMap[pos.y][pos.x].cellType == HERO)
		setColor(Colors::heroStd);
	else if (labirintMap[pos.y][pos.x].isViewed) {
		switch (labirintMap[pos.y][pos.x].cellType) {
			case ENEMY:
				setColor(Colors::enemyStd);
				break;
			default:
				setColor(Colors::labirintStd);
				break;
		}
	}
	else if (labirintMap[pos.y][pos.x].isExplored)
		setColor(Colors::labirintExplored);
	else
		setColor(Colors::labirintFog);
}

void drawCell(position pos) {
	chooseColor(pos);
	if (labirintMap[pos.y][pos.x].cellType == HERO)
		printf("%c", Symbols::Hero);
	else if (!labirintMap[pos.y][pos.x].isExplored)
		printf("%c", Symbols::Fog);
	else if (labirintMap[pos.y][pos.x].cellType == WALL) {
		unsigned char wallType = (labirintMap[pos.y - 1][pos.x].cellType == WALL) * 8
								+ (labirintMap[pos.y][pos.x - 1].cellType == WALL) * 4
								+ (labirintMap[pos.y][pos.x + 1].cellType == WALL) * 2
								+ (labirintMap[pos.y + 1][pos.x].cellType == WALL);
		switch (wallType) {
			case 0: printf("%c", 254); break;
			case 1: printf("%c", 186); break;
			case 2: printf("%c", 205); break;
			case 3: printf("%c", 201); break;
			case 4: printf("%c", 205); break;
			case 5: printf("%c", 187); break;
			case 6: printf("%c", 205); break;
			case 7: printf("%c", 203); break;
			case 8: printf("%c", 186); break;
			case 9: printf("%c", 186); break;
			case 10: printf("%c", 200); break;
			case 11: printf("%c", 204); break;
			case 12: printf("%c", 188); break;
			case 13: printf("%c", 185); break;
			case 14: printf("%c", 202); break;
			case 15: printf("%c", 206); break;
		}
	} else if (labirintMap[pos.y][pos.x].cellType == ENEMY) {
		if (labirintMap[pos.y][pos.x].isViewed)
			printf("%c", Symbols::Enemy);
		else
			printf(" ");
	} else
		printf(" ");
}

void reDisplayCell (position pos) {
	if (labirintMap[pos.y][pos.x].isViewed) {
		setCursor(pos);
		drawCell(pos);
	}
	else return;
}