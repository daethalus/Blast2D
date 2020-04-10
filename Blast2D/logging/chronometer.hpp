
#ifndef CHRONOMETER_HPP
#define CHRONOMETER_HPP

#include <chrono>
#include <vector>
#include <string>

//#include <logging/easylogging++.h>

namespace Blast2D {

	struct LapInfo{
		std::string name;
		long long time;
	};

	class Chronometer {
	private:
		std::vector<LapInfo> laps;
		Chronometer() {
			laps.push_back({"start", std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count()});
		}
	public:		
		static Chronometer create() {			
			return Chronometer();
		}

		void lap() {
            laps.push_back({"lap " + std::to_string(laps.size()), std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count()});
		}

		void end() {
            laps.push_back({"end", std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count()});

			auto first = laps[0];
			auto previous = laps[0];

			for (auto x = 1; x < laps.size(); ++x) {
				auto now = laps[x];

				LOG(INFO) << "duration between " << previous.name << " and " << now.name << ": " << now.time - previous.time;
				previous = now;
			}
		}
		
	};
}
#endif


