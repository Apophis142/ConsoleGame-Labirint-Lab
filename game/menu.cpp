namespace Menu {
	char menu (section &currentSection);
	void display (section &currentSection, char selected);
}

char Menu::menu (Menu::section &currentSection) {
	clearScreen();
	char selected = 1;
	while (true) {
		Menu::display(currentSection, selected);
		switch (_getch()) {
			case Keys::Esc:
				return 0;
			case Keys::Arrows: break;
			case Keys::Arrow_Down:
				++selected;
				selected %= (currentSection.amount + 1);
				break;
			case Keys::Arrow_Up:
				selected += currentSection.amount;
				selected %= (currentSection.amount + 1);
				break;
			case Keys::Enter:
				return selected;
		}
	}
	return selected;
}

void Menu::display (Menu::section &currentSection, char selected) {
	position cursor_pos = {(int)(WIDTH * 0.4), (int)(HEIGHT * 0.3)};
	setCursor(cursor_pos);
	setColor(Colors::Menu::title);
	printf("%s", currentSection.title);
	setColor(Colors::Menu::std);
	cursor_pos = {(int)(WIDTH * 0.4) - 5, (int)(HEIGHT * 0.5)};

	for (size_t i = 1; i <= currentSection.amount; ++i) {
		setCursor(cursor_pos);
		if (i == selected) {
			setColor(Colors::Menu::hover);
			printf("---> %s", currentSection.sections[i - 1]);
			setColor(Colors::Menu::std);
		}
		else
			printf("     %s", currentSection.sections[i - 1]);
		cursor_pos.y += 2;
	}

	cursor_pos.y = HEIGHT - 3;
	setCursor(cursor_pos);
	if (selected == 0) {
		setColor(Colors::Menu::hover);
		printf("---> %s", (currentSection.isMainMenu ? "Exit" : "Back"));
		setColor(Colors::Menu::std);
	}
	else
		printf("     %s", (currentSection.isMainMenu ? "Exit" : "Back"));
}