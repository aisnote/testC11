// testC11.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"


//#include "stdio.h"
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <thread>

#include <functional>
#include <memory>
#include <mutex>
#include <set>
#include <algorithm>
#include <cmath>
#include <ostream>
#include <iomanip>
#include <iosfwd>
#include <sstream>
#include <regex>

#include "StdBindTest.h"
#include "HighResolutionTimeCount.h"
#include "ParamTypeTemplate.h"

#include "TestStdMove.h"
#include "TestSharePtr.h"
#include "TestRegex.h"

using namespace std;

//class
class iAmClass
{
	int a;
	int b;
public:
	iAmClass(int i, int j)
	{
		a = i;
		b = j;
	}
};


//c11 only class
class iAm11class{
	int a[4];
public:
	iAm11class() {};// : a{ 1, 2, 3, 4 }{}; //c11, member array initializer: can not pass the building
};

//c11 container
void	test_Container_initializer()
{
    std::vector<std::string> vs = { "first", "second", "third" };
    std::map<std::string, std::string> singers =
	{ { "Lady Gaga", "+1 (212) 555-7890" },
	{ "Beyonce Knowles", "+1 (212) 555-0987" } };
}

//c11 in-class initialization
class C11_in_class_initialization{
	int a = 7;  //c11 only
public:
	C11_in_class_initialization(){};
};

//demo c11 default function
/*!
 * \class aStru
 *
 * \brief is called a defaulted function. The =default;
 *	part instructs the compiler to generate the default implementation for the function.
 *	Defaulted functions have two advantages: They are more efficient than manual implementations,
 *	and they rid the programmer from the chore of defining those functions manually.
 *
 * \author liuliu
 * \date March 2016
 */
struct  aStru
{
	aStru() = default;
	virtual ~aStru() = default;

	//!The opposite of a defaulted function is a deleted function :
	int func() = delete;
};

/*!
 * \class test_NoCopy_use_delete_function
 *
 * \brief Deleted functions are useful for preventing object copying, among the rest. Recall that C++ automatically declares a copy constructor and an assignment operator for classes. To disable copying, declare these two special member functions =delete:
 *
 * \author liuliu
 * \date March 2016
 */
struct test_NoCopy_use_delete_function
{
	test_NoCopy_use_delete_function() = default;
	test_NoCopy_use_delete_function & operator = (const test_NoCopy_use_delete_function &) = delete;
	test_NoCopy_use_delete_function(const test_NoCopy_use_delete_function &) = delete;
};


/*!
* \class Afterdoc_Test
*
* \brief demo how to use doxygen comments.
*
* \author liuliu
* \date March 2016
*/
class Afterdoc_Test
{
public:
	/** An enum type.
	*  The documentation block cannot be put after the enum!
	*/
	enum EnumType
	{
		EVal1,     /**< enum value 1 */
		EVal2      /**< enum value 2 */
	};
	void member();   //!< a member function.

protected:
	int value;       /*!< an integer value */
};


/*!
 * \class test_c11
 *
 * \brief test some c11's features
 *
 * \author liuliu
 * \date March 2016
 */
class test_c11
{
public:
	test_c11() = default;
	virtual ~test_c11() = default;

	//!run all test
	void run_all_test()
	{
		test_delete_function();
		test_nullptr();
	}

	// make API-like so that Doxygen can generate these APIs documents
public:
	//!test delete function
	void test_delete_function()
	{
		//test_NoCopy_use_delete_function a;
		//! test_NoCopy_use_delete_function b(a);  // cannot complie
	}

	//!test_nullptr
	/*! \brief nullptr is applicable to all pointer categories, including function pointers and pointers to members:
	 */
	void	test_nullptr()
	{
		func(0);		//! do not know which to call: func(int) or func(char*) on some complier
		func(nullptr);  //! will call func(char*)
	}

	//!test_lambda
	/*! \brief lambda expression
	 */
	void	test_lambda()
	{
		char s[] = "hEEllo world!";
		int UpperCase = 0;

		// lambda expression
        std::for_each(s, s + sizeof(s), [&UpperCase](char c){
			if (isupper(c))
				UpperCase++;
		});

        //cout << UpperCase << " uppercase letters in : " << s << endl;
	}


protected:
	void	func(int)
	{
		//cout << "call int_func(int)" << endl;
	}

	void	func(char *)
	{
		//cout << "call int_func(char *)" << endl;
	}
private:

};

/*!
 * \class test_delegating_ctor
 *
 * \brief n C++11 a constructor may call another constructor of the same class:
 *
 * \author liuliu
 * \date March 2016
 */
class test_delegating_ctor
{
	int x, y;
	char *p;
public:
	//! #1 target
	test_delegating_ctor(int v) :x(v), y(0), p(new char[128]) {};
	//! #2
	test_delegating_ctor() : test_delegating_ctor(0) {}
	~test_delegating_ctor();

private:

};

//! test dynamic_cast
namespace TEST_CAST {
	class A
	{
	public:
		virtual void foo()
		{
            std::cout << "call from A::foo()" << std::endl;
		};
	};

	class B
	{
	public:
		virtual void foo()
		{
            std::cout << "call from B::foo()" << std::endl;
		};
	};

	void test()
	{
		A* pA = new A();
		pA->foo();

		B* pB = new B();
		pB->foo();

		//void* pV = dynamic_cast<void*>(pA);

		A* pADynamic = dynamic_cast<A*>(pB);
		if (pADynamic)
			pADynamic->foo();
	}

	class ClassParent
	{
	public:
		void test()
		{
            std::cout << "ClassParent::test();" << std::endl;
		}
	};

	class ClassParentChild : public ClassParent
	{
	public:
		void test()
		{
			std::cout << "ClassParentChild::test();" << std::endl;
		}
	};

	class ClassParentChildSon : public ClassParentChild
	{
	public:
		void test()
		{
			std::cout << "ClassParentChildSon::test();" << std::endl;
		}
	};

	void test_parent_son(ClassParentChildSon* lpClassParentChildSon)
	{
		if (lpClassParentChildSon == nullptr)
			return;

		ClassParentChild* pClassParentChild = dynamic_cast<ClassParentChild*>(lpClassParentChildSon);
		if (pClassParentChild)
			pClassParentChild->test();

		ClassParent* pClassParent = dynamic_cast<ClassParent*>(lpClassParentChildSon);
		if (pClassParent)
			pClassParent->test();

	}

}; //namespace TEST_CAST

//! test lambda
namespace TEST_LAMBDA {
	std::vector<int> const v = { 1, 2, 3, 4, 5 };

	// 	for_each( begin(v), end(v), [](int const n){
	// 		std::cout << n << endl;
	// 	});

	//std::thread t([]{ std::cout << "Hello std::thread"; });

	void abssort(float *x, unsigned N)
	{
		std::sort(x,
			x + N,
			[](float a, float b) { return std::abs(a) < std::abs(b); });   // value, decltype to float
	}

	void TEST_SORT()
	{
		float fArray[8] = {1.0,3.0,4.0,2.0, 8.0, 7.0,6.0,5.0};
		abssort(fArray, 8);

	}

	void TEST() {
		float f0 = 1.0;
		std::cout << [=](float f) mutable { return f0 += std::abs(f); } (-3.5);    //because mutable, so that can passed the compiling
		std::cout << '\n' << f0 << '\n';   //output 1.0 because above is [=] means pass the value.

		std::cout << [](float f) { return std::abs(f); } (-3.5);  //should output 3.5
	}
};

namespace TEST_OVERRIDE{

	class Parent
	{
	public:
		virtual void test_func() { std::cout << "hello from Parent" << endl; };
		virtual int test_func(int)
		{
			std::cout << "hello from Parent, ret = int" << endl;
			return 0;
		};
	};

	class ParentChild : public Parent
	{
	public:
		virtual void test_func() override { std::cout << "hello from ParentChild" << endl; };
		//virtual int test_func() override { std::cout << "hello from ParentChild" << endl; };
	};

	void TEST()
	{
		ParentChild oneParentChild;
		oneParentChild.test_func();
	};
};

namespace TEST_PTR
{
	struct Person {
		std::string strId;
		std::string strName;
	};

	using PersonPtr = std::shared_ptr <Person>;
	PersonPtr	mPersonPtr;
	void SetPerson(const PersonPtr& person)
	{
		mPersonPtr = person;
	}

	PersonPtr GetPerson()
	{
		return mPersonPtr;
	}

	struct Contact {
		Contact()
		{
			strID = "2";
		};
		std::string strID;
		std::string strName;
	};

	//struct Contact;
	using ContactPtr = std::shared_ptr < Contact >;

	ContactPtr mContactPtr;

	void TEST()
	{
		Person aP;
		aP.strId = "1234";
		aP.strName = "name";

		mContactPtr = std::make_shared<Contact>();

		mContactPtr->strID = "1234";
		std::cout << mContactPtr->strID.c_str();
		//SetPerson(std::make_shared<PersonPtr>(aP));
		//cout << GetPerson()->strId.c_str();
	}


};


namespace TEST_SET
{
	bool b1()
	{
		return true;
	}

	bool b2()
	{
		return false;
	}

	void TEST()
	{

		if (!b1() || !b2())
		{
			int i = 0;
            i++;
		}



		std::set<int> s;

		for (int i = 0; i < 200; i++)
		{
			s.insert(i);
		}

		for (int i = 0; i < 200; i++)
		{
			s.insert(i);  //will ignore the duplicated.
		}
	}
}

struct DialInNumber
{
	DialInNumber() {};
	DialInNumber(const std::string& number, bool tollFree) :number(number), tollFree(tollFree) { };
	std::string number;
	bool tollFree{ false };
};

using DialInNumbers = std::vector<DialInNumber>;

namespace TEST_EMPLACE
{
	const int count = 20000;
	void TEST()
	{
		DialInNumbers numbers;
		{
			HighResolutionTimeCount hrtc;
			for (int i = 0; i < count; i++)
			{
				numbers.emplace_back("test",false);
			}

			cout << "emplace_back cost1: " << hrtc.cost() << endl;
		}

		{
			HighResolutionTimeCount hrtc;
			for (int i = 0; i < count; i++)
			{
				numbers.push_back({ "test",false });
			}

			cout << "push_back cost2: " << hrtc.cost() << endl;
		}

		std::vector<std::string> vs;
		{
			HighResolutionTimeCount hrtc;
			for (int i = 0; i < count; i++)
			{
				vs.push_back("test");
			}

			cout << "push_back cost: " << hrtc.cost() << endl;
		}

		{
			HighResolutionTimeCount hrtc;
			for (int i = 0; i < count; i++)
			{
				vs.emplace_back("test");
			}

			cout << "emplace_back cost: " << hrtc.cost() << endl;
		}
	}
}


#include <atomic>
#include <memory>
struct Message {
	int n;
};

using MessagePtr = std::shared_ptr<Message>;
using Messages = std::vector <MessagePtr>;

#define SPARKPROPERTY(Type, SingleType, Name, GetterName) public:\
	Type GetterName() const{\
		std::lock_guard<std::mutex> lock(mDataAccessMutex);\
		return Name; }\
	protected:\
		Type Name;

struct ProtectClass
{
	SPARKPROPERTY(Messages, MessagePtr, messages, getMessages)

private:
	mutable std::mutex mDataAccessMutex;
};

using ProtectClassPtr = std::shared_ptr<ProtectClass>;

#define RUN_ALL_TESTS()	DoAllTest()


#define PROTOCOL(scheme) L"URL: #scheme protocol"

#ifndef _WIN32
            int main(int argc, const char * argv[])
#else
            int _tmain(int argc, _TCHAR* argv[])
#endif
            
{
                
    int size = 100;
    std::unique_ptr<char[]> statusPtr = std::make_unique<char[]>(size);

    
    {
        std::string s("this subject has a subjmarine as a subjsequence subjmite");
        std::smatch m;
        std::regex e("\\b(subj)([^ ]*)");    

        std::cout << "target: " << s << std::endl;
        std::cout << "regex: /\\b(sub)([^ ]*)/" << std::endl;
        std::cout << "The following matches and submatches were found:" << std::endl;

        while (std::regex_search(s, m, e)) {
            std::cout << m.str() << std::endl; 
            s = m.suffix().str(); 
        }
        //return 0;
    }



    std::wstring s = L"Access-Control-Allow-Origin:*\
        Cache - Control:no - cache, no - store, max - age = 0, no - transform, private\
        Connection : Keep - Alive\
        Content-Length: 43\n\
        Content - Type : image / gif\
        Date : Wed, 26 Oct 2016 22 : 18 : 17 GMT\
        ETag : \"58112BA9-4BF8-4E978394\"\
        Expires : Tue, 25 Oct 2016 22 : 18 : 17 GMT\
        Keep - Alive : timeout = 15\
        Last - Modified : Thu, 27 Oct 2016 22 : 18 : 17 GMT\
        P3P : policyref = \"/w3c/p3p.xml\", CP = \"NOI DSP COR NID PSA OUR IND COM NAV STA\"\
        Pragma : no - cache\
        Server : Omniture DC / 2.0.0\
        Vary : *\
        X - C : ms - 5.0.0\
        xserver : www2534";

    auto length = getContentLength(s);

    std::wstring reg = L"Content-Length: {[0-9]+}";
//     std::wcmatch m;

    std::vector<std::wstring> result;

    searchByRegex(s, reg, result);

    MySharedPtrTest();

	std::wcout << PROTOCOL(ciscospark);
	auto atClass = std::make_shared<ProtectClass>();
	atClass->getMessages().reserve(20) ;
	//atClass->messages.reserve(20);

	//auto type
	auto x = 0;					// x is int
	auto c = 'a';				// char
	auto d = 0.5;				// double
	auto national_debt = 14400000000000LL;//long long
	auto f = 0.5f;
	long iAmLong = 203;
	void*	iAmPointer = 0;

	cout << " sizeof(int)=" << sizeof(x) << endl;
	cout << " sizeof(char)=" << sizeof(c) << endl;
	cout << " sizeof(double)=" << sizeof(d) << endl;
	cout << " sizeof(LongLong)=" << sizeof(national_debt) << endl;
	cout << " sizeof(float)=" << sizeof(f) << endl;
	cout << " sizeof(pointer)=" << sizeof(iAmPointer) << endl;

	//init class
	iAmClass aClass{ 0, 0 };  //c11 only, equivalent to below line
	iAmClass bClass(0, 0);

	{
		int *a = new int[3] {0, 1, 2};  //!< c11 only
	}

	//run all test
	test_c11 atest_c11;
	atest_c11.run_all_test();

	//test dynamic_cast
	TEST_CAST::test();

	TEST_CAST::ClassParentChildSon* pClassParentChildSon = new TEST_CAST::ClassParentChildSon();
	TEST_CAST::test_parent_son(pClassParentChildSon);

	TEST_OVERRIDE::TEST();

	TEST_LAMBDA::TEST();
	TEST_LAMBDA::TEST_SORT();

	TEST_PTR::TEST();

	TEST_SET::TEST();

	StdBindTest::instance()->TEST();

	TEST_EMPLACE::TEST();
    
	for (auto index = 0; index < 10; index++)
	{
		wcout << index;
	}
    ParamTypeTemplate::TEST();

	std::stringstream milliStream;
	milliStream << std::setw(3) << std::setfill('0') << 122 << 0;

	auto milliString = milliStream.str();


	//simple test
	const char* test_char = "this is a test string";
	char dest[128] = {0};
	auto destSize = sizeof(dest);
	auto strictSize = std::min<size_t>(strlen(test_char), sizeof(dest));
	memcpy_s(dest, destSize, test_char, strictSize);

	//run all tests
	RUN_ALL_TESTS();

	return 0;
}

