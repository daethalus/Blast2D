#ifndef ECS_STORAGE_HPP
#define ECS_STORAGE_HPP

#include <vector>
#include <ecs/entity.hpp>
#include <ecs/sparse_set.hpp>
#include <type_traits>

namespace Blast2D {

	struct PoolData {
		std::unique_ptr<SparseSet> pool{};		
	};


	template <typename Type>
	class Storage : public SparseSet {
	public:
		void set(const Entity entity, Type & type) {
			if constexpr (std::is_aggregate_v<Type>) {
				instances.push_back(std::move(type));
			} else {
				instances.emplace_back(std::move(type));
			}
			SparseSet::emplace(entity);
		}

		void destroy(const Entity entity) {
			auto other = std::move(instances.back());
			instances[this->index(entity)] = std::move(other);
			instances.pop_back();
			SparseSet::destroy(entity);
		}

		Type& get(const Entity entity) {
			return instances[this->index(entity)];
		}

	private:
		std::vector<Type> instances;
	};

}

#endif


