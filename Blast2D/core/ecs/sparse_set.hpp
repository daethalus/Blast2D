#ifndef ECS_SPARSE_SET_HPP
#define ECS_SPARSE_SET_HPP

#include <vector>
#include <memory>

#include <core/ecs/entity.hpp>

namespace Blast2D {


	class SparseSet {

		static constexpr auto page_size = 32768 / sizeof(Entity);

		auto page(const Entity entt) const {
			return std::size_t{ (entt & 0xFFFFF) / page_size };
		}

		auto offset(const Entity entt) const {
			return std::size_t{ entt & (page_size - 1) };
		}

		Entity* assure(const std::size_t pos) {
			if (!(pos < reverse.size())) {
				reverse.resize(pos + 1);
			}

			if (!reverse[pos]) {
				reverse[pos] = std::make_unique<Entity[]>(page_size);
				std::fill_n(reverse[pos].get(), page_size, NULL_ID);
			}

			return reverse[pos].get();
		}


	public:		
		Entity index(const Entity entity) const {
			return reverse[page(entity)][offset(entity)];
		}

		void emplace(const Entity entity) {
			assure(page(entity))[offset(entity)] = direct.size();
			direct.emplace_back(entity);
		}

		void destroy(const Entity entity) {			
			const auto curr = page(entity);
			const auto pos = offset(entity);
			direct[reverse[curr][pos]] = direct.back();
			reverse[page(direct.back())][offset(direct.back())] = reverse[curr][pos];
			reverse[curr][pos] = NULL_ID;
			direct.pop_back();
		}

		bool has(const Entity entity) const {
			const auto curr = page(entity);
			return (curr < reverse.size() && reverse[curr] && reverse[curr][offset(entity)] != NULL_ID);
		}
		std::size_t size() {
			return direct.size();
		}

		std::vector<Entity>& data() {
			return direct;
		}

		Entity back() {
			return this->index(direct.back());
		}

	private:
		std::vector<std::unique_ptr<Entity[]>> reverse;
		std::vector<Entity> direct;
	};
}




#endif
