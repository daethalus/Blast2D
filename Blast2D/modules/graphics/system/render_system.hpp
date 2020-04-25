#ifndef MESH_SYSTEM_HPP
#define MESH_SYSTEM_HPP

#include <core/system/system.hpp>
#include <modules/graphics/services/vertex_buffer_service.hpp>
#include <modules/graphics/services/shader_service.hpp>

namespace Blast2D {	
	class RenderSystem : public System, public Renderer {
	public:		
		virtual void onUpdate() override;

		// Inherited via Renderer
		virtual void onRenderer() override;
	};

	BLAST_SYSTEM(RenderSystem);

}

#endif


