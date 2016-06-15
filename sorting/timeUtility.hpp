#include <chrono>
#include <iostream>

class Timer {
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> start;
	std::chrono::nanoseconds *duration;
public:
	Timer(std::chrono::nanoseconds *dur) : start(std::chrono::high_resolution_clock::now()), duration(dur) {};
	~Timer() {
		auto end = std::chrono::high_resolution_clock::now();
		*duration = end - start;
	}
};