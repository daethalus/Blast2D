#include "sprite_sheet_loader.hpp"
#include <core/logging/easylogging++.h>
#include <modules/graphics/resources/sprite_sheet.hpp>
#include <core/libs/json.hpp>
#include <modules/graphics/services/image_service.hpp>

using json = nlohmann::json;

void Blast2D::SpriteSheetLoader::loadFile(const Blast2D::ResourceConfigFile &&configFile) {
    LOG(INFO) << "module: " << configFile.module << " file: " << configFile.path;
    auto spriteJson = json::parse(configFile.content);

    std::string name = spriteJson["name"];
    std::string folder = spriteJson["folder"];

    SpriteSheetBuilder spriteSheetBuilder;
    spriteSheetBuilder.id = configFile.module + ":" + name;

    for(const auto & file:  resourceManager.getFilesFromFolder(configFile.folder + "/" + folder)){
        auto img = imageService.loadImage(configFile.module + ":" + fs::path(file).filename().string(), file);
        imageService.pack(spriteSheetBuilder, img);
    }

    resourceManager.emplace<SpriteSheet>(spriteSheetBuilder.id);
    SpriteSheet& spriteSheet = resourceManager.load<SpriteSheet>(spriteSheetBuilder.id);
    imageService.updateSpriteSheet(spriteSheet, spriteSheetBuilder);
}
