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


constexpr unsigned long long/*size_t*/ factorial(size_t n) {
    return n <= 1 ? 1 : (n * factorial(n - 1));
}


size_t operator""_b(const char* dec);// не constexpr функция 

constexpr
size_t myStrlen(const char* ch) {
    return *ch ? myStrlen(ch + 1) + 1 : 0;
}

constexpr
size_t operator""_b2(const char* dec) // constexpr  функция 
{
 return 
  *dec ? (*(dec + 1) ? 
                     ((*dec - '0') << (myStrlen(dec) - 1)) | operator""_b2(dec + 1) :
                     (*dec - '0')) :
       0;
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
    for (auto it = std::cbegin(in); it != std::cend(in); ++it)
    {
        if constexpr
            (std::is_pointer< typename std::remove_reference<
                                            decltype (*std::cbegin(in))>::type >::value)
            std::cout << **it << " ; ";
        else
            std::cout << *it << " ; ";
    }
}

template<typename T, typename T2>
auto sum(const T& in1, const T2& in2)
{
    
    if constexpr (std::is_same<std::vector<T2>, T>::value)
    {
        T tmp(in1);
        for (auto& it : tmp) it = it + in2;
        return tmp;
    }
    else
        if constexpr (std::is_same<T2, T>::value)
            return in1 + in2;
}

//template<typename T>
//void printAdaptor(const T& in2)
//{
//    if constexpr (std::is_pointer<T>::value)
//    {   
//        auto in1(*in2);
//        #define T1  typename decltype(in1)::value_type
//                
//        if constexpr (std::is_same<std::stack<T1>, decltype (in1) >::value ||
//            std::is_same<std::priority_queue<T1>, decltype (in1) >::value)
//        {
//            size_t c_size = in1.size();
//            std::vector<T1> tmp(c_size);
//            for (size_t i = 0; i < c_size; i++)
//            {
//                tmp[i] = in1.top();
//                in1.pop();
//            }
//            for (auto it = tmp.crbegin(); it != tmp.crend(); ++it) {
//                std::cout << *it << " ; ";
//                //in1.push(*it);
//            }
//            return;
//        }
//        if constexpr (std::is_same<std::queue<T1>, decltype (in1) >::value)
//        {
//            size_t c_size = in1.size();
//            for (size_t i = 0; i < c_size; i++)
//            {   
//                std::cout << in1.front() << " ; ";
//                in1.pop();
//            }
//            return;
//        }
//    }
//    else
//    {
//         auto in{ in2 };
//        #define T2 typename T::value_type
//         int r = 0;
//        if constexpr (std::is_same<std::stack<T2>, decltype (in) >::value ||
//            std::is_same<std::priority_queue<T2>, decltype (in) >::value)
//        {
//            size_t c_size = in.size();
//            std::vector<T2> tmp(c_size);
//            for (size_t i = 0; i < c_size; i++)
//            {
//                tmp[i] = in.top();
//                in.pop();
//            }
//            for (auto it = tmp.crbegin(); it != tmp.crend(); ++it) {
//                std::cout << *it << " ; ";
//                //in.push(*it);
//            }
//            return;
//        }
//        if constexpr (std::is_same<std::queue<T2>, decltype (in) >::value)
//        {
//            size_t c_size = in.size();
//
//            for (size_t i = 0; i < c_size; i++)
//            {
//                std::cout << in.front() << " ; ";
//                in.pop();
//            }
//            return;
//        }
//
//    }
//
//
//
// std::cout << " can not print ";
//}


template<typename T>
const auto& get(const T& c) {
    if constexpr (std::is_same<std::stack<typename T::value_type,typename T::container_type>, T >::value ||
               std::is_same<std::priority_queue<typename T::value_type>, T >::value)
        if constexpr (std::is_pointer<typename T::value_type>::value)
        return *c.top();
        else
         return c.top();
    else
     if constexpr (std::is_pointer<typename T::value_type>::value)
        return *c.front();
     else
        return c.front();
}

template<typename T>
void printAdaptor(T in)
{
    while (in.size() != 0) {
        std::cout << get(in)<<" ; ";
        in.pop();
    }
 }




template<typename T>
constexpr auto Smth(T in) {

    /*if constexpr (std::is_scalar < T > ::value)
        return in;*/
    /*if constexpr (std::is_scalar < T > ::value)      // почему это не работает?
            return T(in);*/

    if constexpr (std::is_same < int, decltype (in) > ::value)// так то это можно не писать
        return 1;
    //else
    if constexpr (std::is_same <double, decltype (in) > ::value)// так то это можно не писать
        return 2.2;
    //else
    if constexpr (std::convertible_to < T,std::string > )
        return std::string("abc");
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
};    
template<typename T, size_t size>
MyArray(T const (&arr)[size])->MyArray<T, size>;
