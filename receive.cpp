#include <iostream>
#include <chrono>
#include <thread>
#include "udp_lib_switcher.hpp"
#include "json.hpp"
using namespace nlohmann;
#define SLEEP_TIME 100

int main()
{
	udp_lib::Receiver<std::string> receiver(60000);

	std::string input;
	json input_json;

	const int sleep_time = SLEEP_TIME; // [msec]

	std::cout << "Receive every " << sleep_time / 1000.0 << " seconds" << std::endl;

	while (1)
	{
		if (receiver.udp_receive(&input))
		{
			input_json = json::parse(input);
			std::cout << input << std::endl;
			// access parsed json object :
			std::cout << "time = " << input_json["time"] << std::endl;
			std::cout << "steer_angle = " << input_json["control_input"]["lateral"]["steer_angle"] << std::endl;
			std::cout << "throttle = " << input_json["control_input"]["longitudinal"]["throttle"] << std::endl;		
			std::cout << "brake = " << input_json["control_input"]["longitudinal"]["brake"] << std::endl;		
		}
		else
		{
			std::cout << "Not receive new msg yet." << std::endl;
		}
		// sleep for a while
		std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
	}
	return 0;
}