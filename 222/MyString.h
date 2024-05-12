#pragma once

class MyString
{
	char* m_pStr;	//строка-член класса
	static const char* err;
public:
	MyString();
	explicit MyString(const char*);
	MyString(const MyString&);
	~MyString();
	const char* GetString() const;
	void SetNewString(const char*);
	void AddStr(const char*);
};
void UniStr(MyString&, int, MyString*, ...);

