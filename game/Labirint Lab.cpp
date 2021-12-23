#include "Includes.h"


int main (void) {
	hideCursor();
	SplashScreen::splashScreen();

	bool flag;
	while (true) {
		switch (Menu::menu(Menu::mainMenu)) {
		case 0: return 0;
		case 1:
			flag = true;
			while (flag) {
				switch (Menu::menu(isRunned ? Menu::singleplayer_ContGame : Menu::singleplayer_NewGame)) {
				case 0:
					flag = false;
					break;
				case 1:
					game();
					break;
				case 2: break;
				}
			}
			break;
		case 2: 
			flag = true;
			while (flag) {
				switch (Menu::menu(Menu::settings)) {
					case 0:
						flag = false;
						break;
					case 1:
						Settings::main(Settings::game);
						break;
					case 2:
						Settings::main(Settings::audio);
						break;
				}
			}
			Settings::update();
			break;
		case 3: break;
		case 4: break;
		}
	}
	return 0;
}