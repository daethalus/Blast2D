#define ECS_VIEW_HPP

#include <vector>
#include <core/ecs/component_register.hpp>
#include <core/ecs/storage.hpp>

namespace Blast2D {

	class View {
	public:
		//std::tuple<PoolData> pools;				 
		
		template<typename... Types, typename Func>
		View& forEach(Func func) {





			//std::sort(components.begin(), components.end(), [this](const auto& first, const auto& second) {
			//	return this->pools[first.index].pool->size() > this->pools[second.index].pool->size();
			//});
			//const auto& comp = components.back();
			//components.pop_back();

			//for (const auto entity : pools[comp.index].pool->data()) {
			//	bool call = true;
			//	for (const auto actual : components) {
			//		if (!pools[actual.index].pool->has(entity)){
			//			call = false;
			//			break;
			//		}
			//	}

			//	if (call) {
			//		//std::make_tuple(pools[first.index].pool)


			//		//func(std::get<Storage<Types>*>(pools)->get(entity)...);
			//	}
			//}			
			return *this;
		}

		void wait() {

		}

	};
}