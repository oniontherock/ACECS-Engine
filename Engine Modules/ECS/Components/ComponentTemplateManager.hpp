#ifndef __COMPONENT_TEMPLATE_MANAGER_H__
#define __COMPONENT_TEMPLATE_MANAGER_H__

#include <functional>
#include "../Entities/Entity.hpp"
#include "../Entities/EntityManager.hpp"
#include "Component.hpp"

typedef const char* ComponentTemplateName;
typedef std::vector<EntityComponents::Component*> ComponentTemplate;

enum TemplateApplicationType {
	Overwrite, // deletes all the components of an entity and replaces them with the template
	Merge, // only puts components in unfilled spots in the entity's componentVector
};

namespace ComponentTemplateManager {
	inline std::unordered_map<ComponentTemplateName, ComponentTemplate> componentTemplates;

	inline void componentTemplateAdd(ComponentTemplateName templateName, ComponentTemplate templateComponents) {
		if (templateComponents.size() < EntityComponents::totalComponents) {
			std::cerr << "ERROR: Attempted to add template with fewer components than the total amount of components: " << "\"" << templateName << "\"" << std::endl;
			return;
		}

		componentTemplates.insert({ templateName, templateComponents });
	}
	// applies a template to an entity
	inline void componentTemplateApply(ComponentTemplateName templateName, Entity& entity, TemplateApplicationType applicationType = Overwrite) {
		auto& templateComponents = componentTemplates[templateName];

		if (applicationType == Overwrite) {
			entity.componentsAllTerminate();
		}
		for (uint32_t i = 0; i < componentTemplates[templateName].size(); i++) {

			// go to next iteration if the current component is a nullptr
			if (!static_cast<bool>(componentTemplates[templateName][i])) continue;

			// we use no overwrite regardless of the application type because if the application type IS overwrite,
			// then all the components were terminated, and so adding a component with no overwrite is the same as with overwrite
			entity.entityComponentAddAtIndexNoOverwrite(
				static_cast<EntityComponents::Component*>(Duplicatable::duplicateAndGetRaw(componentTemplates[templateName][i])),
				i
			);
		}
	}
	// applies a template to an entityId
	inline void componentTemplateApply(ComponentTemplateName templateName, EntityID entity, TemplateApplicationType applicationType = Overwrite) {
		componentTemplateApply(templateName, EntityManager::entities[entity], applicationType);
	}
};


#endif
