#ifndef __ACECS_H__
#define __ACECS_H__

#include "../Graphics.hpp"
#include "SFML/Graphics.hpp"

#define GAME_STATE_FUNCTION []()
#define PANEL_DRAW_FUNCTION [](Panel& panel)

class Engine {
private:
	// inputs are registered here
	static void inputsRegister();
	// panels are registered here
	static void panelsRegister();
	// game states are registered here
	static void gameStateRegister();
public:
	// initialize the ACECS engine by registering all inputs, initializing the ECS module, and registering game states.
	// of course, certain modules do not have to be initialized if the user does not want them to be
	static void engineInitialize();
	// updates the engines input
	static void engineInputUpdate(sf::RenderWindow& window);
	// update certain modules of the engine, like the GameState, which itself will usually update the ECS module.
	// note that this does NOT update the input, that must be called manually before updating the game
	static void engineGameUpdate();
	// draws the panels of the current GameState
	static void engineGameDraw(sf::RenderWindow& renderWindowMain);
	// terminates certain engine modules, like the ECS or GameStateHandler
	static void engineTerminate();
};

#endif