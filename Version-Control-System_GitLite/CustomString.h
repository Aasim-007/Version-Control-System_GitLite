#pragma once
#include <iostream>
using namespace std;

class CustomString
{

    char* data = NULL;
    int size = 0;

public:

    CustomString();

    CustomString(int s);

    CustomString(const string s);

    CustomString(char s);

    CustomString(CustomString& str);

    void setSize(int s);

    void setString(const string s);

    void setString(CustomString s);

    void setString(char* s);

    void setString(char s);

    char CustomGetAt(int s);

    void CustomSetAt(int s, char c);

    char* get_String();

    int getSize();

    void print();

    bool operator == (CustomString s);

    bool operator == (string s);

    bool operator != (CustomString s);

    bool operator != (string s);

    void operator = (string s);

    void operator = (CustomString s);

    void operator = (char* s);

    bool operator > (CustomString s);

    bool operator < (CustomString s);

    bool operator <= (CustomString s);

    bool operator >= (CustomString s);

    CustomString operator+(const char& str);

    CustomString operator+(const char* str);

    const char operator[](int i) const;

    void clear();

    friend fstream& operator<<(fstream& output, CustomString& str);

    ~CustomString();

    void changetoComa();
};

//Few fstream and istream OverLoading -------------------------------
istream& operator>>(istream& input, CustomString& s);

fstream& operator<<(fstream& output, CustomString& str);

fstream& operator>>(fstream& input, CustomString& str);
//-------------------------------------------------------------------

//Few Custom String Concatination Functions -------------------------
void concatenate(CustomString& s1, CustomString s2);

void concatenate_flip(CustomString s1, CustomString& s2);

void concatenate(CustomString& s1, const string s);

void concatenate(string s, CustomString& s1);

void concatenate(CustomString& s1, char s);
//-------------------------------------------------------------------

CustomString Num2Str(int n);

int Str2Num(CustomString n);