//Практика 1:
// enum class
// initializer_list и универсальные списки инициализации
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
	//Задание 1. 
	{
		enum class months:unsigned char {January,February,March,April,May,June,July,August,September,October,November,December};

		enum class weekDays { Monday, Tuesday ,Wednesday,Thursday,Friday,Saturday,Sunday};
				
		months m = months::January;

		//а) уберите проблемы (это значит, что КОМПИЛЯТОР не
		//должен позволять программисту осуществлять опасные
		//сравнения!)

		//if (m == weekDays::Monday) { /*...*/ }

		//б) оптимизируйте использование памяти
		months year[] = { months::January,months::February, months::March };
		size_t n = sizeof(year); // 3(12) байт
		//cout << n;
		__asm nop
	}
	/**********************************************************/
		//Задание 2. Создайте и с помощью списка инициализации
		//заполните значениями вектор с элементами - string
		//С помощью range-based for преобразуйте все буквы в 	
		//верхний регистр а остальные символы должны остаться
		//неизменными
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
		///Задание 3. Создайте и заполните значениями
		//map двумя способами (3а и 3б) таким образом, чтобы он содержал 
		//в качестве ключа букву, а в качестве значения 
		//отсортированную по алфавиту совокупность слов (string), 
		//начинающихся с этой буквы
		//3а. Проинициализируйте map "вручную" посредством списка инициализации
		//С помощью range-based for и structured binding
		//распечатайте содержимое, например: A: any, apple, away
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
	//3б. Создайте пустой map и используйте заданный массив
	//для выполнения задания.
	//С помощью range-based for и structured binding
	//распечатайте содержимое, например: A: any, apple, away
	{	//дано (например):
		//const char* s[] = { "yong", "away", "bar", "any", "son", "apple" };
		// чуть расширил задачу, просто попробовать 
		const char* vs[]={ "explanation","refrigerator","","person","$111", "satisfaction","farmer","village",
						"gate","reflection","opportunity","Pizza","sony","first","goal","growl",
						"explanation" ,"explanation","","$222" };
		std::cout << "\n\n";
		map<char, set<string>> m3b; //если с повторениями, то multiset
		
		for (const char* st : vs)
			if(*st)
				m3b[toupper(*st)].insert(st);
			
			//catch (exception e) {};// ловим нулевые стринги, игнорируем их

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
		//Задание 4. создать функцию для вывода на печать
		//элементов последовательностей, заданных ниже:
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
		///Задание 5. 	
		//Cоздать функцию для "отрицания" значений, например:
		//было: {1, -2, 5}, стало: {-1, 2, -5})
		//изменение объектов типа std::string может выглядеть "aBc1" -> "AbC1"
		//элементов последовательностей, заданных ниже:
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
		//Задание 6. Реализовать функцию сортировки по модулю
		//элементов последовательностей, заданных ниже
		//Собственно для сортировки можно использовать обобщенный
		//алгоритм sort(), а для задания условия - лямбда-функцию
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
		//Задание 7.
		//Напишите функцию, которая будет формировать и
		//возвращать вектор, каждый элемент 
		//которого является суммой элементов двух 
		//последовательностей РАЗНОЙ длины
		//и с элементами РАЗНОГО типа.
		//Подсказка 1: так как последовательности могут быть
		//разной длины, логично сделать размер результирующего
		//вектора максимальным из двух
		//Подсказка 2: подумайте о возможности использования
		//алгоритмов copy() и transform(), в котором 
		//трансформирующее действие удобно в свою очередь
		//задавать лямбда-функцией
		//например:
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
		//Задание 8. Реализуйте функцию, которая принимает следующие параметры:	
		//сформированную последовательность любого типа с элементами любого типа, 
		//два (пустых) контейнера любого типа из vector, list, deque, set 
		//с элементами того же типа, что и у сформированной последовательности 

		//Функция должна "разложить" значения заданной последовательности в два пустых контейнера 
		//согласно заданному условию. Условие задать лямбда-функцией
		//Исходная последовательность при этом не меняется
	{
		cout << "\n\n";

		//Например 1:
		std::vector<int> v{ 1,2,3,4,5 };
		std::list<int> l; //сюда четные
		std::deque<int> d; //а сюда нечетные

		Separate(v, l, d, [](const auto a) {return!(a % 2); });
		PrintAnyCont2(l);
		PrintAnyCont2(d);
		__asm nop
	}
	{
		//2.
		//Разложить согласно условию: те значения, которые попадают в заданный диапазон, в один //контейнер, остальные - в другой
		cout << "\n\n";
		double ar[] = { 0.8, 1.1, 33.3, -4.1, 5.5 };
		std::set<double> s; //сюда те, которые попадают в [0,6]
		std::vector<double> v; //сюда остальные
		int d1 = 0,d2=6;


		Separate(ar, s, v, [d1,d2](const auto a) {return a>=d1 && a<=d2; });
		PrintAnyCont2(s);
		PrintAnyCont2(v);
	}
	/********************************************************/
		//Задание 9. C помощью алгоритма for_each()!!! 
		//(а не count_if()) посчитать сколько букв в верхнем
		//регистре.
		//  Использовать лямбда функцию
	{
		char s[] = "Hello World!";
		size_t n{};
		for_each(cbegin(s), cend(s), 
			   [&n](const auto el) {if (isupper(el)) n++; });

		cout << "\n\nUppercase letters- "<<n<<"\n\n";

		__asm nop
	}
	/********************************************************/
		//Задание 10. Реализовать конвертацию enum в строковое представление  - enumToString
		// и наоборот - stringToEnum
		//Подсказки: 
		//***********
		//1. Соответствующие именованным константам строки все равно нужно где-то хранить =>
		//1.1 Именованные константы в перечислении должны быть уникальными => соответствующие строки
		//тоже должны быть уникальными, => уникальные строки могут быть использованы в качестве
		//ключа в std::map
		//1.2 а вот значения (соответствующие именованым константам)
		//могут быть любыми и даже могут повторяться (упрощаем задачу, считая, что значения НЕ повторяются) 
		//=> подходит контейнер std::map<string,<значение> >
		//1.3 Согласно стандарту С++11 переменные перечислимого типа могут быть разного размера и типа,
		//а хотелось бы обеспечить универсальную конвертацию 
		//***********
		//2.1 Так как типы перечислений разные, то enumToString и stringToEnum должны быть шаблонными
		//2.2 Пользователь может ошибиться или злонамеренно передать в функции значения, которым
		//   ничего не соответствует => защита!
		//***********
		//3. Чтобы действия с map<string, <значение> > не зависили от типа перечисления, подумайте над использованием
		//шаблонной переменной (в частности вспомните о возможности специялизации шаблонной переменной)
		//***********
	{
		//Например:
		//enum class color :char { red, green, blue, magenta, yellow, white }; пёрпла нет!!!
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
