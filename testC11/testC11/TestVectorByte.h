#pragma once

#include <vector>
#include <chrono>

typedef unsigned char myByte;
using ByteBuffer = std::vector<unsigned char>;

typedef std::chrono::steady_clock Clock;
typedef std::chrono::time_point<Clock> Timestamp;


ByteBuffer gBuffer;
inline void ByteBufferVector_Test()
{
    gBuffer.reserve(65536);
    gBuffer.resize(65536);
    myByte* pByte = (myByte*)static_cast<myByte*>(&gBuffer[0]);

    myByte* pTestDataByte = new myByte[65536];
    pTestDataByte[65535] = 20;
   
    memcpy_s(pByte,gBuffer.size(), pTestDataByte, 65536);


    auto now = Clock::now();
    for (int i = 0; i < 5000; i++)
    {
        gBuffer.resize(65536*(i+1));
    }

    auto testResult = Clock::now() - now;
    

    now = Clock::now();

    for (int i = 0; i < 5000; i++)
    {
        //myByte* ptest = new myByte[65536*(i+1)];
        //delete[]ptest;
    }

    auto testResult2 = Clock::now() - now;

    auto result = testResult2 - testResult;
    
}
