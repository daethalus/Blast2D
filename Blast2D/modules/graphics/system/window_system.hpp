#ifndef WINDOW_SYSTEM_HPP
#define WINDOW_SYSTEM_HPP

#include <core/system/system.hpp>
#include <modules/graphics/services/vertex_buffer_service.hpp>
#include <modules/graphics/services/shader_service.hpp>

namespace Blast2D {
	class WindowSystem : public System {
	public:

        void preInit() override;

        virtual void onCreate() override;

		virtual void onUpdate() override;

        void onDestroy() override;
    };

	BLAST_SYSTEM(WindowSystem);
}

#endif


