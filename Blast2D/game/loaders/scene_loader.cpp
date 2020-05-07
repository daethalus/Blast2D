#include "scene_loader.hpp"

#include <game/resources/scene.hpp>
#include <core/libs/json.hpp>
#include <core/logging/easylogging++.h>

using json = nlohmann::json;

void Blast2D::SceneLoader::loadFile(const Blast2D::ResourceConfigFile &&configFile) {
    auto sceneJson = json::parse(configFile.content);
    for (json::iterator it = sceneJson.begin(); it != sceneJson.end(); ++it) {
        resourceManager.emplace<Scene>(it.key());
        auto& scene = resourceManager.load<Scene>(it.key());
        for (auto& entities: it.value()) {
            SceneItem item;
            for (json::iterator itComp = entities.begin(); itComp != entities.end(); ++itComp) {
                SceneComponent comp = {itComp.key(), itComp.value().dump()};
                item.components.push_back(comp);
            }
            scene.items.push_back(std::move(item));
        }
    }

}
