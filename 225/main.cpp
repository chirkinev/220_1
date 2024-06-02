#include <iostream>
#include <memory>
#include <vector>
#include <set>
#include <algorithm>
#include <string>
#include <list>
#include <fstream>
#include "hh.h"



int main()
{

	//////////////////////////////////////////////////////////////////////////////////////////////
	//������� 1. unique_ptr
	{

		//1.� - ���������� ���������� ���������� ���������
		{
			std::vector<std::string*> v = 
			{ new std::string("aa"), new std::string("bb"), new std::string("cc") };
			//������������ ��� ������
						
			for (std::string* s : v) std::cout << *s<<" ; ";

			for (std::string* s : v) delete s;
		__asm nop

		std::cout << "\n";
		} //???

		//1.b - ������������� ������� 1.�:
		 //���������� ����������� std::unique_ptr: 
		 //����������� ���������� (��������� ��� ������ ������� ������������ std::unique_ptr), 
		 //���������� �������� ���������� �� ����������� ����������� ������� std::string, 
		 //���������������,
		 //� ������������ ��������
		 //

		{
			std::vector<std::unique_ptr<std::string>> v;
			v.push_back(std::unique_ptr<std::string>(new std::string("aa")));
			v.push_back(std::unique_ptr<std::string>(new std::string("bb")));
			v.push_back(std::make_unique<std::string>(std::string("cc")));
			v.emplace_back(new std::string("bb88"));


			//������������ ��� ������
			for (auto it = v.cbegin(); it != v.cend();++it)
				std::cout << **it << " ; ";
			
			__asm nop
			std::cout << "\n";
			
			//??? ����������� ����������� ��������� ��������?
		} // ���� ����� ��� ������ ����������� ����_���

		{//1.c - ��������� ������� 1.b �������� ����������� �������� ���������� ������
		 //��������� ������� (��������, �������� ��������� �������: "AAA" -> "AAA_1")  



			std::vector<std::unique_ptr<std::string>> v;
			v.push_back(std::unique_ptr<std::string>(new std::string("aa")));
			v.push_back(std::unique_ptr<std::string>(new std::string("bb")));//���
			v.push_back(std::make_unique<std::string>(std::string("cc")));//  � ���

					//������������ ��� ������
					std::cout << "\n";
					for (auto it = v.cbegin(); it != v.cend(); ++it)
						std::cout << **it << " ; ";

			for (auto it = v.cbegin(); it != v.cend(); ++it)
				 **it= **it+"_1";

					//������������ ��� ������
					std::cout << "\n";
					for (auto it = v.cbegin(); it != v.cend(); ++it)
						std::cout << **it << " ; ";

			__asm nop

			std::cout << "\n";
			
		}

		{//1.d - ������������ ������ ��������	

		 //�������� unique_ptr, ������� �������� �������� ��� ������������� �������
		 //� ���������� std::string
		 //� ������� unique_ptr::operator[] ��������� ��������� ������ ����������
		 //����� ���������� ������������ ������?

			size_t n = 5;
			
			std::unique_ptr < std::string[] > upv{new std::string[5]};
			for (size_t i = 0; i < n; i++)
			{
				upv[i] = (std::string("a_") + std::to_string(i));
			}

			for (size_t i = 0; i < n; i++)
			{
				std::cout << upv[i]<<" ; ";
			}
			__asm nop
		}// ������������ ������

		{//1.e - ������� ������������ �������� � ���������������� delete-������� (�������)
		 //����� �������� ������ ���������� �� ����������� ��������� �������
		 //�������� unique_ptr ��� ������ �������
		 //���������� ���������������� delete-������� (�������) ��� ����������� 
		 //������������ ������

			std::string* arStrPtr[] = 
			{ new std::string("aa"), 
				new std::string("bb"), 
				new std::string("cc") };

			auto destroerA = [s= size(arStrPtr) ](std::string** b) {
				for (size_t i = 0; i < /*std::size(b)*//*sizeof(b) / sizeof(b[0])*/s; i++)
					// ��� ������ ��������?
					{
						delete b[i];
						b[i] = 0;
					}
				};

			std::unique_ptr<std::string*[], decltype(destroerA)> ups{ arStrPtr,destroerA };
			for (size_t i = 0; i < size(arStrPtr); i++)
				std::cout << *ups[i];
			__asm nop
		}

		{//1.f �������� � ��������� ������, ���������� unique_ptr ��� ���������� �� std::string
			//����������� ��������� copy() ���������� �������� ������� � ������ ������ � ���������� 
			//���� �� ����
			//���������: ������������ ��������� � ������ std::make_move_iterator
			std::vector<std::unique_ptr<std::string>> v;
			v.push_back(std::unique_ptr<std::string>(new std::string("aa")));
			v.push_back(std::unique_ptr<std::string>(new std::string("bb")));//���
			v.push_back(std::make_unique<std::string>(std::string("cc")));//  � ���

			std::list<std::unique_ptr<std::string>> lv(v.size());

			std::copy(std::make_move_iterator(v.begin()),
				      std::make_move_iterator(v.end()),
				      lv.begin());

			__asm nop

		}
		__asm nop

	}

	////////////////////////////////////////////////////////////////////////////////
	//������� 2.shared_ptr + ���������������� delete-������� 

	//����������� ����������� ������ � ���� ������ (�������) �� ������ ���������� 
	//��� ��� ��� "��������" ����� �� ������� ���������� ���� ������ � ���� � ��� �� ����,
	//������� ������������ �� ����������� ������������ ����� � ��� �� �������� ������ ������ =>
	//���������� �������� ��� ������ ��������� �������� shared_ptr
	//�. ������ �������� ������ �������/������� ���� ��� ������
	//�. ��� ��������� �������� ������ �������������� � �������������
	//�. ��������� �������� ��������� ������ ������� ����

	//���������: ����������� ������� ������ ����� � ������� ������� rand()
	
	{
		

	std::string fmame{ "test1.txt" };

	std::shared_ptr<std::ofstream> writer1(new std::ofstream(fmame), fcloser1(fmame));
	auto writer2 = writer1;
	//"��������":
	//������� writer1, writer2

	//�������� ����� �������� ��������� ������� ��������� ������ �� "���������" �������� � ����
	//���� �������
	
	for (size_t i = 0; i < 10; i++)
	{
		if (rand() > RAND_MAX / 2) 
			  *writer2 << i<<" writer2\n";
		else  *writer1 << i<<" writer1\n";
	}



	__asm nop
	}//�������� �����???

	
	/***************************************************************/
	//������� 3.
	{
		std::cout << "----------\n";
		//��� ������ ��������� ���� string
		std::string strings[] = { "abc", "123", "qwerty", "#$%","aaa","345","!!!"};
		//�� ���������� ��������� ������ ������ ������������ � ������������ ����������.
		//��������� ���������� ��������������� �������� 
		// �) ��� ����������� � 
		// �) ��� ��������� �������
		//��������� � �������!
		auto no_delete = [](std::string* a) {};

		/*std::shared_ptr<std::string[]> ss (strings, no_delete);	*/ //��� �� ������
				
		std::vector< std::shared_ptr<std::string> > v_sptr;

		for (size_t i = 0; i < std::size(strings); i++)
			v_sptr.emplace_back(& strings[i], no_delete);
		
		//� std::set "����������" �� �������� ������� ��� �����, ������� �������� ������ ����� 

		auto s_lesser = [](const std::shared_ptr<std::string>& a,
			               const std::shared_ptr<std::string>& b) 
							{return *a < *b; };

		std::set<std::shared_ptr<std::string>,decltype(s_lesser)>set_s(s_lesser);

		for (auto it = v_sptr.cbegin(); it!=v_sptr.cend() ; ++it)
			if (only_letter(**it))
				set_s.insert(*it);
		
		__asm nop
		/******************************************************************************************/

		//� std::vector "����������" ������� ��� �����, ������� �������� ������ ����� 
		//������� �� �����
		//������� �����
		std::cout <<"\n";

		std::vector<std::shared_ptr < std::string>> v_sptr_d;

		for (auto it = v_sptr.cbegin(); it != v_sptr.cend(); ++it)
			if (only_digit(**it))
				v_sptr_d.push_back(*it);

		for (const std::shared_ptr<std::string>& st : v_sptr_d)
			std::cout << *st << " ; ";

		size_t sum{ 0 };
		for (const std::shared_ptr<std::string>& st : v_sptr_d)
			sum += stoi(*st);

		std::cout << "Sum= " << sum<<"\n";
		/******************************************************************************************/
		//���� "����������" ������� ��� �����, ������� �� �������� �� �������� ����, 
		// �� �������� ����
		//� ������ �������

		std::vector<std::shared_ptr < std::string>> v_sptr_hz;
		for (auto it = v_sptr.cbegin(); it != v_sptr.cend(); ++it)
			if (no_let_no_digit(**it))
				v_sptr_hz.push_back(*it);

		for (const std::shared_ptr<std::string>& st : v_sptr_hz)
			std::cout << *st << " ; ";

		__asm nop
		std::cout << "\n";
		
	}


	/******************************************************************************************/
	//������� 4. 
	{
		auto no_delete = [](std::string* a) {};
		//����:
		std::string ar[] = { "my","Hello", "World" };
		std::vector < std::shared_ptr<std::string>> 
			v = { std::make_shared<std::string>("good"), std::make_shared<std::string>("bye") };

		for (size_t i = 0; i < std::size(ar); i++)
			v.emplace_back(&ar[i], no_delete);

		//�) ��������� �������� � ������ ������� ��� ��������� �������, 
		// �� ������� �������� �������! 
		//�) ������������� ������ �� �������� � ������� �� �����
		//�) ���������� ���������� ������������ ������

		auto greater_sptr = [](const std::shared_ptr<std::string>& a,
								const std::shared_ptr<std::string>& b)
									{return *a < *b; };																	// ���� ��� ����� �������� +std::transform(str.begin(), str.end(), str.begin(), ::toupper);

		std::sort(v.begin(), v.end(), greater_sptr);

		for (const std::shared_ptr<std::string>& st : v)
			std::cout << *st << " ; ";

		
		std::cout << "\n\n";
		__asm nop
	}
	/***************************************************************/
		//������� 5. shared_ptr � weak_ptr
		//������� ��������������� ������ ����������� ������ human. � ������ ��������:
		//��� - string
		//�������� �������: ��� ��� ��� ���...
		//�������� - shared_ptr (�������� �� ������ ��������...)
		//���� - ��������� �� weak_ptr (����� �������� ����������� ������������)

		//������ ������ human:
		//����������� - ��� ������������� ����� � ��������
		//����������� �����������, �������� ������������, move ???
		//����������� ����� child() - 
		//				������ ������� ������� � ������� ������� ��� ����������� ��������
		//				+ ������������ ��� ����� ������� � ���������� � ��������

		//������ ����������� ����������� ��������������� ������ ��� ���������� ����������

	{
		//������� ������ � ����-�� ���������� => "����-���� ��� �� ����, ��������, ���� � ���"
		//(�� ���� �� ����� ���� ��� ���� � ��� ����):
#define sptr_h std::shared_ptr<human>

	sptr_h g_dad1 (new human("Adam",human::sex::male,true)) ;//����-���� ���
	sptr_h g_mom1(new human{ "Eva",human::sex::female,true });//�� ����

	sptr_h g_dad2(new human{ "Lucifer",human::sex::male,true });//�� ����� ���� ��� ����
	sptr_h g_mom2(new human{ "Lilit",human::sex::female,true });//� ��� ����

	sptr_h ded_br=(human::child("Kain", human::sex::male, g_mom1, g_dad1));//������ ��� 2� �������
	sptr_h dad=(human::child("Avel", human::sex::male, g_mom1, g_dad1));

	sptr_h mom_s=(human::child("Kesa", human::sex::female,g_mom2, g_dad2));//������ ��� 2� �������
	sptr_h mom=( human::child("Lilim", human::sex::female, g_mom2, g_dad2));

	(*g_dad1).is_dead();
	(*dad).is_dead();

	sptr_h doth = (human::child("Masha", human::sex::female, mom, dad)); // � ������

	(*doth).print_g();
	
		//std::shared_ptr<human> grandM1(new human("Eva"));
		//...

		//� ��� ��������� ���� - child():


		//� � ����� � ���� ������� ���� ����:


		//...
		__asm nop
	}





	__asm nop
	return 0;
}
