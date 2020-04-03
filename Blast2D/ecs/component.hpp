#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <string>
#include <unordered_map>

namespace Blast2D {
	using Component = std::uint32_t;

	template <typename T>
	class Store {

	};

	class Data {
	public:
		template <typename T>
		Data& operator=(T&& other)& {
			auto asd = Store<T>();
			return *this;
		}
		template <typename T>
		void value(T value) {

		}
	};

	class ComponentInfo {
	public:
		Component index;
		std::size_t id;
		std::string name;

		std::unordered_map <std::string, Data> atributues;

		Data& operator[] (std::string name) {
			auto it = atributues.find(name);
			if (it == atributues.end()) {
				atributues[name] = {};
			}
			return atributues[name];
		}
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




