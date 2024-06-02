#include "hh.h"

//

bool only_letter(std::string st)
{
	for (char a : st)
		if (!((a >= 'a' && a <= 'z') || 
			  (a >= 'A' && a <= 'Z')))
		return false;

	return true;
}
bool only_digit(std::string st)
{
	for (char a : st)
		if (!(a >= '0' && a <= '9'))
			return false;
	return true;
}

bool no_let_no_digit(std::string st)
{
	for (char a : st)
		if ((a >= 'a' && a <= 'z') || 
			(a >= 'A' && a <= 'Z')||
			(a >= '0' && a <= '9'))
		return false;

	return true;
}

std::shared_ptr<human> human::child(
	const std::string& in_name, 
	sex in_sex, 
	const std::shared_ptr<human>& mom,
	const std::shared_ptr<human>& dad)
{
	std::shared_ptr<human> tmp=std::make_shared<human>(in_name, in_sex, true,mom,dad);
	if ((*mom).h_sex == sex::female) (*mom).children.emplace_back(tmp);
	if ((*dad).h_sex == sex::male) (*dad).children.emplace_back(tmp);
	return tmp;
}

void human::print_h() {
	if (h_sex == sex::male) std::cout << "Man ";
	else std::cout << "Woman ";
	std::cout << "\"" << name << "\", ";
	if (alive)std::cout << "alive \n";
	else std::cout << "dead \n";

}

void human::print_g()
{

	this->print_h();
	std::cout << "--------------\n";

	if (children.size() == 0)std::cout << "no children\n";
	else {
		std::cout << this->name << "`s children:\n";
		for (std::weak_ptr<human>& ch : children) {
			auto chh = ch.lock();
			chh->print_h();
		}
	};
	std::cout << "--------------\n";
	if ((this->mother) == nullptr)std::cout << this->name << "`s mother unnown\n";
	else {
		std::cout << this->name << "`s mother:\n";
		mother->print_g();
	};
	std::cout << "--------------\n";
	if ((this->father) == nullptr)std::cout << this->name << "`s father unnown\n";
	else {
		std::cout << this->name << "`s father:\n";
		father->print_g();
	};
}

