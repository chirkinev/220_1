//������������ ������ �2
//
//initializer_list, move, default, delete, move ���������
//
//
//������� 1. �������� �����, ������� ������ ������������� ���������������� ������� � ����������� ���������� ������ ���� � �������� ���������.
//
//��������:
//� ����� ��������� �������� ����� � ����������� ���������� � ������ ����� ��������[1, 10].������������ ����� �������� � ��� ������{ 2,-1,3,33, 5,2 }. � ���������� � ����� ������� ������ ��������� ��������{ 2,3,5 }
//��������: ��� ������������� ��� ������������ �� ����� ������ ������� ��������, �������� �������������!��� ������� ������������� �������� ����� �������� ������!
//�	��� �������� ��������� ����������� std::vector.
//
//o	������� 1 : ������������ std::vector � �������� ����������� �������
//o	������� 2 : ����������� ���� ����� �� std::vector � ��� ���� ����� ����� ������ ���� ������������ ������������
//����������� ��� ��������!
//�	���������� �����������, ������� ����� ��������� ����� ���������� ��������(�������� ����� �����������)
//�	���������� ����� ���������� ������ ���������� ��������(�������� ����� �����������)
//�	���������� ����� �������� ������ ���������� ��������(�������� ����� �����������)
//�	������������� ����������� ��������� ��������� �������� ��������
//�	���������� ����� ����������, ������� ����� ��������� � �������� ��������� ������� ����������(�� ����������� / �� �������� / �� �������)
//�	� ������(�������� �� ��� ������) ������
//�	���� ���������� � ����� ������ �� ����������� ������������� ����������� �������������
//�	���������� ����������� ����������� �� ����� ��������� ������ �������� � ������ ���������, ��������:
//vector<int> v;
//std::copy(my.begin(), my.end(), �);
//
//������� 2. ���������� ������ ������ MyUniquePTR, ������� �������� �������� ��� ��������� �� ������ ������ ����.
//������ � ����� ������ ������������ ����������� �������� ����������� ����������� ��������.��������� ���������������� ������� �� ������� MyString :
//{
//	MyUniquePTR<MyString> p1(new MyString(�abc�));
//	std::cout << p1->GetString();
//	p1->SetNewString(�qwerty�);
//	MyString  s2 = *p1;
//	//MyUniquePTR< MyString > p2=p1; //����� ���������� ������ �������� ������ => 
//	���������!
//		If(p1) { std::cout << �No object!� } //� ��� ������ ��������
//	MyUniquePTR< MyString > p3(new MyString(�vvv�));
//	//p3 = p2; //� ����� ���������� ������ �������� ������
//	vector< MyUniquePTR< MyString >> v; //��� �������������������???
//	list< MyUniquePTR< MyString >> l;
//	//��� ����������� �� v � l ???
//}
//
