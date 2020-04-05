#ifndef ECS_ENTITY_HPP
#define ECS_ENTITY_HPP

#include <vector>

namespace Blast2D {
	using Entity = std::uint32_t;
	constexpr auto NULL_ID = UINT_MAX;


	class EntityIdPool {

	public:
		std::vector<Entity> freeIds;
		Entity counter;

		EntityIdPool() {
			counter = 0;
		}
		Entity generateId() {
			if (freeIds.size() > 0) {
				auto id = freeIds.back();
				freeIds.pop_back();
				return id;
			}
			return counter++;
		}

		void freeEntity(Entity entity) {
			freeIds.emplace_back(std::move(entity));
		}
	};

}



#endif // !ECS_ENTITY_HPP


