#include <string>
//#include "func.h"
////#include <string>
//

 std::string operator-(/*const std::string& s1*/ std::string s) 
{
	//std::string s(s1);
	for (char& ch : s)
		ch = islower(ch)? toupper(ch):tolower(ch);
	return s;
};


