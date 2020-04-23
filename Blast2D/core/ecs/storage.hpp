#ifndef ECS_STORAGE_HPP
#define ECS_STORAGE_HPP

#include <vector>
#include <core/ecs/entity.hpp>
#include <core/ecs/sparse_set.hpp>
#include <type_traits>

#include <string>

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

        Type& assign(const Entity entity) {
            if constexpr (std::is_aggregate_v<Type>) {
                instances.push_back({});
            } else {
                instances.emplace_back(Type());
            }
            SparseSet::emplace(entity);
            return instances.back();
        }

		void destroy(const Entity entity) {
			auto other = instances.back();
			instances[this->index(entity)] = other;
			instances.pop_back();
			SparseSet::destroy(entity);
		}

		Type& get(const Entity entity) {
			return instances[this->index(entity)];
		}
		Type& back() {
			return instances[SparseSet::back()];
		}

	private:
		std::vector<Type> instances;
	};

}

#endif


