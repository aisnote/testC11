//
//  ParamTypeTemplate.h
//  testC11-mac
//
//  Created by liuliu on 9/5/16.
//  Copyright © 2016 liuliu. All rights reserved.
//

#ifndef ParamTypeTemplate_h
#define ParamTypeTemplate_h

#include <iostream>
using namespace std;

template <typename T>
void f(T& param)
{
    int x = param;
    std::cout << x << endl;
}

namespace ParamTypeTemplate {
    void TEST()
    {
        int x = 16;
        const int cx = x;
        const int& rx = x;
        f(x);
        f(cx);
        f(rx);
    }
}



#endif /* ParamTypeTemplate_h */
