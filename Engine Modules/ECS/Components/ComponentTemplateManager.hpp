#ifndef __COMPONENT_TEMPLATE_MANAGER_H__
#define __COMPONENT_TEMPLATE_MANAGER_H__

#include <functional>
#include "../Entities/Entity.hpp"
#include "../Entities/EntityManager.hpp"
#include "Component.hpp"

// just the name of a component template
typedef const char* ComponentTemplateName;
// vector of component instances, this is a special type so it's easier to tell that something is specifically a template
typedef std::vector<ComponentUniquePtr> ComponentTemplate;
// vector of ComponentIndexInstancePairs, used when creating new templates so that the user doesn't have to create a full sized ComponentTemplate every time,
typedef std::vector<EntityComponents::ComponentIndexInstancePair> ComponentTemplatePairVector;

enum TemplateApplicationType {
	Overwrite, // deletes all the components of an entity and replaces them with the template
	Merge, // only puts components in unfilled spots in the entity's componentVector
};

namespace ComponentTemplateManager {
	inline std::unordered_map<ComponentTemplateName, ComponentTemplate> componentTemplates;

	inline bool componentTemplatesErrorIfNameTaken(ComponentTemplateName templateName) {
		if (componentTemplates.count(templateName)) {
			std::cerr << "ERROR: Template name taken: " << "\"" << templateName << "\"" << std::endl;
			return true;
		}
		return false;
	}

	inline void componentTemplateAdd(ComponentTemplateName templateName, ComponentTemplate templateComponentsVector) {
		if (templateComponentsVector.size() < EntityComponents::totalComponents) {
			std::cerr << "ERROR: Attempted to add template with fewer components than the total amount of components: " << "\"" << templateName << "\"" << std::endl;
			return;
		}
		else if (componentTemplatesErrorIfNameTaken(templateName)) {
			return;
		}

		componentTemplates.insert({ templateName, std::move(templateComponentsVector) });
	}
	// this overload should generally be preferred over others, as it is easier to use in one line
	inline void componentTemplateAdd(ComponentTemplateName templateName, ComponentTemplatePairVector templateComponentsMap) {

		if (componentTemplatesErrorIfNameTaken(templateName)) {
			return;
		}

		ComponentTemplate templateComponentsVector(EntityComponents::totalComponents);

		for (uint16_t i = 0; i < templateComponentsMap.size(); i ++) {
			templateComponentsVector[templateComponentsMap[i].first] =
				Duplicatable::duplicateAndConvertToType<EntityComponents::Component>(templateComponentsMap[i].second.get());
		}

		componentTemplates.insert({ templateName, std::move(templateComponentsVector) });
	}

	// applies a template to an entity
	inline void componentTemplateApply(ComponentTemplateName templateName, Entity& entity, TemplateApplicationType applicationType = Overwrite) {

		if (applicationType == Overwrite) {
			entity.componentsAllTerminate();
		}
		for (EntityComponents::ComponentTypeID i = 0; i < componentTemplates[templateName].size(); i++) {

			// go to next iteration if the current component is a nullptr
			if (!static_cast<bool>(componentTemplates[templateName][i])) continue;

			// we use no overwrite regardless of the application type because if the application type IS overwrite,
			// then all the components were terminated, and so adding a component with no overwrite is the same as with overwrite
			entity.entityComponentAddAtIndexNoOverwrite(
				static_cast<EntityComponents::Component*>(Duplicatable::duplicateAndGetRaw(componentTemplates[templateName][i].get())),
				i
			);
		}
	}
	// applies a template to an entityId
	inline void componentTemplateApply(ComponentTemplateName templateName, EntityID entity, TemplateApplicationType applicationType = Overwrite) {
		componentTemplateApply(templateName, EntityManager::entities[entity], applicationType);
	}
	inline void componentTemplateTerminate(ComponentTemplateName templateName) {
		componentTemplates[templateName].clear();
	}
	inline void componentTemplatesAllTerminate() {
		componentTemplates.clear();
	}
};


#endif
