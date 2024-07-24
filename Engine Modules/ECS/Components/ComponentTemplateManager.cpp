#include "ComponentTemplateManager.hpp"



std::unordered_map<ComponentTemplateName, ComponentTemplate> ComponentTemplateManager::componentTemplates{};

bool ComponentTemplateManager::componentTemplatesErrorIfNameTaken(ComponentTemplateName templateName) {
	if (componentTemplates.count(templateName)) {
		std::cerr << "ERROR: Template name taken: " << "\"" << templateName << "\"" << std::endl;
		return true;
	}
	return false;
}

void ComponentTemplateManager::componentTemplateAdd(ComponentTemplateName templateName, ComponentTemplate templateComponentsVector) {
	if (templateComponentsVector.size() < EntityComponents::totalComponents) {
		std::cerr << "ERROR: Attempted to add template with fewer components than the total amount of components: " << "\"" << templateName << "\"" << std::endl;
		return;
	}
	else if (componentTemplatesErrorIfNameTaken(templateName)) {
		return;
	}

	componentTemplates.insert({ templateName, std::move(templateComponentsVector) });
}

void ComponentTemplateManager::componentTemplateAdd(ComponentTemplateName templateName, ComponentTemplatePairVector templateComponentsMap) {

	if (componentTemplatesErrorIfNameTaken(templateName)) {
		return;
	}

	ComponentTemplate templateComponentsVector(EntityComponents::totalComponents);

	for (uint16_t i = 0; i < templateComponentsMap.size(); i++) {
		templateComponentsVector[templateComponentsMap[i].first] =
			Duplicatable::duplicateAndConvertToType<EntityComponents::Component>(templateComponentsMap[i].second.get());
	}

	componentTemplates.insert({ templateName, std::move(templateComponentsVector) });
}

void ComponentTemplateManager::componentTemplateApplyToComponentVector(ComponentTemplateName templateName, std::vector<ComponentUniquePtr>& componentsVector, TemplateApplicationType applicationType = Overwrite) {

	if (applicationType == Overwrite) {
		for (EntityComponents::ComponentTypeID i = 0; i < EntityComponents::totalComponents; i++) {
			componentsVector[i].reset();
		}
	}

	for (EntityComponents::ComponentTypeID i = 0; i < componentTemplates[templateName].size(); i++) {

		// go to next iteration if the current component is a nullptr
		if (!static_cast<bool>(componentTemplates[templateName][i])) continue;

		// we use no overwrite regardless of the application type because if the application type IS overwrite,
		// then all the components were terminated, and so adding a component with no overwrite is the same as with overwrite
		componentsVector[i] = ComponentUniquePtr(static_cast<EntityComponents::Component*>(Duplicatable::duplicateAndGetRaw(componentTemplates[templateName][i].get())));
	}
}

void ComponentTemplateManager::componentTemplateApplyToEntity(ComponentTemplateName templateName, Entity& entity, TemplateApplicationType applicationType = Overwrite) {
	componentTemplateApplyToComponentVector(templateName, entity.componentsVector, applicationType);
}
void ComponentTemplateManager::componentTemplateTerminate(ComponentTemplateName templateName) {
	componentTemplates[templateName].clear();
}
void ComponentTemplateManager::componentTemplatesAllTerminate() {
	componentTemplates.clear();
}

