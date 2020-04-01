#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <string>
#include <unordered_map>

#include <ecs/entity_set.hpp>

namespace Blast2D {
	using Component = std::uint32_t;

	class ComponentInfo {
	public:
		Component index;
		std::size_t id;
		std::string name;

		//template <typename T>
		//T operator[] (std::string name) {
		//	auto T::* asd;
		//	return asd;
		//}
	};

	class ComponentDataPool {
		EntitySet dataSet;
	};


	template <typename Type>
	class ComponentDataPoolHandler : public EntitySet {

	};

	class ComponentRegister {
	private:
		std::unordered_map <std::size_t, ComponentInfo> components;
		Component index;
	public:
		ComponentRegister() {
			index = 0;
		}
		void registerNewComponent(ComponentInfo& info) {
			info.index = index++;
			components[info.id] = info;
		}
	};
}

#endif




