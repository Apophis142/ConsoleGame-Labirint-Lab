namespace Settings {
	struct sectionInt {
		char title[16];
		unsigned char ID;
		const int maxVal, minVal;
		unsigned char selected;
	};
	struct sectionBool {
		char title[16];
		unsigned char ID;
		bool selected;
	};
	struct sectionStr {
		char title[16];
		unsigned char ID;
		char selected;
		std::vector<std::string> values;
	};
	struct setting {
		char title[16];
		std::vector<sectionInt> integerSections;
		std::vector<sectionBool> booleanSections;
		std::vector<sectionStr> stringSections;
	};

	setting game = {"Game",
		{},
		{(sectionBool){"Tips", 121, false}},
		{
			(sectionStr){"Difficulty", 131, 1, {"easy", "normal", "hard"}},
			(sectionStr){"Hero's Symbol", 132, 0, {{1}, {2}, {20}, {64}, {4}}}
		}
	};
	setting audio = {"Audio", 
		{
			(sectionInt){"Music", 211, 10, 0, 10},
			(sectionInt){"Sound Effect", 212, 10, 0, 10}
		},
		{},
		{}
	};

	void main (setting &curr);
	void display (setting &curr, unsigned char selected);
	char sectionByNumber (setting &curr, unsigned char number);
	void displaySection (sectionInt &curr, bool isSelected, position cursor_pos);
	void displaySection (sectionBool &curr, bool isSelected, position cursor_pos);
	void displaySection (sectionStr &curr, bool isSelected, position cursor_pos);
	void change (Settings::sectionInt &curr, bool diff);
	void change (Settings::sectionBool &curr);
	void change (Settings::sectionStr &curr, bool diff);
	void update (void);

	const char TypeNone = 0, TypeInt = 1, TypeBool = 2, TypeStr = 3;

	std::map <unsigned char, int> values = {
		{121, 0},
		{131, 1},
		{132, 0},
		{211, 10},
		{212, 10},
	};
};