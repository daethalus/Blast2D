#include <iostream>
#include <logging/easylogging++.h>
#include <logging/chronometer.hpp>
#include <ecs/entity_manager.hpp>
#include <functional>

INITIALIZE_EASYLOGGINGPP

template<typename>
struct fnv1a_traits;

template<>
struct fnv1a_traits<std::uint32_t> {
	using type = std::uint32_t;
	static constexpr std::uint32_t offset = 2166136261;
	static constexpr std::uint32_t prime = 16777619;
};

template<typename Type>
struct TestX {

	using traits_type = fnv1a_traits<std::uint32_t>;

	static constexpr std::uint32_t helper(const char* curr) {
		auto value = traits_type::offset;

		while (*curr != 0) {
			value = (value ^ static_cast<traits_type::type>(*(curr++)))* traits_type::prime;
		}

		return value;
	}

	constexpr static std::uint32_t id(std::string str) {
		return helper(str.c_str());
	}

	constexpr static std::uint32_t id() {
		//return helper(__FUNCSIG__);
		return helper(typeid(Type).name());
	}

};

struct Test {
	int value;
};

struct Position {
	int value;
};

struct Data {
	std::uint32_t id;
	int value;
};

int main() {

	std::vector<Data> pools(2);

	pools[1] = { TestX<Position>::id(), 10 };

	LOG(INFO) << "Starting engine";

	Blast2D::EntityManager entityManager;
	Blast2D::ComponentRegister reg;

	LOG(INFO) << TestX<Position>::id("asd");
	LOG(INFO) << TestX<Position>::id();
	LOG(INFO) << TestX<Test>::id();
		
	auto chrono = Blast2D::Chronometer::create();	

	auto hash = std::hash<std::string>();

	for (int x = 0; x <= 380; ++x) {
		Blast2D::ComponentInfo info = { x, hash(std::to_string(x)),std::to_string(x) };
		reg.registerNewComponent(info);
	}

	for (auto x = 0; x <= 999999; ++x) {


		static std::size_t index{ pools.size() };
		if (const auto length = pools.size(); !(index < length) || pools[index].id != TestX<Position>::id()) {
			for (index = {}; index < length && pools[index].id != TestX<Position>::id(); ++index);
		}

		if (pools[index].value != 10) {
			LOG(INFO) << "DEU RUIM";
		}
	
	}

	chrono.lap();

	for (auto x = 0; x <= 999999; ++x) {
		reg.get(typeid(Position).hash_code());
		if (pools[1].value != 10) {
			LOG(INFO) << "DEU RUIM";
		}
	}


	//entityManager.view<Test>().each();
	



	chrono.end();
	std::string asd;
	std::cin >> asd;




}
