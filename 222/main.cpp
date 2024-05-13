
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
//Лабораторная работа №2
//
//initializer_list, move, default, delete, move итераторы
//
//
//Задание 1. Создайте класс, который должен предоставлять 
// функциональность вектора с УНИКАЛЬНЫМИ значениями любого типа в заданном диапазоне.
//
//Например:
//В нашей структуре хранятся целые с уникальными значениями и данных задан 
// диапазон[1, 10].Пользователь хочет добавить в наш вектор{ 2,-1,3,33, 5,2 }.
//  В результате в нашем векторе должны храниться значения{ 2,3,5 }
//Внимание: при инициализации или присваивании НЕ нужно менять порядок значений, 
// заданный пользователем!При наличии повторяющихся значений нужно оставить первое!
//•	Для хранения элементов используйте std::vector.
//
//o	Вариант 1 : использовать std::vector в качестве внедренного объекта
//o	Вариант 2 : наследовать свой класс от std::vector – при этом важно 
// каким должен быть спецификатор наследования
//Реализовать оба варианта!
//•	Реализуйте конструктор, который может принимать любое количество 
// значений(значения могут повторяться)
//•	Реализуйте метод добавления любого количества значений(значения могут повторяться)
//•	Реализуйте метод удаления любого количества значений(значения могут повторяться)
//•	Предусмотрите возможность изменения диапазона хранимых значений
//•	Реализуйте метод сортировки, который будет принимать в качестве параметра 
// условие сортировки(по возрастанию / по убыванию / по модулю…)
//•	и другие(полезные на Ваш взгляд) методы
//•	явно обозначьте – какие методы вы делегируете сгенерировать компилятору автоматически
//•	реализуйте возможность копирования из нашей структуры данных значения 
// в другое хранилище, например:
//vector<int> v;
//std::copy(my.begin(), my.end(), …);
//

int main()
{
{
	cout << "\n";
	//xVector<int>::setInterval(1, 20); //можно так интервал задать
	//xVector<double>::setInterval(1, 20); // а можно так
	xVector<double> xVdouble{ 1,20,2,-1,3,33, 5,2 };//первые 2 это интервал
	xVector<int> xVint{ 1,20,14,-1,3,33, 15,2 };
	xVector<int> xVint2(1,20);

	xVint2.add({ 12,-10,19,303, 5,15 });

	PrintAnyCont(xVint);	cout << "\n";
	//PrintAnyCont(xVdouble);	cout << "\n\n";
	//PrintAnyCont(list<double>{4,8,2.2});
	xVint.add({ 5,6,0 }); //можно списком добавлять
	xVint.add(xVint2); // можно с другого вектора
	xVint.add(7); // а можно по 1 элементу
	PrintAnyCont(xVint);	cout << "\n\n";

	xVint.del(7); //Можно по 1 убирать
	xVint.del({ 51,6,0 });// можно по кучке
	xVint = xVint - xVint2; // а можно и так
	PrintAnyCont(xVint);	cout << "\n";

	xVint = xVint + xVint2;// так тоже можно добавлять
	PrintAnyCont(xVint);	cout << "\n";
	xVint.resetInterval(1, 10);// уменьшаем интевал с выкидыванием лишнего
	PrintAnyCont(xVint);	cout << "\n";
	xVint.resetInterval(-20, 30);
	xVint2.resetInterval(-20, 30);
	//interval<int> = { -20,30 };
	xVint.add({ -5,-6,-12,7,-3,10 });// накидаем значений, подготовливаем к сортировке
	PrintAnyCont(xVint);	cout << "\n\n";
	//xVint.xsort(xVector<int>::sortMetod::up); // по возрастанию
	xVint.x2sort([](const auto a ,const auto b) {return a < b; });
	PrintAnyCont(xVint);	cout << "\n";
	//xVint.xsort(xVector<int>::sortMetod::down);// по убыванию
	xVint.x2sort([](const auto a, const auto b) {return a > b; });
	PrintAnyCont(xVint);	cout << "\n";
	//xVint.xsort(xVector<int>::sortMetod::abs); // по модулю
	xVint.x2sort([](const auto a, const auto b) {return abs(a) < abs(b); });
	PrintAnyCont(xVint);	cout << "\n\n";

	vector<int> v;
	copy(xVint.begin(), xVint.end(), back_inserter(v));// копируем в вектор
	PrintAnyCont(v);	cout << "\n--------------------";



	//	--------------------------------------------------------------------
	cout << "\n";
	interval_y<int> = { 1,20 }; //можно так интервал задать
	yVector<double>::setInterval(1, 20); // а можно так
	yVector<double> yVdouble{ 2,-1,3,33, 5,2 };
	yVector<int> yVint{ 14,-1,3,33, 15,2 };
	yVector<int> yVint2;
	yVint2.add({ 12,-10,19,303, 5,15 });

	PrintAnyCont(yVint);	cout << "\n";
	////PrintAnyCont(list<double>{4,8,2.2});
	yVint.add({ 5,6,0 }); //можно списком добавлять
	yVint.add(yVint2); // можно с другого вектора
	yVint.add(7); // а можно по 1 элементу
	PrintAnyCont(yVint);	cout << "\n\n";

	yVint.del(7); //Можно по 1 убирать
	yVint.del({ 51,6,0 });// можно по кучке
	yVint = yVint - yVint2; // а можно и так
	PrintAnyCont(yVint);	cout << "\n";

	yVint = yVint + yVint2;// так тоже можно добавлять
	PrintAnyCont(yVint);	cout << "\n";
	yVint.resetInterval(1, 10);// уменьшаем интевал с выкидыванием лишнего
	PrintAnyCont(yVint);	cout << "\n";

	interval_y<int> = { -20,30 };
	yVint.add({ -5,-6,-12,7,-3,10 });// накидаем значений, подготовливаем к сортировке
	PrintAnyCont(yVint);	cout << "\n\n";
	yVint.xsort(yVector<int>::sortMetod::up); // по возрастанию
	
	PrintAnyCont(yVint);	cout << "\n";
	yVint.xsort(yVector<int>::sortMetod::down);// по убыванию
	PrintAnyCont(yVint);	cout << "\n";
	yVint.xsort(yVector<int>::sortMetod::abs); // по модулю
	PrintAnyCont(yVint);	cout << "\n\n";

	vector<int> vy;
	copy(yVint.begin(), yVint.end(), back_inserter(v));// копируем в вектор
	PrintAnyCont(vy);	cout << "\n";

}

//Задание 2. Реализуйте шаблон класса MyUniquePTR, который является 
// оберткой для указателя на объект любого типа.
//Задача – класс должен обеспечивать единоличное владение динамически
//  создаваемым объектом.Проверить функционирование шаблона на примере MyString :

//

	{
		
		MyUniquePTR<MyString> p1(new MyString("abc"));
		std::cout << p1->GetString()<<"\n";
		p1->SetNewString("qwerty");
		MyString  s2 = *p1;
		//MyUniquePTR< MyString > p2=p1; //здесь компилятор должен выдавать ошибку => 

		//error C2280: "MyUniquePTR<MyString>::MyUniquePTR(const MyUniquePTR<MyString> &)": 
		// предпринята попытка ссылки на удаленную функцию
				 
        //Исправьте! - ок

		MyUniquePTR< MyString > p2 = std::move(p1);

		std::cout << p2->GetString() << "\n";
		std::cout << p1->GetString() << "\n";
		
		if (!p1) { 	std::cout << "No object!\n"; }; //а это должно работать

		MyUniquePTR< MyString > p3(new MyString("vvv"));

		//p3 = p2; //и здесь компилятор должен выдавать ошибку
		
		vector< MyUniquePTR< MyString >> v;
         //как проинициализировать??? 
		 // так или из простого массива как описано ниже
		// списком не получается даже std::move не помогает
		// хочет конструктор копирования

		v.emplace_back(MyUniquePTR<MyString>(new MyString("1a1bc")));
		v.emplace_back(MyUniquePTR<MyString>(new MyString("2a2bc")));
		v.emplace_back(MyUniquePTR<MyString>(new MyString("3a3bc")));
		
		for(auto& n:v)cout << n->GetString() << "\n";		cout << "\n";

		////как скопировать из v в l ???	 
		list< MyUniquePTR< MyString >> l(make_move_iterator(v.begin()), 
										make_move_iterator(v.end()));

		for (auto& n : l)cout << n->GetString() << "\n";
		cout << "\n";
		for (auto& n : v)cout << n->GetString() << "\n";
		


	}

return(0);
}