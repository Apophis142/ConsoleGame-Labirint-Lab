class Enemy {
	friend void EnemyAI (void);
public:
	Enemy (position start) {
		pos = start;
	}

	void move (position step) {
		labirintMap[this->pos.y][this->pos.x].set_cellType(EMPTY);
		this->pos += step;
		labirintMap[this->pos.y][this->pos.x].set_cellType(ENEMY);
		reDisplayCell(this->pos);
	}
private:
	position pos;
};

const std::vector <position> delta = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};

void nullSrc (void) {
	for (size_t i = 0; i < HEIGHT; ++i)
		for (size_t j = 0; j < WIDTH; ++j)
			searchWay[i][j] = {false, 1000};
}

void findWay (void) {
	nullSrc();
	std::vector <position> toVisit = {currentHeroPosition};
	unsigned short amountToVisit = 1;
	searchWay[currentHeroPosition.y][currentHeroPosition.x] = {true, 0};

	while (amountToVisit) {
		for (position move : delta) {
			position newPos = toVisit[0] + move;
			if (!searchWay[newPos.y][newPos.x].isVisited and labirintMap[newPos.y][newPos.x].isPassable()) {
				toVisit.push_back(newPos);
				++amountToVisit;
				unsigned short minLength = searchWay[toVisit[0].y][toVisit[0].x].wayLength + 1;
				searchWay[newPos.y][newPos.x] = {true, minLength};
			}
		}
		toVisit.erase(toVisit.begin());
		--amountToVisit;
	}
}

position findMove (position pos) {
	position res = {0, 0};
	src currMin = {false, 1000};

	for (position move : delta) {
		position newPos = pos + move;
		if (currMin > searchWay[newPos.y][newPos.x]) {
			currMin = searchWay[newPos.y][newPos.x];
			res = move;
		}
	}
	return res;
}

void EnemyAI (void) {
	for (std::vector<Enemy>::iterator it = enemies.begin(); it != enemies.end(); ++it)
		it->move(findMove(it->pos));
	// std::this_thread::sleep_for(std::chrono::milliseconds(250));
}