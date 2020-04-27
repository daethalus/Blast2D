
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
        LapInfo(std::string _name, long long _time): name(_name), time(_time) {

        }
	};

	class Chronometer {
	private:
		std::vector<LapInfo>* laps;
	public:
        Chronometer() {
            laps = new std::vector<LapInfo>;
            laps->emplace_back("start", std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
        }
        ~Chronometer() {
            delete laps;
        }

		void lap() {
            laps->emplace_back("lap " + std::to_string(laps->size()), std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
		}

		void end() {
            laps->emplace_back("end", std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
			auto first = laps->at(0);
			auto previous = laps->at(0);
			for (auto x = 1; x < laps->size(); ++x) {
				auto now = laps->at(x);
				LOG(INFO) << "duration between " << previous.name << " and " << now.name << ": " << now.time - previous.time;
				previous = now;
			}
		}
		
	};
}
#endif


