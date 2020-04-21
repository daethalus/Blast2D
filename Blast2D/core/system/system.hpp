#ifndef SYSTEM_MANAGER_HPP
#define SYSTEM_MANAGER_HPP

#include <core/system/system.hpp>
#include <core/ecs/entity_manager.hpp>

#include <string>
#include <unordered_map>
#include <memory>

#include <core/logging/easylogging++.h>

#define BLAST_SYSTEM(T) bool system_##T = Blast2D::SystemManager::registerSystem<T>(#T)

namespace Blast2D {

    class System {
    public:
        EntityManager& entityManager = EntityManager::getInstance();
        virtual void onCreate() {};
        virtual void onUpdate() = 0;
    };

	struct SystemInformation {
		std::string name;
		std::unique_ptr<System> system;
		bool active;
		double mediumExecutionTime;
	};

	typedef std::unordered_map<std::string, SystemInformation> SystemRegister;

	class SystemManager {
	private:
		SystemManager(){}
		SystemRegister systems;
	public:
		SystemManager(SystemManager const&) = delete;
		void operator=(SystemManager const&) = delete;

		static SystemManager& getInstance() {
			static SystemManager instance;
			return instance;
		}

		void update();
		void create();

		template<typename Sys>
		static bool registerSystem(std::string name);
	};

	template<typename Sys>
	inline bool SystemManager::registerSystem(const std::string name) {
		LOG(INFO) << name << " registered";
		getInstance().systems[name] = { name, std::make_unique<Sys>(), true, 0 };
	//	systems[name] = { name, std::make_unique<Sys>(), true, 0 };
		return true;
	}	
}

#endif // !SYSTEM_MANAGER_HPP


