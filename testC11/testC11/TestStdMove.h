#pragma once
#include "TestT.h"

class TestStdMove:public TestT<ITest>
{
public:
	TestStdMove();
	virtual ~TestStdMove();

	virtual bool doTest() override;
};



