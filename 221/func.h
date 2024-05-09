#pragma once
#include <initializer_list>
#include <string>
#include<ostream>
#include <algorithm>


using namespace std;





//--------------------------------------------
template<typename T>
void  PrintAnyCont(const T& l) 
{
	for (decltype(*cbegin(l)) e : l)
		std::cout << e << " ; ";

	std::cout << "\n";
}
//   -------------------------- 2 варианта оба используютс€
template<typename T>
void  PrintAnyCont2(const T& l)
{
	copy(cbegin(l), cend(l), ostream_iterator<decltype(*begin(l) + *begin(l))>(cout, " ; "));
	std::cout << "\n";
}

//--------------------------------------------
//std::string operator-(const std::string& s1); - тогда делаем копию в функции

std::string operator-(/*const std::string& */ std::string s); // а так копи€ делаетс€ при передаче значени€
//--------------------------------------------
template<typename T>
void NegateAll(T& l) {
	for (decltype(*begin(l)) e : l) 
		e = -e;
}
//--------------------------------------------
template<typename T>
void absSort(T& l) {
	sort(begin(l), end(l), [](auto a, auto b) {return abs(a) <  abs(b); });
	//sort(begin(l), end(l), [](decltype(*begin(l)) a, decltype(*begin(l)) b) {return abs(a) < abs(b); });
}
//--------------------------------------------
template<typename T, typename T2>
auto SumCont(const T& l1, const T2& l2) {
	size_t n = size(l1) > size(l2) ? size(l1) : size(l2);

	vector<decltype(*begin(l1) + *begin(l2))> res(n);
	copy(cbegin(l1), cend(l1), res.begin());
	transform(cbegin(l2), cend(l2), res.begin(), res.begin(), [](auto a, auto b) {return b + a; });

	return res;

}
template<typename T, typename T2, typename T3,typename P>
void Separate(const T& l1, T2& l2, T3& l3,P pred) {
	for (const auto& elem : l1)
	{
		if (pred(elem)) 
			l2.insert(end(l2),elem);
		else 
			l3.insert(end(l3),elem);
	};
}



enum class Col2{ red, green, blue, magenta, yellow, white };

template<typename T>
map<string, T> m1;

template<> 
map<string,Col2> m1<Col2> = 
{
	{"red", Col2::red},
	{ "green",Col2::green },
	{ "blue",Col2::blue },
	{ "magenta",Col2::magenta },
	{ "yellow",Col2::yellow },
	{ "white",Col2::white } 
};
template<typename T>
const T stringToEnum(const string& s) {
	const auto it = m1<T>.find(s);
	if (it == m1<T>.end()) throw string("not found " + s);

	return (*it).second;
}
template<typename T>
const string enumToString(const T& l) {

	const auto it = find_if(cbegin(m1<T>), cend(m1<T>), [&l](const auto& test)
		{return (test.second == l) ? true : false;	});
	return (it == cend(m1<T>))? "unknown color":(*it).first;


}

