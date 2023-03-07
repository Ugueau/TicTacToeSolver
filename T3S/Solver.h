#pragma once
#include <string>
#include <cstring>
#include "Rand.h"
#include <iostream>
#include <fstream>
#include "Grid.h"
#include <vector>

#define DEFAULT_PRECISION 100
class Solver
{
private:
	int id;
	Grid* grid;
	int** lockers;
	int height;
	int width;
	std::string saveFile;
	std::vector<std::pair<int, int>> playedCells;

public:
	static int SAVE_INDEX;
	static std::string DEFAULT_PATH;
	static bool TRACKING;
	Solver(Grid* grid, std::string saveFile);
	void reinit(Grid* grid);
	bool load(std::string savePath);
	int* play();
	bool save();
	bool restartIASave();
	void patchLockers(bool won);
	void setId(int id) { this->id = id; };
	int getId() { return this->id; };
};

