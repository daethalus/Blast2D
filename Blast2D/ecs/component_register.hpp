#ifndef ECS_COMPONENT_REGISTER_HPP
#define ECS_COMPONENT_REGISTER_HPP

#include <string>
#include <iostream>

namespace Blast2D {

	using Component = std::uint32_t;

	struct CompInfo {
		std::string name;
		Component component;

		friend std::ostream& operator<<(std::ostream& os, CompInfo info) {
			os << "name: " << info.name << " id: " << info.component;
			return os;
		}
	};


	class ComponentRegister {
	private:
		static Component index;
	public:
		template<typename Type>
		static CompInfo create(std::string name) {
			return { name, index++ };
		}
	};
	Component ComponentRegister::index = 0;
}

#endif // !ECS_COMPONENT_REGISTER_HPP
