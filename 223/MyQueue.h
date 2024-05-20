#pragma once
#include <utility>


#include <iostream>
#include <algorithm>
#include <iterator>

template<typename T>
class MyQueue {
	T* mm_pp{};//указатель на начало динамического массива
	size_t mm_nn{}; //актуальное количество элементов в очереди
	size_t mm_cap{}; //емкость (сколько выделено пам€ти)
	size_t mm_first{}; //индекс первого элемента в очереди 
						//(это тот элемент, который 
						//  можноизвлечь из очереди с помощью pop())
	const size_t delta{ 2 }; //на сколько увеличиваем емкость при перераспределении пам€ти

 class iterator
	{
		const MyQueue<T>* m_pQ; //итерируема€ очередь
		int m_i;//индекс текущего элемента
	public:
		//чтобы дл€ работы с очередью можно было использовать алгоритмы
		//  STL вводим псевдонимы
		using iterator_category = std::forward_iterator_tag;
		using value_type = T;
		using difference_type = ptrdiff_t;
		using pointer = T*;
		using reference = T&;

		// а также другие, необходимые методы
		iterator() :m_pQ(nullptr), m_i(0) {};
		iterator(const MyQueue& m_q, size_t q_n) :m_pQ(&m_q), m_i(q_n) {};

		// реализуем методы, которые использует range based for
		iterator& operator++ ()
		{
	//		m_i = (m_i + 1) % m_pQ->mm_cap;
			m_i++;
			return *this;
		};

		T& operator* () { return m_pQ->mm_pp[m_i % (m_pQ->mm_cap)]; };// оператор разыменовани€

		bool operator!= (const iterator& in) const { // оператор сравнени€
			return m_pQ != in.m_pQ || m_i != in.m_i;
		};
 };
public:
	// итератор на начало очереди
	iterator begin() { return iterator(*this, mm_first); }
	// итератор на конец очереди
	iterator end() {
		return iterator(*this,
			//mm_cap ? (mm_first + this->mm_nn) % this->mm_cap : 0);//чтобы на 0 не делить;
			mm_first + mm_nn);	}	

	// итератор на начало очереди
	iterator cbegin() const{ return iterator(*this, mm_first); }
	// итератор на конец очереди
	iterator cend() const{
		return iterator(*this,
			//mm_cap ? (mm_first + this->mm_nn) % this->mm_cap : 0);//чтобы на 0 не делить;
			mm_first + mm_nn);
	}
	//-------------------------------- конструкторы итд --------

	MyQueue() = default;
	~MyQueue() 	{delete[] mm_pp;};

	// копировани€
	MyQueue(const MyQueue& in): mm_first(0),mm_cap (in.mm_nn),mm_nn(in.mm_nn)
	{
		mm_pp = new T[in.mm_nn];

		for (size_t i = 0; i < in.mm_nn; i++)
				mm_pp[i] = in.mm_pp[(in.mm_first + i) % in.mm_cap];
	}
	// перемещающий
	MyQueue(MyQueue&& in) :mm_pp(in.mm_pp),
		                  mm_nn(in.mm_nn),
		                  mm_cap(in.mm_cap),
		                  mm_first(in.mm_first)
	{
		in.mm_pp=nullptr;
		in.mm_nn=0;
		in.mm_cap=0;
		in.mm_first = 0;
	};
	// списком инициализации
	/*MyQueue(std::initializer_list<T> il):mm_nn(0), mm_cap(il.size()+1), mm_first(0)
	{
		mm_pp = new T[il.size()+1];
		for (auto& node : il) { push(node); }
	};*/

	MyQueue(std::initializer_list<T> il) :mm_nn(il.size()), mm_cap(il.size())//, //mm_first(0)
	{
		mm_pp = new T[il.size()];
		size_t i = 0;
		//typedef std::move_iterator<std::initializer_list<T>::iterator> mi;

		std::copy(il.begin(),il.end(), mm_pp);
		//for (size_t i = 0; i < il.size(); i++)
		//{
		//	mm_pp[i] = std::move(*it);// почему не работает???
		//	++it;
		//}
		
	};
	// с указанием размера и заполнени€
	MyQueue(size_t n, const T& node) :mm_nn(n), mm_cap(n), mm_first(0)
	{
		mm_pp = new T[n];
		for (size_t i = 0; i < n; i++)
				mm_pp[i] = node;
	};
	
	// ------------------------- = --------------------------------
	MyQueue& operator= (const MyQueue& in)
	{
		if (mm_cap < in.mm_nn)
		{
			delete[] mm_pp;
			mm_pp = new T[in.mm_nn];
			mm_cap = in.mm_nn ;
		}
		mm_first = 0;
		mm_nn = in.mm_nn;

		/*for (size_t i = 0; i < mm_nn; i++)
			mm_pp[i] = in.mm_pp[(in.mm_first+i)%in.mm_cap];
		*/
		std::copy(in.cbegin(), in.cend(), mm_pp);
		return *this;
	};
	// ------------------------- = && --------------------------------
	MyQueue& operator= (MyQueue&& in)
	{
		if (&in == this) return *this;
		delete[] mm_pp;// чищу

		mm_pp = in.mm_pp;//ворую
		mm_nn = in.mm_nn;
		mm_cap = in.mm_cap;
		mm_first = in.mm_first;

		in.mm_pp = nullptr;// обнул€ю
		in.mm_nn = 0;
		in.mm_cap = 0;
		in.mm_first = 0;
		return *this;
	};

	
	void addCapasity(size_t n) { //добавл€ем n элементов в массив
		T* newArr = new T[mm_cap + n];
	/*	for (size_t i = 0; i < mm_nn; i++)
		{
			newArr[i] = std::move(mm_pp[(mm_first + i) % mm_cap]);
		}*/
		size_t i{ 0 };
		for (auto& no : *this)
		{
			newArr[i] = no;
			i++;
		}
		delete[] mm_pp;
		mm_pp = newArr;
		mm_first = 0;
		mm_cap += n;
	}
	// методы, реализующие функциональность очереди
	void push(const T& in) {
		if (mm_cap ==  mm_nn) addCapasity(delta);
		mm_pp[(mm_first + mm_nn)%mm_cap] = in;
		mm_nn++;
	};
	void push(T&& in) {								
		if (mm_cap == mm_nn) addCapasity(delta);
		mm_pp[(mm_first + mm_nn) % mm_cap] = std::move(in);
		mm_nn++;
	};
	T pop() {
		if (mm_nn == 0) throw "queue emty";// тут нужно вызвать исключение
		T tmp1 = std::move(mm_pp[mm_first]);
		
		mm_first = (mm_first + 1) % mm_cap;
		mm_nn--;
		return tmp1;
	};
	
};
