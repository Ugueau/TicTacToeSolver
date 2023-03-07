#pragma once
#include "Grid.h"
#include "Observable.h"
#include <vector>
#include <string>
#include "Solver.h"
#include "colors.h"
class Match : public Observable
{
private:
	Grid* grid;
	int teams;
	int AI_teams;
	int winner;
	int turn;

	std::vector<Observer*> observers;

public:
	const static int DEFAULT_WINNER = -1;

	std::vector<Solver*> AIs;


	Match(int height, int width, int teams);
	Match();
	~Match();
	void reinit();
	bool isPlayable(int x, int y);
	void play(int x, int y);
	bool isWon();
	int getWinner() { return this->winner; };
	int getTeams() { return this->teams; };
	int getAITeams() { return this->AI_teams; };
	Grid* getGrid() { return this->grid; };
	int getTurn() { return this->turn; };
	std::string toString();
	void nextTurn();
	void addAI(Solver* AI);

	virtual void addObserver(Observer* observer) override;
	virtual void notifyObserver() const override;
};

