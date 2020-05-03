#include "sprite_sheet_loader.hpp"
#include <core/logging/easylogging++.h>
#include <modules/graphics/resources/sprite_sheet.hpp>

void Blast2D::SpriteSheetLoader::loadFile(const Blast2D::ResourceConfigFile &&configFile) {
    LOG(INFO) << "module: " << configFile.module << " file: " << configFile.path << " content: " << configFile.content;
    SpriteSheet& spriteSheet = resourceManager.load<SpriteSheet>("game-test:character");

}
