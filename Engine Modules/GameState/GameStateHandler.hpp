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
		linkedInputs(_transitionInputs)
	{}

	// the name of the state that this transition leads to
	GameStateName toStateName;

	// vector of inputs that trigger a transition
	std::vector<InputName> linkedInputs;
};

struct GameState {

	GameState(std::vector<GameStateTransition> _transitions, std::function<void()> _updateFunc) :
		transitions(_transitions),
		updateFunc(_updateFunc)
	{}

	// vector of different GameStateTransitions linked to this GameStates
	std::vector<GameStateTransition> transitions;
	// this GameState's update function
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
				for (uint16_t curTransitionInputInd = 0; curTransitionInputInd < curTransition.linkedInputs.size(); curTransitionInputInd++) {
					// check if the current input of the current transition is active, if it is, transition to that state, and end the check
					if (inputInterface.inputGetActive(curTransition.linkedInputs[curTransitionInputInd])) {
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

		static inline void gameStateTerminate(GameStateName name) {
			delete gameStates[name];
			gameStates.erase(name);
		}

		static inline void gameStateAdd(GameStateName name, std::vector<GameStateTransition> transitions, std::function<void()> updateFunc) {
			gameStates.insert({ name, new GameState(transitions, updateFunc) });
		}

		static inline void gameStateForceSet(GameStateName gameStateName) {
			gameStateCurName = gameStateName;
		}

		static inline void gameStatesAllTerminate() {
			for (const auto& [gameStateNameCur, gameStateNameInstanceCur] : gameStates) {
				delete gameStateNameInstanceCur;
			}
			gameStates.clear();
		}
	};
}

#endif
