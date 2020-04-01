#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <vector>

namespace Blast2D {

	constexpr auto ENTITY_NULL_ID = UINT_MAX;

	using Entity = std::uint32_t;
	using BasicEntityView = std::vector<Entity>;

	class EntityPool {

	public:
		std::vector<Entity> freeEntitities;
		Entity counter;

		EntityPool() {
			counter = 0;
		}
		Entity generate() {
			if (freeEntitities.size() > 0) {
				auto id = freeEntitities.back();
				freeEntitities.pop_back();
				return id;
			}
			return counter++;
		}

		void release(Entity entity) {
			freeEntitities.push_back(entity);
		}
	};
}
#endif // !ENTITY_HPP



