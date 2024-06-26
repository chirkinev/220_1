#include <string>
#include <iostream>
#include <cstdint>
#include <algorithm>
#include <iterator>
#include <memory>
#include "Header.h"
#include <vector>
#include <list>
#include <deque>
#include <set>
#include <queue>
#include <stack>

//using namespace std;

int main()
{


	//////////////////////////////////////////////////////////////////////////////////////////////
	//������� 1. ���������� ���������� ���������� � ������� constexpr-�������.
	//
	//���������/�����������: 
	//		- constexpr � ������� ������ �������� �� ������������ ���������� return <���������>; (����!)
	//		- �� ��� ��������� ����� �������� ����� ������ constexpr � �������, � ��������� �����������
	//		  ����� 
	//		- ���� �������� ����������� constexpr- ������� - ��� ���������, ���������� �������� ���������
	//		  �� ����� ����������

	//��������� ��� ����, ��� ���������� ��������� �������� �� ����� ���������� (���� � ��������
	//				��������� ������������ ���������, ��������� ����������� �� ����� ����������).
	//				��� �������� ���������� ������� ���������� ������ � ������������, �����������
	//				����������� constexpr-�������:

	
	{	//��������:
		int ar[factorial(3)]; 

		//���
		constexpr auto n = factorial(5);
		int ar1[n];  

		//����������:
		int m = 7;
		//constexpr int n1 = factorial(m); //�� �������� �� ����� ����������!!!
		//int ar1[n1];						// ������ ���� const int m = 7;

		//� ���?
		auto n2 = factorial(m); //�� �������� �� ����� ����������!!!
		//int ar1[n2];
		__asm nop
	}

	//////////////////////////////////////////////////////////////////////////////////////////////
	//������� 2a. ������� � ������� ����������������� �������� �� ��������� ������������� ����������
	//� ��������, ��������: ������ "100000000" -> � �������� 256
	//��������� ��������� ����������� �������� 0b
	//����� ����� ����������������� �������� �������� ������ � �������, ��������: 100000000_b
	//������� ������������ ���������������� ������� � ������������ ���������� - const char*

	//��� ��� ���� ���� � ���������, ������� ��������� �������� �� ����� ����������
	// => ���������� ���������������� ������� ����������� constexpr - �������
	//���������/�����������: 
	//		- constexpr � ������� ������ �������� �� ������������ ���������� return <���������>;
	//		- �� ��� ��������� ����� �������� ����� ������ constexpr � �������,
	//		- ������� ����� ���� ����������� (���� �������� ����� ������� - ��� ���������,
	//		  ���������� �������� ��������� ������ ����������� ������� �� ����� ����������)

	{
		/*constexpr*/ auto a = 100000000_b;
		/*constexpr*/ auto b = 0_b;
		
		constexpr auto c = 100000000_b2;
		constexpr auto d = 0_b2;

		
		__asm nop

	}

	//������� 2b. ������� � ��������� �������� �������������, ��������: 256 -> "0b100000000"
	//��� ��� ������ ����� ���� ����� �����, �������� � ����� ���������� ������ std::string
	//=> ������������ �������� �� ����� ���� constexpr!
	//���������: ������������ std::bin ���� ��� => �������������� � �������� ������
	//�������� ������ �������
	//���������: ���������� �������� � ����� ���������� ��������� CHAR_BIT - <cstdint>

	{
		std::string sBin= 256_toBinStr;
		std::string sBin1 = 0_toBinStr;
		std::string sBin2 = 2_toBinStr;
		std::string sBin3 = 63_toBinStr;
		__asm nop
	}


	//////////////////////////////////////////////////////////////////////////////////////////////
	//������� 3. constexpr - ������� 
	//������� ����� (������ ������?) ��� �������� � ��������������� ���������� ��������.
	//� ������ ������ ����:
	//	���������� ��� �������� ������������ � ������������� ��������,
	//	������ ��� ��������� ������� �� ��������
	//	����� ��� �������� - �������� �� ��������� �������� � ��������
	//	�����, ������� �������� ����� �������� ������� ���� � ��������� �������������� ��������:
	//							���� ����������� ���������, �� ��� � ����������
	//							���� ������ ������������ ��������, ���������� �����������
	//							���� ������ ������������� ��������, ���������� ������������

	//��������� ��� ����, ��� ���������� ��������� �������� �� ����� ����������. 

	{

		constexpr int a = mmx(1, 2).getMax(); // 2
		constexpr int a1 = mmx(1, 8).getMin(); // 1
		constexpr bool a2 = mmx(1, 3).isIn(2); // true
		constexpr int a3 = mmx(1, 2).inInD(5); // 2



		__asm nop
	}
	/***************************************************************/
//������� 4.
	/*
	���������� ������ ������� ��� ������ ����� ������������������� 
	(vector, list, deque, set � ����������� �������), ������� ����� ���������:
	�	��� ������� ������ ����,
	�	��� � ��������� �� ������� ������ ���� 
	(��������� ������������� ����������� => � ���� ������ ������� �������� �������� �� ������)
	���������: if constexpr
	*/
	{
		std::vector<int> vi{ 1,2,3 };
		std::list<int> li{ 3,4,5 };
		std::deque<int> di{ 6,7,8 };
		std::set<int> si{ 1,2,3 };
		int mi[] = { 9,8,7,6 };

		std::vector<int*> vpi; for (int& a : vi)vpi.push_back(&a);
		std::list<int*> lpi; for (int& a : li)lpi.push_back(&a);
		std::deque<int*> dpi; for (int& a : di)dpi.push_back(&a);
		std::set<int*> spi; for (int& a : vi)spi.insert(&a);
		int* mpi[] = { &mi[0],&mi[1],&mi[2],&mi[3] };


		std::cout << "\n-------printT---------\n";
		printT(vi); std::cout << "\n";
		printT(li); std::cout << "\n";
		printT(di); std::cout << "\n";
		printT(si); std::cout << "\n";
		printT(mi); std::cout << "\n";
		std::cout << "\n--------printT*--------\n";
		printT(vpi); std::cout << "\n";
		printT(lpi); std::cout << "\n";
		printT(dpi); std::cout << "\n";
		printT(spi); std::cout << "\n";
		printT(mpi); std::cout << "\n\n";


		/*printT(&vi); std::cout << "\n";
		printT(&li); std::cout << "\n";
		printT(&di); std::cout << "\n";
		printT(&si); std::cout << "\n";
		printT(&mi); std::cout << "\n\n";*/
	}

	/***************************************************************/
	//������� 5.
		/* ���������� ������ ������� �������� ���� ��������.
		���� ������ ��������� �������� ��������, �� ��� �������� ������� 
		����� ��������� �� �������� ������� ���������. 
		��� ���� �������� ������� � ������ �������� ������ ���� ������ � ���� �� ����.
		���������: if constexpr, is_same
		*/
	{
		auto a = sum(3, 3);
		std::cout << a<<"\n";
		
		auto b = sum(std::vector<double>{2, 2.2, 3}, 1.1);
		printT(b);
	}


	/***************************************************************/
//������� 6.
	/* 	���������� ������ ������� ������ �� ������ �������� ��������� ������ 
	�������� (stack, queue, priority_queue)
	���������: if constexpr, is_same
	//������������� ����� ��������, ���� � �������� �������� ���������.
	*/
	{
		std::deque<int> d1{ 1,2,3 };
		std::deque<int> d2{ 4,5,6 };
		std::vector<int> v3{ 7,8,9 };

		std::stack<int,std::vector<int>> si{ v3};
		std::queue<int> qi{ d2 };
		std::priority_queue<int> pqi{ std::less<int>(),v3 };

		std::stack<int*> spi; for (int& a : d1)spi.push(&a);
		std::queue<int*> qpi; for (int& a : d2)qpi.push(&a);
		std::priority_queue<int*> pqpi; for (int& a : v3)pqpi.push(&a);

		std::cout << "\n-----------printAdaptor------------------\n";
		printAdaptor(si); std::cout << "\n";
		printAdaptor(qi); std::cout << "\n";
		printAdaptor(pqi); std::cout << "\n-----------printAdaptor*------------------\n"; 
		
		printAdaptor(spi); std::cout << "\n";
		printAdaptor(qpi); std::cout << "\n";
		printAdaptor(pqpi); std::cout << "\n";


	}

	/***************************************************************/
//������� 7.
	/* 	���������� ������ constexpr ������� Smth(), ������� ������ ����������
	�������� ������� ����
	���������: constexpr, if constexpr
	*/
	//constexpr int res1 = /*<����� Smth()>;*/ //res1 = 1
	//constexpr double res2 = /*<����� Smth()>; */ //res2 = 2.2
	//  /*constexpr???*/ std::string res3 = /*<����� Smth()>; */ //res3 = "abc"

	constexpr int res1 = Smth(1);//res1 = 1
	constexpr double res2 = Smth(2.2);//res2 = 2.2
	/*constexpr*/  std::string res3 = Smth("abc");//res3 = "abc"

	//std::string �� ����� ���� constexpr


	//***************************************************************/
	//������� 8.

		/*���������������� deduction guide � ��� ������ ����� ���������� �������
		����� ������ ������, ������� ������������� ���������� ������������ ������ ���������
		����������� � ���������� ������ ����. */
		/*
		template<typename T, size_t size> class MyArray
			{
				T ar[size]; //��� ���������� ������������� ��������� 
				�������� ���� �� ��������� �����?
				�
				public:
				MyArray(const T*[, �������� ������ ���������]);


			};

		*/
		
		//��������� ���������� ����������������� ����������� �������� �������������.
	{
		MyArray<int, 5> ar1;//MyArray<int,5>
		MyArray<char, 5> ar2{"ABCqwerty"};//MyArray<char,5>

		MyArray ar3{"ABC"}; //MyArray<char,4>

		int ar[] = { 1,2,3 };
		MyArray ar4{ ar };

		int r = 0;//������� ����� ��������
	}
		


}
