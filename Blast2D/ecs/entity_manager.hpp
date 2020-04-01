#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP

#include <ecs/component.hpp>
#include <ecs/entity.hpp>
#include <ecs/view.hpp>
#include <ecs/component_data_pool.hpp>

#include <functional>

namespace Blast2D {
	class EntityManager {
	private:		
		ComponentRegister componentRegister;
		EntityPool entityPool;

		mutable std::vector<PoolData> pools;		
		std::unordered_map<Component, SingletonData> singletons;


		template <typename Type>
		Singleton<Type>& assureSingleton(Component component) {
			if (singletons.count(component) <= 0) {
				singletons[component] = { new Singleton<Type>() };
			}
			return static_cast<Singleton<Type>&>(*singletons[component].data);
		}

		template <typename Type>
		PoolHandler<Type>& assure(Component component) {
			if (pools.size() <= component) {
				pools.resize(component + 1);
			}
			if (pools[component].pool == nullptr) {
				pools[component] = { new PoolHandler<Type>() };
			}
			return static_cast<PoolHandler<Type>&>(*pools[component].pool);
		}

		BasicView internalView(std::vector<Component> comps) {
			if (comps.size() > 1) {
				BasicView entities;
				auto first = pools[comps[0]].pool;
				auto pos = 0;

				for (int x = 1; x < comps.size(); ++x) {
					if (pools[comps[x]].pool->size() < first->size()) {
						first = pools[comps[x]].pool;
						pos = x;
					}
				}
				comps.erase(comps.begin() + pos);

				for (const auto& entity : first->view()) {
					bool found = true;
					for (const auto& comp : comps) {
						if (!pools[comp].pool->entityIn(entity)) {
							found = false;
							break;
						}
					}
					if (found) {
						entities.push_back(entity);
					}
				}
				return entities;
			} else {
				return pools[comps[0]].pool->view();
			}
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

		template <typename Type>
		Component getComponent() {
			return componentRegister.get(typeid(Type).hash_code()).index;			
		}
		
		template <typename Type>
		void assign(Entity entity, Type instance) {
			auto comp = getComponent<Type>();
			auto& pool = this->assure<Type>(comp);
			pool.assign(entity, instance);
		}

		template <typename Type>
		Type& get(Entity entity) {					
			return this->assure<Type>(getComponent<Type>()).get(entity);
		}
	};
}

#endif
