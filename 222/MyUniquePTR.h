#pragma once
template<typename T>
class MyUniquePTR  {
public:
	T* pointer;
	MyUniquePTR():pointer(nullptr) {};
	MyUniquePTR(T* in) :pointer(in) {};
	
	MyUniquePTR<T> ( const MyUniquePTR<T>& in) = delete;

	MyUniquePTR<T>& operator=(const MyUniquePTR<T>&) = delete;

	MyUniquePTR<T>(MyUniquePTR<T>& in) {
		pointer = in.pointer;
		in.pointer = 0;
	}

	MyUniquePTR<T> (MyUniquePTR<T>&& in) noexcept {
		pointer = in.pointer;
		in.pointer = 0;
	}
		
	~MyUniquePTR() noexcept {
		delete pointer;
		//pointer = nullptr;
	}
	bool operator==(MyUniquePTR<T>&& in) {
		return in - this;
	}
	operator T*() const { return pointer; }

	T* operator->() const  {
		return this->pointer;
	}

	T& operator*() const  {
		return *(this->pointer);
	}
	
	

	MyUniquePTR<T>& operator=( MyUniquePTR<T>&& in) {
		delete pointer;
		pointer = in.pointer;
		in.pointer = nullptr;
		return *this;
	}
};