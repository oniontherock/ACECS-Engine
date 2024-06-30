#include "GameStateInterface.hpp"

typedef std::vector<InputName> InputList; // list of inputs
typedef GameStateTransition GST; // game-state-transition
typedef std::vector<GST> GSTL; // game-state-transition-list

void GameStateInterface::registerGameStates() {

	GameStateHandler::addGameState("Play",
		GSTL{
			GST("Pause", InputList{"Pause"})
		},
		[]() {
			std::cout << "hello sire" << std::endl;
		}
	);
}

void GameStateInterface::runGameState() {
	GameStateHandler::process();
}

