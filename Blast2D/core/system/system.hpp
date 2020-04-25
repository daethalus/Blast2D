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

    class BaseSystem {
    public:
        EntityManager& entityManager = EntityManager::getInstance();
        virtual void onCreate() {};        
    };

	class Renderer {
	public:
		virtual void onRenderer() = 0;
	};

	class Updater {
	public:
		virtual void onUpdate() = 0;
	};

	class System : public BaseSystem, public Updater { };

	template<typename Type>
	struct SystemInformation {
		std::string name;
		std::shared_ptr<Type> system;
		bool active;
		double mediumExecutionTime;
	};

	typedef std::unordered_map<std::string, SystemInformation<BaseSystem>> SystemRegister;
	typedef std::unordered_map<std::string, SystemInformation<Updater>> UpdaterRegister;
	typedef std::unordered_map<std::string, SystemInformation<Renderer>> RendererRegister;

	class SystemManager {
	private:
		SystemManager(){}
		SystemRegister systems;
		UpdaterRegister updaters;
		RendererRegister renderers;
	public:
		SystemManager(SystemManager const&) = delete;
		void operator=(SystemManager const&) = delete;

		static SystemManager& getInstance() {
			static SystemManager instance;
			return instance;
		}

		void onUpdate();
		void onCreate();
		void onRenderer();

		template<typename Sys>
		static bool registerSystem(std::string name);
	};

	template<typename Sys>
	inline bool SystemManager::registerSystem(const std::string name) {
		LOG(INFO) << name << " registered";
		auto pointer = std::make_shared<Sys>();
		getInstance().systems[name] = { name, pointer , true, 0 };
		if constexpr (std::is_base_of<Updater, Sys>::value) {
			getInstance().updaters[name] = { name, std::static_pointer_cast<Updater>(pointer), true, 0 };
		}
		if constexpr (std::is_base_of<Renderer, Sys>::value) {
			getInstance().renderers[name] = { name, std::static_pointer_cast<Renderer>(pointer), true, 0 };
		}
		return true;
	}	
}

#endif // !SYSTEM_MANAGER_HPP


