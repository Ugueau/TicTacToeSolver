#pragma once
#include "Match.h"
class TicTacToeController
{
private:
	Match* model;
	int* result;
public:
	TicTacToeController(Match* match);
	void control(int x, int y);
	std::string results();
};

