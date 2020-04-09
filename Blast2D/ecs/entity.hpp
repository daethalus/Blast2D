#ifndef ECS_ENTITY_HPP
#define ECS_ENTITY_HPP

#include <vector>

namespace Blast2D {
	using Entity = std::uint32_t;
	constexpr auto NULL_ID = WINT_MAX;


	class EntityIdPool {

	public:
		std::vector<Entity> entities;
		std::vector<Entity> freeIds;
		Entity counter;

		EntityIdPool() {
			counter = 0;
		}
		Entity generateId() {
			if (freeIds.size() == 0) {
				++counter;
				entities.emplace_back(counter);
			} else {
				entities.emplace_back(std::move(freeIds.back()));
				freeIds.pop_back();				
			}
			return entities.back();
		}

		void freeEntity(Entity entity) {
			freeIds.emplace_back(std::move(entity));
		}
	};

}



#endif // !ECS_ENTITY_HPP


