// game.cpp
// written by jared bruni
// for planetsourcecode

#include "thehead.h"


// the game load method
void Game::load()
{
	hero.init(mxhwnd);
	hero.load();
}

// the update method
void Game::update()
{
	// update hero
	hero.update();
}




