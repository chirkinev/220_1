//������������ ������ �3
//
//initializer_list, move, default, delete, move ���������
//
//
//�������.������������ �����, ������� ��������� ���������������� ������� 
// � ���������� ������ ����.
//������ ��������� ������� � ������������ �������, 
// ��� ���� ������������ ������ ��� ����������� �����.
// ���������: ��� ��� ������� � ��� ������������� ��������� ������, 
// ��� ������� ����� ������ ���������� � �����, �  ������� ������
//  ��������� �� ������ ������� = > ���� ��������� ������� ������� 
// ������������, �� ������ ������ ����� ��� ������������ = > 
// ��������������� �����, ��������� ��������� � �������� ��������.
//�������� �� ��������� ������������� ����� ��������� ������, �����
//  ��������� ��������, ����� ������������ ������ push(), � ���������
//  ��������� � ������� �� �������� = > ��� ������������� ������ ������� �����������.
//��� ���������� ����� ���������� ����������� ������ � ������������ ������� = >
//�	������������� ������� ��������� ���������
//�	������ ��� ��������� ������������� �� ����������������
//��������!
//1.	������� ��������� ��� ������������� ������ ������!� ������������� 
// ��������� �� ���� ������������� move - ���������
//2.	������� ������� �� ������ � ������� range - base - for
//��������� ������������� ����� �� ����������� ���� ���������.���������: 
// ���� �� �� ������� �� ���������� ������ � �� ������������� ������������ �
//  ������� ����� MyString, ������ �������� ��� �� std::string
//
//��������� �������� ������ �������� �� ������ ���������, �� � ���������� :

#include "MyQueue.h"
#include <iostream>
#include "MyString.h"

int main()
{   // ������ ��� ��� ������� ������ ������
	{
	MyQueue<int>  i1;
	i1.push(1);
	i1.push(2);
	i1.push(3);

	int r = i1.pop();
	std::cout << r << " ; ";
	r = i1.pop();
	std::cout << r << " ; ";
	//r = i1.pop();
	std::cout << "\n";

	i1.push(4);
	i1.push(5);
	i1.push(6);
	i1.push(7);
	i1.push(8);
	i1.push(10);
	for (auto i = i1.begin(); i != i1.end(); ++i)
	{
		std::cout << *i << " ; ";
	}
	std::cout << "\n";
	for (int i : i1)
		std::cout << i << " ; ";
	i1.push(9);
	}
	// ------------------   ������� � ������������ -----------
	{
		MyQueue<MyString>  q1{ MyString("AAA"),
								MyString("qwerty"),
								MyString("1erty"),
								MyString("2rty") };

			std::cout << "\n\n q1 - 4 strings\n";
		//
		////������������� MyQueue � ����������� for:
		for (const auto& el : q1) { std::cout << el << ' '; }
		//
			std::cout << "\n\n";
		MyString s("abc");
		q1.push(s);
		q1.push(MyString("123"));

			std::cout << " q1 + 2 strings\n";
			for (const auto& el : q1) { std::cout << el << ' '; }
			std::cout << "\n\n";

		MyString s1 = q1.pop();
		q1.push("qqq");

			std::cout << " q1 - 1pop +1 push strings\n";
			for (const auto& el : q1) { std::cout << el << ' '; }
			std::cout << "\n\n";

		MyQueue < MyString >  q2 = q1;

			std::cout << " q2 = q1\n";
			for (const auto& el : q2) { std::cout << el << ' '; }
			std::cout << "\n\n";

		MyQueue < MyString >  q22 = std::move(q1);
		//
			std::cout << " q22 = move q1\n";
			for (const auto& el : q22) 
			{ std::cout << el << ' '; }
			std::cout << "\n\n";

		MyQueue < MyString >  q3{ 10, MyString("!")}; //������� ������ ��������� 10 ��������� �� ������� �!� 

			std::cout << " q3  10 element \"!\"\n";
			for (const auto& el : q3) { std::cout << el << ' '; }
			std::cout << "\n\n";

		q1 = q3;

			std::cout << " q1 =q3\n";
			for (const auto& el : q1) { std::cout << el << ' '; }
			std::cout << "\n\n";

		q2 = MyQueue < MyString >(5, MyString(" ? "));

			std::cout << " q2 5 strings \" ? \"\n";
			for (const auto& el : q2) { std::cout << el << ' '; }
			std::cout << "\n\n";

		q1 = { MyString("bbb"), MyString("ssss")};

			std::cout << " q1 2 strings \n";
			for (const auto& el : q1) { std::cout << el << ' '; }
			std::cout << "\n\n";
	}
	return 0;
}
