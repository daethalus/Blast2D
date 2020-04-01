#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP

#include <ecs/component.hpp>
#include <ecs/entity.hpp>
#include <ecs/view.hpp>


#include <functional>

namespace Blast2D {
	class EntityManager {
	private:		

		ComponentRegister componentRegister;
		EntityPool entityPool;
		mutable std::vector<ComponentDataPool> pools;
		
		template <typename Type>
		ComponentDataPoolHandler<Type>& assure(Component component) {
			if (pools.size() <= component) {
				pools.resize(component + 1);
			}
			if (pools[component].pool == nullptr) {
				pools[component] = { new ComponentDataPoolHandler<Type>() };
			}
			return static_cast<ComponentDataPoolHandler<Type>&>(*pools[component].pool);
		}

	public:
		template <typename Type>
		ComponentInfo registerComponent(std::string name) {
			ComponentInfo info;
			info.id = typeid(Type).hash_code();
			info.name = name;
			componentRegister.registerNewComponent(info);
			return info;
		}

		Entity createEntity() {
			return entityPool.generate();
		}

		void destroyEntity(Entity entity) {
			entityPool.release(entity);
		}

		template <typename Type, typename... Args>
		void addComponentData(Entity entity, Args&&... args) {

			//{std::forward<Args>(args)...}
		}

		template<typename... Components>
		EntityView<Components...>  view() {
			return EntityView<Components...>();
		}
	};
}

#endif
