
#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <deque>
#include <map>
//#include "func.h"
#include"xVector.h"
#include "yVector.h"
#include "MyString.h"
#include "MyUniquePTR.h"

using namespace std;
//������������ ������ �2
//
//initializer_list, move, default, delete, move ���������
//
//
//������� 1. �������� �����, ������� ������ ������������� 
// ���������������� ������� � ����������� ���������� ������ ���� � �������� ���������.
//
//��������:
//� ����� ��������� �������� ����� � ����������� ���������� � ������ ����� 
// ��������[1, 10].������������ ����� �������� � ��� ������{ 2,-1,3,33, 5,2 }.
//  � ���������� � ����� ������� ������ ��������� ��������{ 2,3,5 }
//��������: ��� ������������� ��� ������������ �� ����� ������ ������� ��������, 
// �������� �������������!��� ������� ������������� �������� ����� �������� ������!
//�	��� �������� ��������� ����������� std::vector.
//
//o	������� 1 : ������������ std::vector � �������� ����������� �������
//o	������� 2 : ����������� ���� ����� �� std::vector � ��� ���� ����� 
// ����� ������ ���� ������������ ������������
//����������� ��� ��������!
//�	���������� �����������, ������� ����� ��������� ����� ���������� 
// ��������(�������� ����� �����������)
//�	���������� ����� ���������� ������ ���������� ��������(�������� ����� �����������)
//�	���������� ����� �������� ������ ���������� ��������(�������� ����� �����������)
//�	������������� ����������� ��������� ��������� �������� ��������
//�	���������� ����� ����������, ������� ����� ��������� � �������� ��������� 
// ������� ����������(�� ����������� / �� �������� / �� �������)
//�	� ������(�������� �� ��� ������) ������
//�	���� ���������� � ����� ������ �� ����������� ������������� ����������� �������������
//�	���������� ����������� ����������� �� ����� ��������� ������ �������� 
// � ������ ���������, ��������:
//vector<int> v;
//std::copy(my.begin(), my.end(), �);
//

int main()
{
{
	cout << "\n";
	//xVector<int>::setInterval(1, 20); //����� ��� �������� ������
	//xVector<double>::setInterval(1, 20); // � ����� ���
	xVector<double> xVdouble{ 1,20,2,-1,3,33, 5,2 };//������ 2 ��� ��������
	xVector<int> xVint{ 1,20,14,-1,3,33, 15,2 };
	xVector<int> xVint2(1,20);

	xVint2.add({ 12,-10,19,303, 5,15 });

	PrintAnyCont(xVint);	cout << "\n";
	//PrintAnyCont(xVdouble);	cout << "\n\n";
	//PrintAnyCont(list<double>{4,8,2.2});
	xVint.add({ 5,6,0 }); //����� ������� ���������
	xVint.add(xVint2); // ����� � ������� �������
	xVint.add(7); // � ����� �� 1 ��������
	PrintAnyCont(xVint);	cout << "\n\n";

	xVint.del(7); //����� �� 1 �������
	xVint.del({ 51,6,0 });// ����� �� �����
	xVint = xVint - xVint2; // � ����� � ���
	PrintAnyCont(xVint);	cout << "\n";

	xVint = xVint + xVint2;// ��� ���� ����� ���������
	PrintAnyCont(xVint);	cout << "\n";
	xVint.resetInterval(1, 10);// ��������� ������� � ������������ �������
	PrintAnyCont(xVint);	cout << "\n";
	xVint.resetInterval(-20, 30);
	xVint2.resetInterval(-20, 30);
	//interval<int> = { -20,30 };
	xVint.add({ -5,-6,-12,7,-3,10 });// �������� ��������, �������������� � ����������
	PrintAnyCont(xVint);	cout << "\n\n";
	//xVint.xsort(xVector<int>::sortMetod::up); // �� �����������
	xVint.x2sort([](const auto a ,const auto b) {return a < b; });
	PrintAnyCont(xVint);	cout << "\n";
	//xVint.xsort(xVector<int>::sortMetod::down);// �� ��������
	xVint.x2sort([](const auto a, const auto b) {return a > b; });
	PrintAnyCont(xVint);	cout << "\n";
	//xVint.xsort(xVector<int>::sortMetod::abs); // �� ������
	xVint.x2sort([](const auto a, const auto b) {return abs(a) < abs(b); });
	PrintAnyCont(xVint);	cout << "\n\n";

	vector<int> v;
	copy(xVint.begin(), xVint.end(), back_inserter(v));// �������� � ������
	PrintAnyCont(v);	cout << "\n--------------------";



	//	--------------------------------------------------------------------
	cout << "\n";
	interval_y<int> = { 1,20 }; //����� ��� �������� ������
	yVector<double>::setInterval(1, 20); // � ����� ���
	yVector<double> yVdouble{ 2,-1,3,33, 5,2 };
	yVector<int> yVint{ 14,-1,3,33, 15,2 };
	yVector<int> yVint2;
	yVint2.add({ 12,-10,19,303, 5,15 });

	PrintAnyCont(yVint);	cout << "\n";
	////PrintAnyCont(list<double>{4,8,2.2});
	yVint.add({ 5,6,0 }); //����� ������� ���������
	yVint.add(yVint2); // ����� � ������� �������
	yVint.add(7); // � ����� �� 1 ��������
	PrintAnyCont(yVint);	cout << "\n\n";

	yVint.del(7); //����� �� 1 �������
	yVint.del({ 51,6,0 });// ����� �� �����
	yVint = yVint - yVint2; // � ����� � ���
	PrintAnyCont(yVint);	cout << "\n";

	yVint = yVint + yVint2;// ��� ���� ����� ���������
	PrintAnyCont(yVint);	cout << "\n";
	yVint.resetInterval(1, 10);// ��������� ������� � ������������ �������
	PrintAnyCont(yVint);	cout << "\n";

	interval_y<int> = { -20,30 };
	yVint.add({ -5,-6,-12,7,-3,10 });// �������� ��������, �������������� � ����������
	PrintAnyCont(yVint);	cout << "\n\n";
	yVint.xsort(yVector<int>::sortMetod::up); // �� �����������
	
	PrintAnyCont(yVint);	cout << "\n";
	yVint.xsort(yVector<int>::sortMetod::down);// �� ��������
	PrintAnyCont(yVint);	cout << "\n";
	yVint.xsort(yVector<int>::sortMetod::abs); // �� ������
	PrintAnyCont(yVint);	cout << "\n\n";

	vector<int> vy;
	copy(yVint.begin(), yVint.end(), back_inserter(v));// �������� � ������
	PrintAnyCont(vy);	cout << "\n";

}

//������� 2. ���������� ������ ������ MyUniquePTR, ������� �������� 
// �������� ��� ��������� �� ������ ������ ����.
//������ � ����� ������ ������������ ����������� �������� �����������
//  ����������� ��������.��������� ���������������� ������� �� ������� MyString :

//

	{
		
		MyUniquePTR<MyString> p1(new MyString("abc"));
		std::cout << p1->GetString()<<"\n";
		p1->SetNewString("qwerty");
		MyString  s2 = *p1;
		//MyUniquePTR< MyString > p2=p1; //����� ���������� ������ �������� ������ => 

		//error C2280: "MyUniquePTR<MyString>::MyUniquePTR(const MyUniquePTR<MyString> &)": 
		// ����������� ������� ������ �� ��������� �������
				 
        //���������! - ��

		MyUniquePTR< MyString > p2 = std::move(p1);

		std::cout << p2->GetString() << "\n";
		std::cout << p1->GetString() << "\n";
		
		if (!p1) { 	std::cout << "No object!\n"; }; //� ��� ������ ��������

		MyUniquePTR< MyString > p3(new MyString("vvv"));

		//p3 = p2; //� ����� ���������� ������ �������� ������
		
		vector< MyUniquePTR< MyString >> v;
         //��� �������������������??? 
		 // ��� ��� �� �������� ������� ��� ������� ����
		// ������� �� ���������� ���� std::move �� ��������
		// ����� ����������� �����������

		v.emplace_back(MyUniquePTR<MyString>(new MyString("1a1bc")));
		v.emplace_back(MyUniquePTR<MyString>(new MyString("2a2bc")));
		v.emplace_back(MyUniquePTR<MyString>(new MyString("3a3bc")));
		
		for(auto& n:v)cout << n->GetString() << "\n";		cout << "\n";

		////��� ����������� �� v � l ???	 
		list< MyUniquePTR< MyString >> l(make_move_iterator(v.begin()), 
										make_move_iterator(v.end()));

		for (auto& n : l)cout << n->GetString() << "\n";
		cout << "\n";
		for (auto& n : v)cout << n->GetString() << "\n";
		


	}

return(0);
}