#include "Match.h"

Match::Match(int height, int width, int teams)
{
	if (teams < 1 && height < 2 && width < 2) {
		this->teams = 2;
		this->grid = new Grid();
	}
	else {
		this->teams = teams;
		this->grid = new Grid(height, width);
	}
	this->winner = DEFAULT_WINNER;
	this->AI_teams = 0;
	this->turn = 1;
}

Match::Match()
{
	this->teams = 2;
	this->AI_teams = 0;
	this->grid = new Grid();
	this->winner = DEFAULT_WINNER;
	this->turn = 1;
}

Match::~Match() 
{
	delete grid;
}

void Match::reinit()
{
	this->grid = new Grid(grid->getHeight(),grid->getWidth());
	std::cout << this->grid->toString() << std::endl;
	this->winner = DEFAULT_WINNER;
	this->turn = 1;
}

bool Match::isPlayable(int x, int y)
{
	if (x == -1 || y == -1) {
		return false;
	}
	return this->grid->isEmpty(x,y);
}

void Match::play(int x, int y)
{
	this->grid->add(x, y, this->turn);
	this->isWon();
	this->nextTurn();
	this->notifyObserver();
}

bool Match::isWon()
{

	bool isWon = grid->checkGrid();
	if (isWon) {
		this->winner = turn;
	}
	else {
		if (this->grid->isFulled())
		{
			this->winner = 0;
		}
	}
	return isWon;
}

std::string Match::toString()
{
	std::string result;
	result = grid->toString();
	result += "\n ----------------------";
	result += "\n\n Player " + std::to_string(turn);
	result += " : \n";
	return result;
}

void Match::nextTurn()
{
	if (turn == teams) {
		turn = 1;
	}
	else
	{
		turn++;
	}
}

void Match::addObserver(Observer* observer)
{
	this->observers.push_back(observer);
}

void Match::notifyObserver() const
{
	for (Observer* obs : this->observers) {
		obs->update();
	}
}

void Match::addAI(Solver* AI)
{
	for (auto ai : AIs) {
		if (ai == AI)
		{
			std::cout << RED << "Can't add the same AI twice" << RESET << std::endl;
			return;
		}
	}
	if (this->AI_teams == this->teams) {
		std::cout << RED << "Only " << this->teams << " autorized" << RESET << std::endl;
		return;
	}
	this->AIs.push_back(AI);
	this->AI_teams++;
	AI->setId(AI_teams);
}
