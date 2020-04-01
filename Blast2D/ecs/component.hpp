#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <string>
#include <unordered_map>

namespace Blast2D {
	using Component = std::uint32_t;

	class ComponentInfo {
	public:
		Component index;
		std::size_t id;
		std::string name;
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

		ComponentInfo get(std::size_t id) {
			return components[id];
		}
	};
}

#endif




