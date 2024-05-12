#define _CRT_SECURE_NO_WARNINGS
#pragma once

#include <string>
#include "myString.h"
#include <cstdarg>
//using namespace std;
const char* MyString::err = "EMPTY STRING- nullptr string";
// Определение конструктора.
MyString::MyString() {
    m_pStr = new char[1];
    m_pStr[0] = '\0';
};

MyString::MyString(const char* inc) {
    m_pStr = new char[strlen(inc) + 1];
    strcpy(m_pStr, inc);

};

MyString::MyString(const MyString& scopy) {
    if (scopy.m_pStr && strlen(scopy.m_pStr)) {
        //if (!m_pStr) delete[]m_pStr;
        m_pStr = new char[strlen(scopy.m_pStr) + 1];
        strcpy(m_pStr, scopy.m_pStr);
    }
    else {
        m_pStr = new char[1];
        m_pStr[0] = '\0';
    };
};

// Определение деструктора.
MyString::~MyString() {
    delete[] m_pStr;
    m_pStr = nullptr;
};

const char* MyString::GetString() const {
    if (this==nullptr) 
        return MyString::err;
    return m_pStr;
};

void MyString::SetNewString(const char* newstr) {
    if (newstr && strlen(newstr)) {
        if (strlen(newstr) <= strlen(m_pStr)) {
            strcpy(m_pStr, newstr);
        }
        else {
            delete[] m_pStr;
            m_pStr = new char[strlen(newstr) + 1];
            strcpy(m_pStr, newstr);
        }

    }
    else {
        delete[] m_pStr;
        m_pStr = 0;
    }

}
void MyString::AddStr(const char* newstr)
{
    if (strlen(newstr))

    {
        char* tmp = new char[strlen(newstr) + strlen(m_pStr) + 1];
        char* pp = m_pStr;
        int ii = 0;
        while (*pp) { tmp[ii] = m_pStr[ii]; ii++; pp++; };
        int jj = 0;
        pp = const_cast <char*>(newstr);
        while (*pp) { tmp[ii] = newstr[jj]; ii++; jj++; pp++; };
        tmp[ii] = 0;
        delete[] m_pStr;
        m_pStr = tmp;
    }
}
void UniStr(MyString& dist, int c, MyString* a, ...)
{

    MyString** p = &a;
    for (int i = 0; i < c; i++)
    {

        dist.AddStr((*p)->GetString());
        p += 1;//sizeof(MyString);
    }
}
