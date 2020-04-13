#ifndef ECS_COMPONENT_REGISTER_HPP
#define ECS_COMPONENT_REGISTER_HPP

#include <string>
#include <iostream>
#include <vector>

namespace Blast2D {

	using Index = std::size_t;

	template<typename Type>
	struct TypeInfo {
		static Index index(Index index) {
			static const Index constIndex = index;
			return constIndex;
		}
		static Index index() {
			return index(0);
		}

	};
}

#endif // !ECS_COMPONENT_REGISTER_HPP
