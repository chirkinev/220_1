#pragma once

class MyString
{
	char* m_pStr;	//строка-член класса
	static const char* err;
public:
	MyString();
	/*explicit*/ MyString(const char*);
	MyString(const MyString&);
	MyString(MyString&& in)noexcept {
		m_pStr = in.m_pStr;
		in.m_pStr = 0; /*new char[1];
		in.m_pStr[0] = '\0';*/
	};
	~MyString();
	const char* GetString() const;
	void SetNewString(const char*);
	void AddStr(const char*);
	MyString& operator=(const MyString& in);
	MyString& operator=(MyString&& in)noexcept;
	friend std::ostream& operator<<(std::ostream& os, const MyString& s);

};
void UniStr(MyString&, int, MyString*, ...);

