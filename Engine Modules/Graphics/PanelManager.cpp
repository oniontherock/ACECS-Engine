#include "PanelManager.hpp"

std::unordered_map<PanelName, Panel*> PanelManager::panels{};

void PanelManager::panelAdd(PanelName panelName, PanelRect panelScreenRect, PanelRect panelViewRect, sf::Color panelClearColor, std::function<void(Panel& panel)> panelDrawFunction) {
	panels.insert({ panelName, new Panel(panelScreenRect, panelViewRect, panelDrawFunction, panelClearColor) });
}

Panel* PanelManager::panelGet(PanelName panelName) {
	return panels[panelName];
}

bool PanelManager::panelExists(PanelName panelName) {
	return panels.count(panelName);
}

void PanelManager::panelDelete(PanelName panelName) {
	delete panels[panelName];
	panels.erase(panelName);
}

void PanelManager::panelManagerTerminate() {
	for (const auto& [key, value] : panels) {
		delete value;
	}
	panels.clear();
}
