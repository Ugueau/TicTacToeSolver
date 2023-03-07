#pragma once
#include "Match.h";
#include "TicTacToeController.h"
#include <iostream>
#include "Observer.h";
#include <vector>;
#include "Solver.h"
class TicTacToeView : public Observer
{
private:
	Match* model;
	TicTacToeController* controller;

public:

	TicTacToeView(Match* model);
	virtual void update() override;
	void play();
	std::string getResults();
};

