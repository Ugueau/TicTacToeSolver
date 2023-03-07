#pragma once
#include "Cell.h"
#include <iostream>
#include <string>
class Grid
{
private:
	Cell** grid;
	int height;
	int width;

	

public:
	const static int DEFAULT_VALUE = -1;
	const static int DEFAULT_SIZE = 3;


	Grid(int height, int width);
	Grid();
	~Grid();
	bool exist(int x, int y);
	bool isEmpty(int x, int y);
	void add(int x, int y, int value);
	bool checkGrid();
	bool checkRows();
	bool checkColumns();
	bool checkDiagonals();
	bool checkCell(int x, int y);
	bool isFulled();
	int getHeight() { return height; };
	int getWidth() { return width; };
	std::string toString();
};

