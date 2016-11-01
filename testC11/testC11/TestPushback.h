#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "HighResolutionTimeCount.h"

struct President
{
    std::string name;
    std::string country;
    int year;

    President(std::string p_name, std::string p_country, int p_year)
        : name(std::move(p_name)), country(std::move(p_country)), year(p_year)
    {
        std::cout << "I am being constructed.\n";
    }
    President(President&& other)
        : name(std::move(other.name)), country(std::move(other.country)), year(other.year)
    {
        std::cout << "I am being moved.\n";
    }
    President& operator=(const President& other) = default;
};

using TestList = std::vector<int>;

TestList testReturn()
{
    TestList vReturn;
    for (int i = 0; i < 55000; i++)
    {
        vReturn.emplace_back(i);
    }

    return vReturn;
}

void testReturnByReference(TestList& vReturn)
{
    for (int i = 0; i < 55000; i++)
    {
        vReturn.emplace_back(i);
    }
}


inline int PUSH_TEST()
{
    {
        HighResolutionTimeCount hrtc;
        auto vReturn = testReturn();
    }

    {
        HighResolutionTimeCount hrtc;
        TestList vReturn;
        testReturnByReference(vReturn);
    }

    std::vector<President> elections;
    std::cout << "emplace_back:\n";
    elections.emplace_back("Nelson Mandela", "South Africa", 1994);

    std::vector<President> reElections;
    std::cout << "\npush_back:\n";
    reElections.push_back(President("Franklin Delano Roosevelt", "the USA", 1936));

    std::cout << "\nContents:\n";
    for (President const& president : elections) {
        std::cout << president.name << " was elected president of "
            << president.country << " in " << president.year << ".\n";
    }
    for (President const& president : reElections) {
        std::cout << president.name << " was re-elected president of "
            << president.country << " in " << president.year << ".\n";
    }

    return 0;
}