#include "ACECS.hpp"


void Engine::inputsRegister() {
	InputInterface::inputRegister("Example Input", KeySet{ KeyEvent("Escape", Pressed) });
}

void Engine::panelsRegister() {
	using namespace PanelManager;
	panelAdd(PanelTypes::GameView, PanelPtr(new PanelGameView(
		PanelRect(0, 0, 1280, 720), // screen coordinates
		PanelRect(0, 0, 640, 360), // world coordinates
		sf::Color::Black
	)));
}

void Engine::gameStateRegister() {

	GameStateHandler::gameStateForceSet(GameStateType::Play);

	GameStateHandler::gameStateAdd(GameStateUniquePtr(new GameStatePlay(
		/// transitions
		// vector of GameStateTransitions, and their inputs
		{
			GameStateTransition(GameStateType::Pause, // name of the state to transition to
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
			PanelTypes::GameView,
		}
	)));
	GameStateHandler::gameStateAdd(GameStateUniquePtr(new GameStatePause(
		/// transitions
		// vector of GameStateTransitions, and their inputs
		{
			GameStateTransition(GameStateType::Play, // name of the state to transition to
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
			PanelTypes::GameView,
		}
		)));

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

		auto& panelCur = PanelManager::panelGet(gameStatePanels[i]);

		panelCur.panelDrawObjects();
		panelCur.panelRender(renderWindowMain);
		panelCur.panelClear();
	}
}
void Engine::engineTerminate() {
	ECSRegistry::ECSTerminate();
	GameStateHandler::gameStatesAllTerminate();
	PanelManager::panelManagerTerminate();
}
