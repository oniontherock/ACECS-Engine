#ifndef __PANEL_MANAGER_H__
#define __PANEL_MANAGER_H__

#include <unordered_map>
#include <vector>
#include "Panel.hpp"

namespace PanelManager {
	std::unordered_map<PanelName, Panel*> panels;

	void panelAdd(PanelName panelName, PanelRect panelScreenRect, PanelRect panelViewRect, sf::Color panelClearColor) {


		panels.insert({ panelName, new Panel(panelScreenRect, panelViewRect, panelClearColor)});
	}

	Panel* panelGet(PanelName panelName) {
		return panels[panelName];
	}

	void panelDelete(PanelName panelName) {
		delete panels[panelName];
		panels.erase(panelName);
	}
}

#endif