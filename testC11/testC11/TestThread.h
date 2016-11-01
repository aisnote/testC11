/*!
 * \class TestThread
 *
 * \ingroup GroupName
 *
 * \brief
 *
 * TODO: long description
 *
 * \note
 *
 * \author liuliu
 *
 * \version 1.0
 *
 * \date October 2016
 *
 * Contact: user@company.com
 *
 */


#pragma once

#include <iostream>
#include <thread>
#include <string.h>
#include <mutex>
#include <vector>
using namespace std;

mutex mt;
static void thread_task()
{
    mt.lock();
    std::cout << "hi,Enter Critical section" << std::endl;
    this_thread::sleep_for(chrono::seconds(1));
    std::cout << "hi, Leave Critical section" << endl;
    mt.unlock();
}

static void Test_Thread()
{
    vector<thread> v(5);
    for (auto &i : v)
    {
        i = std::thread(thread_task);
    }

    for (auto &i : v)
    {
        i.join();
    }
}

class TestThread
{
public:
    TestThread();
    virtual ~TestThread();
};

