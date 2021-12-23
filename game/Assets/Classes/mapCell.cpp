mapCell::mapCell (void) {
	return;
}

void mapCell::set_cellType (unsigned short type) {
	cellType = type;
}


bool mapCell::isPassable (void) {
	switch (cellType) {
		case EMPTY: return true;
		case WALL: return false;
		case ENEMY: return false;
		case HERO: return false;
		default: return true;
	}
}

bool mapCell::isEmpty (void) {
	return cellType == EMPTY;
}

void mapCell::viewCell (void) {
	isExplored = true;
	isViewed = true;
}

void mapCell::blindCell (void) {
	isViewed = false;
}