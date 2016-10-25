#include "stdafx.h"
#include "TestStdMove.h"

#include <iostream>

//////////////////////////////////////////////////////////////////////////
//testClass
//////////////////////////////////////////////////////////////////////////

class TestClass
{
public:
	TestClass()
	{

	}

	virtual ~TestClass()
	{

	}

	TestClass(const TestClass& a)
	{
		std::cout << "copy constructor..." << std::endl;
	}
private:
	int *array {nullptr };
};


TestStdMove::TestStdMove()
{
	
}


TestStdMove::~TestStdMove()
{
}

bool TestStdMove::doTest()
{
	TestClass testClassA;
	TestClass testClassB(testClassA);


	return true;
}

/*TEST_CLASS(TestStdMove);*/