class mapCell {
	friend void chooseColor(position);
	friend void drawCell(position);
	friend void reDisplayCell(position);
public:
	mapCell (void);
	void set_cellType (unsigned short type);
	bool isPassable (void);
	bool isEmpty (void);
	void viewCell (void);
	void blindCell (void);
private:
	bool isExplored = false;
	bool isViewed = false;
	unsigned short cellType;
};