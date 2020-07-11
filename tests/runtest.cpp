#include "Datastructure.hpp"
#include "Random.hpp"
#include <iostream>
#include <vector>

int main(int argc, const char* argv[])
{
  for(int i=0; i<argc; i++)
    {
      std::cout << argv[i] << std::endl;
    }
  auto data = random_uniform<float>(5, 0.0f, 100.0f);
  for(int i=0; i<5; i++)
    {
    std::cout << data[i] << std::endl;
    }

  DataStructure<float> ds(data);
  std::cout << " - - - - \n";
  std::cout << ds << std::endl;

  std::cout << "sum = " << ds.sum<double>() << std::endl;
  std::cout << "Mean = " << ds.mean<double>() << std::endl;
  std::cout << "Max = " << ds.max<float>() << std::endl;
  std::cout << "Min = " << ds.min<float>() << std::endl;
  std::cout << "std = " << ds.std<float>() << std::endl;
  return 0;
}
