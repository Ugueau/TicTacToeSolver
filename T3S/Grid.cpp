#include "Grid.h"

Grid::Grid(int height, int width)
{
	this->height = height;
	this->width = width;
	grid = new Cell*[height];
	for (int i = 0; i < height; i++)
	{
		grid[i] = new Cell[width];
	}


	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			grid[i][j].value = DEFAULT_VALUE;
		}
	}
}

Grid::Grid()
{
	this->height = DEFAULT_SIZE;
	this->width = DEFAULT_SIZE;
	grid = new Cell * [height];
	for (int i = 0; i < height; i++)
	{
		grid[i] = new Cell[width];
	}


	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			grid[i][j].value = DEFAULT_VALUE;
		}
	}
}

Grid::~Grid()
{
	for (int i = 0; i < height; i++)
	{
		delete grid[i];
	}
	delete grid;
}

bool Grid::exist(int x, int y)
{
	return x < height && y < width;
}

bool Grid::isEmpty(int x, int y)
{
	if (this->exist(x, y)) {
		return this->grid[x][y].value == DEFAULT_VALUE;
	}
	else {
		return false;
	}
}

void Grid::add(int x, int y, int value)
{
	this->grid[x][y].value = value;
}

// Return true if the Tic Tac Toe is won
bool Grid::checkGrid()
{
	if (checkRows() || checkColumns() || checkDiagonals()) {
		return true;
	}
	return false;
}

bool Grid::checkRows()
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width - 2; j++)
		{
			if (grid[i][j].value == grid[i][j + 1].value && grid[i][j].value == grid[i][j + 2].value) {
				if (grid[i][j].value != DEFAULT_VALUE)
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool Grid::checkColumns()
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height - 2; j++)
		{
			if (grid[j][i].value == grid[j + 1][i].value && grid[j][i].value == grid[j + 2][i].value) {
				if (grid[j][i].value != DEFAULT_VALUE)
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool Grid::checkDiagonals()
{
	// Check Asc Diagonals
	for (int i = 0; i < height - 2; i++)
	{
		for (int j = 0; j < width - 2; j++)
		{
			if (grid[i + 2][j].value == grid[i + 1][j + 1].value && grid[i + 2][j].value == grid[i][j + 2].value) {
				if (grid[i + 2][j].value != DEFAULT_VALUE)
				{
					return true;
				}

			}
		}
	}

	// Check Desc Diagonals
	for (int i = 0; i < height - 2; i++)
	{
		for (int j = 0; j < width - 2; j++)
		{
			if (grid[i][j].value == grid[i + 1][j + 1].value && grid[i][j].value == grid[i + 2][j + 2].value) {
				if (grid[i][j].value != DEFAULT_VALUE)
				{
					return true;
				}
			}
		}
	}

	return false;
}
// Return true if the Cell is fulled
bool Grid::checkCell(int x, int y)
{

	return grid[x][y].value != DEFAULT_VALUE;
}

bool Grid::isFulled()
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (grid[i][j].value == DEFAULT_VALUE) {
				return false;
			}
		}
	}
	return true;;
}

std::string Grid::toString()
{
	std::string result;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (grid[i][j].value == DEFAULT_VALUE) {
				result += "_ | ";
			}
			else {
				result += std::to_string(grid[i][j].value) + " | ";
			}
		}
		result += "\n";
	}
	return result;
}
