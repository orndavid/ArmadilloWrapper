#ifndef _RANDOM_H_
#define _RANDOM_H_

#include <random>
#include <vector>

/**
   @func random
   @brief Create and return an array of T with count number of values
   @param
   @returns
            Pointer to the starting point of the array of type T
  */
template<typename T>
std::vector<T> random_uniform(int count,
                     float low=0.0f,
                     float high=1.0f)
{
  std::vector<T> data;
  std::random_device r;
  std::mt19937 gen(r());
  std::uniform_real_distribution<> unifDist(low, high);
  for(int i=0; i<count; i++)
    {
      data.push_back(unifDist(gen));
    }
  return data;
}



#endif //_RANDOM_H_
