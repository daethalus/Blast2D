#ifndef BLAST2D_SPRITESHEETLOADER_HPP
#define BLAST2D_SPRITESHEETLOADER_HPP

#include <core/resource/resource_manager.hpp>

namespace Blast2D{

    class SpriteSheetLoader : public ResourceLoader {
    public:
        void loadFile(const ResourceConfigFile &&configFile) override;
    };

    BLAST_RESOURCE_LOADER(SpriteSheetLoader, spritesheet)
}

#endif
