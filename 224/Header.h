#pragma once
//#include <xkeycheck.h>
#include <string.h>
#include <string>
#include<iostream>
#include <vector>
#include <stack>

#include <cstdint>
#include <algorithm>
#include <iterator>
#include <memory>
#include <list>
#include <deque>
#include <set>
#include <queue>


constexpr unsigned long long/*size_t*/ factorial(unsigned long long n) {
    return n <= 1 ? 1 : (n * factorial(n - 1));
}


unsigned long long/*size_t*/ operator""_b(const char* dec);// не constexpr функция 

constexpr
size_t myStrlen(const char* ch) {
    return *ch ? myStrlen(ch + 1) + 1 : 0;
}

constexpr
size_t operator""_b2(const char* dec) // constexpr  функция 
{
    return *dec ? (
        *(dec + 1) ? ((*dec - '0') << (myStrlen(dec) - 1)) + operator""_b2(dec + 1) :
        (*dec - '0')) : 0;
};

std::string operator""_toBinStr(unsigned long long in);


template<typename T> class mmx
{
    T min;
    T max;
public:
    constexpr mmx(const T& mn,const T& mx):min(mn), max(mx) {};
    constexpr bool isIn(const T& in) const { return in >= min && in <= max; }
    constexpr T getMin() const { return min; }
    constexpr T getMax() const { return max; }
    constexpr T inInD(const T& in) const {
        return ((in < min) ? min :( (in>max )? max : in));
    }
};


template<typename T>
void printT(const T& in) {
    
    if constexpr (std::is_pointer<T>::value)
    {
        for (auto it = std::cbegin(*in); it != std::cend(*in); ++it) {
            std::cout << *it << " ; ";
        }
    }
    else
    {
        for (auto it = std::cbegin(in); it != std::cend(in); ++it) {
            std::cout << *it << " ; ";
        }
    }
}

template<typename T, typename T2>
auto sum( T in1, const T2& in2)
{
    
    if constexpr (std::is_same<std::vector<T2>,decltype(in1)>::value)
    {
        for (auto& it : in1) it = it + in2;
        return in1;
    }

    if constexpr (std::is_scalar<T>::value && std::is_scalar<T2>::value)
        return in1 + in2; 
    return T{};
}

template<typename T>
void printAdaptor(const T& in2)
{
    
     if constexpr (std::is_pointer<T>::value)
    {   
        auto in1(*in2);
        #define T1  typename decltype(in1)::value_type
                
        if constexpr (std::is_same<std::stack<T1>, decltype (in1) >::value ||
            std::is_same<std::priority_queue<T1>, decltype (in1) >::value)
        {
            size_t c_size = in1.size();
            std::vector<T1> tmp(c_size);
            for (size_t i = 0; i < c_size; i++)
            {
                tmp[i] = in1.top();
                in1.pop();
            }
            for (auto it = tmp.crbegin(); it != tmp.crend(); ++it) {
                std::cout << *it << " ; ";
                //in1.push(*it);
            }
            return;
        }
        if constexpr (std::is_same<std::queue<T1>, decltype (in1) >::value)
        {
            size_t c_size = in1.size();

            T1 tmp;
            for (size_t i = 0; i < c_size; i++)
            {
                tmp = in1.front();
                in1.pop();
                //in1.push(tmp);
                std::cout << tmp << " ; ";
            }
            return;
        }
    }
    else
    {
         auto in{ in2 };
        #define T2 typename T::value_type
         int r = 0;
        if constexpr (std::is_same<std::stack<T2>, decltype (in) >::value ||
            std::is_same<std::priority_queue<T2>, decltype (in) >::value)
        {
            size_t c_size = in.size();
            std::vector<T2> tmp(c_size);
            for (size_t i = 0; i < c_size; i++)
            {
                tmp[i] = in.top();
                in.pop();
            }
            for (auto it = tmp.crbegin(); it != tmp.crend(); ++it) {
                std::cout << *it << " ; ";
                //in.push(*it);
            }
            return;
        }
        if constexpr (std::is_same<std::queue<T2>, decltype (in) >::value)
        {
            size_t c_size = in.size();

            T2 tmp;
            for (size_t i = 0; i < c_size; i++)
            {
                tmp = in.front();
                in.pop();
                //in.push(tmp);
                std::cout << tmp << " ; ";
            }
            return;
        }

    }
 std::cout << " can not print ";
}


template<typename T>
constexpr auto Smth(T in) {

    if constexpr (std::is_same < int, decltype (in) > ::value)// так то это можно не писать
        return int(in);
    if constexpr (std::is_same <double, decltype (in) > ::value)// так то это можно не писать
        return double(in);
    if constexpr (std::is_same < const char*, decltype (in) > ::value)
        return std::string(in);
}

template<typename T, size_t size> class MyArray
{
    T ar[size]{}; //как обеспечить инициализацию элементов базового типа по умолчанию нулем?

public:
    MyArray() = default;
    ~MyArray() = default;
    MyArray(const T* ch) { for (int i = 0; i < size ; i++)ar[i] = *(ch + i); 
    if constexpr (std::is_same < char, T > ::value) ar[size - 1] = '\0';
    }
    //MyArray(const char* ch) { for (int i = 0; i < size-1 /*&& i < strlen(ch)*/; i++)ar[i] = *(ch + i); }
};    
template<typename T, size_t size>
MyArray(T const (&arr)[size])->MyArray<T, size>;
