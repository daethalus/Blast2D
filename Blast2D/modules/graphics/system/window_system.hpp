#ifndef WINDOW_SYSTEM_HPP
#define WINDOW_SYSTEM_HPP

#include <core/system/system.hpp>

namespace Blast2D {
	class WindowSystem : public System {

		virtual void onCreate() override;

		virtual void onUpdate() override;
	};
}

#endif


