#ifndef ECS_COMPONENT_DATA_POOL
#define ECS_COMPONENT_DATA_POOL

#include <ecs/entity_set.hpp>
#include <functional>
#include <vector>


namespace Blast2D {

	template <typename Type>
	struct PoolItem {
		Entity id;
		Type instance;
	};

	struct PoolData {
		EntitySet* pool;
	};


	template <typename Type>
	class PoolHandler : public EntitySet {
	public:
		Type& get(Entity entity) {
			auto index = EntitySet::index(entity);
			if (index > -1) {
				return instances[index].instance;
			}
			throw std::invalid_argument("DEBUG: ALERT! entity " + std::to_string(entity) + " don't have this object!: " + typeid(Type).name());
		}

		BasicView view() override {
			BasicView view;
			if (instances.size() > 0) {
				for (std::size_t x = 0; x < instances.size(); ++x) {
					auto& item = instances[x];
					if (item.id != ENTITY_NULL_ID) {
						view.emplace_back(item.id);
					}
				}
			}
			return view;
		}

		void internalRemove(Entity pos, Entity entity) override {
			auto& poolInstance = instances[pos];
			for (const auto& removeEvent : removeEvents) {
				removeEvent(entity, poolInstance.instance);
			}
			poolInstance.id = ENTITY_NULL_ID;
		}

		void assign(Entity entity, Type& type) {
			this->assure(entity);
			auto index = EntitySet::index(entity);
			if (instances.size() <= index) {
				instances.resize(index + 1);
			}
			instances[index] = { entity, type };

			for (const auto& assignEvent : assignEvents) {
				assignEvent(entity, type);
			}
		}

		void registerOnAssignEvent(std::function<void(Entity, Type)> assignEvent) {
			assignEvents.push_back(assignEvent);
		}

		void registerOnRemoveEvent(std::function<void(Entity, Type)> removeEvent) {
			removeEvents.push_back(removeEvent);
		}

		std::vector<PoolItem<Type>> instances;

		std::vector<std::function<void(Entity, Type)>> assignEvents;
		std::vector<std::function<void(Entity, Type)>> removeEvents;
	};

	//-----------------------------singletons


	class Generic {
	};

	template <typename Type>
	class Singleton : public Generic {
	public:
		Type instance;
	};

	struct SingletonData {
		Generic* data;
	};
}

#endif
