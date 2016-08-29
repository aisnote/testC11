#pragma once
#include <chrono>

class HighResolutionTimeCount
{
public:
	HighResolutionTimeCount()
	{
		start = std::chrono::high_resolution_clock::now();
	};
	~HighResolutionTimeCount()
	{
		//end = std::chrono::high_resolution_clock::now();
	}

	double cost()
	{
		duration = std::chrono::high_resolution_clock::now() - start;
		return duration.count();
	}

private:
	std::chrono::time_point<std::chrono::steady_clock> start;
	std::chrono::time_point<std::chrono::steady_clock> end;
	std::chrono::duration<double> duration;
};



