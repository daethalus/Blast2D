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

		template<typename Type>
		Storage<Type>& assure(const Index index) const {
			return static_cast<Storage<Type>&>(*pools[index].pool);
		}

	public:
		template<typename Type>
		void createComponent() {
			TypeInfo<Type>::index(pools.size());
			pools.push_back({std::unique_ptr<SparseSet>{new Storage<Type>()}});
		}

		template<typename Type>
		Index runtimeComponent() {
			auto size = pools.size();
			pools.push_back({ std::unique_ptr<SparseSet>{new Storage<Type>()} });
			return size;
		}

		template<typename Type>
		void createContainer() {
			TypeInfo<Type>::index(pools.size());
			pools.push_back({ std::unique_ptr<SparseSet>{new Storage<Type>()} });
		}

		Entity create() {
			return entityIdPool.generateId();
		}

		template<typename Func>
		void all(Entity entity, Func func) {

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
		void set(const Index index, const Entity entity, Type type) {
			this->assure<Type>(index).set(entity, type);
		}

		template<typename Type>
		Type& get(const Entity entity) {
			return this->assure<Type>().get(entity);
		}

		template<typename Type>
		Type& get(const Index index, const Entity entity) {
			return this->assure<Type>(index).get(entity);
		}

		template<typename Type>
		void remove(const Entity entity) {
			this->assure<Type>().destroy(entity);
		}

		template<typename Type>
		void remove(const Index index, const Entity entity) {
			this->assure<Type>(index).destroy(entity);
		}

		template<typename ...Types, typename Func>
		void forEach(Func func) {
			auto viewPools = std::make_tuple(&assure<Types>()...);
			auto firstPool = std::get<0>(viewPools);
			for (const auto entity: firstPool->data()) {
				if ((std::get<Storage<Types>*>(viewPools)->has(entity) && ...)) {
					//auto tuple = std::make_tuple(std::get<Storage<Types>*>(viewPools)->get(entity)...);
					//std::apply(func, tuple);
					func(std::get<Storage<Types>*>(viewPools)->get(entity)...);
				}
			}
		}
		
		template<typename ...Args, typename Func>
		void runtimeView(Func func, Args ...args) {
			std::vector<Index> components = { args... };
			view(std::move(func), std::move(components));
		}
		template<typename Func>
		void runtimeView(Func func, std::vector<Index> components) {
			for (const auto entity : pools[components[0]].pool->data()) {
				bool contains = true;
				for (auto i = components.size() - 1; i > 0; --i) {
					if (!pools[components[i]].pool->has(entity)) {
						contains = false;
						break;
					}
				}
				if (contains) func(entity);
			}						
		}
	};
	
}
#endif