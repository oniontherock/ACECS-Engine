#ifndef __COMPONENT_TEMPLATE_MANAGER_H__
#define __COMPONENT_TEMPLATE_MANAGER_H__

#include <functional>
#include "../Entities/Entity.hpp"
#include "Component.hpp"

typedef const char* ComponentTemplateName;

enum TemplateApplicationType {
	Override, // deletes all the components of an entity and replaces them with the template
	Merge, // only puts components in unfilled spots in the entity's componentVector
};

namespace {
	class ComponentTemplateManager {
		std::unordered_map<ComponentTemplateName, std::vector<EntityComponents::Component*>> componentTemplates;
	public:
		void componentTemplateAdd(ComponentTemplateName templateName, std::vector<EntityComponents::Component*> templateComponents) {
			if (templateComponents.size() < EntityComponents::totalComponents) {
				std::cerr << "ERROR: Attempted to add template with fewer components than the total amount of components: " << "\"" << templateName << "\"" << std::endl;
				return;
			}

			componentTemplates.insert({ templateName, templateComponents });
		}
		// applies a template to an entity
		void componentTemplateApply(ComponentTemplateName templateName, Entity& entity, TemplateApplicationType applicationType = Override) {
			auto& templateComponents = componentTemplates[templateName];

			if (applicationType == Override) {
				entity.componentsAllTerminate();
			}

			for (uint32_t i = 0; i < componentTemplates[templateName].size(); i++) {

			}
		}
	};
}


#endif
