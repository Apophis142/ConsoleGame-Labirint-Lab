mapCell labirintMap[HEIGHT][WIDTH];
position currentHeroPosition = {60, 15};
unsigned char viewRange = 5;

src searchWay[HEIGHT][WIDTH];
std::vector <Enemy> enemies;

void game (void) {
	if (!isRunned) {
		// thread Enem(EnemyAI);
		isRunned = true;
		getMap("Assets/Maps/map1.txt");
		labirintMap[currentHeroPosition.y][currentHeroPosition.x].set_cellType(HERO);
		updateView(viewRange);
	}	
	displayMap();

	while (true) {
		bool flag = true;
		switch (_getch()) {
			case Keys::Esc: return;
			case Keys::Arrows: break;
			case Keys::Arrow_Up:
				moveHero(MOVE_UP);
				break;
			case Keys::Arrow_Down:
				moveHero(MOVE_DOWN);
				break;
			case Keys::Arrow_Left:
				moveHero(MOVE_LEFT);
				break;
			case Keys::Arrow_Right:
				moveHero(MOVE_RIGHT);
				break;
			case Keys::Space:
				break;
			case Keys::Ctrl_R:
				hideCursor();
				break;
		}
		findWay();
		updateView(viewRange);
		displayMap(viewRange);
	}
}