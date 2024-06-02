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
	//Задание 1. unique_ptr
	{

		//1.а - обеспечьте корректное выполнение фрагмента
		{
			std::vector<std::string*> v = 
			{ new std::string("aa"), new std::string("bb"), new std::string("cc") };
			//Распечатайте все строки
						
			for (std::string* s : v) std::cout << *s<<" ; ";

			for (std::string* s : v) delete s;
		__asm nop

		std::cout << "\n";
		} //???

		//1.b - модифицируйте задание 1.а:
		 //обеспечьте посредством std::unique_ptr: 
		 //эффективное заполнение (вспомните про разные способы формирования std::unique_ptr), 
		 //безопасное хранение указателей на динамически создаваемые объекты std::string, 
		 //манипулирование,
		 //и освобождение ресурсов
		 //

		{
			std::vector<std::unique_ptr<std::string>> v;
			v.push_back(std::unique_ptr<std::string>(new std::string("aa")));
			v.push_back(std::unique_ptr<std::string>(new std::string("bb")));
			v.push_back(std::make_unique<std::string>(std::string("cc")));
			v.emplace_back(new std::string("bb88"));


			//Распечатайте все строки
			for (auto it = v.cbegin(); it != v.cend();++it)
				std::cout << **it << " ; ";
			
			__asm nop
			std::cout << "\n";
			
			//??? Уничтожение динамически созданных объектов?
		} // сами умрут при вызове деструктора юник_птр

		{//1.c - дополните задание 1.b добавьте возможность изменять хранящиеся строки
		 //следующим образом (например, добавить указанный суффикс: "AAA" -> "AAA_1")  



			std::vector<std::unique_ptr<std::string>> v;
			v.push_back(std::unique_ptr<std::string>(new std::string("aa")));
			v.push_back(std::unique_ptr<std::string>(new std::string("bb")));//так
			v.push_back(std::make_unique<std::string>(std::string("cc")));//  и так

					//Распечатайте все строки
					std::cout << "\n";
					for (auto it = v.cbegin(); it != v.cend(); ++it)
						std::cout << **it << " ; ";

			for (auto it = v.cbegin(); it != v.cend(); ++it)
				 **it= **it+"_1";

					//Распечатайте все строки
					std::cout << "\n";
					for (auto it = v.cbegin(); it != v.cend(); ++it)
						std::cout << **it << " ; ";

			__asm nop

			std::cout << "\n";
			
		}

		{//1.d - динамический массив объектов	

		 //Создайте unique_ptr, который является оберткой для динамического массива
		 //с элементами std::string
		 //С помощью unique_ptr::operator[] заполните обернутый массив значениями
		 //Когда происходит освобождения памяти?

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
		}// освобождение памяти

		{//1.e - массивы динамических объектов и пользовательская delete-функция (функтор)
		 //Задан стековый массив указателей на динамически созданные объекты
		 //Создайте unique_ptr для такого массива
		 //Реализуйте пользовательскую delete-функцию (функтор) для корректного 
		 //освобождения памяти

			std::string* arStrPtr[] = 
			{ new std::string("aa"), 
				new std::string("bb"), 
				new std::string("cc") };

			auto destroerA = [s= size(arStrPtr) ](std::string** b) {
				for (size_t i = 0; i < /*std::size(b)*//*sizeof(b) / sizeof(b[0])*/s; i++)
					// как размер получить?
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

		{//1.f Создайте и заполните вектор, содержащий unique_ptr для указателей на std::string
			//Посредством алгоритма copy() скопируйте элементы вектора в пустой список с элементами 
			//того же типа
			//Подсказка: перемещающие итераторы и шаблон std::make_move_iterator
			std::vector<std::unique_ptr<std::string>> v;
			v.push_back(std::unique_ptr<std::string>(new std::string("aa")));
			v.push_back(std::unique_ptr<std::string>(new std::string("bb")));//так
			v.push_back(std::make_unique<std::string>(std::string("cc")));//  и так

			std::list<std::unique_ptr<std::string>> lv(v.size());

			std::copy(std::make_move_iterator(v.begin()),
				      std::make_move_iterator(v.end()),
				      lv.begin());

			__asm nop

		}
		__asm nop

	}

	////////////////////////////////////////////////////////////////////////////////
	//Задание 2.shared_ptr + пользовательская delete-функция 

	//Реализовать возможность записи в файл данных (строчек) из разных источников 
	//Так как все "писатели" будут по очереди записывать свои данные в один и тот же файл,
	//логично предоставить им возможность пользоваться одним и тем же объектом потока вывода =>
	//безопасной оберткой для такого указателя является shared_ptr
	//а. Первый владелец должен открыть/создать файл для записи
	//б. Все остальные писатели должны присоединиться к использованию
	//в. Последний владелец указателя должен закрыть файл

	//Подсказка: имитировать порядок записи можно с помощью функции rand()
	
	{
		

	std::string fmame{ "test1.txt" };

	std::shared_ptr<std::ofstream> writer1(new std::ofstream(fmame), fcloser1(fmame));
	auto writer2 = writer1;
	//"писатели":
	//Создать writer1, writer2

	//заданное число итераций случайным образом позволяем одному из "писателей" записать в файл
	//свою строчку
	
	for (size_t i = 0; i < 10; i++)
	{
		if (rand() > RAND_MAX / 2) 
			  *writer2 << i<<" writer2\n";
		else  *writer1 << i<<" writer1\n";
	}



	__asm nop
	}//закрытие файла???

	
	/***************************************************************/
	//Задание 3.
	{
		std::cout << "----------\n";
		//Дан массив элементов типа string
		std::string strings[] = { "abc", "123", "qwerty", "#$%","aaa","345","!!!"};
		//До завершения фрагмента строки должны существовать в единственном экземпляре.
		//Требуется обеспечить манипулирование строками 
		// а) без копирования и 
		// б) без изменения порядка
		//элементов в массиве!
		auto no_delete = [](std::string* a) {};

		/*std::shared_ptr<std::string[]> ss (strings, no_delete);	*/ //так не пойдет
				
		std::vector< std::shared_ptr<std::string> > v_sptr;

		for (size_t i = 0; i < std::size(strings); i++)
			v_sptr.emplace_back(& strings[i], no_delete);
		
		//В std::set "складываем" по алфавиту обертки для строк, которые содержат только буквы 

		auto s_lesser = [](const std::shared_ptr<std::string>& a,
			               const std::shared_ptr<std::string>& b) 
							{return *a < *b; };

		std::set<std::shared_ptr<std::string>,decltype(s_lesser)>set_s(s_lesser);

		for (auto it = v_sptr.cbegin(); it!=v_sptr.cend() ; ++it)
			if (only_letter(**it))
				set_s.insert(*it);
		
		__asm nop
		/******************************************************************************************/

		//В std::vector "складываем" обертки для строк, которые содержат только цифры 
		//Выводим на экран
		//Находим сумму
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
		//сюда "складываем" обертки для строк, которые не содержат ни символов букв, 
		// ни символов цифр
		//и просто выводим

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
	//Задание 4. 
	{
		auto no_delete = [](std::string* a) {};
		//Дано:
		std::string ar[] = { "my","Hello", "World" };
		std::vector < std::shared_ptr<std::string>> 
			v = { std::make_shared<std::string>("good"), std::make_shared<std::string>("bye") };

		for (size_t i = 0; i < std::size(ar); i++)
			v.emplace_back(&ar[i], no_delete);

		//а) Требуется добавить в вектор обертки для элементов массива, 
		// НЕ копируя элементы массива! 
		//б) Отсортировать вектор по алфавиту и вывести на экран
		//в) Обеспечить корректное освобождение памяти

		auto greater_sptr = [](const std::shared_ptr<std::string>& a,
								const std::shared_ptr<std::string>& b)
									{return *a < *b; };																	// если без учета регистра +std::transform(str.begin(), str.end(), str.begin(), ::toupper);

		std::sort(v.begin(), v.end(), greater_sptr);

		for (const std::shared_ptr<std::string>& st : v)
			std::cout << *st << " ; ";

		
		std::cout << "\n\n";
		__asm nop
	}
	/***************************************************************/
		//Задание 5. shared_ptr и weak_ptr
		//Создаем генеалогическое дерево посредством класса human. В классе хранятся:
		//имя - string
		//возможно признак: жив или уже нет...
		//родители - shared_ptr (родители не всегда известны...)
		//дети - контейнер из weak_ptr (чтобы избежать циклических зависимостей)

		//Методы класса human:
		//конструктор - для инициализации имени и признака
		//конструктор копирования, оператор присваивания, move ???
		//статический метод child() - 
		//				должен создать создать и вернуть обертку для родившегося человека
		//				+ сформировать все связи ребенка с родителями и наоборот

		//Ввести возможность распечатать генеалогическое дерево для указанного индивидума

	{
		//История должна с кого-то начинаться => "Жили-были дед да баба, например, Адам и Ева"
		//(то есть на самом деле два деда и две бабы):
#define sptr_h std::shared_ptr<human>

	sptr_h g_dad1 (new human("Adam",human::sex::male,true)) ;//Жили-были дед
	sptr_h g_mom1(new human{ "Eva",human::sex::female,true });//да баба

	sptr_h g_dad2(new human{ "Lucifer",human::sex::male,true });//на самом деле два деда
	sptr_h g_mom2(new human{ "Lilit",human::sex::female,true });//и две бабы

	sptr_h ded_br=(human::child("Kain", human::sex::male, g_mom1, g_dad1));//родили они 2х сыновей
	sptr_h dad=(human::child("Avel", human::sex::male, g_mom1, g_dad1));

	sptr_h mom_s=(human::child("Kesa", human::sex::female,g_mom2, g_dad2));//родили они 2х дочерей
	sptr_h mom=( human::child("Lilim", human::sex::female, g_mom2, g_dad2));

	(*g_dad1).is_dead();
	(*dad).is_dead();

	sptr_h doth = (human::child("Masha", human::sex::female, mom, dad)); // и внучку

	(*doth).print_g();
	
		//std::shared_ptr<human> grandM1(new human("Eva"));
		//...

		//у них появились дети - child():


		//а у детей в свою очередь свои дети:


		//...
		__asm nop
	}





	__asm nop
	return 0;
}
