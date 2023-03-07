#include "TicTacToeController.h"
#include <iostream>
#include "colors.h"
#include <windows.h>
TicTacToeController::TicTacToeController(Match* match)
{
	this->model = match;
	int teams = this->model->getTeams();
	this->result = new int[teams+1];
	for (int i = 0; i < teams+1; i++)
	{
		this->result[i] = 0;
	}
}
void TicTacToeController::control(int x, int y)
{
	if (model->isPlayable(x, y)) {
		model->play(x, y);
		if (model->getWinner() != -1)
		{
			if (model->getWinner() == 0) {
				std::cout << IYELLOW << "Draw !" << RESET << std::endl << std::endl << std::endl;
				this->result[0] ++;
				for (Solver* AI : model->AIs)
				{
					AI->save();
				}
			}
			else {
				for (Solver* AI : model->AIs)
				{
					AI->patchLockers(model->getWinner() == AI->getId());
					AI->save();
				}
				std::cout << YELLOW << "Match won by :" << model->getWinner() << RESET << std::endl << std::endl << std::endl;
				this->result[model->getWinner()] ++;
			}
		}
	}
	else {
		std::cout << RED << "/!\\ Invalid cell " << x << ":" << y << RESET << std::endl;
		Sleep(500);
	}
	return;
}

std::string TicTacToeController::results()
{
	std::string results = "Draw : " + std::to_string(this->result[0]) + "\n";
	int teams = this->model->getTeams();
	for (int i = 1; i < teams+1; i++)
	{
		results = results + "Team " + std::to_string(i) + " : " + std::to_string(this->result[i]) + " wins \n";
	}
	return results;
}
