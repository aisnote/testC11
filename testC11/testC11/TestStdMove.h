#pragma once
#include "TestT.h"

class TestStdMove:public TestT<ITest>
{
public:
	TestStdMove();
	virtual ~TestStdMove();
};

TEST_CLASS(TestStdMove);

