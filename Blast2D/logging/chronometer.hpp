
#ifndef CHRONOMETER_HPP
#define CHRONOMETER_HPP

#include <chrono>
#include <vector>
#include <string>

#include <logging/easylogging++.h>

namespace Blast2D {

	struct LapInfo{
		std::string name;
		std::chrono::time_point<std::chrono::steady_clock> time;
	};

	class Chronometer {
	private:
		std::vector<LapInfo> laps;
		Chronometer() {
			laps.push_back({"start", std::chrono::high_resolution_clock::now()});
		}
	public:		
		static Chronometer create() {			
			return Chronometer();
		}

		void lap() {
			laps.push_back({ "lap " + std::to_string(laps.size()), std::chrono::high_resolution_clock::now() });
		}

		void end() {
			laps.push_back({ "end", std::chrono::high_resolution_clock::now() });

			auto first = laps[0];
			auto previous = laps[0];

			for (auto x = 1; x < laps.size(); ++x) {
				auto now = laps[x];

				LOG(INFO, "Chronometer") << "duration between " << previous.name << " and " << now.name << ": "
					<< std::chrono::duration_cast<std::chrono::milliseconds>(now.time - previous.time).count();
				previous = now;
			}
		}
		
	};
}
#endif


