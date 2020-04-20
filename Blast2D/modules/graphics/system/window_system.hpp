#ifndef WINDOW_SYSTEM_HPP
#define WINDOW_SYSTEM_HPP

#include <core/system/system.hpp>
#include <modules/graphics/services/vertex_buffer_service.hpp>
#include <modules/graphics/services/shader_service.hpp>

#include <core/system/system_manager.hpp>

namespace Blast2D {
	class WindowSystem : public System {
	public:

		VertexBufferService vertexBufferService;
		ShaderService shaderService;

		virtual void onCreate() override;

		virtual void onUpdate() override;
	};

	BLAST_SYSTEM(WindowSystem);
}

#endif


