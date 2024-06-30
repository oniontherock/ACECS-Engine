#ifndef __GAME_STATE_HANDLER_H__
#define __GAME_STATE_HANDLER_H__

#include <unordered_map>
#include <functional>
#include <cstdint>
#include <iostream>
#include "../Input.hpp"

typedef const char* GameStateName;

struct GameStateTransition {

	GameStateTransition(GameStateName _toStateName, std::vector<InputName> _transitionInputs) :
		toStateName(_toStateName),
		transitionInputs(_transitionInputs)
	{}

	// the name of the state that this transition leads to
	GameStateName toStateName;

	std::vector<InputName> transitionInputs;
};

struct GameState {

	GameState(std::vector<GameStateTransition> _transitions, std::function<void()> _updateFunc) :
		transitions(_transitions),
		updateFunc(_updateFunc)
	{}

	std::vector<GameStateTransition> transitions;
	std::function<void()> updateFunc;
};

namespace {
	class GameStateHandler {
		static inline std::unordered_map<GameStateName, GameState*> gameStates;

		static inline GameStateName gameStateCurName = "";

		static inline void gameStateUpdate() {

			auto& curGameState = gameStates[gameStateCurName];

			Input::Interface inputInterface{};

			// iterate through the game state's transitions
			for (uint16_t curTransitionInd = 0; curTransitionInd < curGameState->transitions.size(); curTransitionInd++) {
				// get the current transition
				auto& curTransition = curGameState->transitions[curTransitionInd];

				// iterate through every input of the current transition
				for (uint16_t curTransitionInputInd = 0; curTransitionInputInd < curTransition.transitionInputs.size(); curTransitionInputInd++) {
					// check if the current input of the current transition is active, if it is, transition to that state, and end the check
					if (inputInterface.getInputActive(curTransition.transitionInputs[curTransitionInputInd])) {
						gameStateCurName = curTransition.toStateName;
						return;
					}
				}
			}
		}

		static inline const void gameStateRun() {
			std::invoke(gameStates[gameStateCurName]->updateFunc);
		}
	public:

		static inline void gameStateProcess() {
			if (std::strcmp(gameStateCurName, "") == 0) {
				std::cerr << "ERROR: Uninitialized game state. Please set game state to an initial value" << std::endl;
				return;
			}
			else if (!gameStates.count(gameStateCurName)) {
				std::cerr << "ERROR: Unknown game state: " << "\"" << gameStateCurName << "\"" << std::endl;
				return;
			}
			gameStateUpdate();
			gameStateRun();
		}

		static inline void gameStateDelete(GameStateName name) {
			delete gameStates[name];
			gameStates.erase(name);
		}

		static inline void gameStateAdd(GameStateName name, std::vector<GameStateTransition> transitions, std::function<void()> updateFunc) {
			gameStates.insert({ name, new GameState(transitions, updateFunc) });
		}

		static inline void gameStateForceSet(GameStateName gameStateName) {
			gameStateCurName = gameStateName;
		}
	};
}

#endif
