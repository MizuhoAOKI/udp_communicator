#include <thread>
#include <chrono>
#include <iostream>
#include "udp_lib_switcher.hpp"
#include "json.hpp"
using namespace nlohmann;
#define INDENT_SPACE 2
#define SLEEP_TIME 100

int main()
{
	udp_lib::Sender<std::string> sender("127.0.0.1", 60000);

	std::string input;
	double time = 0;

	const int sleep_time = SLEEP_TIME; // [msec]

	std::cout << "Send every " << sleep_time / 1000.0 << " seconds" << std::endl;

	while (1)
	{
		// set control input in json format
		json input_json = 
		{
			{"time", time},
			{"control_input", {
				{"lateral",{
					{"steer_angle", 2.0}
				  }
				},
				{"longitudinal",{
					{"throttle",1.0},
					{"brake", 0.0}
				  }
				}
			  }
			}
		};

		input = input_json.dump(INDENT_SPACE);
		sender.udp_send(input);

		std::cout << input << std::endl;

		std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
		time += (double)sleep_time/1000;
	}

	return 0;
}