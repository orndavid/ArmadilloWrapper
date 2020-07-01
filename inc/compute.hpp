#ifndef _COMPUTE_H_
#define _COMPUTE_H_

#include <armadillo> //Armadillo
#include <memory>
#include <vector>
#include <iostream>
#include <ostream>

template<typename T>
class DataStructure
{
public:
    DataStructure(T data);
    ~DataStructure();

private:
    std::unique_ptr<T> data;
    template<typename W>
    friend operator <<(std::ostream& os, const DataStructure<W>& ds);
}

template<typename T>
DataStructure::DataStructure(T data):
    data(std::make_unique(data)
{}

template<typename T>
DataStructure::~DataStructure()
{}

template<typename W>
friend operator <<(std::ostream& os, const DataStructure<W>& ds)
{
    return os << *data;
}


template<typename W>
friend operator <<(std::ostream& os, const DataStructure<std::vector<W>>& ds)
{
    for(auto x:*data)
        os << x << " ";
    return os;
}
#endif //_COMPUTE_H_
