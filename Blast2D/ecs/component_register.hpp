#ifndef ECS_COMPONENT_REGISTER_HPP
#define ECS_COMPONENT_REGISTER_HPP

#include <string>
#include <iostream>
#include <vector>

namespace Blast2D {

	struct CompInfo {
		std::size_t index;
		std::string name;		

		friend std::ostream& operator<<(std::ostream& os, CompInfo info) {
			os << "name: " << info.name << " index: " << info.index;
			return os;
		}
	};	
}

#endif // !ECS_COMPONENT_REGISTER_HPP
