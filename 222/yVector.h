#pragma once
#include <initializer_list>
#include <string>
#include <vector>
#include<iostream>
#include <algorithm>
using namespace std;

template <typename T>
pair<T, T> interval_y{};

template<typename T>
class yVector:protected vector<T> {
	
public:
	enum class sortMetod { up, down, abs };

	yVector() = default;
	yVector(const yVector<T>&) = default;
	yVector(yVector<T>&&) = default;
	yVector& operator= (const yVector&) = default;
	yVector& operator= (yVector&&) = default;
	bool operator== (const yVector&)const = default;// cpp 20
	~yVector() = default;

	yVector(const T& node) { this->add(node); }
	yVector(std::initializer_list<T> il)
	{
		for (auto& node : il) this->add(node);
	};
	void add(const T& node)
	{
		if (node > interval_y<T>.first && node < interval_y<T>.second)
			if (find(this->begin(), this->end(), node) == this->end())
				this->push_back(node);
	};
	void add(std::initializer_list<T> il)
	{
		for (auto& node : il) this->add(node);
	};
	void add(const yVector<T>& nodes)
	{
		for (auto i = nodes.cbegin(); i != nodes.cend(); ++i)this->add(*i);
	};

	auto cbegin() const { return vector<T>::cbegin(); };
	auto cend() const { return vector<T>::cend(); };
	auto begin() { return vector<T>::begin(); };
	auto end() { return vector<T>::end(); };

	static void setInterval(const T& ibeg, const T& iend) 
		{ interval_y<T> = { ibeg,iend }; };

	void del(const T& node)
	{
		auto it = find(this->begin(), this->end(), node);
		if (it != this->end()) {
			for (; (it + 1) != this->end(); ++it) *it = *(it + 1);
			this->pop_back();
		}
	}

	void del(std::initializer_list<T> il)
	{
		for (auto& node : il) this->del(node);
	}

	yVector& operator-(const yVector& l2)
	{//xVector tmp{ *this };
		for (auto i = l2.cbegin(); i != l2.cend(); ++i)
			this->del(*i);
		return *this;
	}
	yVector& operator+(const yVector& l2)
	{
		for (auto i = l2.cbegin(); i != l2.cend(); ++i)
			this->add(*i);
		return *this;
	}
	void resetInterval(const T& ibeg, const T& iend) {
		if (ibeg > interval_y<T>.first || iend < interval_y<T>.second) {
			size_t counter = 0;
			auto ie = this->end();
			for (auto i = this->begin(); i != ie;) {
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
			for (; counter > 0; counter--)this->pop_back();
		}
		interval_y<T>.first = ibeg;
		interval_y<T>.second = iend;
	}
	void xsort(const sortMetod	sm)
	{  switch (sm)
		{
		case sortMetod::up:
			sort(this->begin(), this->end(),
				[](const T& a, const T& b) {return a < b; });
			break;
		case sortMetod::down:
			sort(this->begin(), this->end(), [](const T& a, const T& b) {return a > b; });
			break;
		case sortMetod::abs:
			sort(this->begin(), this->end(), [](const T& a, const T& b) {return abs(a) < abs(b); });
			break;
		}
	}
};