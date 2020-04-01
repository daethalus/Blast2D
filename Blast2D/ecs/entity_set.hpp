#ifndef ECS_ENTITY_SET
#define ECS_ENTITY_SET

#include <ecs/entity.hpp>

constexpr auto ENTITY_SIZE = 1000000;

namespace Blast2D {
	class EntitySet {
	public:
		std::vector<Entity> entities;


		EntitySet() {
			entities.resize(ENTITY_SIZE);
			for (auto x = 0; x < entities.size(); x++) {
				entities[x] = ENTITY_NULL_ID;
			}
			counter = 0;
		}

		int index(Entity entity) {
			return entities[entity];
		}

		void assure(Entity entity) {
			if (entities[entity] == ENTITY_NULL_ID) {
				if (freeIds.size() > 0) {
					entities[entity] = freeIds.back();
					freeIds.pop_back();
				} else {
					entities[entity] = counter++;
				}
			}
		}

		bool entityIn(Entity entity) {
			return entities[entity] != ENTITY_NULL_ID;
		}

		virtual int size() {
			return counter - freeIds.size();
		}

		virtual void internalRemove(Entity pos, Entity entity) {

		}

		bool contains(Entity entity) {
			auto id = entities[entity];
			return (id != ENTITY_NULL_ID);
		}

		void remove(Entity entity) {
			auto id = entities[entity];
			if (id == ENTITY_NULL_ID) return;

			freeIds.push_back(id);
			entities[entity] = ENTITY_NULL_ID;
			internalRemove(id, entity);
		}
		virtual BasicView view() {
			return entities;
		}

	private:
		int counter;
		std::vector<Entity> freeIds;
	};
}
#endif
