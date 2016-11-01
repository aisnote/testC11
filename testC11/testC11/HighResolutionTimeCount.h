#pragma once
#include <chrono>
#include <iostream>

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
        std::cout << "Cost = " << cost();
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



