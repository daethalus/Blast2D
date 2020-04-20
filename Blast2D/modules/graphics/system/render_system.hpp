#ifndef MESH_SYSTEM_HPP
#define MESH_SYSTEM_HPP

#include <core/system/system.hpp>
#include <modules/graphics/services/vertex_buffer_service.hpp>
#include <modules/graphics/services/shader_service.hpp>
#include <core/system/system_manager.hpp>

namespace Blast2D {	
	class RenderSystem : public System {		
	public:
		VertexBufferService vertexBufferService;
		ShaderService shaderService;
		virtual void onUpdate() override;
	};

	BLAST_SYSTEM(RenderSystem);

}

#endif


