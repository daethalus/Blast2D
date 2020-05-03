#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP

#include <unordered_map>
#include <memory>
#include <functional>
#include <assert.h>

#include <core/ecs/component_register.hpp>
#include <core/ecs/sparse_set.hpp>
#include <core/ecs/storage.hpp>
#include <core/ecs/view.hpp>
#include "type_info.hpp"

#define BLAST_COMPONENT(T) const static bool component_##T = Blast2D::EntityManager::getInstance().createComponent<T>()

namespace Blast2D {

    struct Object {
        Index index;
    };

    template<typename Type>
    struct EventStorage : Object {
        std::vector<std::function<void(Type&)>> events;
    };

	class EntityManager {
	private:

		EntityManager(){}

		EntityIdPool entityIdPool;

		mutable std::vector<PoolData> pools{};

        mutable std::vector<std::unique_ptr<Object>> objects{};

		template<typename Type>
		Storage<Type>& assure() const {
		    const auto index = TypeInfo<Type>::index(-1);
            assert(pools.size() > index);
			return static_cast<Storage<Type>&>(*pools[index].pool);
		}

		template<typename Type>
		Storage<Type>& assure(const Index index) const {
			return static_cast<Storage<Type>&>(*pools[index].pool);
		}

        template<typename Type>
		Type& assureObject(){
            const auto index = TypeInfo<Type>::index(objects.size());
            if(index == objects.size()) {
                objects.push_back(std::make_unique<Type>());
            }
            return static_cast<Type&>(*objects[index]);
		}

	public:
		EntityManager(EntityManager const&) = delete;
		void operator=(EntityManager const&) = delete;

		static EntityManager& getInstance() {
			static EntityManager instance;
			return instance;
		}

		template<typename Type>
        bool createComponent() {
			TypeInfo<Type>::index(pools.size());
			pools.push_back({std::unique_ptr<SparseSet>{new Storage<Type>()}});
			return true;
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

		template<typename ...Types>
		Entity create(Types...args) {
			const auto entity = entityIdPool.generateId();
			((void)set(entity, args), ...);
			return entity;
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
        Type& assign(const Entity entity) {
            return this->assure<Type>().assign(entity);
        }

        void assign(const Entity entity, std::string componentName) {

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
		Type& last() {
			return this->assure<Type>().back();
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
        template<typename Type>
		void on(std::function<void(Type&)> event) {
            auto &eventStorage = assureObject<EventStorage<Type>>();
            eventStorage.events.push_back(event);
		}
        template<typename Type>
		void emit(Type& item) {
            auto &eventStorage = assureObject<EventStorage<Type>>();
            for(auto& event : eventStorage.events) {
                event(item);
            }
		}

		template<typename ...Types, typename Func>
		void forEach(Func func) {
			if constexpr (sizeof...(Types) == 1) {
				auto viewPools = std::make_tuple(&assure<Types>()...);
				for (const auto entity : std::get<0>(viewPools)->data()) {
					auto tuple = std::tie(std::get<Storage<Types>*>(viewPools)->get(entity)...);
					if constexpr (std::is_invocable_v<Func, decltype(tuple)>) {
						std::apply(func, tuple);
					} else {
						auto entityTuple = std::tuple_cat(std::make_tuple(entity), tuple);
						std::apply(func, entityTuple);
					}
				}
			} else {
				auto viewPools = std::make_tuple(&assure<Types>()...);
				auto firstPool = std::get<0>(viewPools);
				for (const auto entity : firstPool->data()) {
					if ((std::get<Storage<Types>*>(viewPools)->has(entity) && ...)) {

						auto tuple = std::tie(std::get<Storage<Types>*>(viewPools)->get(entity)...);
						if constexpr (std::is_invocable_v<Func, decltype(tuple)>) {
							std::apply(func, tuple);
						} else {
							auto entityTuple = std::tuple_cat(std::make_tuple(entity), tuple);
							std::apply(func, entityTuple);
						}
					}
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
    static EntityManager &entityManager = EntityManager::getInstance();
}
#endif