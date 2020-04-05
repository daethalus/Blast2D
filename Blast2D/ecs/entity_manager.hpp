#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP

#include <unordered_map>
#include <memory>
#include <functional>
#include <ecs/component_register.hpp>
#include <ecs/sparse_set.hpp>
#include <ecs/storage.hpp>


namespace Blast2D {

	struct PoolData {
		CompInfo info;
		std::unique_ptr<SparseSet> pool{};
	};


	class EntityManager {
	private:

		EntityIdPool entityIdPool;


		mutable std::vector<PoolData> pools{};

		template<typename Type>
		Storage<Type>& assure(CompInfo info) {
			return static_cast<Storage<Type>&>(*pools[info.index].pool);
		}
		
	public:		

		template<typename Type>
		CompInfo createComponent(std::string name) {
			auto info = CompInfo{ pools.size(), name };			
			pools.push_back({ info, std::unique_ptr<SparseSet>{new Storage<Type>()}});
			return info;
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
		void set(CompInfo info, Entity entity, Type& type) {
			this->assure<Type>(info).set(entity, type);
		}

		template<typename Type>
		Type& get(CompInfo info, Entity entity) {
			this->assure<Type>(info).get(entity);
		}



		void remove(CompInfo info, Entity entity) {

		}
	};
	
}
#endif