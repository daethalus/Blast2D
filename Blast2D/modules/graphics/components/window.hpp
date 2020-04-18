#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <core/math/vector2.hpp>

namespace Blast2D {

	struct WindowProperties {		
		bool maximize = false;
		bool vsync = true;
		bool running = true;
		Vector2 size = { 800,600 };
	};

	struct WindowHandler {
		void* handler;
		bool vsyncOn = false;
		bool maximized = false;
	};
}

#endif


