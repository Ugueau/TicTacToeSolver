#include "Solver.h"
#include "colors.h"

int Solver::SAVE_INDEX;
bool Solver::TRACKING;
std::string Solver::DEFAULT_PATH;

Solver::Solver(Grid* grid, std::string saveFile)
{
	Rand::newSeed(rand());
	Solver::SAVE_INDEX = 0;
	Solver::TRACKING = false;
	Solver::DEFAULT_PATH = "save\\";
	this->grid = grid;
	if (!this->load(saveFile)) {
		if(this->load("")) {
			std::cout << "Due to a invalid save file name. It will be saved in : " << MAGENTA << Solver::DEFAULT_PATH << "save" + std::to_string(Solver::SAVE_INDEX) + ".txt" << RESET << std::endl;
		}
		else {
			std::cout << RED << "Invalid save file name" << RESET << std::endl;
		}
	}
}

void Solver::reinit(Grid* grid) {
	this->playedCells.clear();
	this->load(this->saveFile);
	this->grid = grid;
}

bool Solver::load(std::string savePath)
{
	if(savePath == ""){
		if (this->restartIASave())
		{
			savePath = "save" + std::to_string(Solver::SAVE_INDEX) + ".txt";
		}
		else {
			return false;
		}
	}
	this->saveFile = savePath;
	savePath = Solver::DEFAULT_PATH + savePath;
	const char* char_array = savePath.c_str();
	std::ifstream loadStream(char_array, std::ios::in);
	if (!loadStream) {
		std::cout <<RED << "Open save failed" << RESET <<std::endl;
		loadStream.close();
		return false;
	}

	char* readed;
	int readingSize = 5;
	readed = new char[readingSize];

	loadStream.getline(readed, readingSize,':');
	this->height = atoi(readed);
	loadStream.getline(readed, readingSize, '\n');
	this->width = atoi(readed);

	if (!(this->height == grid->getHeight() && this->width == grid->getWidth())) {
		std::cout << RED << "Saved configuration don't match" << RESET << std::endl;
		return false;
	}
	
	this->lockers = new int*[this->height];
	for (int i = 0; i < this->height; i++)
	{
		lockers[i] = new int[this->width];
	}

	for (int i = 0; i < this->height; i++)
	{
		for (int j = 0; j < this->width; j++)
		{
			loadStream.getline(readed, readingSize, ':');
			lockers[i][j] = atoi(readed);
		}
	}
	std::cout << GREEN << "Saved successfully loaded" << RESET << std::endl;
	loadStream.close();
	return true;
}

bool Solver::save()
{
	std::string saveUsed = this->saveFile;
	if (Solver::TRACKING)
	{
		Solver::SAVE_INDEX++;
		saveUsed = "save" + std::to_string(Solver::SAVE_INDEX) + ".txt";
	}

	std::string saveName = Solver::DEFAULT_PATH + saveUsed;
	const char* char_array = saveName.c_str();
	std::ofstream saveStream(saveName, std::ios::out);
	if (!saveStream) {
		std::cout << RED << "Save failed" << RESET << std::endl;
		saveStream.close();
		return false;
	}
	std::string tmpH = std::to_string(height);
	std::string tmpW = std::to_string(width);
	const char* gridH = tmpH.c_str();
	const char* gridW = tmpW.c_str();

	saveStream << gridH << ":" << gridW << "\n";
	std::string valueToStr = "";
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			 valueToStr += std::to_string(lockers[i][j]);
			 valueToStr += ":";
		}
	}
	const char* formatedValue = valueToStr.c_str();
	saveStream << formatedValue;
	saveStream.close();
	std::cout << GREEN << "Successfully saved in :" << saveName << RESET << std::endl;
	return true;
}

bool Solver::restartIASave()
{
	Solver::SAVE_INDEX++;
	std::string saveName = Solver::DEFAULT_PATH + "save" + std::to_string(Solver::SAVE_INDEX) + ".txt";
	const char* char_array = saveName.c_str();
	std::ofstream saveStream(saveName, std::ios::out);
	if (!saveStream) {
		std::cout << RED << "Making new save failed" << RESET << std::endl;
		saveStream.close();
		return false;
	}

	this->height = this->grid->getHeight();
	this->width =this->grid->getWidth();

	std::string tmpH = std::to_string(height);
	std::string tmpW = std::to_string(width);
	const char* gridH = tmpH.c_str();
	const char* gridW = tmpW.c_str();
	saveStream << gridH << ":" << gridW << "\n";


	std::string initValue = "";
	for (int i = 0; i < height * width; i++)
	{
		initValue += std::to_string(DEFAULT_PRECISION);
		initValue += ":";
	}
	const char* formatedValue = initValue.c_str();
	saveStream << formatedValue;
	saveStream.close();
	return true;
}

int* Solver::play() {

	int maxLocker = 0;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (!grid->checkCell(i, j)) {
				maxLocker += lockers[i][j];
			}
		}
	}
	int rand = Rand::randi(maxLocker+1);

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (!grid->checkCell(i, j)) {
				if (maxLocker - lockers[i][j] >= rand) { 
					maxLocker = maxLocker - lockers[i][j];
				}
				else {
					int coord[2] = { i,j };
					playedCells.push_back(std::make_pair(i, j));
					return coord;
				}
			}
		}
	}
	int coord[2] = { -1,-1 };
	std::string t = "";
	return coord;

}
void Solver::patchLockers(bool won) {
	if (won) {
		for (std::pair<int, int> playedCell : playedCells) {
			lockers[playedCell.first][playedCell.second] ++;
		}
	}
	else {
		for (std::pair<int, int> playedCell : playedCells) {
			if (lockers[playedCell.first][playedCell.second] > 1) {
				lockers[playedCell.first][playedCell.second] --;
			}
		}
	}
}