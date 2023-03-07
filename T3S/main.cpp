#include <iostream>
#include "Match.h"
#include "TicTacToeView.h"
#include "Solver.h"
#include "colors.h"
int main(void) {

	Match m;
	Solver s(m.getGrid(), "save0.txt");
	//Solver s1(m.getGrid(), "save0.txt");
	m.addAI(&s);
	//m.addAI(&s1);
	TicTacToeView tttv(&m);
	int round = 3;


	std::cout << "Number of round : ";
	std::cin >> round;
	std::cout << std::endl << std::endl << std::endl;

	for (int i = 0; i < round; i++)
	{
		tttv.play();
		m.reinit();
		s.reinit(m.getGrid());
		//s1.reinit(m.getGrid());
	}
	
	std::cout << round << " round played" << std::endl;
	std::cout << tttv.getResults();

	return EXIT_SUCCESS;
}