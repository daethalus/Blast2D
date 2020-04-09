#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP

#include <unordered_map>
#include <memory>
#include <functional>
#include <ecs/component_register.hpp>
#include <ecs/sparse_set.hpp>
#include <ecs/storage.hpp>
#include <ecs/view.hpp>


namespace Blast2D {

	class EntityManager {
	private:

		EntityIdPool entityIdPool;

		mutable std::vector<PoolData> pools{};

		template<typename Type>
		Storage<Type>& assure() const {
			return static_cast<Storage<Type>&>(*pools[TypeInfo<Type>::index(0)].pool);
		}

	public:
		template<typename Type>
		void createComponent() {
			TypeInfo<Type>::index(pools.size());
			pools.push_back({std::unique_ptr<SparseSet>{new Storage<Type>()}});
		}

		Entity create() {
			return entityIdPool.generateId();
		}

		void destroy(Entity entity) {
			for (auto pos = pools.size(); pos; --pos) {
				if (auto& pdata = pools[pos - 1]; pdata.pool->has(entity)) {
					pdata.pool.get()->destroy(entity);
				}
			}
			entityIdPool.freeEntity(entity);
		}

		template<typename Type>
		void set(const Entity entity, Type type) {
			this->assure<Type>().set(entity, type);
		}

		template<typename Type>
		Type& get(const Entity entity) {
			return this->assure<Type>().get(entity);
		}

		template<typename Type>
		void remove(const Entity entity) {
			this->assure<Type>().destroy(entity);
		}

		template<typename ...Types, typename Func>
		void forEach(Func func) {
            auto tuple = std::make_tuple(assure<Types>().get(1)...);
			std::apply(func, tuple);
		}
	};
	
}
#endif