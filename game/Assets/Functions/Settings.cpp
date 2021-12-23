void Settings::main(Settings::setting &curr) {
	clearScreen();
	char selected = 1;
	size_t sectionAmount = curr.integerSections.size() + curr.booleanSections.size() + curr.stringSections.size();
	bool flag, diff;

	while (true) {
		Settings::display(curr, selected);
		switch (_getch()) {
			case Keys::Esc: return;
			case Keys::Arrows: break;
			case Keys::Arrow_Up:
				selected += sectionAmount;
				selected %= (sectionAmount + 1);
				break;
			case Keys::Arrow_Down:
				++selected;
				selected %= (sectionAmount + 1);
				break;
			case Keys::Arrow_Right:
				flag = true;
				diff = true;
				break;
			case Keys::Arrow_Left:
				flag = true;
				diff = false;
				break;
			case Keys::Enter:
				if (!selected)
					return;
				break;
		}
		if (flag) {
			switch (Settings::sectionByNumber(curr, selected)) {
				case Settings::TypeNone: break;
				case Settings::TypeInt:
					Settings::change(curr.integerSections[selected - 1], diff);
					break;
				case Settings::TypeBool:
					Settings::change(curr.booleanSections[selected - curr.integerSections.size() - 1]);
					break;
				case Settings::TypeStr:
					Settings::change(curr.stringSections[selected - curr.integerSections.size() - curr.booleanSections.size() - 1], diff);
					break;
			}
			flag = false;
		}
	}
}

void Settings::display (Settings::setting &curr, unsigned char selected) {
	position cursor_pos = {(int)(WIDTH * 0.4), (int)(HEIGHT * 0.3)};
	setCursor(cursor_pos);
	setColor(Colors::Settings::title);
	printf("%s", curr.title);
	setColor(Colors::Settings::std);
	cursor_pos = {(int)(WIDTH * 0.4), (int)(HEIGHT * 0.5)};

	size_t counter = 1;

	for(size_t i = 0; i < curr.integerSections.size(); ++i) {
		Settings::displaySection(curr.integerSections[i], counter == selected, cursor_pos);
		++counter;
		cursor_pos.y += 2;
	}
	for(size_t i = 0; i < curr.booleanSections.size(); ++i) {
		Settings::displaySection(curr.booleanSections[i], counter == selected, cursor_pos);
		++counter;
		cursor_pos.y += 2;
	}
	for(size_t i = 0; i < curr.stringSections.size(); ++i) {
		Settings::displaySection(curr.stringSections[i], counter == selected, cursor_pos);
		++counter;
		cursor_pos.y += 2;
	}

	cursor_pos.y = HEIGHT - 2;
	setCursor(cursor_pos);
	setColor(!selected ? Colors::Settings::hover : Colors:: Settings::std);
	printf("%s", "Back");
}

char Settings::sectionByNumber (Settings::setting &curr, unsigned char number) {
	if (!number)
		return Settings::TypeNone;
	if (number <= curr.integerSections.size()) {
		return Settings::TypeInt;
	}
	number -= curr.integerSections.size();
	if (number <= curr.booleanSections.size()) {
		return Settings::TypeBool;
	}
	number -= curr.booleanSections.size();
	if (number <= curr.stringSections.size()) {
		return Settings::TypeStr;
	}
	return Settings::TypeNone;
}

void Settings::displaySection (Settings::sectionInt &curr, bool isSelected, position cursor_pos) {
	setCursor(cursor_pos);
	setColor(isSelected ? Colors::Settings::hover : Colors::Settings::std);
	if (curr.selected == curr.maxVal)
		printf("%s\t%c %i            ", curr.title, Symbols::ArrowLeft, curr.selected);
	else if (curr.selected == curr.minVal)
		printf("%s\t  %i %c          ", curr.title, curr.selected, Symbols::ArrowRight);
	else
		printf("%s\t%c %i %c          ", curr.title, Symbols::ArrowLeft, curr.selected, Symbols::ArrowRight);
}

void Settings::displaySection (Settings::sectionBool &curr, bool isSelected, position cursor_pos) {
	setCursor(cursor_pos);
	setColor(isSelected ? Colors::Settings::hover : Colors::Settings::std);
	printf("%s\t%c %s %c          ", curr.title, Symbols::ArrowLeft, curr.selected ? "Yes" : "No", Symbols::ArrowRight);
}

void Settings::displaySection (Settings::sectionStr &curr, bool isSelected, position cursor_pos) {
	setCursor(cursor_pos);
	setColor(isSelected ? Colors::Settings::hover : Colors::Settings::std);
	std::cout << curr.title << "\t" << Symbols::ArrowLeft << " " 
				<< curr.values[curr.selected] << " " << Symbols::ArrowRight << "          ";
	// printf("%s\t%s", curr.title, curr.values[curr.selected]);
}

void Settings::change (Settings::sectionInt &curr, bool diff) {
	if (diff)
		curr.selected = std::min(curr.maxVal, curr.selected + 1);
	else
		curr.selected = std::max(curr.minVal, curr.selected - 1);
	Settings::values[curr.ID] = curr.selected;
}

void Settings::change (Settings::sectionBool &curr) {
	curr.selected = !curr.selected;
	Settings::values[curr.ID] = curr.selected;
}

void Settings::change (Settings::sectionStr &curr, bool diff) {
	if (diff)
		++curr.selected;
	else
		curr.selected += curr.values.size() - 1;
	curr.selected %= curr.values.size();
	Settings::values[curr.ID] = curr.selected;
}

void Settings::update (void) {
	std::map <unsigned char, int>::iterator it = Settings::values.begin(), it_end = Settings::values.end();
	for (; it != it_end; ++it) {
		switch (it->first) {
			case 121: break; // tips
			case 131: break; // difficulty
			case 132:
				Symbols::Hero = Settings::game.stringSections[1].values[it->second][0];
				break; // symbol
			case 211: break; // music
			case 212: break; // sound effect
		}
	}
}