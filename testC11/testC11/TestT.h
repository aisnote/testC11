#pragma once

#include <vector>
#include <memory>

class ITest
{
public:
	virtual void init() = 0;
	virtual void destroy() = 0;
	virtual bool doTest() = 0;
};


template<class BaseClass>
class TestT:public BaseClass, public std::enable_shared_from_this<BaseClass>
{
public:

	virtual void init() override;

	virtual void destroy() override
	{

	}

	virtual bool doTest() override
	{
		return false;
	}

};

using TestPtr = std::shared_ptr < ITest >;
using TestTPtrs = std::vector < TestPtr>;

static TestTPtrs g_Tests;


template<class BaseClass>
void TestT<BaseClass>::init()
{

}

#define TEST_CLASS(testClass)	\
	testClass a;


#define TEST_PTR()	\
auto ptr = shared_from_this();	\
g_Tests.emplace_back(ptr);

static inline void DoAllTest()
{
	for (const auto& test : g_Tests)
	{
		test->doTest();
	}
}

