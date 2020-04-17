#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <core/math/vector2.hpp>

namespace Blast2D {

	struct WindowProperties {
		Vector2 size = {800,600};
		bool maximize = false;
		bool vsync = true;
		bool running = true;
	};

	struct WindowHandler {
		void* handler;
	};
}

#endif


