#ifndef WINDOW_SYSTEM_HPP
#define WINDOW_SYSTEM_HPP

#include <core/system/system.hpp>

namespace Blast2D {
	class WindowSystem : public System {
		// Inherited via System
		virtual void onUpdate(EntityManager& entityManager) override;
	};
}

#endif


