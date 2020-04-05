#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP

#include <unordered_map>
#include <memory>
#include <functional>
#include <ecs/component_register.hpp>


namespace Blast2D {

	class EntityManager {
	private:

	public:		
		template<typename Type>
		static CompInfo component(std::string name) {
			return ComponentRegister::create<Type>(name);
		}

	};
	
}
#endif