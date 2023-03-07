#include "TicTacToeView.h"
#include "colors.h"

TicTacToeView::TicTacToeView(Match* model)
{
	if (model == nullptr) {
		std::cout << RED << "Model can't be null" << RESET << std::endl;
		return;
	}
	this->model = model;
	this->model->addObserver(this);
	controller = new TicTacToeController(this->model);
}

void TicTacToeView::update()
{
	std::cout << model->toString();
}

void TicTacToeView::play()
{
	int x, y;
	int turn;
	while (model->getWinner() == -1)
	{
		turn = model->getTurn();
		if (turn <= model->getAITeams()) {
			int* coord = model->AIs.at(turn-1)->play();
			controller->control(coord[0], coord[1]);
		}
		else {
			std::cout << "Choix" << std::endl;
			std::cout << "x : ";
			std::cin >> x;
			std::cout << "y : ";
			std::cin >> y;
			std::cout << std::endl;
			controller->control(x, y);
		}

	}
}

std::string TicTacToeView::getResults()
{
	return this->controller->results();
}
