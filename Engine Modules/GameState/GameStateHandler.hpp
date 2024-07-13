#ifndef __GAME_STATE_HANDLER_H__
#define __GAME_STATE_HANDLER_H__

#include <unordered_map>
#include <functional>
#include <cstdint>
#include <iostream>
#include "../Graphics/Panel.hpp"
#include "../Graphics/PanelManager.hpp"
#include "../Input/InputInterface.hpp"

typedef const char* GameStateName;

struct GameStateTransition {

	GameStateTransition(GameStateName _toStateName, std::vector<InputName> _transitionInputs);

	// the name of the state that this transition leads to
	GameStateName toStateName;

	// vector of inputs that trigger a transition
	std::vector<InputName> linkedInputs;
};

struct GameState {

	GameState(std::vector<GameStateTransition> _transitions, std::function<void()> _updateFunc, std::vector<PanelName> _panelNames);

	// vector of different GameStateTransitions linked to this GameStates
	std::vector<GameStateTransition> transitions;
	// vector of different PanelNames belonging to this GameState
	std::vector<PanelName> panelNames;
	// this GameState's update function
	std::function<void()> updateFunc;
};

class GameStateHandler {
	static std::unordered_map<GameStateName, GameState*> gameStates;
	static GameStateName gameStateNameCur;

	static void gameStateUpdate();
	static const void gameStateRun();
	// checks if gameStateCurName is valid, and if it is, returns true, otherwise, prints an error and returns false
	static bool gameStateNameCurCheckValid();

public:
	static bool gameStateExists(GameStateName stateName);
	static void gameStateProcess();
	static void gameStateTerminate(GameStateName name);
	static void gameStateAdd(GameStateName name, std::vector<GameStateTransition> transitions, std::vector<PanelName> panels, std::function<void()> updateFunc);
	// does some error checking on every state, should be called after adding new game states
	static void gameStateFinalizeAddedStates();
	static void gameStateForceSet(GameStateName gameStateName);
	static void gameStatesAllTerminate();
	static const std::vector<PanelName>& gameStateGetPanels();
};

#endif
