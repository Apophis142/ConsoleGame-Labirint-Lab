#define MOVE_UP 1
#define MOVE_DOWN 2
#define MOVE_LEFT 3
#define MOVE_RIGHT 4

#define EMPTY 48
#define WALL 49
#define ENEMY 56
#define HERO 57

const unsigned char WIDTH = 120, HEIGHT = 30;
const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

bool isRunned = false;

namespace Symbols {
	char Hero = 1;
	const char Axe = 15;
	const char Fog = 176;
	const char Apple = 248;
	const char Enemy = 253;

	const char ArrowLeft = 17;
	const char ArrowRight = 16;
};

namespace Colors {
	namespace Menu {
		const char title = 11;
		const char std = 6;
		const char hover = 14;
	};

	namespace Settings {
		const char title = 13;
		const char std = 3;
		const char hover = 10;
	};

	const char labirintFog = 63;
	const char heroStd = 58;
	const char enemyStd = 60;
	const char labirintStd = 62;
	const char labirintExplored = 54;
};

namespace Menu {
	struct section {
		char title[16];
		bool isMainMenu;
		size_t amount;
		const char* sections[];
	};

	section mainMenu = {"Labirint Lab", true, 4, {"Singleplayer", "Settings", "LeaderBoard", "Authors"}};
	section singleplayer_NewGame = {"Singleplayer", false, 2, {"New Game", "Load Game"}};
	section singleplayer_ContGame = {"Singleplayer", false, 2, {"Continue Game", "Load Game"}};
	section settings = {"Settings", false, 2, {"Game", "Audio"}};
};

namespace Keys {
	const short int Esc = 27;
	const short int Enter = 13;
	const short int Arrows = 224;
	const short int Arrow_Up = 72;
	const short int Arrow_Down = 80;
	const short int Arrow_Left = 75;
	const short int Arrow_Right = 77;
	const short int Space = 32;
	const short int Ctrl_E = 5;
	const short int Ctrl_Q = 17;
	const short int Ctrl_R = 18;
};

struct position {
	int x;
	int y;

	position operator+ (position const& other) {
		return (position){x + other.x, y + other.y};
	}

	position operator+= (position const& other) {
		return (position){x += other.x, y += other.y};
	}

	position operator++ (int) {
		return (position){x++, y++};
	}

	position operator++ (void) {
		return (position){++x, ++y};
	}

	position operator% (position const& other) {
		return (position){x % other.x, y % other.y};
	}

	position operator%= (position const& other) {
		return (position){x %= other.x, y %= other.y};
	}
};

position SCREEN = {WIDTH, HEIGHT};

struct src {
	bool isVisited = false;
	unsigned short wayLength = 1000;

	bool operator< (const src& other) const {
		return wayLength < other.wayLength;
	}

	bool operator<= (const src& other) const {
		return wayLength <= other.wayLength;
	}

	bool operator> (const src& other) const {
		return wayLength > other.wayLength;
	}

	bool operator>= (const src& other) const {
		return wayLength >= other.wayLength;
	}

	bool operator== (const src& other) const {
		return wayLength == other.wayLength;
	}
};

class mapCell;
class Enemy;

extern mapCell labirintMap[HEIGHT][WIDTH];
extern position currentHeroPosition;
extern unsigned char viewRange;
extern std::vector <Enemy> enemies;
extern src searchWay[HEIGHT][WIDTH];