#pragma once
#include <ostream>

class Counter
{
	static Counter* m_pHead;
	static unsigned int m_curCounters;

	char* m_pStr;
	unsigned int m_nOwners;
	Counter* pNext;

	Counter() :m_pStr(0), m_nOwners(0), pNext(0) {};

	friend class MyString;
	Counter* add_member(const char* s); // можно и static. как лучше?
	void kill();
	//~Counter() { int i=0; };
	static void ord();
};

class MyString
{
	Counter* m_pMyCounter;
public:
	MyString() :m_pMyCounter(0) {};
	explicit MyString(const char* s);
	MyString(const MyString& s) { 
		m_pMyCounter = s.m_pMyCounter; 
		if (m_pMyCounter)m_pMyCounter->m_nOwners++;
	};
	MyString(MyString&& s) noexcept;
	~MyString();
	
	//MyString& operator=(MyString& s);
	//MyString& operator=(MyString&& s);
	const char* GS()const { if (m_pMyCounter)return m_pMyCounter->m_pStr; else return""; };
	const char* GetString()const { if (m_pMyCounter)return m_pMyCounter->m_pStr; else return""; };
	const char firstChar() const { return m_pMyCounter->m_pStr[0]; };

	static Counter* GP() { return Counter::m_pHead; };
	static unsigned int GCc() { return Counter::m_curCounters; };
	unsigned int GC() { return m_pMyCounter->m_nOwners; };
	friend std::ostream& operator<<(std::ostream& os, const MyString& s);
	static void print();
	MyString& operator= (const MyString& s);
	MyString& operator= (const char* s);
	static void changeCase();
	static void printAlph();

};
