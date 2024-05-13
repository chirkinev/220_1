#pragma once
template<typename T>
class MyQueue {
	MyUniquePTR<T> container;
	T* qbegin;
	T* qend;
	size_t size;
	size_t capacity;
public:
	MyQueue()container(nullptr), 
		    qbegin(nullptr),
			qend (nullptr),
			size(0),
			capacity(0);
	void push(const T& in) {
		if (capacity == size) addCapacity();
	}
	void addCapacity() {
		if (!container) {
			container(new T[3]);
			//size = 3;
			capacity = 3;
			return;
		}

		MyUniquePTR<T> containernew = (new T[capacity * 2]);

		capacity *= 2;
	}

};
