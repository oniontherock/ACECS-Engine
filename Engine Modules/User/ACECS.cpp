#include "ACECS.hpp"


void Engine::inputsRegister() {
	InputInterface::inputRegister("Example Input", KeySet{ KeyEvent("Escape", Pressed) });
}

void Engine::panelsRegister() {
	using namespace PanelManager;
	panelAdd("Example View",
		PanelRect(0, 0, 1280, 720), // screen coordinates
		PanelRect(0, 0, 640, 360), // world coordinates
		sf::Color::Black,
		PANEL_DRAW_FUNCTION{
		}
	);
}

void Engine::gameStateRegister() {

	GameStateHandler::gameStateForceSet("Example State");

	GameStateHandler::gameStateAdd("Example State",
		/// transitions
		// vector of GameStateTransitions, and their inputs
		{
			GameStateTransition("Other Example State", // name of the state to transition to
				/// transition inputs
				// vector of inputs that trigger this transition
				// note the commas after an input name, without commas every name will become a single string
				{
					"Example Input",
				}
			)
		},
		/// panels
		// the panels belonging to this GameState,
		// note the commas after every panel name, without commas every name will become a single string
		{
			"Example View",
		},

		/// update function
		// update function for this GameState, called every frame
		GAME_STATE_FUNCTION{
			LevelUpdater::levelsUpdate();
		}
	);
	GameStateHandler::gameStateAdd("Other Example State",
		/// transitions
		// vector of GameStateTransitions, and their inputs
		{
			GameStateTransition("Example State", // name of the state to transition to
				/// transition inputs
				// vector of inputs that trigger this transition
				// note the commas after an input name, without commas every name will become a single string
				{
					"Example Input",
				}
			)
		},
		/// panels
		// the panels belonging to this GameState,
		// note the commas after every panel name, without commas every name will become a single string
		{
			"Example View",
		},

		/// update function
		// update function for this GameState, called every frame
		GAME_STATE_FUNCTION{
		}
		);

	GameStateHandler::gameStatesAddedStatesFinalize();
}

void Engine::engineInitialize() {
	GameLevelGrid::levelGridInitialize(5, 5, 5);
	inputsRegister();
	ECSRegistry::ECSInitialize();
	panelsRegister();
	gameStateRegister();
}
void Engine::engineInputUpdate(sf::RenderWindow& window) {
	InputInterface::inputUpdate();
	InputInterface::eventsProcess(window);
}
void Engine::engineGameUpdate() {
	GameStateHandler::gameStateProcess();
}
void Engine::engineGameDraw(sf::RenderWindow& renderWindowMain) {

	auto& gameStatePanels = GameStateHandler::gameStateGetPanels();

	for (uint16_t i = 0; i < gameStatePanels.size(); i++) {
		PanelManager::panelGet(gameStatePanels[i])->panelDrawObjects();
		PanelManager::panelGet(gameStatePanels[i])->panelRender(renderWindowMain);
		PanelManager::panelGet(gameStatePanels[i])->panelClear();
	}
}
void Engine::engineTerminate() {
	ECSRegistry::ECSTerminate();
	GameStateHandler::gameStatesAllTerminate();
	PanelManager::panelManagerTerminate();
}
