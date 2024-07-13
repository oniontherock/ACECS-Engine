#ifndef __PANEL_MANAGER_H__
#define __PANEL_MANAGER_H__

#include <unordered_map>
#include <vector>
#include "Panel.hpp"

namespace PanelManager {
	extern std::unordered_map<PanelName, Panel*> panels;

	void panelAdd(PanelName panelName, PanelRect panelScreenRect, PanelRect panelViewRect, sf::Color panelClearColor, std::function<void(Panel& panel)> panelDrawFunction);
	Panel* panelGet(PanelName panelName);
	bool panelExists(PanelName panelName);
	void panelDelete(PanelName panelName);
	void panelManagerTerminate();
}

#endif