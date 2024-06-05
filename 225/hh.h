#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <istream>
#include <fstream>



class fcloser1 {
private:
	std::string fname;
public:
	fcloser1(const std::string& fn) :fname(fn) {}
	void operator() (std::ofstream* deleting) { 
		deleting->close();
		//std::remove(fname.c_str());
		delete deleting;
	}

};

bool only_letter(const std::string& st);// объ€вление функций выборки из стринга
bool only_digit(const std::string& st);
bool no_let_no_digit(const std::string& st);

class human {  // класс человек
	std::string name;
	bool alive;
public: enum class sex{male,female};
private:
	sex h_sex;
	std::shared_ptr<human> mother{};
	std::shared_ptr<human> father{}; 
	std::vector<std::weak_ptr<human>> children{};
public:
    human(const std::string& in_name, sex in_sex, bool in_alive,
		const std::shared_ptr<human>& in_mother,// конструктор детей
		const std::shared_ptr<human>& in_father) :
		name(in_name), 
		h_sex(in_sex), 
		alive (in_alive),
		mother(in_mother), 
		father(in_father) {};

	human(const std::string& in_name,sex in_sex,bool in_alive) ://основной конструктор
		name{ in_name }, h_sex{ in_sex }, alive{ in_alive } {};

	human(human&& h_in) noexcept:name(std::move(h_in.name)),//можно ли так?
		h_sex(h_in.h_sex),			// перемещающий конструктор
		alive(h_in.alive)
	{
		mother.swap(h_in.mother);// или нужно так? или вообще дефолт
		father.swap(h_in.father);
		children.swap(h_in.children);
	};

	human(const human&) =default; // конструктор копировани€

	static std::shared_ptr<human> child //создание реебенка
	  (const std::string& name,
		  sex in_sex, 
		  const std::shared_ptr<human>& mom, 
		  const std::shared_ptr<human>& dad);

	void is_dead() { alive = false; };// умер

	void print_h(const size_t& level = 0);
	void print_g(const size_t& level = 0);

};