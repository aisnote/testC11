#pragma once
#include <memory>
#include <iostream>

class MySharedPtr
{
public:
    MySharedPtr(int _n) : mN(_n)
    {
    };

    virtual ~MySharedPtr()
    {
        std::cout << "~MySharedPtr() mN= " << mN << endl;
    }

    int mN{ 0 };
};

inline void MySharedPtrTest()
{
    std::shared_ptr<MySharedPtr> mMySharedPtr;

    mMySharedPtr = std::make_shared<MySharedPtr>(10);

    mMySharedPtr = std::make_shared<MySharedPtr>(5);

}