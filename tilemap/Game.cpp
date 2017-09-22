// game.cpp
// written by jared bruni
// specificly for planetsourcecode
// www.lostsidedead.com

#include "thehead.h"


// on load
void Game::onload()
{
	map.init(mxhwnd);
	map.onload();
}

// update callback function
void Game::update()
{
	map.update();
}