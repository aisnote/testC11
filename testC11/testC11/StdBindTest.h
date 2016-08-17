#pragma once

class StdBindTest
{
public:
	static StdBindTest*	instance()
	{
		static StdBindTest gStdBindTest;
		return &gStdBindTest;
	};
	void TEST();
	void onClick();
private:
	StdBindTest();
	virtual ~StdBindTest();

};

