#include "Datastructure.hpp"
#include "Random.hpp"
#include "gtest/gtest.h"

#include <vector>
#include <string>
#include <iostream>

namespace
{
    TEST(initilization, types)
    {
      auto data = random_uniform<float>(100, 0.0f, 100.0f);
      DataStructure<float> structure1(data);
      //Although the structure isn't developed for strings it still works for them
      std::vector<std::string> data2;
      data2.push_back("Hello");
      data2.push_back("My");
      data2.push_back("Name");
      data2.push_back("Is");
      data2.push_back("Jurgen");
      EXPECT_TRUE("Hello"==data2.at(0) &&
                  "My"==data2.at(1) &&
                  "Name"==data2.at(2) &&
                  "Is"==data2.at(3) &&
                  "Jurgen"==data2.at(4));
    } /*  end of testing initialization and types */
} // End of test namespace

