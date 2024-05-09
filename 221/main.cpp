//�������� 1:
// enum class
// initializer_list � ������������� ������ �������������
// auto
// decltype
// lambda 
// template variable

#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <deque>
#include <map>
#include "func.h"

using namespace std;

int main()
{
	//������� 1. 
	{
		enum class months:unsigned char {January,February,March,April,May,June,July,August,September,October,November,December};

		enum class weekDays { Monday, Tuesday ,Wednesday,Thursday,Friday,Saturday,Sunday};
				
		months m = months::January;

		//�) ������� �������� (��� ������, ��� ���������� ��
		//������ ��������� ������������ ������������ �������
		//���������!)

		//if (m == weekDays::Monday) { /*...*/ }

		//�) ������������� ������������� ������
		months year[] = { months::January,months::February, months::March };
		size_t n = sizeof(year); // 3(12) ����
		//cout << n;
		__asm nop
	}
	/**********************************************************/
		//������� 2. �������� � � ������� ������ �������������
		//��������� ���������� ������ � ���������� - string
		//� ������� range-based for ������������ ��� ����� � 	
		//������� ������� � ��������� ������� ������ ��������
		//�����������
	{
		vector<string> vs{ "a$a","jBhh","C*&^C","ddd","eee"};
		for (const string& st : vs) cout << st << " ; ";
		cout <<  "\n";

		for (string& st : vs)
			for (char& ch : st)
				/*if (islower(ch))ch =*/ toupper(ch);
			
		for (const string& st : vs) cout << st << " ; ";
		cout << "\n";

		__asm nop
	}
	/**********************************************************/
		///������� 3. �������� � ��������� ����������
		//map ����� ��������� (3� � 3�) ����� �������, ����� �� �������� 
		//� �������� ����� �����, � � �������� �������� 
		//��������������� �� �������� ������������ ���� (string), 
		//������������ � ���� �����
		//3�. ������������������ map "�������" ����������� ������ �������������
		//� ������� range-based for � structured binding
		//������������ ����������, ��������: A: any, apple, away
	{
		map<char, set<string>> m3a = { {'y',{"yong"}},{'a',{"away","any","apple"}},{'b',{ "bar"}},{'s',{ "son"}} };
		cout << "\n\n";

		for (const auto& [a, b] : m3a)//
		{
			/* = p;*/
			cout << a << ": ";
			for (const string& s : b)	cout << s << " ; ";
			cout << "\n";
		}
		__asm nop
	}
	//3�. �������� ������ map � ����������� �������� ������
	//��� ���������� �������.
	//� ������� range-based for � structured binding
	//������������ ����������, ��������: A: any, apple, away
	{	//���� (��������):
		//const char* s[] = { "yong", "away", "bar", "any", "son", "apple" };
		// ���� �������� ������, ������ ����������� 
		const char* vs[]={ "explanation","refrigerator","","person","$111", "satisfaction","farmer","village",
						"gate","reflection","opportunity","Pizza","sony","first","goal","growl",
						"explanation" ,"explanation","","$222" };
		std::cout << "\n\n";
		map<char, set<string>> m3b; //���� � ������������, �� multiset
		
		for (const char* st : vs)
			if(*st)
				m3b[toupper(*st)].insert(st);
			
			//catch (exception e) {};// ����� ������� �������, ���������� ��

		for (const auto& [a, b] : m3b)//
		{
			cout << a << ": ";
			for (const string& s : b)
				cout << s << " ; ";
			cout << "\n";
		}
		__asm nop
	}
	/*********************************************************/
		//������� 4. ������� ������� ��� ������ �� ������
		//��������� �������������������, �������� ����:
	{
		cout << "\n\n";
		std::vector<double> vd = { 1.1,2.2,3.3 };
		PrintAnyCont(vd);

		std::string s("abc");
		PrintAnyCont(s);

		int ar[] = { 1, 2, 3 };
		PrintAnyCont(ar);

		std::initializer_list<int> il{ 3,4,5 };
		PrintAnyCont(il);		
		
		__asm nop
	}
	/********************************************************/
		///������� 5. 	
		//C������ ������� ��� "���������" ��������, ��������:
		//����: {1, -2, 5}, �����: {-1, 2, -5})
		//��������� �������� ���� std::string ����� ��������� "aBc1" -> "AbC1"
		//��������� �������������������, �������� ����:
	{
		cout << "\n\n";
		std::vector<double> vd{ 1.1,2.2,3.3 };
		NegateAll(vd);

		PrintAnyCont(vd);

		std::list<std::string> ls{ "aBc", "Qwerty", "n12" };
		NegateAll(ls);

		PrintAnyCont(ls);

		int ar[]{ 1, 2, 3 };
		NegateAll(ar);

		PrintAnyCont(ar);

		__asm nop

	}
	/********************************************************/
		//������� 6. ����������� ������� ���������� �� ������
		//��������� �������������������, �������� ����
		//���������� ��� ���������� ����� ������������ ����������
		//�������� sort(), � ��� ������� ������� - ������-�������
	{	cout << "\n\n";

		std::vector<double> vd = { -3.3,  2.2, -1.1 };
		absSort(vd);
		PrintAnyCont(vd);

		int ar[] = { -3, 2, -1 };
		absSort(ar);
		PrintAnyCont(ar);

		__asm nop
	}
	/********************************************************/
		//������� 7.
		//�������� �������, ������� ����� ����������� �
		//���������� ������, ������ ������� 
		//�������� �������� ������ ��������� ���� 
		//������������������� ������ �����
		//� � ���������� ������� ����.
		//��������� 1: ��� ��� ������������������ ����� ����
		//������ �����, ������� ������� ������ ���������������
		//������� ������������ �� ����
		//��������� 2: ��������� � ����������� �������������
		//���������� copy() � transform(), � ������� 
		//���������������� �������� ������ � ���� �������
		//�������� ������-��������
		//��������:
	{
		cout << "\n\n";

		std::vector<int> v{ 1,2,3,4 };
		std::list<double> l{ 1.1, 2.2, 3.3, 4.4, 5.5 };

		auto res = SumCont(v, l);

		PrintAnyCont2(res);

		std::list<int> ll{ 1, 2, 3, 4, 5, 6, 7, 8 };
		double ar[] = { 1.1, 2.2, 3.3, 4.4, 5.5 };
		auto res2 = SumCont(ar, ll);
		PrintAnyCont2(res2);

		std::set<std::string> s{ "abc", "qwerty", "my" };
		std::deque<const char*> d{ "111", "22" };
		auto res3 = SumCont(s, d);
		PrintAnyCont2(res3);
		__asm nop
	}
	/********************************************************/
		//������� 8. ���������� �������, ������� ��������� ��������� ���������:	
		//�������������� ������������������ ������ ���� � ���������� ������ ����, 
		//��� (������) ���������� ������ ���� �� vector, list, deque, set 
		//� ���������� ���� �� ����, ��� � � �������������� ������������������ 

		//������� ������ "���������" �������� �������� ������������������ � ��� ������ ���������� 
		//�������� ��������� �������. ������� ������ ������-��������
		//�������� ������������������ ��� ���� �� ��������
	{
		cout << "\n\n";

		//�������� 1:
		std::vector<int> v{ 1,2,3,4,5 };
		std::list<int> l; //���� ������
		std::deque<int> d; //� ���� ��������

		Separate(v, l, d, [](const auto a) {return!(a % 2); });
		PrintAnyCont2(l);
		PrintAnyCont2(d);
		__asm nop
	}
	{
		//2.
		//��������� �������� �������: �� ��������, ������� �������� � �������� ��������, � ���� //���������, ��������� - � ������
		cout << "\n\n";
		double ar[] = { 0.8, 1.1, 33.3, -4.1, 5.5 };
		std::set<double> s; //���� ��, ������� �������� � [0,6]
		std::vector<double> v; //���� ���������
		int d1 = 0,d2=6;


		Separate(ar, s, v, [d1,d2](const auto a) {return a>=d1 && a<=d2; });
		PrintAnyCont2(s);
		PrintAnyCont2(v);
	}
	/********************************************************/
		//������� 9. C ������� ��������� for_each()!!! 
		//(� �� count_if()) ��������� ������� ���� � �������
		//��������.
		//  ������������ ������ �������
	{
		char s[] = "Hello World!";
		size_t n{};
		for_each(cbegin(s), cend(s), 
			   [&n](const auto el) {if (isupper(el)) n++; });

		cout << "\n\nUppercase letters- "<<n<<"\n\n";

		__asm nop
	}
	/********************************************************/
		//������� 10. ����������� ����������� enum � ��������� �������������  - enumToString
		// � �������� - stringToEnum
		//���������: 
		//***********
		//1. ��������������� ����������� ���������� ������ ��� ����� ����� ���-�� ������� =>
		//1.1 ����������� ��������� � ������������ ������ ���� ����������� => ��������������� ������
		//���� ������ ���� �����������, => ���������� ������ ����� ���� ������������ � ��������
		//����� � std::map
		//1.2 � ��� �������� (��������������� ���������� ����������)
		//����� ���� ������ � ���� ����� ����������� (�������� ������, ������, ��� �������� �� �����������) 
		//=> �������� ��������� std::map<string,<��������> >
		//1.3 �������� ��������� �++11 ���������� ������������� ���� ����� ���� ������� ������� � ����,
		//� �������� �� ���������� ������������� ����������� 
		//***********
		//2.1 ��� ��� ���� ������������ ������, �� enumToString � stringToEnum ������ ���� ����������
		//2.2 ������������ ����� ��������� ��� ������������ �������� � ������� ��������, �������
		//   ������ �� ������������� => ������!
		//***********
		//3. ����� �������� � map<string, <��������> > �� �������� �� ���� ������������, ��������� ��� ��������������
		//��������� ���������� (� ��������� ��������� � ����������� ������������� ��������� ����������)
		//***********
	{
		//��������:
		//enum class color :char { red, green, blue, magenta, yellow, white }; ����� ���!!!
			Col2 c1,c2,c3; 
			try {
				c1 = stringToEnum<Col2>("blue");
			}
			catch (string err)
			{
				cout << "\n" << err << "\n\n";
			}
			
			try {
				c2 = stringToEnum<Col2>("red");
			}
			catch (string err)
			{
				cout << "\n" << err << "\n\n";
			}

			try {
				c3 = stringToEnum<Col2>("purple");
			}
			catch (string err)
			{
				cout << "\n"<<err<<"\n\n";
			}

			auto Str = enumToString(c1);
			auto Str1 = enumToString(c2);
			auto Str2 = enumToString(c3);

			cout << Str<<"\n" << Str1 << "\n" << Str2 ;

			__asm nop
	}

	return 0;
}
