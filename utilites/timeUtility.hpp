#include <chrono>
#include <iostream>

template<class DurationType>
class Timer {
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> start;
	DurationType *duration;
public:
	Timer(DurationType *dur) : start(std::chrono::high_resolution_clock::now()), duration(dur) {};
	~Timer() {
		auto end = std::chrono::high_resolution_clock::now();
		*duration = std::chrono::duration_cast<DurationType>(end - start);
	}
};