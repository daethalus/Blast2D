#ifndef SYSTEM_MANAGER_HPP
#define SYSTEM_MANAGER_HPP

#include <core/system/system.hpp>
#include <core/ecs/entity_manager.hpp>

#include <string>
#include <unordered_map>
#include <memory>


namespace Blast2D {

	struct SystemInformation {
		std::string name;
		std::unique_ptr<System> system;
		bool active;
		double mediumExecutionTime;
	};

	typedef std::unordered_map<std::string, SystemInformation> SystemRegister;

	class SystemManager {
	private:
		SystemRegister systems;		
	public:
		template<typename Sys>
		void add(std::string name);
		void update();
		void create();
	};

	template<typename Sys>
	inline void SystemManager::add(std::string name) {
		systems[name] = {name, std::make_unique<Sys>(), true, 0};
	}
}



#endif // !SYSTEM_MANAGER_HPP


