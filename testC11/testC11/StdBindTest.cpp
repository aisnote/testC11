#include "stdafx.h"
#include "StdBindTest.h"

#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>
using namespace std;


class ViewButton
{
public:
	void onClick(int x, int y)
	{
		cout << "StdBindTest::onClick() x=" << x << " y=" << y << endl;
	}
};
function<void(ViewButton, int, int)>  clickCallback;

int TestFunc(int a, char c, float f)
{
	cout << a << endl;
	cout << c << endl;
	cout << f << endl;

	return a;
}

StdBindTest::StdBindTest()
{
}


StdBindTest::~StdBindTest()
{
}

void StdBindTest::TEST()
{
	vector<int> coll;
	for (int i=1; i<=10; ++i)
	{
		coll.push_back(i);
	}

	//find the elements which less 10. means 10 < element is true
	int res = count_if(coll.begin(), coll.end(), bind1st(less<int>(), 10));
	cout << res << endl;

	res = count_if(coll.begin(), coll.end(), bind2nd(less<int>(), 10));
	cout << res << endl;

	//explain:
	less<int>  functionr = less<int>();
	bool bRet = functionr(10, 20);   //should return the true. Means 10 < 20 is true. please debug it.
	//explain:
	/* that means, bind1st only bind the left parameter. on above 10 is left param, 20 is right parameter.
	 *   so for bind1st(less<int>(), 10) ===>    will be like  function(10, element).  so first bind res = 0;
	 *   so for bind2nd(less<int>(), 10) ===>    will keep the right parameter, and left is the elements from the container.
	 *   just like:   function(element, 10)  [the 2nd parameter is keep on change].  now you can understand. :)
	 */

	ViewButton button;

	clickCallback = &ViewButton::onClick;

	clickCallback(button, 10, 1234);

	//now let me use std::bind
	auto bindFunc1 = std::bind(TestFunc, std::placeholders::_1, 'A', 1000.01f);
	bindFunc1(10);   //! if you debug, you can understand. _1 means  10 is the first parameter to TestFunc. see below test

	auto bindFunc2 = std::bind(TestFunc, std::placeholders::_2, std::placeholders::_1, 1000.01f);
	//explain:   _2 on the bind first parameter. that means bindFunc2's 2nd parameter is passed to TestFunc's 1st parameter.
	bindFunc2('c', 10);

	//Now you should understand std::placeholders::_2
	auto bindFunc3 = bind(TestFunc, std::placeholders::_2, std::placeholders::_3, std::placeholders::_1);
	//! again.  bindFunc3.1stParam == TestFunc._2ndParam. so below can be executed.
	bindFunc3(                       100.1f,                30,                                      'C');

	//!why std::bind:
	// bind1st and bind2nd only can bind 1 parameter. but std::bind can bind any account of parameters.
	// reference:  http://www.cnblogs.com/xusd-null/p/3698969.html  [Chinese but diagram is English]

	//!summary:
	/* 1. pre-bind parameter is pass-by-value
	 * 2. if not pre-bind parameter means need pass std::placeholders, begin 1 then increase
	 * 3. bind can directly to return on object then pass the value to std::function
	 * 4. client need to ensure this, pointer can be used before call the bind function
	 * 5. class like this pointer can bind via pointer.
	 */
}







