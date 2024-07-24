#ifndef __COMPONENT_TEMPLATE_MANAGER_H__
#define __COMPONENT_TEMPLATE_MANAGER_H__

#include <functional>
#include "../Entities/Entity.hpp"
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
	extern std::unordered_map<ComponentTemplateName, ComponentTemplate> componentTemplates;

	bool componentTemplatesErrorIfNameTaken(ComponentTemplateName templateName);
	void componentTemplateAdd(ComponentTemplateName templateName, ComponentTemplate templateComponentsVector);
	// this overload should generally be preferred over others, as it is easier to use in one line
	void componentTemplateAdd(ComponentTemplateName templateName, ComponentTemplatePairVector templateComponentsMap);
	// applies a template to a componentVector
	void componentTemplateApplyToComponentVector(ComponentTemplateName templateName, std::vector<ComponentUniquePtr>& componentsVector, TemplateApplicationType applicationType = Overwrite);
	// applies a template to an entity
	void componentTemplateApplyToEntity(ComponentTemplateName templateName, Entity& entity, TemplateApplicationType applicationType = Overwrite);
	void componentTemplateTerminate(ComponentTemplateName templateName);
	void componentTemplatesAllTerminate();
};


#endif
