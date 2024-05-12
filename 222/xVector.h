#pragma once
#include <initializer_list>
#include <string>
#include <vector>
#include<iostream>
#include <algorithm>
using namespace std;

template<typename T>
void  PrintAnyCont(const T& l)
{
	for ( auto i = l.cbegin(); i != l.cend(); ++i)
		cout << *i << " ; ";
};

template <typename T>
pair<T, T> interval{};

template<typename T>
class xVector {
	vector<T> cont;
public:
	enum class sortMetod { up, down, abs };

	xVector() =default;
	xVector(const xVector<T>&) = default;
	xVector(xVector<T>&&) = default;
	xVector& operator= (const xVector&) = default;
	xVector& operator= (xVector&&) = default;
	bool operator== (const xVector&)const = default;// cpp 20
	~xVector() = default;

	xVector(const T& node){	this->add(node); }
	xVector(std::initializer_list<T> il)
			{for (auto& node : il) this->add(node);	};
	void add(const T& node)
		{ if (node > interval<T>.first && node < interval<T>.second)
			if (find(cont.begin(), cont.end(), node) == cont.end())
				cont.push_back(node);	};
	void add (std::initializer_list<T> il)
		{ for (auto& node : il) this->add(node);};
	void add(const xVector<T>& nodes)
		{for (auto i=nodes.cbegin();i!=nodes.cend();++i)this->add(*i);};

	auto cbegin() const { return cont.cbegin(); };
	auto cend() const { return cont.cend(); };
	auto begin() { return cont.begin(); };
	auto end() { return cont.end(); };

	static void setInterval(const T& ibeg, const T& iend) {interval<T> = { ibeg,iend };};

	void del(const T& node) 
	{
		auto it = find(cont.begin(), cont.end(), node);
		if (it != cont.end()) {
			for (; (it+1) != cont.end(); ++it) *it = *(it + 1);
			cont.pop_back();
		}
	}
	
	void del(std::initializer_list<T> il)
		{for (auto& node : il) this->del(node);}

	xVector& operator-(const xVector& l2) 
		{
		for (auto i = l2.cbegin(); i != l2.cend(); ++i) 
			this->del(*i);
		return *this;
		}
	xVector& operator+(const xVector& l2)
	{
		for (auto i = l2.cbegin(); i != l2.cend(); ++i)
			this->add(*i);
		return *this;
	}
	void resetInterval(const T& ibeg, const T& iend) {
		if (ibeg > interval<T>.first || iend < interval<T>.second) {
			size_t counter = 0;
			auto ie = cont.end();
			for (auto i = cont.begin(); i != ie;) {
				if (*i<ibeg || *i>iend) 
				{
				for (auto it = i; (it + 1) != ie; ) 
					{   
					*it = *(it + 1);
					++it;
					}
				--ie;
				counter++;
				}
				else ++i;
			}
			for (; counter > 0;counter--)this->cont.pop_back();
		}
		interval<T>.first = ibeg;
		interval<T>.second = iend;
	}
	void xsort(const sortMetod	sm)
	{
		//auto pred = [](const T& a, const T& b) {};
		switch (sm)
		{
		case sortMetod::up:		
			//auto pred = [](const T& a, const T& b) {return a < b; };
			sort(cont.begin(),cont.end(),
				[](const T& a, const T& b) {return a < b; });
			break;
		case sortMetod::down:	
			//auto pred = [](const T& a, const T& b) {return a > b; };
			sort(cont.begin(), cont.end(), [](const T& a, const T& b) {return a > b; });
			break;
		case sortMetod::abs:	
			//auto pred = [](const T& a, const T& b) {return abs(a) < abs(b); };
			sort(cont.begin(), cont.end(), [](const T& a, const T& b) {return abs(a) < abs(b); });
			break;
		}
		//sort(cont.begin, cont.end, pred);
	}
};



