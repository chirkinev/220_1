#pragma once
template<typename T>
class MyUniquePTR  {
	T* pointer;
public:
	MyUniquePTR():pointer(nullptr) {};
	MyUniquePTR(T* in) :pointer(in)  {};
	
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
		delete[] pointer;
		//pointer = nullptr;
	}
	
	 operator const T*() const noexcept 
	 { return pointer; }

	T* operator->() const  noexcept {
		return this->pointer;
	}

	T& operator*() const  noexcept {
		return *(this->pointer);
	}
	
	MyUniquePTR<T>& operator=( MyUniquePTR<T>&& in) noexcept {
		delete[] pointer;
		pointer = in.pointer;
		in.pointer = nullptr;
		return *this;
	}
};