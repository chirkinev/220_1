#define _CRT_SECURE_NO_WARNINGS
#include "MyString.h"
#include <string.h>
#include <iostream>

Counter* Counter::m_pHead = 0;
unsigned int Counter::m_curCounters = 0;

MyString::MyString(const char* s)
{
	m_pMyCounter = m_pMyCounter->add_member(s);
}

Counter* Counter::add_member(const char* s)
{
	Counter* p = m_pHead;
	Counter* pred = 0;
	bool s_nf = true;
	while (p)
	{
		if (!static_cast<bool>(strcmp(s, p->m_pStr)))
		{
			//this->m_pStr = p->m_pStr;
			p->m_nOwners++;
			return p;
		};
		pred = p;
		p = p->pNext;
	}
	Counter* tmp = new Counter;
	//tmp.m_pStr = 0;
	tmp->m_pStr = new char[strlen(s) + 1];
	strcpy(tmp->m_pStr, s);
	tmp->m_nOwners = 1;
	//m_pStr = tmp->m_pStr ;
	m_curCounters++;
	if (pred) pred->pNext = tmp;
	if (!static_cast<bool>(m_pHead)) m_pHead = tmp;
	tmp->pNext = 0;
	return tmp;
}

void Counter::kill()
{
	m_nOwners--;
	if (m_nOwners) return;

	delete[] m_pStr;
	Counter* p = m_pHead;
	Counter* pred = 0;
	while (p != this)
	{
		pred = p;
		p = p->pNext;
	};
	if (pred) pred->pNext = p->pNext;
	else m_pHead = p->pNext;
	m_curCounters--;
	delete this;
}





MyString::~MyString()
{
	if (m_pMyCounter) m_pMyCounter->kill();
	m_pMyCounter = 0;
}

void MyString::print()
{
	std::cout << "\n all sfrings:\n";
	Counter* tmp = MyString::GP();
	for (unsigned int i = 0; i < MyString::GCc(); i++)
	{
		std::cout << "srting N " << (i + 1) << "   " << tmp->m_pStr << " count " << tmp->m_nOwners << "\n";
		tmp = tmp->pNext;
	}
}


std::ostream& operator<<(std::ostream& os, const MyString& s)
{
	if(s.m_pMyCounter)
	os << s.GS();
	return os;
}

MyString::MyString(MyString&& s) noexcept
{
	m_pMyCounter = s.m_pMyCounter;
	s.m_pMyCounter = 0;
}

MyString& MyString::operator= (const MyString& s)
{
	if (m_pMyCounter)m_pMyCounter->kill();
	if (s.m_pMyCounter) {
		m_pMyCounter = s.m_pMyCounter;
		m_pMyCounter->m_nOwners++;
	}
	return *this;
}

MyString& MyString::operator= (const char* s)
{
	if (m_pMyCounter)m_pMyCounter->kill();
	if (s)m_pMyCounter = m_pMyCounter->add_member(s);
	return *this;
}

void MyString::printAlph()
{
	Counter::ord();
	print();
}

void MyString::changeCase()
{
	Counter* tmp = MyString::GP();
	for (unsigned int i = 0; i < MyString::GCc(); i++)
	{
		for (size_t j = 0; j < strlen(tmp->m_pStr); j++)
			tmp->m_pStr[j] = static_cast<char>(toupper(static_cast<int>(tmp->m_pStr[j])));
		tmp = tmp->pNext;
	}
}

void Counter::ord()
{
	/*static Counter* m_pHead;
	static unsigned int m_curCounters;

	char* m_pStr;
	unsigned int m_nOwners;
	Counter* pNext;*/
	int cc = 0;
	do
	{
		cc = 0;
		Counter* p = m_pHead;
		Counter* pred = 0;
		for (unsigned int i = 0; i < (m_curCounters - 1); i++)
		{

			if (strcmp(p->m_pStr, p->pNext->m_pStr) > 0)
			{
				if (pred)pred->pNext = p->pNext;
				else m_pHead = p->pNext;
				pred = p->pNext;
				Counter* tmp = p->pNext->pNext;
				p->pNext->pNext = p;
				p->pNext = tmp;
				cc++;
			}
			else
			{
				pred = p;
				p = p->pNext;
			}
		}
	} while (cc);
}

