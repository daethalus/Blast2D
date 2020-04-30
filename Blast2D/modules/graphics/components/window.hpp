#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <core/math/vector2.hpp>

namespace Blast2D {

	struct WindowProperties {		
		bool maximize = true;
		bool vsync = true;
		bool running = true;
		Vector2 size = { 800,600 };
		std::string title = "Blast2D";
	};

    BLAST_COMPONENT(WindowProperties);

	struct WindowHandler {
		void* handler;
		bool vsyncOn = false;
		bool maximized = false;
	};
    BLAST_COMPONENT(WindowHandler);
}

#endif


