#ifndef _DATASTRUCTURE_H_
#define _DATASTRUCTURE_H_

#include <memory>
#include <vector>
#include <iostream>
#include <cmath>

#include <stdexcept>

/**
   @class DataStructure
   @brief A datastructure takes ownership of the object it contains using a pointer to
          store the data.
*/
// Introduce a storage method so the values don't have to be computed multiple times

template<typename T>
class DataStructure
{
public:
  DataStructure(std::vector<T> data);
  ~DataStructure();

  int size() {return data->size();}
  const T at(int i) {return data->at(i);}

  template<typename W>
  W sum()
  {
    W sum_{0};
    for(int i=0; i < size(); i++)
      {
        sum_ += at(i);
      }
    return sum_;
  }

  template<typename W>
  W mean()
  {
    W value{0};
    for(int i=0; i < size(); i++)
      {
        value += at(i);
      }
    return value/(float)size();
  }

  template<typename W>
  W max()
  {
    W maxVal = at(0);
    for(int i=1; i<size(); i++)
      {
        maxVal = at(i)>maxVal? at(i) : maxVal;
      }
    return maxVal;
  }

  template<typename W>
  W min()
  {
    W minVal = at(0);
    for(int i=1; i<size(); i++)
      {
        minVal = at(i)<minVal? at(i) : minVal;
      }
    return minVal;
  }

  /**
     @func std
     @brief Sample standard deviation
  */
  template<typename W>
  W std()
  {
    W mean_ = mean<W>();
    W temp;
    W div = 1.0/(W)(size()-1);
    if(div == 0)
      throw std::runtime_error("Vector size is to small for std");
    W std {0};
    // We need to safeguard against buffer overflow since we are summing the squares
    if(size() > 1000)
      {
        for(int i=0; i<size(); i++)
          {
            temp = at(i) - mean_;
            std += temp*temp*div;
          }
      }else
      {
        for(int i=0; i<size(); i++)
          {
            temp = at(i) - mean_;
            std += temp*temp;
          }
        std *= div;
      }

    return sqrt(std);
  }

private:
  std::unique_ptr<std::vector<T>> data;
  template<typename W>
  friend std::ostream& operator <<(std::ostream& os, DataStructure<W>& ds);
};

template<typename T>
DataStructure<T>::DataStructure(std::vector<T> data_):
  data(std::make_unique<std::vector<T>>(data_))
{}

template<typename T>
DataStructure<T>::~DataStructure()
{}

template<typename W>
std::ostream& operator <<(std::ostream& os, DataStructure<W>& ds)
{
  for(int i=0; i < ds.size(); i++)
    if(i < ds.size()-1)
      os << ds.at(i) << " ";
    else
      os << ds.at(i);

  return os;
}
#endif // _DATASTRUCTURE_H_
